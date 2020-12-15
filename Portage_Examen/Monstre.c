#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defineStruct.h"
#include "phaseMonstre.h"
#include "trace.h"

//BUT:      Deplacer le monstre en fonction de sa position et de ce qui se trouve autour de lui tel que des traces ou des pisteurs
//ENTREE:   Le monstre, le tableau de ses traces, les pisteurs, la map a afficher, le nombre de pisteur ainsi que les traces appercues par les pisteurs
//SORTIE:   Le monstre d�placer avec peut etre un pisteur mort
void phaseMonstre(str_monstre *monstre, int tabTraceM[HEIGHTAB][WIDTHTAB], struct str_pisteur tabPisteur[], char mapAffiche[HEIGHTAB][WIDTHTAB],int nbPisteur,int tabTraceVue[HEIGHTAB][WIDTHTAB]){
    int xgoto=0;
    int ygoto=0;

    int trace=0;
    int traceAutour=0;

    int i=0;

    //Ne faire sa phase seulement si il a encore des vies
    if(monstre->PV>0){
        //V�rifie d'abord si un pisteur se trouve sur les cases juste � cot� de lui
        if(checkAutour(monstre,mapAffiche,&xgoto,&ygoto)==1){
            //Si oui on se d�place sur la case et on tue le pisteur
            //Si le monstre est bless�, il laisse du sang sur son ancienne zone
            if(monstre->saignement>0){
                tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
            }
            //Donne la nouvelle position au monstre
            monstre->pos.x=xgoto;
            monstre->pos.y=ygoto;
            //Ajoute ses traces
            tabTraceM[ygoto][xgoto]=17;
            //Retire le pisteur pr�sent sur la mapAffiche
            mapAffiche[ygoto][xgoto]=' ';
            //Le pisteur pr�sent sur cette case passe sa vie � 0
            for(i=0;i<nbPisteur;i++){
                if(tabPisteur[i].pos.x==xgoto && tabPisteur[i].pos.y==ygoto){
                    printf("Le monstre a devore le pisteur numero %d!\n",i+1);
                    tabPisteur[i].vivant=0;
                }
            }
        }else {
            //Si non, on v�rifie si il est pr�sent sur une case poss�dant une trace et on la r�cup�re
            trace=checkTraceActuelle(monstre,tabPisteur,nbPisteur);
            //Si il y a une trace ou non, on cherche une trace plus r�cente au tour du pisteur
            if(trace==0){
                traceAutour=checkTraceAutour(monstre,tabPisteur,nbPisteur,500,&xgoto,&ygoto);
            }else{
                traceAutour=checkTraceAutour(monstre,tabPisteur,nbPisteur,trace,&xgoto,&ygoto);
            }


            if(traceAutour==0){
                //Si il n'y a pas de trace autour, le monstre se d�place de mani�re random
                deplacementRandom(tabTraceM,monstre,&xgoto,&ygoto);
                //Si le monstre saigne, il laisse une trace derri�re lui
                if(monstre->saignement>0){
                    tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
                }
                //Recupere les coordonnees de la nouvelle position
                monstre->pos.x=xgoto;
                monstre->pos.y=ygoto;
                tabTraceM[ygoto][xgoto]=17;

            }else if(traceAutour==1){
                //Si il trouve des traces, il se dirige vers une trace plus r�cente
                //Si le monstre saigne, il laisse une trace derri�re lui
                if(monstre->saignement>0){
                    tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
                }
                //Recupere les coordonnees de la nouvelle position
                monstre->pos.x=xgoto;
                monstre->pos.y=ygoto;
                tabTraceM[ygoto][xgoto]=17;
            }
            //Apr�s avoir boug� sans avoir tu�, on v�rifie si un pisteur se trouve � cot� du monstre
            if(checkAutour(monstre,mapAffiche,&xgoto,&ygoto)==1){
                //Si oui on se d�place sur cette nouvelle zone et on tue le pisteur
                deleteTrace(tabTraceM);
                //Si le monstre saigne, il laisse une trace derri�re lui
                if(monstre->saignement>0){
                    tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
                }
                //Recupere les coordonnees de la nouvelle position
                monstre->pos.x=xgoto;
                monstre->pos.y=ygoto;
                //Ajoute ses traces
                tabTraceM[ygoto][xgoto]=17;
                //Retire le pisteur pr�sent sur la mapAffiche
                mapAffiche[ygoto][xgoto]=' ';
                //Le pisteur pr�sent sur cette case passe sa vie � 0
                for(i=0;i<nbPisteur;i++){
                    if(tabPisteur[i].pos.x==xgoto && tabPisteur[i].pos.y==ygoto){
                        printf("Le monstre a devore le pisteur numero %d!\n",i);
                        tabPisteur[i].vivant=0;
                    }
                }
            }

        }
        //Si le monstre saigne, a la fin de sa phase on retire un tour de saignement
        if(monstre->saignement>0){
            monstre->saignement-=1;
        }
    }

}

//BUT:      V�rifier si un pisteur se trouve autour du monstre
//ENTREE:   Le monstre, la map a afficher et la nouvelle position du monstre
//SORTIE:   Une nouvelle position du monstre si un pisteur se trouve autour de lui
int checkAutour(str_monstre *monstre, char mapAffiche[HEIGHTAB][WIDTHTAB], int *xgoto, int *ygoto){
    int found=0;
    //V�rifie si un pisteur se trouve sur les cases � cot� de lui
    if(mapAffiche[monstre->pos.y-1][monstre->pos.x]=='P'){
        found=1;
        *xgoto=monstre->pos.x;
        *ygoto=monstre->pos.y-1;
    }else if(mapAffiche[monstre->pos.y+1][monstre->pos.x]=='P'){
        found=1;
        *xgoto=monstre->pos.x;
        *ygoto=monstre->pos.y+1;
    }else if(mapAffiche[monstre->pos.y][monstre->pos.x-1]=='P'){
        found=1;
        *xgoto=monstre->pos.x-1;
        *ygoto=monstre->pos.y;
    }else if(mapAffiche[monstre->pos.y][monstre->pos.x+1]=='P'){
        found=1;
        *xgoto=monstre->pos.x+1;
        *ygoto=monstre->pos.y;
    }
    else if(mapAffiche[monstre->pos.y][monstre->pos.x]=='P'){
        found=1;
        *xgoto=monstre->pos.x;
        *ygoto=monstre->pos.y;
    }
    return found;
}

//BUT:      R�cup�re la plus r�cente sur laquel le monstre se trouve
//ENTREE:   Le monstre, la liste des pisteurs, le nombre de pisteur
//SORTIE:   La trace la plus r�cente surlaquel le monstre se trouve
int checkTraceActuelle(str_monstre *monstre, struct str_pisteur tabPisteur[], int nbPisteur){
    int onTrace=0;
    int i=0;
    //On r�cup�re la trace la plus r�cente sur laquel il se trouve
    for(i=0;i<nbPisteur;i++){
        if(tabPisteur[i].vivant==1){
            if(tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x]!=0){
                if(onTrace==0){
                    onTrace=tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x];
                }else if(tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x]<onTrace){
                    onTrace=tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x];
                }
            }
        }
    }
    return onTrace;
}

//BUT:      V�rifie les traces autour du monstre qui sont plus r�cente que laquel il se trouve sur
//ENTREE:   Le monstre, la liste des pisteurs, le nombre de pisteur, la valeur de la trace sur laquel il se trouve, sa nouvelle position
//SORTIE:   Un d�placement du monstre si il trouve une case avec une trace plus r�cente
int checkTraceAutour(str_monstre *monstre, struct str_pisteur tabPisteur[], int nbPisteur, int traceAct, int *xgoto, int *ygoto){
    int xtemp=0;
    int ytemp=0;

    int i=0;

    //V�rifie si les traces autour de lui sont plus r�centes que d'autre
    for(i=0;i<nbPisteur;i++){
        if(tabPisteur[i].vivant==1){
            if(tabPisteur[i].mapTracePisteur[monstre->pos.y-1][monstre->pos.x]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y-1][monstre->pos.x]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y-1][monstre->pos.x];
                xtemp=monstre->pos.x;
                ytemp=monstre->pos.y-1;
            }
            if(tabPisteur[i].mapTracePisteur[monstre->pos.y+1][monstre->pos.x]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y+1][monstre->pos.x]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y+1][monstre->pos.x];
                xtemp=monstre->pos.x;
                ytemp=monstre->pos.y+1;
            }
            if(tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x-1]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x-1]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x-1];
                xtemp=monstre->pos.x-1;
                ytemp=monstre->pos.y;
            }
            if(tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x+1]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x+1]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x+1];
                xtemp=monstre->pos.x+1;
                ytemp=monstre->pos.y;
            }
        }
    }
    //Si aucune trace, pas de mouvement
    if(xtemp==0 && ytemp==0){
        return 0;
    }else{//Si trace, mouvement
        *xgoto=xtemp;
        *ygoto=ytemp;
        return 1;
    }
}

//BUT:      Si le monstre ne trouve aucune trace ni de pisteur, il va donc se d�placer de mani�re random
//ENTREE:   La map des traces du monstre, le monstre, ses positions
//SORTIE:   Une nouvelle position pour le monstre
void deplacementRandom(int mapTraceMonstre[HEIGHTAB][WIDTHTAB], str_monstre *monstre, int *xgoto, int *ygoto){
    srand(time(NULL));
    int sens=0;
    int good=0;

    //D�placement al�atoire avec v�rification si destination est accessible
    do{
        sens=(rand()%(4 + 1 - 1))+1;
        switch(sens){
        case 1:
            if(mapTraceMonstre[monstre->pos.y-1][monstre->pos.x]!=-1 && mapTraceMonstre[monstre->pos.y-1][monstre->pos.x]!=15){
                *xgoto=monstre->pos.x;
                *ygoto=monstre->pos.y-1;
                good=1;
            }
            break;
        case 2:
            if(mapTraceMonstre[monstre->pos.y+1][monstre->pos.x]!=-1 && mapTraceMonstre[monstre->pos.y+1][monstre->pos.x]!=15){
                *xgoto=monstre->pos.x;
                *ygoto=monstre->pos.y+1;
                good=1;
            }
            break;
        case 3:
            if(mapTraceMonstre[monstre->pos.y][monstre->pos.x-1]!=-1 && mapTraceMonstre[monstre->pos.y][monstre->pos.x-1]!=15){
                *xgoto=monstre->pos.x-1;
                *ygoto=monstre->pos.y;
                good=1;
            }
            break;
        case 4:
            if(mapTraceMonstre[monstre->pos.y][monstre->pos.x+1]!=-1 && mapTraceMonstre[monstre->pos.y][monstre->pos.x+1]!=15){
                *xgoto=monstre->pos.x+1;
                *ygoto=monstre->pos.y;
                good=1;
            }
            break;
        }

    }while(good==0);
}
