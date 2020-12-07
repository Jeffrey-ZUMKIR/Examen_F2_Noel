#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "phaseInit.h"
#include "defineStruct.h"

#define NBMAXPIS 10
#define NBMINPIS 1

//BUT:      Savoir le nombre de pisteur présent durant cette partie
//ENTREE:   /
//SORTIE:   Le nombre de pisteur
int nombrePisteur(){
    int good=0;
    int nbPisteur=0;
    //Demander le nombre de pisteur
    do{
        printf("Veuillez choisir un nombre de pisteur (entre 1 et 10) :\n");
        scanf("%d",&nbPisteur);
        //Vérifie si ce trouve dans la limite de pisteur
        if(nbPisteur>=NBMINPIS && nbPisteur<=NBMAXPIS){
            good=1;
        }else{
            printf("Veuillez saisir un autre nombre de pisteur!\n");
        }
        fflush(stdin);
    }while(good==0);
    return nbPisteur;
}

//BUT:      Initialiser les variables de pisteur et leur positon
//ENTREE:   La liste des pisteurs, le tableau à afficher, le nombre de pisteur
//SORTIE:   La liste de pisteur initialisé et les pisteurs positionnés
void initPisteur(struct str_pisteur tabPisteur[],char mapAffich[HEIGHTAB][WIDTHTAB],int nbPisteur){
    int good=0;
    int ok=0;
    int x=0;
    int y=0;
    //Initialiser chaque pisteur
    for(int i=0;i<nbPisteur;i++){
        tabPisteur[i].vivant=1;
        //demander les coordonnes du pisteur
        printf("Ou souhaitez-vous placer le pisteur numero %d ?\n",i+1);
        do{
            //Vérif si x se trouve dans le cadre
            do{
                printf("Dans quel colonne?\n");
                scanf("%d",&x);
                if(x>0 && x<WIDTHTAB){
                    ok=1;
                }else{
                    printf("Cette colonne n'existe pas!\n");
                }
                fflush(stdin);
            }while(ok==0);
            ok=0;
            //Vérif si y se trouve dans le cadre
            do{
                printf("Dans quel ligne?\n");
                scanf("%d",&y);
                if(y>0 && y<HEIGHTAB){
                    ok=1;
                }else{
                    printf("Cette ligne n'existe pas!\n");
                }
                fflush(stdin);
            }while(ok==0);
            //Vérif si un pisteur si trouve déjà
            if(mapAffich[y][x]!='P'){
                mapAffich[y][x]='P';
                tabPisteur[i].pos.x=x;
                tabPisteur[i].pos.y=y;
                good=1;
            }

        }while(good==0);
        good=0;
        system("cls");
        //Afficher la map avec le pisteur
        Affichage(mapAffich);
    }
}

/*void initMapAffBeginning(char tab[HEIGHTAB][WIDTHTAB]){
    for(int i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            if((i==0)||(j==0)||(i==HEIGHTAB-1)||(j==WIDTHTAB-1)){
                tab[i][j]='*';
            }

            if(i==0){
                tab[i][j]=j+'0';
            }else if(j==0){
                tab[i][j]=i+'0';
            }else{
                tab[i][j]=' ';
            }
        }
    }
}*/

//BUT:      Initialiser le tableau à afficher
//ENTREE:   Le tableau
//SORTIE:   Le tableau initialiser
void initMapAff(char tab[HEIGHTAB][WIDTHTAB]){
    for(int i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            //Poser le cadre
            if((i==0)||(j==0)||(i==HEIGHTAB-1)||(j==WIDTHTAB-1)){
                tab[i][j]='*';
            }else{
                tab[i][j]=' ';
            }
        }
    }
}

//BUT:      Initialiser la variable du monstre
//ENTREE:   Le monstre
//SORTIE:   Le monstre initialiser
void initMonstre(str_monstre *monstre,char tab[HEIGHTAB][WIDTHTAB]){
    monstre->PV=4;

    srand(time(NULL));

    int Min=1;
    int MaxX=WIDTHTAB-2;
    int MaxY=HEIGHTAB-2;

    int x=0;
    int y=0;
    int good=0;
    do{
        x = (rand() % (MaxX + 1 - Min)) + Min;
        y = (rand() % (MaxY + 1 - Min)) + Min;

        good=1;
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(tab[y+i][x+j]=='P'){
                    good=0;
                }
            }
        }
        if(good==1){
            tab[y][x]='M';
            monstre->pos.x=x;
            monstre->pos.y=y;
        }
    }while(good==0);
}
