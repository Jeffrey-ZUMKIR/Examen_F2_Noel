#include <stdio.h>
#include <stdlib.h>

#include "defineStruct.h"
#include "Affich.h"
#include "phaseDeplacement.h"

//BUT:      Enclencher la d�placement de chaque pisteur
//ENTREE:   La liste des pisteurs, le nombre de pisteur, la map � afficher, les traces appercus par les pisteurs
//SORTIE:   Phase de d�placement de pisteur termin�
void phaseDeplacement(str_pisteur tabPisteur[],int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB],int tabTraceVue[HEIGHTAB][WIDTHTAB],str_monstre monstre){
    if(monstre.PV>0){
        for(int i=0;i<nbPisteur;i++){
            if(tabPisteur[i].vivant==1){
                //Indiquer quel pisteur veut se d�placer
                mapAffiche[tabPisteur[i].pos.y][tabPisteur[i].pos.x]='?';
                //Afficher la map
                AffichageTrace(tabTraceVue,mapAffiche);
                //D�placer le pisteur
                doDeplacement(&tabPisteur[i],mapAffiche);
                //Afficher la modification
                AffichageTrace(tabTraceVue,mapAffiche);
                system("pause");
                system("cls");
            }
        }
    }


}

//BUT:      Faire d�placer un pisteur
//ENTREE:   Le pisteur, la map � afficher
//SORTIE:   Le pisteur d�plac�
void doDeplacement(str_pisteur *pisteur, char mapAffiche[HEIGHTAB][WIDTHTAB]){
    int depl=0;//Nombre de case d�plac�
    int sens=0;//Sens pris
    int good=0;//Booleen de v�rification

    int xtemp;//Coordonn� x temporaire
    int ytemp;//Coordonn� y temporaire

    //Faire tant que la zone ou se d�placer est d�j� utiliser par un pisteur
    do{
        xtemp=pisteur->pos.x;//Donner les coordonn�es aux variables temporaires
        ytemp=pisteur->pos.y;

        printf("De combien de case voulez-vous vous deplacer? (0 a 4)\n");
        do{//Faire tant que le nombre de pas re�u est plus petit que 0 ou plus grand que 4
            scanf("%d",&depl);
            fflush(stdin);
            if(depl>=0 && depl<=4){
                good=1;
            }else{
                printf("Mauvais chiffre.\n");
            }
        }while(good==0);

        //Si pas de d�placement, pas besoin de savoir le sens de d�placement
        if(depl!=0){
            printf("Dans quel sens? (1=haut, 2=droite, 3=bas, 4=gauche)\n");
            //Aide visuel pour le sens
            printf("%c ",' ');
            printf("%d ",1);
            printf("%c\n",' ');
            printf("%d ",4);
            printf("%c ",'P');
            printf("%d\n",2);
            printf("%c ",' ');
            printf("%d ",3);
            printf("%c\n",' ');
            good=0;
            do{//Faire tant que le nombre pour le sens donner est plus petit que 1 ou plus grand que 4
                scanf("%d",&sens);
                fflush(stdin);
                if(sens>=1 && sens<=4){
                    good=1;
                }else{
                    printf("Mauvais chiffre.\n");
                }
            }while(good==0);

            good=0;
            mapAffiche[pisteur->pos.y][pisteur->pos.x]=' ';
            //Donne une nouvelle posisition en fonction du sens
            switch(sens) {
            case 1:
                //Si le d�placement faire sortir le pisteur, retirer autant pour que le pisteur reste dans le cadre
                if(pisteur->pos.y-depl<=0){
                    depl=ytemp-1;
                    ytemp=1;
                }else{
                    ytemp-=depl;
                }
                break;
            case 2:
                if(pisteur->pos.x+depl>=WIDTHTAB){
                    depl=WIDTHTAB-1-xtemp;
                    xtemp=WIDTHTAB-1;

                }else{
                    xtemp+=depl;
                }
                break;
            case 3:
                if(pisteur->pos.y+depl>=HEIGHTAB){
                    depl=HEIGHTAB-1-ytemp;
                    ytemp=HEIGHTAB-1;

                }else{
                    ytemp+=depl;
                }
                break;
            case 4:
                if(pisteur->pos.x-depl<=0){
                    depl=xtemp-1;
                    xtemp=1;

                }else{
                    xtemp-=depl;
                }
                break;
            }
            //V�rification si un autre pisteur se trouve d�j� sur cette case
            if(mapAffiche[ytemp][xtemp]!='P'){
                good=1;
            }
        }
    }while(good==0);
    //Pose le joueur au nouvel emplacement
    mapAffiche[ytemp][xtemp]='P';
    //Donne les nouvelles coordonn�es
    pisteur->pos.x=xtemp;
    pisteur->pos.y=ytemp;

    //Ajoute les traces laiss�s par le pisteur lors de son d�placement
    addTrace(pisteur,sens,depl);

    system("cls");
}

//BUT:      Ajouter les traces de pas du pisteur derri�re lui
//ENTREE:   Le pisteur, le sens et le d�placement
//SORTIE:   Ajout de straces de pas
void addTrace(str_pisteur *pisteur, int sens, int depl){
    int i=0;
    //Ajout de l'anciennete sur les anciennes trace pour aller avec les nouvelles
    for(i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            if(pisteur->mapTracePisteur[i][j]>0){
                pisteur->mapTracePisteur[i][j]=pisteur->mapTracePisteur[i][j]+depl;
            }
        }
    }
    //Ajout des traces en fonction du sens
    switch(sens){
    case 1:
        for(i=1;i<depl+1;i++){
            pisteur->mapTracePisteur[pisteur->pos.y+i][pisteur->pos.x]=i;
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

}
