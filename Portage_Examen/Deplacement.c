#include <stdio.h>
#include <stdlib.h>

#include "defineStruct.h"
#include "Affich.h"
#include "phaseDeplacement.h"


void phaseDeplacement(str_pisteur tabPisteur[],int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB],int tabTraceVue[HEIGHTAB][WIDTHTAB]){

    for(int i=0;i<nbPisteur;i++){
        mapAffiche[tabPisteur[i].pos.y][tabPisteur[i].pos.x]='?';
        AffichageTrace(tabTraceVue,mapAffiche);
        doDeplacement(&tabPisteur[i],mapAffiche);
        AffichageTrace(tabTraceVue,mapAffiche);
        system("pause");
        system("cls");
    }

}


void doDeplacement(str_pisteur *pisteur, char mapAffiche[HEIGHTAB][WIDTHTAB]){
    int depl=0;
    int sens=0;
    int good=0;


    printf("De combien de case voulez-vous vous deplacer? (0 a 4)\n");
    do{
        scanf("%d",&depl);
        fflush(stdin);
        if(depl>=0 && depl<=4){
            good=1;
        }else{
            printf("Mauvais chiffre.\n");
        }
    }while(good==0);

    if(depl!=0){
        printf("Dans quel sens? (1=haut, 2=droite, 3=bas, 4=gauche)\n");
        good=0;
        do{
            scanf("%d",&sens);
            fflush(stdin);
            if(sens>=1 && sens<=4){
                good=1;
            }else{
                printf("Mauvais chiffre.\n");
            }
        }while(good==0);


        mapAffiche[pisteur->pos.y][pisteur->pos.x]=' ';
        switch(sens) {
        case 1:
            if(pisteur->pos.y-depl<=0){
                mapAffiche[1][pisteur->pos.x]='P';
                depl=pisteur->pos.y-1;
                pisteur->pos.y=1;

            }else{
                mapAffiche[pisteur->pos.y-depl][pisteur->pos.x]='P';
                pisteur->pos.y-=depl;
            }
            break;
        case 2:
            if(pisteur->pos.x+depl>=WIDTHTAB){
                mapAffiche[pisteur->pos.y][WIDTHTAB-1]='P';
                depl=WIDTHTAB-1-pisteur->pos.x;
                pisteur->pos.x=WIDTHTAB-1;

            }else{
                mapAffiche[pisteur->pos.y][pisteur->pos.x+depl]='P';
                pisteur->pos.x+=depl;
            }
            break;
        case 3:
            if(pisteur->pos.y+depl>=HEIGHTAB){
                mapAffiche[HEIGHTAB-1][pisteur->pos.x]='P';
                depl=HEIGHTAB-1-pisteur->pos.y;
                pisteur->pos.y=HEIGHTAB-1;

            }else{
                mapAffiche[pisteur->pos.y+depl][pisteur->pos.x]='P';
                pisteur->pos.y+=depl;
            }
            break;
        case 4:
            if(pisteur->pos.x-depl<=0){
                mapAffiche[pisteur->pos.y][1]='P';
                depl=pisteur->pos.x-1;
                pisteur->pos.x=1;

            }else{
                mapAffiche[pisteur->pos.y][pisteur->pos.x-depl]='P';
                pisteur->pos.x-=depl;
            }
            break;
        }
        printf("depl %d", depl);
        addTrace(pisteur,sens,depl);

    }

    system("cls");
}


void addTrace(str_pisteur *pisteur, int sens, int depl){
    //tabTrace[1][1]=3;
    int i=0;
    for(i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            if(pisteur->mapTracePisteur[i][j]>0){
                pisteur->mapTracePisteur[i][j]=pisteur->mapTracePisteur[i][j]+depl;
            }
        }
    }
    printf("Le depl %d", depl);
    switch(sens){
    case 1:
        for(i=1;i<depl+1;i++){
            pisteur->mapTracePisteur[pisteur->pos.y+i][pisteur->pos.x]=i;
            //printf("valeur :%d", tabTrace[pisteur.pos.y+i][pisteur.pos.x]);
        }
        break;
    case 2:
        for(i=1;i<depl+1;i++){
            pisteur->mapTracePisteur[pisteur->pos.y][pisteur->pos.x-i]=i;
        }
        break;
    case 3:
        for(i=1;i<depl+1;i++){
            pisteur->mapTracePisteur[pisteur->pos.y-i][pisteur->pos.x]=i;
        }
        break;
    case 4:
        for(i=1;i<depl+1;i++){
            pisteur->mapTracePisteur[pisteur->pos.y][pisteur->pos.x+i]=i;
        }
        break;
    }
    for(int i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            printf("%d",pisteur->mapTracePisteur[i][j]);
        }
        printf("\n");
    }
    system("pause");

}
