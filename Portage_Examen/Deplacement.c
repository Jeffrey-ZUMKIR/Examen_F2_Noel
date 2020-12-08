#include <stdio.h>
#include <stdlib.h>

#include "defineStruct.h"
#include "phaseDeplacement.h"

void phaseDeplacement(str_pisteur tabPisteur[], int tabTrace[HEIGHTAB][WIDTHTAB],int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB]){
        for(int i=0;i<nbPisteur;i++){
            doDeplacement(&tabPisteur[i],tabTrace,mapAffiche);
        }

}

void doDeplacement(str_pisteur *pisteur, int tabTrace[HEIGHTAB][WIDTHTAB], char mapAffiche[HEIGHTAB][WIDTHTAB]){
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
                pisteur->pos.y=1;
                depl=pisteur->pos.y-1;
            }else{
                mapAffiche[pisteur->pos.y-depl][pisteur->pos.x]='P';
                pisteur->pos.y-=depl;
            }
            break;
        case 2:
            if(pisteur->pos.x+depl>=WIDTHTAB){
                mapAffiche[pisteur->pos.y][WIDTHTAB-1]='P';
                pisteur->pos.x=WIDTHTAB-1;
                depl=WIDTHTAB-1-pisteur->pos.x;
            }else{
                mapAffiche[pisteur->pos.y][pisteur->pos.x+depl]='P';
                pisteur->pos.x+=depl;
            }
            break;
        case 3:
            if(pisteur->pos.y+depl>=HEIGHTAB){
                mapAffiche[HEIGHTAB-1][pisteur->pos.x]='P';
                pisteur->pos.y=HEIGHTAB-1;
                depl=HEIGHTAB-1-pisteur->pos.y;
            }else{
                mapAffiche[pisteur->pos.y+depl][pisteur->pos.x]='P';
                pisteur->pos.y+=depl;
            }
            break;
        case 4:
            if(pisteur->pos.x-depl<=0){
                mapAffiche[pisteur->pos.y][1]='P';
                pisteur->pos.x=1;
                depl=pisteur->pos.x-1;
            }else{
                mapAffiche[pisteur->pos.y][pisteur->pos.x-depl]='P';
                pisteur->pos.x-=depl;
            }
            break;
        }
        addTrace(*pisteur,tabTrace,sens,depl);
    }
}

void addTrace(str_pisteur pisteur, int tabTrace[HEIGHTAB][WIDTHTAB], int sens, int depl){
    int i=0;
    switch(sens){
    case 1:
        for(i=1;i<depl+1;i++){
            tabTrace[pisteur.pos.y+i][pisteur.pos.x]=1;
        }
        break;
    case 2:
        for(i=1;i<depl+1;i++){
            tabTrace[pisteur.pos.y][pisteur.pos.x-i]=1;
        }
        break;
    case 3:
        for(i=1;i<depl+1;i++){
            tabTrace[pisteur.pos.y-i][pisteur.pos.x]=1;
        }
        break;
    case 4:
        for(i=1;i<depl+1;i++){
            tabTrace[pisteur.pos.y][pisteur.pos.x+i]=1;
        }
        break;
    }

}
