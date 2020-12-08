#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "Affich.h"
#include "phaseVision.h"
#include "defineStruct.h"

#define MAXSHOUT 40
#define MINSHOOT 1

//BUT:      Enclencher la vision de chaque pisteur
//ENTREE:   La liste de pisteur, les tableaux des traces, le tableau d'affichage et la variable du monstre
//SORTIE:   Phase de vision terminé
void phaseVision(struct str_pisteur tabpisteur[], int tabTraceMonstre[HEIGHTAB][WIDTHTAB], int tabTracePisteur[HEIGHTAB][WIDTHTAB],
                 char tabAff[HEIGHTAB][WIDTHTAB], int nbPisteur, str_monstre *monstre){
    //Répéter l'action de vue pour chaque pisteur
    for(int i=0;i<nbPisteur;i++){
        doVision(tabpisteur[i],tabTraceMonstre,tabTracePisteur,tabAff,&monstre);
    }
    //monstre->PV=2;
}

//BUT:      Checker ce que voie le pisteur
//ENTREE:   Le pisteur, les tableaux des traces, le tableau d'affichage et la variable du monstre
//SORTIE:   Les zones avec des traces affichés
void doVision(str_pisteur pisteur, int tabTraceMonstre[HEIGHTAB][WIDTHTAB], int tabTracePisteur[HEIGHTAB][WIDTHTAB], char tabAff[HEIGHTAB][WIDTHTAB], str_monstre *monstre){
    if(pisteur.vivant==1){
        int x=pisteur.pos.x;
        int y=pisteur.pos.y;
        int nb=1;
        int foundMonst=0;

        //Indiquer quel pisteur voie
        tabAff[y][x]='!';
        AffichageTrace(tabTraceMonstre,tabAff);

        //Vérification de chaque case autour du pisteur
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                //Détection si le monstre est là
                if(tabTraceMonstre[y+i][x+j]==16){
                    printf("Le monstre se trouve en case numero %d! \n",nb);
                    foundMonst=1;
                }//Détection si il y a des traces environnantes
                else if(tabTraceMonstre[y+i][x+j]>0){
                    printf(" Trace en %d de valeur %d. ",nb,tabTraceMonstre[y+i][x+j]);
                }//Si aucune trace, indication des zones vides
                else{
                    printf(" Pas de trace en %d.",nb);
                }
                nb++;
            }
            printf("\n");
        }

        //Si le monstre est là, enclencher le tir
        if(foundMonst==1){
            Tirer(&monstre);
        }

        //Remettre le pisteur en défaut
        tabAff[y][x]='P';

        //monstre->PV=2;
        //printf("PV du monstre%d",monstre.PV);

        system("pause");
        system("cls");

    }
}

//BUT:      Tirer sur le monstre
//ENTREE:   La varaible du monstre
//SORTIE:   Toucher ou louper
void Tirer(str_monstre *monstre){

    printf("Voulez vous tirer? (T)");
    int good=0;
    char tir;

    //Empêcher de faire une mauvaise manipulation en n'entrant rien
    do{
        tir=getchar();
        fflush(stdin);
        good=1;
        if(toupper(tir)=='T'){
            good=2;
        }
        if(tir=='\n'){
            good=0;
        }
    }while(good==0);

    //Si la valeur donnée est 't' ou 'T', tirer
    if(good==2){
        //Obtenir un nombre n'avoir que 40% de chance de toucher
        int shoot=(rand()%(MAXSHOUT + 1 - MINSHOOT))+MINSHOOT;
        //Si le nombre obtenu est plus petit ou égal à 40, tirer. Sinon louper
        if(shoot<=40){
            printf("Toucher!");
            monstre->PV-=1;
        }else{
            printf("Louper!");
        }
    }

}
