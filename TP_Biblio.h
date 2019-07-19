#ifndef TP1_BIBLIO_H_INCLUDED
#define TP1_BIBLIO_H_INCLUDED

#define Long_Nom 10
#define Min_Chaine 4
#define Max_Chaine 10

#define NB_ETAB_OUEST 28
#define NB_ETAB_EST 35
#define NB_ETAB_CENTRE 42
#define MAX_ETAB 105
#define NB_WILAYAS 48
#define NB_GSANGUINS 8
#define NB_GRADES 6
#define NB_DIPLOMES 5
#define MAX_NB_PROFS 50000
#define MAX_NB_ENRG 1000
#define NB_SPECIALITE 10
#define ANNEE_ACTUELLE 2018


///************************************************** STRUCTURES **************************************************************

typedef struct Etablissement{
    char Nom_Etab[256];
    int Region;         /// 0 : Ouest ; 1 : Centre ; 2 : Est
}Etablissement;

typedef struct Prof             /* Structure des enregistrements dans le fichier */
{
    int Matricule ;
    char Nom[Long_Nom];
    char Prenom[Long_Nom];
    struct tm Date_Naissance;
    char Wilaya[30];
    char Groupe_Sanguin[3] ;
    struct tm Date_Recrutement;
    char Grade[30] ;
    char Specialite[30] ;
    char Diplome[25] ;
    char Sexe[6] ;
    Etablissement Etab;
}Prof;

typedef struct Tbloc                            /* Type "Bloc" : On définit chaque bloc par un tableau d'enregistrements "PROF"*/
{                                               /* Ainsi que le nombre d'entregistrements contenus dans le bloc (Utile à l'insertion) */
  Prof tab[MAX_NB_ENRG]  ;
  int nb ;
}Tbloc ;

typedef struct Entete
{
 int adrDerBloc;
 int nombre_profs;
}Entete;

typedef struct TObF
{
 FILE *fichier;
 Entete entete;
} TObF;

/// ***************************** ELEMENTS DES INDEX
typedef struct cle
{
    int matricule ;
    int num_bloc ;                                      /*Certains champs de notre index principal sont organisés sous forme de liste en représentation statique (Liste dans un tableau)*/
    int adr_dans_bloc ;                                 /*Cela permet un gain en espace important. Plusieurs autres champs supplémentaires sont utilisés pour faciliter la manipulation*/
    int num_spec ;
    int num_etab ;
    int anciennete;
    signed int suiv_selon_etab;
    signed int suiv_selon_spec ;
    signed int suiv_selon_reg ;
    int supprime ; /// 1 = supprimée | 0 = non-supprimée
}cle ;

///*************************************** TABLEAUX INDEX
        ///INDEX PRINCIPAL
typedef struct Index_Matricule
{
    cle tab[MAX_NB_PROFS] ;
    int niveau_remplissage ;            //Pour faciliter la recherche dichotomique et ne pas donner MAX_NB_PROFS en parametre
}Index_Matricule ;

        ///INDEX SECONDAIRES
typedef struct Index_Etablissement
{
  signed int tab[MAX_ETAB] ;            ///Les index secondaires contiennent l'indice du matricule représentant la tête de liste dans l'index principal
}Index_Etablissement ;

typedef struct Index_Specialite
{
  signed int tab[NB_SPECIALITE] ;
}Index_Specialite ;

typedef struct Index_Region
{
  signed int tab[3] ;
}Index_Region ;

/// ================================================================== PROTOTYPES DES FONCTIONS LOGICIELLES

int  Genere_Nombre(int a,int b);
void Genere_Chaine_Alphabetique(char Chaine[]);
void Genere_Date(struct tm *date, int Min_Annee, int Max_Annee);

void Genere_Wilaya(char Wilaya[], char Tab_Wilaya[NB_WILAYAS][30]);
void Genere_Groupe_Sanguin(char Groupe[], char Tab_Sanguin[NB_GSANGUINS][5]);
void Genere_Grade(char Grade[], char Tab_Grades[NB_GRADES][30]);
void Genere_Diplome(char Diplome[], char Tab_Diplomes[NB_DIPLOMES][25]);
int  Genere_Etablissement(Etablissement *Etab,Etablissement Table_Etab[])  ;
void Genere_Tab_Etablissement(Etablissement Tab_Etab[]) ;
void Genere_Sexe(char Sexe[]) ;
int  Genere_Specialite(char Specialite[],char Tab_specialite[7][30]) ;
void Genere_Prof(Prof* Nouveau_Prf, int *num_spec, int *num_etab, Etablissement tab_etab[]);
int  rechercheDicho(cle tab[], int nbVal, int val);
int  inserer(int element_a_inserer, cle tab[], int taille);


int ouvrir(TObF **f,char *chemin, char mode);
void fermer(TObF *f);
void lireDir(TObF *f,int N_Bloc,Tbloc *buffer);
void ecrireDir(TObF *f,int N_Bloc,Tbloc *buffer);
int entete(TObF *f,int i);
void aff_entete(TObF *f, int i, int val);

void creation_Fichier_Index(TObF* *Fichier_Profs, Etablissement tab_etab[], Index_Etablissement* Index_etab , Index_Matricule* Index_matr , Index_Region* Index_reg , Index_Specialite* Index_spec);
int Ajouter_Prof(TObF* *Fichier_Profs, int num_etab, int num_spec, Prof Infos_Prof, Index_Etablissement* Index_etab , Index_Matricule* Index_matr , Index_Region* Index_reg , Index_Specialite* Index_spec);
int Mutation_Prof(TObF* *Fichier_Profs, int matricule, int num_netab, Index_Matricule* Ind_Mat, Etablissement Tab_Etab[]);
void Sup_Prof(TObF* *Fichier_Profs, int matricule, Index_Matricule* Ind_Mat,int pos);
int Sup_Selon_Spec(TObF* *Fichier_Profs, int nspec, Index_Matricule* Index_matr, Index_Specialite* Index_spec);
int Requete_Intervalle(TObF* *Fichier_Profs, int Exp_Min, int Exp_Max, int numetab, Index_Matricule *Ind_Mat, Index_Etablissement *Ind_Etb);
int consulter_profs_region(TObF* *Fichier_Profs, int nreg, Index_Matricule* Index_matr, Index_Region* Index_reg,Etablissement tab_etab[], int nbprofs);

void Init_Indexs(Index_Etablissement *Index_Etab ,Index_Matricule *Index_Matr,Index_Region *Index_Reg,Index_Specialite *Index_Spec);
void creer_index_specialite(Index_Matricule* Index_matr, Index_Specialite* Index_spec);
void Ecrire_Index_Spec(Index_Specialite *Index_spec);
void Ecrire_Index_Mat(Index_Matricule *Ind_Mat);
void creer_index_etab(Index_Matricule* Index_matr, Index_Etablissement* Ind_etb);
void Ecrire_Index_Etab(Index_Etablissement *Index_Etb);
void creer_index_region(Index_Matricule* Index_matr , Index_Region* Index_reg,Etablissement tab_etab[]);
void Ecrire_Index_reg(Index_Region *Ind_reg);

///============================================================================ PARTIE GRAPHIQUE
int getkey(void);
void aff_btn(char txt[],int bordercolr,int bkgrndcolr,int highlight);
void Information_programme();
void pied_page();
void clear_screen_Accueil(void);
void clear_screen(int nb_profs, int nb_blocs, int nbdoub);
void printfslow(char ch[],int temps);
int scanstr_num(int *nombre);
int confirmation(char *msgfr);
int quitter(TObF* *f,Index_Matricule *Ind_Mat,Index_Specialite *Index_spec,Index_Etablissement *Index_Etb,Index_Region *Ind_reg);// confirmation pour quitter le programme
int quitter_a();
void afficher_prof(TObF* *Fichier,Index_Matricule *Index_matr,int indice);
void Affich_Prof(int matricule, int ligne, int colonne);

int ACCUEIL();
void menu_principal(int *choix1, int nb_profs, int l, int profs_actuels);
void login_menu(int *choix1);

///================================ QUELQUES VARIABLES GRAPHIQUES GLOBALES ========================================
typedef char* tabstr ; //tableau de chaine de caractere
enum //les code numerique des touches du clavier
{
    ESC =27,
    ARROW_UP =328,
    ARROW_DOWN =336,
    ARROW_LEFT =331,
    ARROW_RIGHT =333,
    F1 =315,
    CTRL_L =12,
    ENTRER =13,
    ALPHA_a =97,
    ALPHA_z =122,
    ALPHA_A =65,
    ALPHA_Z =90,
    KEY_0 =48,
    KEY_9 =57,
    BACK_SPACE=8,
    SPACE_BAR=32

};

#endif // TP1_BIBLIO_H_INCLUDED
