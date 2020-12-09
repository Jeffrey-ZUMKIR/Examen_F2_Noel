#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "defineStruct.h"
#include "phaseMonstre.h"
#include "trace.h"

void phaseMonstre(str_monstre *monstre, int tabTraceM[HEIGHTAB][WIDTHTAB], struct str_pisteur tabPisteur[], char mapAffiche[HEIGHTAB][WIDTHTAB],int nbPisteur,int tabTraceVue[HEIGHTAB][WIDTHTAB]){
    //checkAutour();
    int xgoto=0;
    int ygoto=0;

    int trace=0;
    int traceAutour=0;

    if(monstre->PV>0){
        if(checkAutour(monstre,mapAffiche,&xgoto,&ygoto)==1){
            if(monstre->saignement>0){
                tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
            }
            monstre->pos.x=xgoto;
            monstre->pos.y=ygoto;
            tabTraceM[ygoto][xgoto]=17;
            mapAffiche[ygoto][xgoto]=' ';
            for(int i=0;i<nbPisteur;i++){
                if(tabPisteur[i].pos.x==xgoto && tabPisteur[i].pos.y==ygoto){
                    printf("Le monstre a devore le pisteur numero %d!",i+1);
                    tabPisteur[i].vivant=0;
                }
            }
        }else {
            trace=checkTraceActuelle(monstre,tabPisteur,nbPisteur);
            if(trace==0){
                traceAutour=checkTraceAutour(monstre,tabPisteur,nbPisteur,500,&xgoto,&ygoto);
            }else{
                traceAutour=checkTraceAutour(monstre,tabPisteur,nbPisteur,trace,&xgoto,&ygoto);
            }

            if(traceAutour==0){
                //random
                deplacementRandom(tabTraceM,monstre,&xgoto,&ygoto);
                if(monstre->saignement>0){
                    tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
                }
                monstre->pos.x=xgoto;
                monstre->pos.y=ygoto;
                tabTraceM[ygoto][xgoto]=17;

            }else if(traceAutour==1){
                //deplacement sur la case + check si personne autour
                if(monstre->saignement>0){
                    tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
                }
                monstre->pos.x=xgoto;
                monstre->pos.y=ygoto;
                /*if(checkAutour(monstre,mapAffiche,&xgoto,&ygoto)==1){
                    monstre->pos.x=xgoto;
                    monstre->pos.y=ygoto;
                }*/
                tabTraceM[ygoto][xgoto]=17;
                //mapAffiche[ygoto][xgoto]=' ';
                /*for(int i=0;i<nbPisteur;i++){
                    if(tabPisteur[i].pos.x==xgoto && tabPisteur[i].pos.y==ygoto){
                        tabPisteur[i].vivant=0;
                    }
                }*/

            }
            if(checkAutour(monstre,mapAffiche,&xgoto,&ygoto)==1){
                deleteTrace(tabTraceM);
                if(monstre->saignement>0){
                    tabTraceVue[monstre->pos.y][monstre->pos.x]='&';
                }
                monstre->pos.x=xgoto;
                monstre->pos.y=ygoto;
                tabTraceM[ygoto][xgoto]=17;
                mapAffiche[ygoto][xgoto]=' ';
                for(int i=0;i<nbPisteur;i++){
                    if(tabPisteur[i].pos.x==xgoto && tabPisteur[i].pos.y==ygoto){
                        printf("Le monstre a devore le pisteur numero %d!",i);
                        tabPisteur[i].vivant=0;
                    }
                }
            }

        }
    }
}


int checkAutour(str_monstre *monstre, char mapAffiche[HEIGHTAB][WIDTHTAB], int *xgoto, int *ygoto){
    int found=0;
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

int checkTraceActuelle(str_monstre *monstre, struct str_pisteur tabPisteur[], int nbPisteur){
    int onTrace=0;

    for(int i=0;i<nbPisteur;i++){
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

int checkTraceAutour(str_monstre *monstre, struct str_pisteur tabPisteur[], int nbPisteur, int traceAct, int *xgoto, int *ygoto){
    int xtemp=0;
    int ytemp=0;

    for(int i=0;i<nbPisteur;i++){
        if(tabPisteur[i].vivant==1){
            if(tabPisteur[i].mapTracePisteur[monstre->pos.y-1][monstre->pos.x]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y-1][monstre->pos.x]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y-1][monstre->pos.x];
                printf("J'ai trouvé une piste\n");
                xtemp=monstre->pos.x;
                ytemp=monstre->pos.y-1;
            }else if(tabPisteur[i].mapTracePisteur[monstre->pos.y+1][monstre->pos.x]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y+1][monstre->pos.x]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y+1][monstre->pos.x];
                xtemp=monstre->pos.x;
                ytemp=monstre->pos.y+1;
            }
            else if(tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x-1]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x-1]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x-1];
                xtemp=monstre->pos.x-1;
                ytemp=monstre->pos.y;
            }
            else if(tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x+1]>0 && tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x+1]<traceAct){
                traceAct=tabPisteur[i].mapTracePisteur[monstre->pos.y][monstre->pos.x+1];
                xtemp=monstre->pos.x+1;
                ytemp=monstre->pos.y;
            }
        }
    }
    if(xtemp==0 && ytemp==0){
        return 0;
    }else{
        *xgoto=xtemp;
        *ygoto=ytemp;
        return 1;
    }
}


void deplacementRandom(int mapTraceMonstre[HEIGHTAB][WIDTHTAB], str_monstre *monstre, int *xgoto, int *ygoto){
    srand(time(NULL));
    int sens=0;
    int good=0;

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
