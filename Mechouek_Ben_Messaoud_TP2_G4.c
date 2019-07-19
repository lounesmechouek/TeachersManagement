#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "conio21/conio2.h"
#include "TP_Biblio.h"

///==================================================================================================
///     Travail réalisé dans le cadre du TP du module SFSD du 1er semestre 2CP à l'ESI (Oued Smar)
///     ETUDIANTS : Mechouek Lounes 2CP4 et Ben Messaoud Mohamed Issam Daoud 2CP4 (2018/2019)
///     ENCADREUR : DR. KERMI ADEL.
///==================================================================================================

int main()
{
    srand(time(NULL));
    TObF *Fichier;
    system("mode con LINES=40 COLS=110");  //definition des dimension de la console
    int choix ;
    char mode_ouverture = 'N' ;

refaire:
    choix=ACCUEIL() ;

    switch(choix)
    {
        case 0:
            Information_programme();
            goto refaire;
            break ;
        case 1:
            break;
        case 2:
            if(quitter_a() == ENTRER)
            {
                gotoxy(1,36);
                return 0;
            }

            else
                goto refaire;
            break ;
    }

    choix = -1 ;
login:
    login_menu(&choix);

    switch(choix)
    {
        case 0:
            mode_ouverture = 'A' ;
            break ;
        case 1:
            mode_ouverture = 'N' ;
            break;
        case 2:
            goto refaire ;
            break ;
    }

    /**////*----------------------------------------------DECLARATION/INITIALISATIONS---------------------------------------------------------*/
    /**/ /// Déclaration index
    /**/ Etablissement Table_Etab[250] ;
    /**/ Genere_Tab_Etablissement(Table_Etab); Prof Nouveau_Prf;
    /**/ Index_Etablissement Index_Etab ; Index_Matricule Index_Matr;Index_Region Index_Reg ; Index_Specialite Index_Spec ;
    /**/
    /**/ int i,c = 0,k,reg,mat,e_min,e_max,pos,num_spec, num_etab, nb_profs,netab = 0 ,boole = -1 ; Tbloc *Buuffer=malloc(sizeof(Tbloc));
    /**/
    /**/ Init_Indexs(&Index_Etab,&Index_Matr,&Index_Reg,&Index_Spec);
    /**/ char nomf[30];
    /**////*-----------------------------------------------------------------------------------------------------------------------------------*/
ouvrir_fich:
    clear_screen_Accueil() ;
    pied_page();
    gotoxy(30,20);
    printf("Veuillez entrer le nom du fichier s'il vous plait ");
    scanf("%s",nomf);
    if (ouvrir(&Fichier,nomf,mode_ouverture) == 0)
    {
        gotoxy(30,25);
        printf("Appuyez sur ENTRER pour r%cessayer\n",130);
        c= getkey() ;
        if (c == ESC) goto login ;
        goto ouvrir_fich ;
    }
    else{
        if(mode_ouverture=='N')
        {
            creation_Fichier_Index(&Fichier, Table_Etab, &Index_Etab, &Index_Matr, &Index_Reg, &Index_Spec);

            ///ANIMATION DE CHARGEMENT
            int cp=0;
            for (cp; cp!=21; cp++)
            {
                textbackground(CYAN);
                textcolor(WHITE);
                gotoxy(25,30);
                printf("            CREATION DE LA STRUCTURE ET EPURATION %d %%            ", cp*5);
                delay(100);
            }
        }
        else
        {
        /// chargement des indexs secondaires vers la MC
              FILE *F=fopen("Table_Matricules.bin","rb+");
             if (F != NULL)
             {
                 fread(&Index_Matr,1,sizeof(Index_Matricule),F);
                 fclose(F);
             }
               F=fopen("Table_Specialites.bin","rb+");
             if (F != NULL)
             {
                 fread(&Index_Spec,1,sizeof(Index_Specialite),F);
                 fclose(F);
             }
                F=fopen("Table_Etablissements.bin","rb+");
              if (F != NULL)
             {
                fread(&Index_Etab,1,sizeof(Index_Etablissement),F);
                fclose(F);
             }

               F=fopen("Table_Regions.bin","rb+");
           if (F != NULL)
           {
             fread(&Index_Reg,1,sizeof(Index_Region),F);
             fclose(F);
           }

        }
        textbackground(LIGHTGRAY);
        textcolor(BLUE);
        }

        nb_profs=Fichier->entete.nombre_profs-Index_Matr.niveau_remplissage; ///nb_profs : Nombre de collisions

 menu: choix=-1;
       menu_principal(&choix, Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);

    switch(choix)
    {
        case 0:
            Genere_Prof(&Nouveau_Prf,&num_spec,&num_etab, Table_Etab);
            pos=Ajouter_Prof(&Fichier, num_etab, num_spec, Nouveau_Prf, &Index_Etab, &Index_Matr, &Index_Reg, &Index_Spec);

            clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
            lireDir(Fichier, Index_Matr.tab[pos].num_bloc,Buuffer);

            gotoxy(22,18);
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

            gotoxy(22,19);
            printf("%c MATRICULE : %d | NOM : %s | PRENOM : %s ",186,Buuffer->tab[Index_Matr.tab[pos].adr_dans_bloc].Matricule,Buuffer->tab[Index_Matr.tab[pos].adr_dans_bloc].Nom, Buuffer->tab[Index_Matr.tab[pos].adr_dans_bloc].Prenom);
            gotoxy(81,19); printf("%c",186);

            gotoxy(22,20);
            printf("%c NUM BLOC : %d | POS DANS BLOC : %d | ANCIENNETE : %d  ",186,Index_Matr.tab[pos].num_bloc,Index_Matr.tab[pos].adr_dans_bloc,Index_Matr.tab[pos].anciennete);
            gotoxy(81,20); printf("%c",186);

            gotoxy(22,21);
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);


            gotoxy(22,35);
            printf("Appuyez sur n%cimporte qu%celle touche pour revenir en arri%cre",39,39,138);

            getkey();
            goto menu;

            break ;

        case 1:         ///MUTATION D'UN PROF VERS UN AUTRE ETAB
              clrscr();
            switchbackground(LIGHTGRAY);
            textbackground(LIGHTGRAY);
            gotoxy(8,1); printf("*****************************************************************************");
            gotoxy(8,2); printf("*             LISTE DES PROFS : (APPUYEZ SUR UNE TOUCHE)                    *");
            gotoxy(8,3); printf("*****************************************************************************");
            getkey();

            gotoxy(8,5);
            int k;
            for(i=0 ; i < Index_Matr.niveau_remplissage ; i++)
            {
                if( !(((k=i) % 1000)) && i!=0 )
                    getkey();
                printf("        %d | Matricule : %d  | NUM_SPEC : %d | NUM_ETAB : %d\n",i,Index_Matr.tab[i].matricule, Index_Matr.tab[i].num_spec, Index_Matr.tab[i].num_etab) ;
            }
            printf("\n\n\t Appuyez sur une touche ... \n");
            getkey();

        mutation:
            clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
            pied_page();
            gotoxy(30,15);
            printf("Veuillez entrer le matricule du professeur SVP :   ");
            boole = scanstr_num(&mat);
            if(boole ==0)
            {

                if( (mat < 1) || (mat > Index_Matr.tab[Index_Matr.niveau_remplissage-1].matricule))
                {
                            gotoxy(30,19) ;
                            textcolor(RED);
                            printf("Matricule erron%c\n",130);
                            textcolor(BLUE);
                            gotoxy(30,21) ;
                            printf("Veuillez appuyer sur ENTRER pour r%cssayer",130) ;
                            if(getkey() == ESC) goto menu ;
                            else goto mutation ;
                    goto mutation ;
                }
                else
                {
                    gotoxy(30,16);
                    printf("Quel est le numero de l%cetablissement vers lequel il a %ct%c transf%cr%c ?   ",39,130,130,130,130);
                    boole = scanstr_num(&netab) ;
                    if(boole == 0)
                    {
                        if((netab < 0) || (netab > MAX_ETAB))
                        {
                            gotoxy(33,19) ;
                            textcolor(RED);
                            printf("Numero d%cetablissement erron%c",39,130);
                            textcolor(BLUE);
                            gotoxy(33,21) ;
                            printf("Veuillez appuyer sur ENTRER pour r%cssayer",130) ;
                            if(getkey() == ESC) goto menu ;
                            else goto mutation ;
                        }
                        else
                        {
                            pos=Mutation_Prof(&Fichier, mat,netab , &Index_Matr, Table_Etab);

                                if(pos==-1)
                                    {delay(500); goto menu;}

                                else{

                                    gotoxy(2,20);
                                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

                                    gotoxy(2,21);
                                    printf("%c L'OPERATION A ETE EFFECTUEE AVEC SUCCES ! NOUVEL ETABLISSEMENT : ",186);
                                    gotoxy(106,21); printf("%c",186);


                                    gotoxy(2,22);
                                    printf("%c %s ",186,Table_Etab[Index_Matr.tab[pos].num_etab].Nom_Etab);
                                    gotoxy(106,22); printf("%c",186);

                                    gotoxy(2,23);
                                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

                                    gotoxy(20,35);
                                    printf("Appuyez sur n%cimporte quelle touche pour revenir ...",39);
                                    getkey();

                                    goto menu;
                        }
                        }
                    }
                }
            }

               goto menu;
            break;
        case 2:     ///SUPPRESSION D'UN ENSEIGNANT PAR LE MATRICULE

            clrscr();
            switchbackground(LIGHTGRAY);
            textbackground(LIGHTGRAY);
            gotoxy(8,1); printf("*****************************************************************************");
            gotoxy(8,2); printf("*             LISTE DES PROFS : (APPUYEZ SUR UNE TOUCHE)                    *");
            gotoxy(8,3); printf("*****************************************************************************");
            getkey();

            gotoxy(8,5);
            for(i=0 ; i < Index_Matr.niveau_remplissage ; i++)
            {
                if( !(((k=i) % 1000)) && i!=0 )
                    getkey();
                printf("        %d | Matricule : %d  | NUM_SPEC : %d | NUM_ETAB : %d\n",i,Index_Matr.tab[i].matricule, Index_Matr.tab[i].num_spec, Index_Matr.tab[i].num_etab) ;
            }
            printf("\n\n\t Appuyez sur une touche ... \n");
            getkey();

        SUPP :
            clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
            pied_page();
            gotoxy(15,20); printf("Quel est le matricule du professeur %c supprimer ?  ",133);
            boole=scanstr_num(&mat);

            if( !(boole) && ((i=confirmation("Vous vous appretez a effectuer une suppression ")) == ENTRER) )
            {

            if((pos=rechercheDicho(Index_Matr.tab,Index_Matr.niveau_remplissage,mat)) != -1)
            {
                clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
                lireDir(Fichier,Index_Matr.tab[pos].num_bloc,Buuffer);
                gotoxy(18,22);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

                gotoxy(18,23);
                printf("%c AVANT SUPPRESSION : MAT => %d | BLOC => %d | POS => %d         ",186,Buuffer->tab[Index_Matr.tab[pos].adr_dans_bloc].Matricule,Index_Matr.tab[pos].num_bloc,Index_Matr.tab[pos].adr_dans_bloc);
                gotoxy(87,23); printf("%c",186);

                gotoxy(18,24);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

                Sup_Prof(&Fichier, mat, &Index_Matr,pos);
                Ecrire_Index_Mat(&Index_Matr);

                lireDir(Fichier,Index_Matr.tab[pos].num_bloc,Buuffer);

                gotoxy(18,26);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

                gotoxy(18,27);
                printf("%c APRES SUPPRESSION : MAT => %d | BLOC => %d | POS => %d           ",186,Buuffer->tab[Index_Matr.tab[pos].adr_dans_bloc].Matricule,Index_Matr.tab[pos].num_bloc,Index_Matr.tab[pos].adr_dans_bloc);
                gotoxy(87,27); printf("%c",186);

                gotoxy(18,28);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

                gotoxy(18,35); printf("Appuyez sur une touche pour revenir ...");
                getkey(); goto menu;
            }

                else
                {
                    clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
                    pied_page(); if(getkey() == ESC) goto menu ;
                    gotoxy(40,20); printf("Ce matricule est introuvable, Reessayez."); delay(1000);
                    goto SUPP;
                }
            }
            else
            {
                if(boole) goto menu;
                else goto SUPP;
            }


            goto menu;

            break;

        case 3:         ///SUPPRESSION DE TOUS LES ENSEIGNANTS D'UNE SPECIALITE DONNEE
        sup_spec:
            clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
            switchbackground(LIGHTGRAY) ;
            textbackground(LIGHTGRAY);
            textcolor(BLUE);
            pied_page();
            gotoxy(25,19) ;
            printf("Veuillez entrer le num%cro de la sp%ccialite s%cil vous plait [|0,%d|]  ",130,130,39,NB_SPECIALITE);
            boole=scanstr_num(&num_spec) ;

            if( !(boole) && ((i=confirmation("Vous vous appretez a effectuer une suppression ")) == ENTRER) )
            {
                if((num_spec < 0 ) || (num_spec > NB_SPECIALITE))
                {
                    gotoxy(33,20) ;
                    textcolor(RED);
                    printf("Num%cro de specialit%c erron%c, veuillez r%cessayer s%cil vous plait\n",130,130,130,130,39);
                    delay(1000);
                    textcolor(BLUE);
                    goto sup_spec ;
                }


                if( (k=Sup_Selon_Spec(&Fichier,num_spec,&Index_Matr,&Index_Spec)) == 1)
                {

                    clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);

                    gotoxy(22,18);
                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);

                    gotoxy(22,19);
                    printf("%c Suppression effectu%ce avec succ%cs",186,130,138);
                    gotoxy(81,19); printf("%c",186);

                    gotoxy(22,20);
                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205);
                    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);

                    gotoxy(22,25);
                    textcolor(RED);
                    printf("Appuyez sur n%cimporte qu%celle touche pour revenir en arri%cre",39,39,138);
                    getkey() ;
                    goto menu ;
                }

                else
                    goto sup_spec;
            }


            else
            {
                if (boole) goto menu;
                else goto sup_spec;
            }

            goto menu;
            break ;
        case 4:             ///TOUS LES PROFS D'UN ETABLISSEMENT AVEC UNE EXPERIENCE ENTRE 2 VALEURS
        requette:
            clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
            gotoxy(29,19) ;
            printf("Veuillez entrer le num%cro d%c%ctablissement s%cil vous plait :  ",130,39,130,39);
            scanstr_num(&num_etab) ;
            if((num_etab < 0 ) || (num_etab > MAX_ETAB))
            {
                gotoxy(29,20) ;
                textcolor(RED);
                printf("Numero d%c%ctablissement erron%c, veuillez r%cessayer s%cil vous plait\n",39,130,130,130,39);
                delay(1000);
                textcolor(BLUE);
                goto requette ;
            }
            anciennte:
            gotoxy(33,20) ;
            printf("Anciennete minimale :  ");
            scanstr_num(&e_min) ;
            gotoxy(33,21) ;
            printf("Anciennete maximale :  ");
            scanstr_num(&e_max) ;
            if (e_min >= e_max) goto anciennte ;
            if( (k=Requete_Intervalle(&Fichier,e_min,e_max,num_etab,&Index_Matr,&Index_Etab) == ESC))
                    goto menu;
            goto menu ;
            break ;
        case 5:
          CONSUL:
            clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
            gotoxy(18,19); printf("     0 : OUEST | 1 : CENTRE | 2 : EST ");
            gotoxy(18,21); printf("Entrez, s'il vous plait, le numero de la region voulue :    ");
            scanstr_num(&reg);

            if(reg>=0 && reg<=2)
            {
                clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
                if( (k=consulter_profs_region(&Fichier,reg,&Index_Matr,&Index_Reg,Table_Etab,nb_profs)) == ESC)
                    goto menu;

                gotoxy(50,39); printf("Appuyez sur une touche pour revenir ...");
                getkey();
                goto menu;
            }

            else{
                clear_screen(Fichier->entete.nombre_profs,entete(Fichier,1),nb_profs);
                gotoxy(18,20) ;
                printf("Numero de region erron%c, veuillez r%cssayer s%cil vous plait\n",130,130,39);
                delay(500);
                goto CONSUL ;
            }

            goto menu;
            break;

        case 6:
            if(quitter(&Fichier,&Index_Matr,&Index_Spec,&Index_Etab,&Index_Reg) == ENTRER)
            {
                gotoxy(1,36);
                return 0;
            }

            else
                goto menu;
            break ;
    }

    free(Buuffer);
    fermer(Fichier);

    return 1;
}






