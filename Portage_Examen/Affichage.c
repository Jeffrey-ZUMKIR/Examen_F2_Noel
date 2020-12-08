#include <stdio.h>
#include <stdlib.h>

#include "phaseInit.h"
#include "defineStruct.h"

//BUT:      Afficher le tableau
//ENTREE:   Le tableau
//SORTIE:   Le tableau affiché
void AffichageInit(char tab[HEIGHTAB][WIDTHTAB]){
    for(int i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            printf("%c ",tab[i][j]);
        }
        printf("\n");
    }
}

//BUT:      Afficher la map de jeu
//ENTREE:   Le tab des traces du monstres et le tab affichage
//SORTIE:   Affichage de la map, des pisteurs et des traces trouvés
void AffichageTrace(int tabTrace[HEIGHTAB][WIDTHTAB],char tabAff[HEIGHTAB][WIDTHTAB]){
    for(int i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            if(tabTrace[i][j]==-1){
                printf("%c ",'*');
            }else if(tabAff[i][j]=='P'){
                printf("%c ",'P');
            }else if(tabAff[i][j]=='!'){
                printf("%c ",'!');
            }else if(tabAff[i][j]=='?'){
                printf("%c ",'?');
            }else if(tabTrace[i][j]>0){
                if(tabTrace[i][j]<10){
                    printf("%d ",tabTrace[i][j]);
                }else{
                    printf("%d",tabTrace[i][j]);
                }
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
}
