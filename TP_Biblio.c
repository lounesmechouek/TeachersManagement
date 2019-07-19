#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TP_Biblio.h"
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include "conio21/conio2.h"
#define Tmp 10
#define CR 0x0D

///=============================================================================================================================================================///
///                             BIENVENUE, CECI EST LA BIBLIOTHEQUE DE TOUTES LES FONCTIONS/PROCEDURES LOGICIELLES ET GRAPHIQUES DU TP.                         ///
///=============================================================================================================================================================///




/// ***************************************************** PROCEDURES *********************************************************************


                                ///            I/ PROCEDURES DE GENERATION ALEATOIRE            ///
///======================================================================================================///
/// Genere_Nombre :GENERE UN NOMBRE ENTIER APPARTENANT A [a,b[                                           ///
///======================================================================================================///

int Genere_Nombre(int a,int b)
{
    return rand()%(b-a) +a;
}

///==========================================================================================================///
/// Genere_Chaine : PREND EN ENTREE Long_Ch ET GENERE UNE CHAINE DE CETTE LONGUEUR (Caractères alphabétiques)///
///==========================================================================================================///

void Genere_Chaine_Alphabetique(char Chaine[])
{
    int i=0, Long_Ch=Genere_Nombre(Min_Chaine,Max_Chaine);

    for(i=0;i<Long_Ch;i++)
        Chaine[i]=Genere_Nombre(1,27)+96;

    Chaine[i]='\0';
    Chaine[0]-=32;  //Pour mettre en majuscule le premier caractère
}
///==========================================================================================================///
/// Genere_Wilaya : GENERE UN NOMBRE ALEATOIRE ET LUI ASSOCIE UNE WILAYA DU TABLEAU                          ///
///==========================================================================================================///
void Genere_Wilaya(char Wilaya[], char Tab_Wilaya[48][30])
{
    int nbraleat=Genere_Nombre(0,47);
    strcpy(Wilaya,Tab_Wilaya[nbraleat]);

}
///==========================================================================================================///
/// Genere_Date : RENVOIE UNE DATE DE NAISSANCE DANS UNE STRUCT TM                                           ///
///==========================================================================================================///
void Genere_Date(struct tm *date, int Min_Annee, int Max_Annee)
{
    int bissextile=0, Annee, Mois, Jour;

    Annee=Genere_Nombre(Min_Annee,Max_Annee+1);

    if(! (Annee % 4))
        bissextile=1;

    Mois=Genere_Nombre(1,13);

    if(Mois <= 7)
    {
        if(!(Mois % 2))
            Jour=Genere_Nombre(1,32);

        else
        {
            if (Mois != 2)
                Jour = Genere_Nombre(1,31);

            else
            {
                if(bissextile)
                    Jour = Genere_Nombre(1,30);
                else
                    Jour = Genere_Nombre(1,29);
            }


        }
    }

    else
    {
        if(Mois % 2)
            Jour = Genere_Nombre(1,32);

        else
            Jour = Genere_Nombre(1,31);
    }

    (*date).tm_year=Annee;
    (*date).tm_mon=Mois;
    (*date).tm_mday=Jour;



}
///==========================================================================================================///
/// Genere_Groupe_Sanguin : GENERE UN NOMBRE ALEATOIRE ET LUI ASSOCIE UN DES GROUPES SANGUINS DU TABLEAU     ///
///==========================================================================================================///
void Genere_Groupe_Sanguin(char Groupe[], char Tab_Sanguin[8][5])
{
    int Nb_Alea=Genere_Nombre(0,8);

    strcpy(Groupe,Tab_Sanguin[Nb_Alea]);

}
///==========================================================================================================///
/// Genere_Grade : GENERE UN NOMBRE ALEATOIRE ET LUI ASSOCIE UN DES GRADES DU TABLEAU                        ///
///==========================================================================================================///
void Genere_Grade(char Grade[], char Tab_Grades[6][30])
{
    int Nbalea=Genere_Nombre(0,6);

    strcpy(Grade,Tab_Grades[Nbalea]);
}
///==========================================================================================================///
/// Genere_Diplome : GENERE UN NOMBRE ALEATOIRE ET LUI ASSOCIE UN DES Diplomes DU TABLEAU                    ///
///==========================================================================================================///
void Genere_Diplome(char Diplome[], char Tab_Diplomes[5][25])
{
    int nbralea=Genere_Nombre(0,5);
    strcpy(Diplome,Tab_Diplomes[nbralea]);
}
///==========================================================================================================///
/// Genere_Sexe : 0 Pour Homme, 1 Pour Femme                                                                 ///
///==========================================================================================================///
void Genere_Sexe(char Sexe[])
{
    int sx = Genere_Nombre(0,2) ;
    if (sx == 0) strcpy(Sexe,"Homme");
    else strcpy(Sexe,"Femme") ;

}
///==========================================================================================================///
/// Genere_Spécialité : GENERE UN NOMBRE ALEATOIRE ET LUI ASSOCIE UNE SPECIALITE DU TABLEAU.                 ///
///==========================================================================================================///
int Genere_Specialite(char Specialite[],char Tab_specialite[7][30])
{
    int nbaleatr = Genere_Nombre(0,7) ;
    strcpy(Specialite,Tab_specialite[nbaleatr]);
    return nbaleatr ;
}
///==========================================================================================================///
/// Genere_Etablissement : GENERE LE TABLEAU CONTENANT LES COUPLES (ETABLISSEMENT,REGION)                    ///
///==========================================================================================================///
void Genere_Tab_Etablissement(Etablissement Tab_Etab[])
{
    FILE *FAC=fopen("Etablissements.txt","r");
    int i=0;
    char Nom_Fac[256];

        while(!feof(FAC))
        {
            fgets(Nom_Fac,256,FAC);
            strcpy(Tab_Etab[i].Nom_Etab,Nom_Fac);
            if(i<NB_ETAB_OUEST)
                Tab_Etab[i].Region=0;

            else{
                if(i<NB_ETAB_EST+NB_ETAB_OUEST)                        /*Les établissement sont triés dans le fichier "Etablissements.txt*/
                    Tab_Etab[i].Region=1;                               /*Toute modification du fichier doit prendre en compte les variables globales utilisées dans cette procédure*/

                else{
                    if(i<NB_ETAB_CENTRE+NB_ETAB_EST+NB_ETAB_OUEST)
                        Tab_Etab[i].Region=2;}
            }
            i++;
        }
        fclose(FAC);
}
///==========================================================================================================///
/// Genere_Etablissement : GENERE UN NOMBRE ALEATOIRE ET LUI ASSOCIE UN COUPLE (Etab,Region) DU TABLEAU      ///
///==========================================================================================================///
int Genere_Etablissement(Etablissement *Etab,Etablissement Table_Etab[])
{
        int nbaleatr=Genere_Nombre(0,MAX_ETAB-1);
        strcpy(Etab->Nom_Etab,Table_Etab[nbaleatr].Nom_Etab);
        Etab->Region=Table_Etab[nbaleatr].Region;
        return nbaleatr;
}
///==========================================================================================================///
/// Genere_Prof : GENERE UN ENREGISTREMENT COMPLET CONTENANT TOUTES LES INFORMATIONS RELATIVES AU PROF       ///
///==========================================================================================================///
void Genere_Prof(Prof* Nouveau_Prf, int *num_spec, int *num_etab, Etablissement tab_etab[])
{
    char
                Tab_Sanguin[8][5]= {"O+\0", "A+\0", "B+\0", "O-\0", "A-\0", "AB+\0", "B-\0", "AB-\0"},
                Tab_Grades[6][30] = {"Professeur(e)\0", "Maitre de conferences Rang A\0", "Maitre de conferences Rang B\0",
                                "Maitre assistant(e) Rang A\0", "Maitre assistant(e) Rang B\0", "Assistant(e)\0"},
                Tab_Diplomes[5][25] = { "Doctorat d'Etat\0", "Doctorat en Sciences\0", "PhD\0", "HDR\0", "Magistere\0"},
                Tab_Wilaya[48][30] = { "Adrar\0", "Chlef\0", "Laghouat\0", "Oum El Bouaghi\0", "Batna\0", "Bejaia\0", "Biskra\0", "Bechar\0",
                                "Blida\0", "Bouira\0", "Tamanrasset\0", "Tebessa\0", "Tlemcen\0", "Tiaret\0", "Tizi Ouzou\0", "Alger\0",
                                "Djelfa\0", "Jijel\0", "Setif\0", "Saida\0", "Skikda\0", "Sidi Bel Abbes\0", "Annaba\0", "Guelma\0",
                                "Constantine\0", "Medea\0", "Mostaganem\0", "M'Sila\0", "Mascara\0", "Ouargla\0", "Oran\0", "El Bayadh\0",
                                "Illizi\0", "Bordj Bou Arreridj\0", "Boumerdes\0", "El Tarf\0", "Tindouf\0", "Tissemsilt\0", "El Oued\0",
                                "Khenchela\0","Souk Ahras\0", "Tipaza\0", "Mila\0", "Ain Defla\0", "Naama\0", "Ain Temouchent\0", "Ghardaia\0", "Relizane\0"},
                Tab_Specialite[11][30] = {"Informatique\0", "Architecture\0", "Electronique\0", "Mathematiques\0", "Economie\0", "Anglais\0", "Physique\0","Medecine\0","Mecanique\0","Geologie\0","Biologie\0"};

     (Nouveau_Prf->Matricule) = Genere_Nombre(11111,100000);
     Genere_Chaine_Alphabetique(Nouveau_Prf->Nom);
     Genere_Chaine_Alphabetique(Nouveau_Prf->Prenom);
     Genere_Wilaya(Nouveau_Prf->Wilaya, Tab_Wilaya);
     Genere_Date(&(Nouveau_Prf->Date_Naissance), 1958, 1992);
     Genere_Sexe(Nouveau_Prf->Sexe);
     Genere_Groupe_Sanguin(Nouveau_Prf->Groupe_Sanguin, Tab_Sanguin);
     Genere_Date(&(Nouveau_Prf->Date_Recrutement),1979,2018);
     Genere_Grade(Nouveau_Prf->Grade, Tab_Grades);
     (*num_spec) = Genere_Specialite(Nouveau_Prf->Specialite,Tab_Specialite) ;
     (*num_etab) = Genere_Etablissement(&(Nouveau_Prf->Etab),tab_etab);
     Genere_Diplome(Nouveau_Prf->Diplome,Tab_Diplomes);

     printf("NOM : %s | PRENOM : %s | MATRICULE : %d | NUM ETAB : %d |\n",Nouveau_Prf->Nom,Nouveau_Prf->Prenom,Nouveau_Prf->Matricule, (*num_etab));
}
///============================================================================================================///
/// EFFECTUE UNE RECHERCHE DICHOTOMIQUE. (UTILISEE DANS L'INDEX PRINCIPAL DES MATRICULES)                      ///
///============================================================================================================///
int rechercheDicho(cle tab[], int nbVal, int val) /*Renvoie -1 si val n'est pas dans le tableau*/
{

  int trouve=0 ;  //vaut faux tant que la valeur "val" n'aura pas été trouvée
  int id=0;      //indice de début
  int ifin=nbVal;   //indice de fin
  int im;    //indice de milieu

  /* boucle de recherche */
  while((trouve == 0) && ((ifin - id) > 1)){

    im = (id + ifin)/2;  //on détermine l'indice de milieu
    if((tab[im].matricule == val) && (tab[im].supprime == 0))
    {trouve = 1 ;}  //on regarde si la valeur recherchée est à cet indice

    if(tab[im].matricule > val) ifin = im;  //si la valeur qui est à la case "im" est supérieure à la valeur recherchée, l'indice de fin "ifin" << devient >> l'indice de milieu, ainsi l'intervalle de recherche est restreint lors du prochain tour de boucle
    else id = im;  //sinon l'indice de début << devient >> l'indice de milieu et l'intervalle est de la même façon restreint
  }

  /* test conditionnant la valeur que la fonction va renvoyer */
  if((tab[id].matricule == val) && (tab[id].supprime == 0)) return(id);  //si on a trouvé la bonne valeur, on retourne l'indice
  else return(-1);  //sinon on retourne -1

}
///========================================================================================================///
/// Module d'insertion dans l'ordre croissant d'une valeur donnée dans un tableau                          ///
///========================================================================================================///
int inserer(int element_a_inserer, cle tab[], int taille_gauche)
{
    int j= 0;
    for (j = taille_gauche; j > 0 && tab[j-1].matricule > element_a_inserer; j--)
      //{tab[j] = tab[j-1];}
     {
      tab[j].adr_dans_bloc = tab[j-1].adr_dans_bloc ;
      tab[j].matricule = tab[j-1].matricule ;
      tab[j].num_bloc = tab[j-1].num_bloc ;
      tab[j].suiv_selon_etab = tab[j-1].suiv_selon_etab ;
      tab[j].suiv_selon_reg = tab[j-1].suiv_selon_reg ;
      tab[j].suiv_selon_spec = tab[j-1].suiv_selon_spec ;
      tab[j].supprime = tab[j-1].supprime ;
      tab[j].num_etab = tab[j-1].num_etab ;
      tab[j].num_spec = tab[j-1].num_spec ;
      tab[j].anciennete=tab[j-1].anciennete;
     }
   // tab[j] = element_a_inserer;
   return j ;
}



///********************************************************* MACHINE ABSTRAITE ***************************************************

///==========================================================================================================///
/// Fonction d'ouverture d'un fichier                                                                        ///
///==========================================================================================================///
int ouvrir(TObF **f,char *chemin, char mode)
{
    *f = malloc(sizeof(TObF));
    char s[3];

    if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
    else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
    else return 0;

    (*f)->fichier = fopen(chemin, s);

    if((*f)->fichier == NULL)
    {
       gotoxy(30,23);
       textcolor(RED) ;
       printf("Ouuups! Une erreur s%cest produite a l%couverture du fichier !\n",39,39);
       textcolor(BLUE);
       delay(1000);
        return 0;
    }


    if((mode == 'A') || (mode == 'a'))
    {
        fread(&((*f)->entete), sizeof(Entete), 1, (*f)->fichier);
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        (*f)->entete.adrDerBloc = 0;
    }
    return 1;
}


///==========================================================================================================///
/// Fonction de fermeture d'un fichier                                                                       ///
///==========================================================================================================///
void fermer(TObF *f)
{
    //Sauvegarde de l'entête
    rewind(f->fichier);
    fwrite(&(f->entete), sizeof(Entete), 1, f->fichier);
    fclose(f->fichier);
    free(f);
}

///==========================================================================================================///
/// Fonction de lecture d'un bloc                                                                            ///
///==========================================================================================================///
void lireDir(TObF *f,int N_Bloc,Tbloc *buffer)
{
    if(N_Bloc <= (f->entete).adrDerBloc)
    {
        fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);
        fread(buffer, 1, sizeof(Tbloc), f->fichier);
    }
}

///==========================================================================================================///
/// Fonction d'écriture d'un bloc                                                                            ///
///==========================================================================================================///
void ecrireDir(TObF *f,int N_Bloc,Tbloc *buffer)
{
    if(N_Bloc <= (f->entete).adrDerBloc)
    {
        fseek(f->fichier, sizeof(Entete) + (N_Bloc-1) * sizeof(Tbloc),SEEK_SET);
        fwrite(buffer, 1, sizeof(Tbloc), f->fichier);
    }
}
///==========================================================================================================///
/// Fonction de lecture de l'entête (lorsque i=1 ====> lecture de l'adresse du dernier bloc)                 ///
///==========================================================================================================///
int entete(TObF *f,int i)
{
    if(i == 1) return (f->entete).adrDerBloc;
    else return -1;
}

///==========================================================================================================///
/// Fonction de modification de l'entête                                                                     ///
/// lorsque i=1 ====> modification de l'adresse du dernier bloc                                              ///
///==========================================================================================================///
void aff_entete(TObF *f, int i, int val)
{
    if(i == 1) (f->entete).adrDerBloc = val;
}

///==========================================================================================================///
/// L'allocation d'un bloc                                                                                   ///
///==========================================================================================================///
int alloc_bloc(TObF *f)
{
    aff_entete(f,1,entete(f,1)+1);
    return entete(f,1);
}



///********************************************************* PROCEDURES RELATIVES AU TP ***************************************************
///==========================================================================================================///
/// PROCEDURE QUI INITIALISE LES INDEXS                                                                      ///
///==========================================================================================================///
void Init_Indexs(Index_Etablissement *Index_Etab ,Index_Matricule *Index_Matr,Index_Region *Index_Reg,Index_Specialite *Index_Spec)
{
    int i=0;
        /// Initialisations Index
     Index_Matr->niveau_remplissage = 0;

     for(i=0 ; i<= MAX_ETAB ; i++)
         Index_Etab->tab[i] = -1 ;

     for(i=0 ; i<= NB_SPECIALITE ; i++)
         Index_Spec->tab[i] = -1 ;

     for(i=0 ; i<= 3 ; i++)
         Index_Reg->tab[i] = -1 ;
}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE LA CREATION DE L'INDEX DES REGIONS                                             ///
///==========================================================================================================///
void creer_index_region(Index_Matricule* Index_matr , Index_Region* Index_reg,Etablissement tab_etab[])
{
    int    i = Index_matr->niveau_remplissage ;
    int  j ,tempo , num_etab;
    int k ;
    for(k=0 ; k<= 3 ; k++)
         Index_reg->tab[k] = -1 ;
    for (j = 0 ; j < i; j++)
    {
           num_etab = Index_matr->tab[j].num_etab ;
           tempo = Index_reg->tab[tab_etab[num_etab].Region] ;
           Index_reg->tab[tab_etab[num_etab].Region] = j ;
           Index_matr->tab[j].suiv_selon_reg = tempo ;
    }
    Index_matr->tab[j-1].suiv_selon_reg = -1 ;

}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE L'ECRITURE DE L'INDEX DES REGIONS                                          ///
///==========================================================================================================///
void Ecrire_Index_reg(Index_Region *Ind_reg)
{

    FILE *F=fopen("Table_Regions.bin","wb+");
           fwrite(Ind_reg,1,sizeof(Index_Region),F);

    fclose(F);
}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE LA CREATION DE L'INDEX DES SPECIALITES                                              ///
///==========================================================================================================///
void creer_index_specialite(Index_Matricule* Index_matr, Index_Specialite* Index_spec)
{
    int i = Index_matr->niveau_remplissage, j, tempo, num_spec ;
    int k ;
     for(k=0 ; k<= NB_SPECIALITE ; k++)
         Index_spec->tab[k] = -1 ;
    for (j = 0 ; j < i; j++)
    {
        num_spec = Index_matr->tab[j].num_spec ;
        tempo = Index_spec->tab[num_spec] ;
        Index_spec->tab[num_spec] = j ;
        Index_matr->tab[j].suiv_selon_spec = tempo ;
    }

    Index_matr->tab[j-1].suiv_selon_spec=-1;
}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE LA CREATION DE L'INDEX DES ETABLISSEMENTS                                           ///
///==========================================================================================================///
void creer_index_etab(Index_Matricule* Index_matr, Index_Etablissement* Ind_etb)
{
    int i = Index_matr->niveau_remplissage, j, tempo, num_etab ;
    int k ;
    for(k=0 ; k<= MAX_ETAB ; k++)
         Ind_etb->tab[k] = -1 ;
    for (j = 0 ; j < i; j++)
    {
        num_etab = Index_matr->tab[j].num_etab ;
        tempo = Ind_etb->tab[num_etab] ;
        Ind_etb->tab[num_etab] = j ;
        Index_matr->tab[j].suiv_selon_etab = tempo ;
    }

    Index_matr->tab[j-1].suiv_selon_etab=-1;

}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE L'ECRITURE DE L'INDEX DES SPECIALITES EN MS                                         ///
///==========================================================================================================///
void Ecrire_Index_Spec(Index_Specialite *Index_spec)
{
     FILE *F=fopen("Table_Specialites.bin","wb+");
           fwrite(Index_spec,1,sizeof(Index_Specialite),F);

    fclose(F);
}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE L'ECRITURE DE L'INDEX DES ETABLISSEMENTS EN MS                                      ///
///==========================================================================================================///
void Ecrire_Index_Etab(Index_Etablissement *Index_Etb)
{
     FILE *F=fopen("Table_Etablissements.bin","wb+");
           fwrite(Index_Etb,1,sizeof(Index_Etablissement),F);

    fclose(F);
}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE L'ECRITURE DE L'INDEX DES MATRICULES EN MS                                          ///
///==========================================================================================================///
void Ecrire_Index_Mat(Index_Matricule *Ind_Mat)
{

    FILE *F=fopen("Table_Matricules.bin","wb+");
           fwrite(Ind_Mat,1,sizeof(Index_Matricule),F);

    fclose(F);
}
///==========================================================================================================///
/// PROCEDURE QUI ASSURE :                                                                                   ///
///         1. LA CREATION DU FICHIER EN LE REMPLISSANT DE DONNEES GENEREES ALEATOIREMENT                    ///
///         2. LA CREATION ET L'ECRITURE DE LA TABLE D'INDEX PRIMAIRE EN MEMOIRE SECONDAIRE                  ///
///         3. L'EPURATION (SUPPRESSION DES DOUBLONS QUI EST FAITE EN MEME TEMPS QUE LA CREATION)            ///
///==========================================================================================================///
void creation_Fichier_Index(TObF* *Fichier_Profs, Etablissement tab_etab[], Index_Etablissement* Index_etab , Index_Matricule* Index_matr , Index_Region* Index_reg , Index_Specialite* Index_spec)
{
    ///************************************** INITIALISATIONS ET CHARGEMENTS
    int nbprofs=0, parcours=0, i=0, num_bloc=1;
    int matricule, position, booleen=0 ;
    char
                Tab_Sanguin[8][5]= {"O+\0", "A+\0", "B+\0", "O-\0", "A-\0", "AB+\0", "B-\0", "AB-\0"},
                Tab_Grades[6][30] = {"Professeur(e)\0", "Maitre de conferences Rang A\0", "Maitre de conferences Rang B\0",
                                "Maitre assistant(e) Rang A\0", "Maitre assistant(e) Rang B\0", "Assistant(e)\0"},
                Tab_Diplomes[5][25] = { "Doctorat d Etat\0", "Doctorat en Sciences\0", "PhD\0", "HDR\0", "Magistere\0"},
                Tab_Wilaya[48][30] = { "Adrar\0", "Chlef\0", "Laghouat\0", "Oum El Bouaghi\0", "Batna\0", "Bejaia\0", "Biskra\0", "Bechar\0",
                                "Blida\0", "Bouira\0", "Tamanrasset\0", "Tebessa\0", "Tlemcen\0", "Tiaret\0", "Tizi Ouzou\0", "Alger\0",
                                "Djelfa\0", "Jijel\0", "Setif\0", "Saida\0", "Skikda\0", "Sidi Bel Abbes\0", "Annaba\0", "Guelma\0",
                                "Constantine\0", "Medea\0", "Mostaganem\0", "M'Sila\0", "Mascara\0", "Ouargla\0", "Oran\0", "El Bayadh\0",
                                "Illizi\0", "Bordj Bou Arreridj\0", "Boumerdes\0", "El Tarf\0", "Tindouf\0", "Tissemsilt\0", "El Oued\0",
                                "Khenchela\0","Souk Ahras\0", "Tipaza\0", "Mila\0", "Ain Defla\0", "Naama\0", "Ain Temouchent\0", "Ghardaia\0", "Relizane\0"},
                Tab_Specialite[11][30] = {"Informatique\0", "Architecture\0", "Electronique\0", "Mathematiques\0", "Economie\0", "Anglais\0", "Physique\0","Medecine\0","Mecanique\0","Geologie\0","Biologie\0"};



    while(booleen == 0)
    {
        gotoxy(30,22);
        printf("Veuillez mentionner le nombre total de profs : (MAX : %d)  ",MAX_NB_PROFS);
        scanstr_num(&nbprofs);

        if((nbprofs <= MAX_NB_PROFS) && (nbprofs >= 1))
            booleen=1;
        else{
            gotoxy(30,25); printf("Le matricule est erron%c, veuillez r%cessayer",130,130); delay(1000);
            clear_screen_Accueil();}
    }

    (*Fichier_Profs)->entete.nombre_profs=nbprofs;

    ///**************************************  GENERATION, REMPLISSAGE DU FICHIER, CONSTRUCTION DE L'INDEX :
    Tbloc* Buffer = malloc(sizeof(Tbloc));

    while (parcours<nbprofs)
    {
        if  (i == MAX_NB_ENRG)
        {
            Buffer->nb = i-1 ;
            (**Fichier_Profs).entete.adrDerBloc++ ;
            ecrireDir(*Fichier_Profs,num_bloc,Buffer);
            num_bloc++ ;
            i = 0 ;
        }
        else
        {
            matricule =  Genere_Nombre(11111,99999);
            if (rechercheDicho(Index_matr->tab,Index_matr->niveau_remplissage,matricule) == -1 )
                {
                Buffer->tab[i].Matricule= matricule ;

                /// mise du matricule dans la table d'index avec ses coordonnées dans la bonne position----------:
                position = inserer(matricule,Index_matr->tab,Index_matr->niveau_remplissage) ;
                Index_matr->tab[position].matricule= matricule ;
                Index_matr->tab[position].adr_dans_bloc = i ;
                Index_matr->tab[position].num_bloc = num_bloc ;
                Index_matr->tab[position].supprime = 0 ;
                Index_matr->tab[position].suiv_selon_etab = -1 ;
                Index_matr->tab[position].suiv_selon_reg = -1 ;
                Index_matr->tab[position].suiv_selon_spec = -1 ;
                Index_matr->niveau_remplissage++ ;
                ///---------------
                Genere_Chaine_Alphabetique(Buffer->tab[i].Nom);
                Genere_Chaine_Alphabetique(Buffer->tab[i].Prenom);
                Genere_Wilaya(Buffer->tab[i].Wilaya, Tab_Wilaya);
                Genere_Date(&(Buffer->tab[i].Date_Naissance), 1958, 1993);
                Genere_Sexe(Buffer->tab[i].Sexe);
                Genere_Groupe_Sanguin(Buffer->tab[i].Groupe_Sanguin, Tab_Sanguin);
                Genere_Date(&(Buffer->tab[i].Date_Recrutement),1979,ANNEE_ACTUELLE);    //Ancienneté minimale : 1 année
                Index_matr->tab[position].anciennete=(ANNEE_ACTUELLE+1)-(Buffer->tab[i].Date_Recrutement.tm_year);
                Genere_Grade(Buffer->tab[i].Grade, Tab_Grades);
                Index_matr->tab[position].num_spec = Genere_Specialite(Buffer->tab[i].Specialite,Tab_Specialite) ;
                Index_matr->tab[position].num_etab = Genere_Etablissement(&(Buffer->tab[i].Etab),tab_etab);
                Genere_Diplome(Buffer->tab[i].Diplome,Tab_Diplomes);
            ///---------------
                i++;
                }
                parcours++ ;
        }
    }

    (**Fichier_Profs).entete.adrDerBloc = num_bloc ;            //ECRITURE DU DERNIER BLOC EN MS
    Buffer->nb = i-1 ;
    ecrireDir(*Fichier_Profs,num_bloc,Buffer);
    free(Buffer) ;

        Ecrire_Index_Mat(Index_matr);
    }
///===============================================================================================================///
/// PROCEDURE QUI PERMET D'INSERER UN NOUVEAU PROFESSEUR DANS LE FICHIER AINSI QUE DANS LA TABLE D'INDEX PRIMAIRE ///
/// ELLE RENVOIE LA POSITION OU A ETE INSERE LE PROF DANS LA TABLE D'INDEX PRIMAIRE                               ///
///===============================================================================================================///
int Ajouter_Prof(TObF* *Fichier_Profs, int num_etab, int num_spec, Prof Infos_Prof, Index_Etablissement* Index_etab , Index_Matricule* Index_matr , Index_Region* Index_reg , Index_Specialite* Index_spec)
{
        ///******************************** INSERTION DANS LE FICHIER

        Tbloc *Buffer=malloc(sizeof(Tbloc));

        /* Determination de l'état du fichier : Vide/Non Vide */
        if(((**Fichier_Profs).entete.adrDerBloc)==0)          ///SI LE FICHIER EST VIDE, on crée le premier bloc (qui est aussi le dernier)
        {
            (**Fichier_Profs).entete.adrDerBloc=1;
            aff_entete(*Fichier_Profs,1,1);
            Buffer->nb=0;
        }


        else
            lireDir((*Fichier_Profs), (**Fichier_Profs).entete.adrDerBloc, Buffer); ///Sinon, on lit le dernier bloc où l'on fera l'insertion


        /* Copie des infos dans le buffer puis écriture à la fin du fichier */
        if(Buffer->nb < MAX_NB_ENRG)            ///Cas 1 : Le dernier bloc n'est pas plein
        {
            Buffer->nb++;

            Buffer->tab[Buffer->nb].Matricule=Infos_Prof.Matricule;
            strcpy(Buffer->tab[Buffer->nb].Nom,Infos_Prof.Nom);
            strcpy(Buffer->tab[Buffer->nb].Prenom,Infos_Prof.Prenom);

            Buffer->tab[Buffer->nb].Date_Naissance.tm_mday=Infos_Prof.Date_Naissance.tm_mday;
            Buffer->tab[Buffer->nb].Date_Naissance.tm_year=Infos_Prof.Date_Naissance.tm_year;
            Buffer->tab[Buffer->nb].Date_Naissance.tm_mon=Infos_Prof.Date_Naissance.tm_mon;
            Buffer->tab[Buffer->nb].Date_Recrutement.tm_mday=Infos_Prof.Date_Recrutement.tm_mday;
            Buffer->tab[Buffer->nb].Date_Recrutement.tm_year=Infos_Prof.Date_Recrutement.tm_year;
            Buffer->tab[Buffer->nb].Date_Recrutement.tm_mon=Infos_Prof.Date_Recrutement.tm_mon;

            strcpy(Buffer->tab[Buffer->nb].Wilaya,Infos_Prof.Wilaya);
            strcpy(Buffer->tab[Buffer->nb].Prenom,Infos_Prof.Prenom);
            strcpy(Buffer->tab[Buffer->nb].Groupe_Sanguin,Infos_Prof.Groupe_Sanguin);
            strcpy(Buffer->tab[Buffer->nb].Grade,Infos_Prof.Grade);
            strcpy(Buffer->tab[Buffer->nb].Specialite,Infos_Prof.Specialite);
            strcpy(Buffer->tab[Buffer->nb].Diplome,Infos_Prof.Diplome);
            strcpy(Buffer->tab[Buffer->nb].Sexe,Infos_Prof.Sexe);
            strcpy(Buffer->tab[Buffer->nb].Etab.Nom_Etab,Infos_Prof.Etab.Nom_Etab);
            Buffer->tab[Buffer->nb].Etab.Region=Infos_Prof.Etab.Region;

            ecrireDir(*Fichier_Profs,(**Fichier_Profs).entete.adrDerBloc, Buffer);
        }

        else        ///Cas 2 : Le dernier bloc est plein, on alloue un bloc
        {
            Buffer->nb=0;

            Buffer->tab[Buffer->nb].Matricule=Infos_Prof.Matricule;
            strcpy(Buffer->tab[Buffer->nb].Nom,Infos_Prof.Nom);
            strcpy(Buffer->tab[Buffer->nb].Prenom,Infos_Prof.Prenom);

            Buffer->tab[Buffer->nb].Date_Naissance.tm_mday=Infos_Prof.Date_Naissance.tm_mday;
            Buffer->tab[Buffer->nb].Date_Naissance.tm_year=Infos_Prof.Date_Naissance.tm_year;
            Buffer->tab[Buffer->nb].Date_Naissance.tm_mon=Infos_Prof.Date_Naissance.tm_mon;
            Buffer->tab[Buffer->nb].Date_Recrutement.tm_mday=Infos_Prof.Date_Recrutement.tm_mday;
            Buffer->tab[Buffer->nb].Date_Recrutement.tm_year=Infos_Prof.Date_Recrutement.tm_year;
            Buffer->tab[Buffer->nb].Date_Recrutement.tm_mon=Infos_Prof.Date_Recrutement.tm_mon;

            strcpy(Buffer->tab[Buffer->nb].Wilaya,Infos_Prof.Wilaya);
            strcpy(Buffer->tab[Buffer->nb].Prenom,Infos_Prof.Prenom);
            strcpy(Buffer->tab[Buffer->nb].Groupe_Sanguin,Infos_Prof.Groupe_Sanguin);
            strcpy(Buffer->tab[Buffer->nb].Grade,Infos_Prof.Grade);
            strcpy(Buffer->tab[Buffer->nb].Specialite,Infos_Prof.Specialite);
            strcpy(Buffer->tab[Buffer->nb].Diplome,Infos_Prof.Diplome);
            strcpy(Buffer->tab[Buffer->nb].Sexe,Infos_Prof.Sexe);
            strcpy(Buffer->tab[Buffer->nb].Etab.Nom_Etab,Infos_Prof.Etab.Nom_Etab);
            Buffer->tab[Buffer->nb].Etab.Region=Infos_Prof.Etab.Region;

            aff_entete(*Fichier_Profs,1,(**Fichier_Profs).entete.adrDerBloc+1);
            ecrireDir(*Fichier_Profs,(**Fichier_Profs).entete.adrDerBloc+1, Buffer);

        }

        ///******************************* MODIFICATION TABLE D'INDEX PRIMAIRE
        int position = inserer(Infos_Prof.Matricule,Index_matr->tab,Index_matr->niveau_remplissage);
        Index_matr->tab[position].matricule=Infos_Prof.Matricule;
        Index_matr->tab[position].adr_dans_bloc=Buffer->nb;
        Index_matr->tab[position].num_bloc=(**Fichier_Profs).entete.adrDerBloc;
        Index_matr->tab[position].num_etab=num_etab;
        Index_matr->tab[position].num_spec=num_spec;
        Index_matr->tab[position].suiv_selon_etab=-1;
        Index_matr->tab[position].suiv_selon_reg=-1;
        Index_matr->tab[position].suiv_selon_spec=-1;
        Index_matr->tab[position].anciennete=((ANNEE_ACTUELLE+1)-(Buffer->tab[Buffer->nb].Date_Recrutement.tm_year));
        Index_matr->tab[position].supprime=0;
        Index_matr->niveau_remplissage++ ;

      //  Ecrire_Index_Mat(Index_matr);
      (*Fichier_Profs)->entete.nombre_profs++;

      gotoxy(13,6); printf("Un enregistrement a %ct%c g%cn%cr%c al%catoirement puis a bien %ct%c ins%cr%c", 130,130,130,130,130,130,130,130,130,130);

        free(Buffer);
        return position;
}
///===============================================================================================================///
/// PROCEDURE QUI PERMET DE MODIFIER L'ETAB D'UN PROF EN AYANT SON MATRICULE EN ENTREE                            ///
/// ELLE RENVOIE LA POSITION DANS L'INDEX PRIMAIRE DE CE PROF (POUR UN AFFICHAGE EVENTUEL)                        ///
///===============================================================================================================///
int Mutation_Prof(TObF* *Fichier_Profs, int matricule, int num_netab, Index_Matricule* Ind_Mat, Etablissement Tab_Etab[])
{
    int pos=rechercheDicho(Ind_Mat->tab,Ind_Mat->niveau_remplissage,matricule);
    int  reg=Tab_Etab[num_netab].Region;

       if(pos != -1)
       {
           Tbloc *Buffer=malloc(sizeof(Tbloc));
           Ind_Mat->tab[pos].num_etab=num_netab;

           strcpy(Buffer->tab[Ind_Mat->tab[pos].adr_dans_bloc].Etab.Nom_Etab, Tab_Etab[num_netab].Nom_Etab);
           Buffer->tab[Ind_Mat->tab[pos].adr_dans_bloc].Etab.Region=reg;


           ecrireDir(*Fichier_Profs,Ind_Mat->tab[pos].num_bloc,Buffer);
        //   Ecrire_Index_Mat(Ind_Mat);

           free(Buffer);

           return pos;
       }

       else
       {
            gotoxy(25,20);
            printf("Il se trouve que ce professeur n%cexiste pas. Veuillez refaire votre choix",39);
            return 0;
       }
}
///===============================================================================================================///
/// PERMET DE SUPPRIMER UN PROF DU FICHIER AINSI QUE DE LA TABLE INDEX DES MATRICULES                             ///
///===============================================================================================================///
void Sup_Prof(TObF* *Fichier_Profs, int matricule, Index_Matricule* Ind_Mat,int pos)
{
    if(pos != -1)
    {


        ///************************************ SUPPRESSION DU FICHIER

        int k ,Pos_Bloc=Ind_Mat->tab[pos].adr_dans_bloc, Num_Bloc=Ind_Mat->tab[pos].num_bloc, Nb_Blocs=entete(*Fichier_Profs,1);
        Tbloc *Buffer1=malloc(sizeof(Tbloc)), *Buffer2=malloc(sizeof(Tbloc)),*Buffer=malloc(sizeof(Tbloc));

        if(Num_Bloc!=Nb_Blocs) //L'enregistrement à supprimer n'est pas dans le dernier bloc
        {
            lireDir(*Fichier_Profs,Num_Bloc,Buffer1);
            lireDir(*Fichier_Profs,Nb_Blocs,Buffer2);

            Buffer1->tab[Pos_Bloc].Matricule=Buffer2->tab[Buffer2->nb].Matricule;
            /*** mise a jour des coordonnes du dernier prof dans la table d'index car il se peut qu'on essayera d'y acceder +tard **/
            k = rechercheDicho(Ind_Mat->tab,Ind_Mat->niveau_remplissage,Buffer1->tab[Pos_Bloc].Matricule);
            Ind_Mat->tab[k].adr_dans_bloc = Pos_Bloc ;
            Ind_Mat->tab[k].num_bloc = Num_Bloc ;
            ///-------------------------------------------------------------------------------
            strcpy(Buffer1->tab[Pos_Bloc].Diplome,Buffer2->tab[Buffer2->nb].Diplome);
            strcpy(Buffer1->tab[Pos_Bloc].Wilaya,Buffer2->tab[Buffer2->nb].Wilaya);
            strcpy(Buffer1->tab[Pos_Bloc].Grade,Buffer2->tab[Buffer2->nb].Grade);
            strcpy(Buffer1->tab[Pos_Bloc].Groupe_Sanguin,Buffer2->tab[Buffer2->nb].Groupe_Sanguin);
            strcpy(Buffer1->tab[Pos_Bloc].Sexe,Buffer2->tab[Buffer2->nb].Sexe);
            strcpy(Buffer1->tab[Pos_Bloc].Specialite,Buffer2->tab[Buffer2->nb].Specialite);
            strcpy(Buffer1->tab[Pos_Bloc].Nom,Buffer2->tab[Buffer2->nb].Nom);
            strcpy(Buffer1->tab[Pos_Bloc].Prenom,Buffer2->tab[Buffer2->nb].Prenom);
            strcpy(Buffer1->tab[Pos_Bloc].Etab.Nom_Etab,Buffer2->tab[Buffer2->nb].Etab.Nom_Etab);

            Buffer1->tab[Pos_Bloc].Etab.Region=Buffer2->tab[Buffer2->nb].Etab.Region;
            Buffer1->tab[Pos_Bloc].Date_Recrutement.tm_mday=Buffer2->tab[Buffer2->nb].Date_Recrutement.tm_mday;
            Buffer1->tab[Pos_Bloc].Date_Recrutement.tm_mon=Buffer2->tab[Buffer2->nb].Date_Recrutement.tm_mon;
            Buffer1->tab[Pos_Bloc].Date_Recrutement.tm_year=Buffer2->tab[Buffer2->nb].Date_Recrutement.tm_year;
            Buffer1->tab[Pos_Bloc].Date_Naissance.tm_mday=Buffer2->tab[Buffer2->nb].Date_Naissance.tm_mday;
            Buffer1->tab[Pos_Bloc].Date_Naissance.tm_mon=Buffer2->tab[Buffer2->nb].Date_Naissance.tm_mon;
            Buffer1->tab[Pos_Bloc].Date_Naissance.tm_year=Buffer2->tab[Buffer2->nb].Date_Naissance.tm_year;
            Buffer2->nb--;
            ecrireDir(*Fichier_Profs,Num_Bloc,Buffer1);

            if(Buffer2->nb>0) // buffer2 non vide
                ecrireDir(*Fichier_Profs,Nb_Blocs,Buffer2);
            else
                aff_entete(*Fichier_Profs,1,Nb_Blocs-1);
        }

        else    //L'enregistrement à supprimer est dans le dernier bloc
        {
            lireDir(*Fichier_Profs,Nb_Blocs,Buffer);

            Buffer->tab[Pos_Bloc].Matricule=Buffer->tab[Buffer->nb].Matricule;
              /*** mise a jour des coordonnes du dernier prof dans la table d'index car on pourrait y acceder apres **/
            k = rechercheDicho(Ind_Mat->tab,Ind_Mat->niveau_remplissage,Buffer->tab[Buffer->nb].Matricule);
            Ind_Mat->tab[k].adr_dans_bloc = Pos_Bloc ;
           /// Ind_Mat->tab[k].num_bloc = Num_Bloc ; on le met pas a jour car on est dans le meme bloc
            ///-------------------------------------------------------------------------------
            strcpy(Buffer->tab[Pos_Bloc].Diplome,Buffer->tab[Buffer->nb].Diplome);
            strcpy(Buffer->tab[Pos_Bloc].Wilaya,Buffer->tab[Buffer->nb].Wilaya);
            strcpy(Buffer->tab[Pos_Bloc].Grade,Buffer->tab[Buffer->nb].Grade);
            strcpy(Buffer->tab[Pos_Bloc].Groupe_Sanguin,Buffer->tab[Buffer->nb].Groupe_Sanguin);
            strcpy(Buffer->tab[Pos_Bloc].Sexe,Buffer->tab[Buffer->nb].Sexe);
            strcpy(Buffer->tab[Pos_Bloc].Specialite,Buffer->tab[Buffer->nb].Specialite);
            strcpy(Buffer->tab[Pos_Bloc].Nom,Buffer->tab[Buffer->nb].Nom);
            strcpy(Buffer->tab[Pos_Bloc].Prenom,Buffer->tab[Buffer->nb].Prenom);
            strcpy(Buffer->tab[Pos_Bloc].Etab.Nom_Etab,Buffer->tab[Buffer->nb].Etab.Nom_Etab);

            Buffer->tab[Pos_Bloc].Etab.Region=Buffer->tab[Buffer->nb].Etab.Region;
            Buffer->tab[Pos_Bloc].Date_Recrutement.tm_mday=Buffer->tab[Buffer->nb].Date_Recrutement.tm_mday;
            Buffer->tab[Pos_Bloc].Date_Recrutement.tm_mon=Buffer->tab[Buffer->nb].Date_Recrutement.tm_mon;
            Buffer->tab[Pos_Bloc].Date_Recrutement.tm_year=Buffer->tab[Buffer->nb].Date_Recrutement.tm_year;
            Buffer->tab[Pos_Bloc].Date_Naissance.tm_mday=Buffer->tab[Buffer->nb].Date_Naissance.tm_mday;
            Buffer->tab[Pos_Bloc].Date_Naissance.tm_mon=Buffer->tab[Buffer->nb].Date_Naissance.tm_mon;
            Buffer->tab[Pos_Bloc].Date_Naissance.tm_year=Buffer->tab[Buffer->nb].Date_Naissance.tm_year;

            Buffer->nb--;

            if(Buffer->nb>0)
                ecrireDir(*Fichier_Profs,Nb_Blocs,Buffer);
            else
                aff_entete(*Fichier_Profs,1,Nb_Blocs-1);
        }

        free(Buffer1); free(Buffer2); free(Buffer);

    (*Fichier_Profs)->entete.nombre_profs--;
    ///************************************ SUPPRESSION DANS L'INDEX PRINCIPAL
    Ind_Mat->tab[pos].supprime=1;

    ///Ind_Mat->niveau_remplissage--;  <-- on le decremente pas car on fait une supression logique ;
    ///L'écriture de l'index se fera dans le module appelant
    }


    else
        printf("Desole, le professeur a ete supprime ou n'existe pas. \n");
}

///===============================================================================================================///
/// PERMET DE SUPPRIMER UN PROF DU FICHIER AINSI QUE DE LA TABLE INDEX DES MATRICULES                             ///
///===============================================================================================================///
int Sup_Selon_Spec(TObF* *Fichier_Profs, int nspec, Index_Matricule* Index_matr, Index_Specialite* Index_spec)
{

   ///***************************** CREATION DE LLC STATIQUE DANS LA TABLE PRIMAIRE, DONT LES TETES SONT DANS L'INDEX DES SPECS
    creer_index_specialite(Index_matr,Index_spec);

    int suiv=Index_spec->tab[nspec], i ;

    if(Index_spec->tab[nspec] == -1)
    {
        gotoxy(20,20); printf("Il n%cexiste aucun professeur enseignant cette sp%cialite, r%cessayez !",39,130,130); delay(500); return 0;
    }

    else{
    while(suiv!=-1)
    {
        i = suiv ;

        if(Index_matr->tab[i].supprime != 1)
            Sup_Prof(Fichier_Profs,Index_matr->tab[i].matricule,Index_matr,i);


        suiv=Index_matr->tab[i].suiv_selon_spec;

    }
        Index_spec->tab[nspec]=-1;
        return 1;
    }

    printf("\nOK");


    /*Ecrire_Index_Mat(Index_matr);
    Ecrire_Index_Spec(Index_spec);*/
}
///===============================================================================================================///
/// AFFICHE TOUS LES ENSEIGNANTS D'UN ETAB AYANT UNE EXPERIENCE ENTRE Exp_Min et Exp_Min                          ///
///===============================================================================================================///
int Requete_Intervalle(TObF* *Fichier_Profs, int Exp_Min, int Exp_Max, int numetab, Index_Matricule *Ind_Mat, Index_Etablissement *Ind_Etb)
{
    creer_index_etab(Ind_Mat,Ind_Etb);
    int P=Ind_Etb->tab[numetab];
    int x = 5 ;
    int y = 1 ;
    clrscr();
    switchbackground(LIGHTGRAY);
    textcolor(BLUE) ;
    textbackground(LIGHTGRAY);
    if (P == -1)
    {
        gotoxy(29,28);
        printf("Aucun professeur dans cet etablissement n'a une exp%crience entre %d et %d ans\n",130,Exp_Min,Exp_Max);
    }
    while(P!=-1)
    {
        if((Ind_Mat->tab[P].supprime == 0) && (Ind_Mat->tab[P].anciennete <= Exp_Max) && (Ind_Mat->tab[P].anciennete >= Exp_Min))
        {
            gotoxy(x ,y );
            afficher_prof(Fichier_Profs,Ind_Mat,P);
            x = x + 32 ;
            if (x >= 100)
            {
              x = 5 ;
              y = y + 8 ;
            }
            if (y >= 32)
            {
                gotoxy(33,34);
               printf("ENTRER : continuer | ESC : retour  ...  ") ;
               if (getkey() == ESC ) return ESC;
                clrscr();
                y = 1 ;
                switchbackground(LIGHTGRAY);
                textcolor(BLUE) ;
                textbackground(LIGHTGRAY);
            }
        }
        P=Ind_Mat->tab[P].suiv_selon_etab;
    }
              /*  Ecrire_Index_Mat(Ind_Mat);
                Ecrire_Index_Etab(Ind_Etb);*/
                gotoxy(29,37);
                printf("Appuyez sur n%cimporte quelle touche pour continuer ...  ",39) ;
                getkey() ;

}
///===============================================================================================================///
/// AFFICHE TOUS LES ENSEIGNANTS EXERCANT DANS UNE REGION DONNEE                                                  ///
///===============================================================================================================///
int consulter_profs_region(TObF* *Fichier_Profs, int nreg, Index_Matricule* Index_matr, Index_Region* Index_reg,Etablissement tab_etab[], int nbprofs)
{

   ///***************************** CREATION DE LLC STATIQUE DANS LA TABLE PRIMAIRE, DONT LES TETES SONT DANS L'INDEX DES REG
      creer_index_region(Index_matr,Index_reg,tab_etab);
    int suiv=Index_reg->tab[nreg],i;
    int x = 5 ;
    int y = 1 ;
    clrscr();
    switchbackground(LIGHTGRAY);
    textcolor(BLUE) ;
    textbackground(LIGHTGRAY);
    pied_page();

        if(suiv ==-1)
        {
            gotoxy(29,28); printf("Il n%cy a pas de profs dans cette region !",39);
        }

        else{
            while(suiv != -1)
            {
                gotoxy(50,37); printf("Appuyez sur une touche pour defiler les informations");
                if( !(Index_matr->tab[suiv].supprime) )
                {
                    i=suiv;

                    gotoxy(x ,y );
                    afficher_prof(Fichier_Profs,Index_matr,i);
                    x = x + 32 ;
                    if (x >= 100)
                    {
                        x = 5 ;
                        y = y + 8 ;
                    }
                    if (y >= 32)
                    {
                        gotoxy(33,34);
                        if (getkey() == ESC ) return ESC;
                        clrscr();
                        y = 1 ;
                        switchbackground(LIGHTGRAY);
                        textcolor(BLUE) ;
                        textbackground(LIGHTGRAY);
                        pied_page();

                    }

                    if(getkey()==ESC)
                        return ESC;
                }

            suiv = Index_matr->tab[suiv].suiv_selon_reg;
            }
        }


    //Ecrire_Index_Mat(Index_matr);
   // Ecrire_Index_reg(Index_reg);
}

    ///============================================ PARTIE GRAPHIQUE ====================================================
///===============================================================================================================///
/// RECUPERE UN CARACTERE A PARTIR DU CLAVIER                                                                     ///
///===============================================================================================================///
int getkey(void)
{
    int ch;
    clearkeybuf();
    ch=getch();
    if (ch==0 || ch==224)
        ch=getch()+256;

    return ch;
}
///===============================================================================================================///
/// AFFICHE LE DESING DE TOUS LES BOUTONS DU PROGRAMME                                                            ///
///===============================================================================================================///
void aff_btn(char txt[],int bordercolr,int bkgrndcolr,int highlight)
{
    int i,n=strlen(txt),x,y;
    x=wherex();
    y=wherey();
    // normvideo();
    if (highlight==0)
    {
        textattr(9);
        textcolor(BLACK);
        textbackground(LIGHTGRAY);
        printf("%c",218);
        gotoxy(x+1+n,y);
        printf("%c",191);
        gotoxy(x,y+2);
        printf("%c",192);
        gotoxy(x+1+n,y+2);
        printf("%c",217);
        gotoxy(x,y+1);
        printf("%c",179);
        gotoxy(x+n+1,y+1);
        printf("%c",179);
        gotoxy(x+1,y);
        for (i=1; i<n+1; i++)
        {
            printf("%c",196);
        }
        gotoxy(x+1,y+2);
        for (i=1; i<n+1; i++)
        {
            printf("%c",196);
        }
        gotoxy(x+1,y+1);
        textcolor(BLUE);
        printf("%s",txt);

    }
    if (highlight==1)
    {
        // textbackground(bkgrndcolr);
        textcolor(bordercolr);
        textbackground(LIGHTGRAY);
        printf("%c",220);
        gotoxy(x+1+n,y);
        printf("%c",220);
        gotoxy(x,y+2);
        printf("%c",223);
        gotoxy(x+1+n,y+2);
        printf("%c",223);
        gotoxy(x,y+1);
        printf("%c",219);
        gotoxy(x+n+1,y+1);
        printf("%c",219);
        gotoxy(x+1,y);

        for (i=1; i<n+1; i++)
        {
            printf("%c",220);
        }
        gotoxy(x+1,y+2);
        for (i=1; i<n+1; i++)
        {
            printf("%c",223);
        }
        gotoxy(x+1,y+1);
        textcolor(BLUE);
        textbackground(bkgrndcolr);
        printf("%s",txt);
    }
    textbackground(0);

    gotoxy(1,y+3);
}
///===============================================================================================================///
/// AFFICHAGE DE LA PAGE INFORMATION SUR LE TP                                                                    ///
///===============================================================================================================///
void Information_programme()
{
    clear_screen_Accueil() ;

    gotoxy(2,20);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

     gotoxy(2,21);
     printf("%c Bienvenue. Tout d%cabord ce programme a %ct%c r%calis%c dans un but purement p%cdagogique par des           %c",186,39,130,130,130,130,130,186);
     gotoxy(2,22);
     printf("%c %ctudiants de l%cESI. Son but est de simuler la gestion d%cune base de donn%ces de professeurs sur        %c",186,130,39,39,130,186);
     gotoxy(2,23);
     printf("%c le territoire national en s%cappuyant sur une structure de fichiers vue comme T non Ordonn%c avec       %c",186,39,130,186);
     gotoxy(2,24);
     printf("%c des enregistrements de taille fixe. Ce projet reste am%cliorable, il ne se veut en aucun cas parfait.  %c",186,130,186);
     gotoxy(2,25);
     printf("%c Merci de votre compr%chension et bonne utilisation !                                                   %c",186,130,186);

   gotoxy(2,26);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

     pied_page() ;

    while(getkey() != ESC)
        gotoxy(110,40);


}
///===============================================================================================================///
/// CREE L'ENVIRONNEMENT DES PAGES ANTERIEURE A LA CREATION DU FICHIER (ENTETE STATIQUE)                          ///
///===============================================================================================================///
void clear_screen_Accueil(void)
{
    clrscr();
    switchbackground(LIGHTGRAY) ;
    textbackground(LIGHTGRAY);


    int i=0, j=0;
    textcolor(BLACK);
        for(j=1;j<=10;j++)
        {
            for(i=2;i<=109;i++)
            {
                gotoxy(i,j);

                if(i==2 || i==109) printf("%c", 219);
                else {
                   if(j==1 || j==10) printf("%c",220);
                   }

            }
        }

    gotoxy(2,1); printf(" ");
    gotoxy(109,1); printf(" ");
    textcolor(BLUE);

    gotoxy(8,3); printf("REALISATION : MECHOUEK LOUNES | BEN MESSAOUD M. ISSAM DAOUD | G04");
    gotoxy(29,6); printf("ECOLE NATIONALE SUPERIEURE D'INFORMATIQUE (ESI)");
    gotoxy(29,7); printf("TP SFSD | ORGANISATION DES ENSEIGNANTS AU NIVEAU NATIONAL");
    gotoxy(65,9); printf("ENCADREUR : DR. A.KERMI | 2CP4 - 2018/2019");
}
///===============================================================================================================///
/// AFFICHE LE PIED DE PAGE (RETOUR/QUITTER)                                                                      ///
///===============================================================================================================///
void pied_page()// affiche un pied de page (les touche retour et changer de langue)
{
    textbackground(LIGHTGRAY);
    int xi,yi,x=1,y=36;
    xi=wherex();
    yi=wherey();
    gotoxy(1,37);
    textcolor(BLACK);
    gotoxy(x,y+3);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,217);
    gotoxy(x,y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,191);
    gotoxy(x,y+2);
    printf("%c            %c",179,179);
    gotoxy(x,y+1);
    printf("%c            %c",179,179);
     textcolor(BLUE);

        gotoxy(x+1,y+1);
        printf("   Retour");
        gotoxy(x+1,y+2);
        printf("   (Echap)");

    gotoxy(xi,yi);
}
///===============================================================================================================///
/// AFFICHE L'ENVIRONNEMENT POSTERIEUR A LA CREATION DU FICHIER (ENTETE DYNAMIQUE)                                ///
///===============================================================================================================///
void clear_screen(int nb_profs, int nb_blocs, int nbdoub)
{
    clrscr();
    switchbackground(LIGHTGRAY) ;
    textbackground(LIGHTGRAY);


    int i=0, j=0;
    textcolor(BLACK);
        for(j=1;j<=8;j++)
        {
            for(i=2;i<=109;i++)
            {
                gotoxy(i,j);

                if(i==2 || i==109) printf("%c", 219);
                else {
                   if(j==1 || j==8) printf("%c",220);
                   }

            }
        }

    gotoxy(2,1); printf(" ");
    gotoxy(109,1); printf(" ");
    textcolor(BLUE);

    gotoxy(30,2); printf("ECOLE NATIONALE SUPERIEURE D%cINFORMATIQUE (ESI)",39);
    gotoxy(24,3); printf("MINISTERE DE L%cENSEIGNEMANT SUPERIEUR ET DE LA RECHERCHE SCIENTIFIQUE",39);
    gotoxy(4,5); printf("STATISTIQUES SUR LE FICHIER : ");
    gotoxy(6,6); printf("%c NB PROFS INITIAL : %d | NOMBRE DE DOUBLONS : %d ",254,nb_profs,nbdoub);
    gotoxy(6,7); printf("%c NOMBRE DE BLOCS : %d | NOMBRE PROFS ACTUELS : %d ",254,nb_blocs, (nb_profs-nbdoub));
    gotoxy(110,40);
}
///===============================================================================================================///
/// ECRIT A L'ECRAN DU TEXTE AU RALENTI                                                                           ///
///===============================================================================================================///
void printfslow(char ch[],int temps)
{
    int i;
    for (i=0 ; i < strlen(ch); i++)
    {
        printf("%c",ch[i]);
        delay(temps);
    }
}
///===============================================================================================================///
/// AFFICHAGE D'UNE FENÊTRE DE CONFIRMATION                                                                       ///
///===============================================================================================================///
int confirmation(char *msgfr)
{
    int x,y,c;
    x=25; int xi=wherex();
    y=13; int yi=wherey();
    clrscr();
    switchbackground(LIGHTGRAY);
    textbackground(RED);
    textcolor(WHITE);
    gotoxy(x,y);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
    gotoxy(x,y+1);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+2);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+3);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+4);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+5);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+6);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+7);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+8);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+9);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+10);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+11);
    printf("%c                                                          %c",186,186);
    gotoxy(x,y+12);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

    textcolor(WHITE);
    gotoxy(x+2,y+11);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,217);
    gotoxy(x+2,y+9);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,191);
    gotoxy(x+2,y+10);
    printf("%c            %c",179,179);
    gotoxy(x+44,y+11);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,196,196,217);
    gotoxy(x+44,y+9);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,196,196,191);
    gotoxy(x+44,y+10);
    printf("%c            %c",179,179);

    gotoxy(x+2,y);
    textcolor(WHITE);
    printf("[Confirmation]");


    textbackground(BLUE);
    textcolor(15);
    gotoxy(x+59,y);
    printf("X");

    textbackground(RED);
    textcolor(WHITE);
    do
    {
            gotoxy(x+2,y+3);
            printf("%-57s",msgfr);
            gotoxy(x+2,y+6);
            printf("         Etes vous s%cr de vouloir continuer ?",150);
            gotoxy(x+3,y+10);
            printf(" Non (ESC)");
            gotoxy(x+45,y+10);
            printf("Oui (Entrer)");


        gotoxy(110,40);
        c=getkey();

    }
    while((c!=ESC)&&(c!=ENTRER));
   textcolor(BLUE);
    textbackground(LIGHTGRAY);
   gotoxy(x,y);
    clreol();
    gotoxy(x,y+1);
    clreol();
    gotoxy(x,y+2);
    clreol();
    gotoxy(x,y+3);
    clreol();
    gotoxy(x,y+4);
    clreol();
    gotoxy(x,y+5);
    clreol();
    gotoxy(x,y+6);
    clreol();
    gotoxy(x,y+7);
    clreol();
    gotoxy(x,y+8);
    clreol();
    gotoxy(x,y+9);
    clreol();
    gotoxy(x,y+10);
    clreol();
    gotoxy(x,y+11);
    clreol();
    gotoxy(x,y+12);
    clreol();
    gotoxy(x,y+1);

    gotoxy(xi,yi+1);


    return c;//retourne esc ou entrer

}
///===============================================================================================================///
/// SE CHARGE DE QUITTER LE PROGRAMME                                                                             ///
///===============================================================================================================///
int quitter_a()// confirmation pour quitter le programme
{
    int c;
    clrscr();
    gotoxy(25,11);
    c=confirmation("Vous vous appretez a quitter le programme !");
    if (c==ENTRER)
    {
        clrscr();
        gotoxy(55,20);
        printf("Au revoir");
        delay(200);
    }
    return c;
}
///===============================================================================================================///
///  AUTRE PROCEDURE DE SORTIE                                                                                    ///
///===============================================================================================================///
int quitter(TObF* *f,Index_Matricule *Ind_Mat,Index_Specialite *Index_spec,Index_Etablissement *Index_Etb,Index_Region *Ind_reg)
{
    int c;
    clrscr();
    gotoxy(25,11);
    c=confirmation("Vous vous appretez a quitter le programme !");
    if (c==ENTRER)
    {
        clrscr();
        gotoxy(55,20);
        fermer(*f) ;
        Ecrire_Index_Mat(Ind_Mat);
        Ecrire_Index_Etab(Index_Etb) ;
        Ecrire_Index_Spec(Index_spec);
        Ecrire_Index_reg(Ind_reg);
        ///ANIMATION DE CHARGEMENT
            int cp=0;
            for (cp; cp!=21; cp++)
            {
                textbackground(CYAN);
                textcolor(WHITE);
                gotoxy(25,20);
                printf("            FERMUTURE ET SAUVEGARDE DE DONNEES %d %%            ", cp*5);
                delay(100);
            }
        clrscr() ;
        switchbackground(LIGHTGRAY);
        textbackground(LIGHTGRAY);
        textcolor(BLUE);
        gotoxy(55,20);
        printf("Au revoir");
        delay(200);
    }
    return c;
}
///===============================================================================================================///
/// AFFICHE LA PAGE D'ACCUEIL                                                                                     ///
///===============================================================================================================///
int ACCUEIL(){
    clear_screen_Accueil() ;
    int x,y,i,k=0;
    int choix1 ;
    pied_page() ;


    tabstr choixloginfr[]= {"    Informations sur le programme    ",
                            "    Lancer le programme              "
                           };
    choix1=-1;
    gotoxy(25,15);
    printfslow("Bienvenue, veuillez faire un choix s'il vous plait : ",20);
    gotoxy(39,20);
    x=wherex();
    y=wherey();
    do
    {
        for(i=0; i<2; i++)
        {
            gotoxy(x,y+5*i);
                aff_btn(choixloginfr[i],BLACK,LIGHTGRAY,0);
        }
        gotoxy(x,y+5*k);
            aff_btn(choixloginfr[k],BLACK,LIGHTGRAY,1);
        gotoxy(1,y+5*1+2);
        gotoxy(110,40);
        switch(getkey())
        {
        case ARROW_UP :
            k=(k-1+2)%2;
            break;
        case ARROW_DOWN :
            k=(k+1)%2;
            break;
        case ENTRER :
            choix1=k;
            break;
        case ESC :
            choix1=2;////quiter
            break;

        }
    }
    while(choix1==-1);
    return choix1;
}
///===============================================================================================================///
/// AFFICHE LA DEUXIEME PAGE                                                                                      ///
///===============================================================================================================///
void login_menu(int *choix1)
{
    int x,y,i,k=0;




    tabstr choixloginfr[]= {"    Ouvrir un fichier existant      ",
                            "    Construire un nouveau fichier   "
                           };
   // clrscr();

   clear_screen_Accueil();
   gotoxy(13,16); printf("Comment voulez-vous proc%cder ?",130);
    pied_page();
    *choix1=-1;
    gotoxy(39,20);
    x=wherex();
    y=wherey();
    do
    {
        for(i=0; i<2; i++)
        {
            gotoxy(x,y+5*i);
                aff_btn(choixloginfr[i],BLACK,LIGHTGRAY,0);
        }
        gotoxy(x,y+5*k);
            aff_btn(choixloginfr[k],BLACK,LIGHTGRAY,1);
        gotoxy(1,y+5*1+2);
        gotoxy(110,40);
        switch(getkey())
        {
        case ARROW_UP :
            k=(k-1+2)%2;
            break;
        case ARROW_DOWN :
            k=(k+1)%2;
            break;
        case ENTRER :
            *choix1=k;
            break;
        case ESC :
            *choix1=2;////quiter
            break;


        }


    }
    while(*choix1==-1);
}
///===============================================================================================================///
/// DEPLOIE LE MENU PRINCIPAL                                                                                     ///
///===============================================================================================================///
void menu_principal(int *choix1, int nb_profs, int l, int profs_actuels)
{
    int x,y,i,k=0;

    clear_screen(nb_profs,l,profs_actuels);
    tabstr choixloginfr[]= {"Ajouter un nouvel enseignant au fichier.                                     ",
                            "Modifier l etablissement universitaire d un enseignant.                      ",
                            "Supprimer un enregistrement donne par le matricule.                          ",
                            "Supprimer les enregistrements relatifs a une specialite donnee.              ",
                            "Afficher les enseignants d un etablissement donne ayant une anciennete donnee",
                            "Consulter les enseignants exercant dans une region donnee.                   "
                           };
    pied_page();
    *choix1=-1;
    gotoxy(19,9);
    x=wherex();
    y=wherey();
    do
    {
        for(i=0; i<6; i++)
        {
            gotoxy(x,y+5*i);
                aff_btn(choixloginfr[i],BLACK,LIGHTGRAY,0);
        }
        gotoxy(x,y+5*k);
            aff_btn(choixloginfr[k],BLACK,LIGHTGRAY,1);
        gotoxy(1,y+5*1+2);
        gotoxy(110,40);
        switch(getkey())
        {
        case ARROW_UP :
            k=(k-1+6)%6;
            break;
        case ARROW_DOWN :
            k=(k+1)%6;
            break;
        case ENTRER :
            *choix1=k;
            break;
        case ESC :
            *choix1=6;////quiter
            break;


        }


    }
    while(*choix1==-1);
}
///===============================================================================================================///
/// EFFECTUE LES VERIFICATIONS NECESSAIRES SUR L'ENTIER SAISI                                                     ///
///===============================================================================================================///
int scanstr_num(int *nombre) //lit une chaine de numero
{
    char *num = malloc(10*sizeof(char));
    int x,y,i=-1,c=-1,quit=0;
    x=wherex();
    y=wherey();


    while ( ((c!=ENTRER) || i==-1) && (c!=ESC))
    {
        gotoxy(x+i,y);

        c=getkey();
        if (c==ESC) quit=1;
        else if((c>=KEY_0&&c<=KEY_9)&&(i<8))
        {
            num[1+i]=c;
            printf("%c",c);
            i++;
            gotoxy(x+1+i,y);
        }
        else if ((c==BACK_SPACE)&&(i>=0))
        {
                num[i]=" ";
                i--;
                gotoxy(x+i,y);
                printf(" ");
        }
        else if (((i==-1)&&(c==ENTRER))||((i==7)&&(c!=ENTRER))) flashbackground(RED,100);

    }
    num[8]='\0';
    *nombre = strtol(num,NULL,10);

    gotoxy(1,y+1);
    free(num);
    return quit;

}
///===============================================================================================================///
/// FONCTION D'AFFICHAGE D'UN ENREGISTREMENT N°1                                                                  ///
///===============================================================================================================///
void afficher_prof(TObF* *Fichier,Index_Matricule *Index_matr,int indice)
{
    int matricule = Index_matr->tab[indice].matricule ;
    int num_bloc  = Index_matr->tab[indice].num_bloc ;
    int adr_dans_bloc = Index_matr->tab[indice].adr_dans_bloc;
    int num_etab = Index_matr->tab[indice].num_etab;
    int anciennete = Index_matr->tab[indice].anciennete;
     Tbloc* Buffer = malloc(sizeof(Tbloc)) ;
   lireDir(*Fichier,num_bloc,Buffer);
    char Nom[Long_Nom];
    char Prenom[Long_Nom];
    char Specialite[30] ;
    char Sexe[6] ;
    strcpy(Nom,Buffer->tab[adr_dans_bloc].Nom);
    strcpy(Prenom,Buffer->tab[adr_dans_bloc].Prenom);
    strcpy(Specialite,Buffer->tab[adr_dans_bloc].Specialite);
    strcpy(Sexe,Buffer->tab[adr_dans_bloc].Sexe);
    int i,n=30,x,y;
        x=wherex();
        y=wherey();
       // normvideo();
       // textattr(9);
        textcolor(BLUE);
        textbackground(LIGHTGRAY);
        printf("%c",201);
        gotoxy(x+1+n,y);
        printf("%c",187);
        gotoxy(x+1,y);
          for (i=2; i<5; i++)
        {
            printf("%c",205);
        }
        textcolor(BLACK);
        textbackground(LIGHTGRAY);
        printf("N= %d",matricule);
        textcolor(BLUE);
        textbackground(LIGHTGRAY);
          for (i=13; i<n+2; i++)
        {
            printf("%c",205);
        }
         for (i=1; i<8; i++)
        {
            gotoxy(x,y+i);
            printf("%c",186);
        }
        for (i=1; i<8; i++)
        {
            gotoxy(x+1+n,y+i);
            printf("%c",186);
        }
        gotoxy(x+1,y+7);
        for (i=1; i<n+2; i++)
        {
            printf("%c",205);
        }
        gotoxy(x+1+n,y+7);
        printf("%c",188);
        gotoxy(x,y+7);
        printf("%c",200);
        textcolor(RED);
       gotoxy(x+1,y+1);
       printf("Nom : %s",Nom);
       gotoxy(x+1,y+2);
       printf("Pr%cnom : %s",130,Prenom);
       gotoxy(x+1,y+3);
       printf("Specialit%c : %s",130,Specialite);
       gotoxy(x+1,y+4);
       printf("N %ctablissement : %d",130,num_etab);
       gotoxy(x+1,y+5);
       printf("Experience : %d an(s)",anciennete);
       gotoxy(x+1,y+6);
       printf("Sexe : %s",Sexe);
       gotoxy(110,40);
       delay(100);

///------------------------
        gotoxy(x,y);
      //  textattr(9);
        textcolor(BLACK);
        textbackground(LIGHTGRAY);
        printf("%c",201);
        gotoxy(x+1+n,y);
        printf("%c",187);
        gotoxy(x+1,y);
         for (i=2; i<5; i++)
        {
            printf("%c",205);
        }
        textcolor(BLUE);
        textbackground(LIGHTGRAY);
        printf("N= %d",matricule);
        textcolor(BLACK);
        textbackground(LIGHTGRAY);
          for (i=13; i<n+2; i++)
        {
            printf("%c",205);
        }
         for (i=1; i<8; i++)
        {
            gotoxy(x,y+i);
            printf("%c",186);
        }
        for (i=1; i<8; i++)
        {
            gotoxy(x+1+n,y+i);
            printf("%c",186);
        }
        gotoxy(x+1,y+7);
        for (i=1; i<n+2; i++)
        {
            printf("%c",205);
        }
        gotoxy(x+1+n,y+7);
        printf("%c",188);
        gotoxy(x,y+7);
        printf("%c",200);
        textcolor(BLUE);
       gotoxy(x+1,y+1);
       printf("Nom : %s",Nom);
       gotoxy(x+1,y+2);
       printf("Prenom : %s",Prenom);
       gotoxy(x+1,y+3);
       printf("Specialite : %s",Specialite);
       gotoxy(x+1,y+4);
       printf("N etablissement : %d",num_etab);
       gotoxy(x+1,y+5);
       printf("Experience : %d an(s)",anciennete);
       gotoxy(x+1,y+6);
       printf("Sexe : %s",Sexe);
       gotoxy(110,40);
}
///===============================================================================================================///
/// FONCTION D'AFFICHAGE D'UN ENREGISTREMENT N°2                                                                  ///
///===============================================================================================================///
void Affich_Prof(int matricule, int ligne, int colonne){


                printf("%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,187);
                gotoxy(colonne,ligne+1);
                printf("%c   %d  %c",186,matricule,186);
                gotoxy(colonne,ligne+2);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,188);
}


///============================================================================================ FIN
/// Merci d'avoir pris le temps de lire ce travail pratique,
/// Il fut extrêmement bénéfique pour nous sur tous les plans
/// Nous espèrons qu'il aura été tout autant satisfaisant aux utilisateurs qui l'ont testé.
