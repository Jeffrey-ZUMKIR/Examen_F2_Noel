#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Affich.h"
#include "defineStruct.h"

//BUT:      Afficher le tableau
//ENTREE:   Le tableau
//SORTIE:   Le tableau affiché
void AffichageInit(char tab[HEIGHTAB][WIDTHTAB]){
    /*//if(pRenderer){
        //Set Color
        //SDL_SetRenderDrawColor(pRenderer,205,92,92,SDL_ALPHA_OPAQUE);
        //Clear Render
        //SDL_RenderClear(pRenderer);
        int i=0;
        int j=0;

        for(i=0;i<HEIGHTAB;i++){
            for(j=0;j<WIDTHTAB;j++){
                if(i==0 && j!=0 && j!=WIDTHTAB-1){
                    if(j<10){
                        printf("%d ",j);
                    }else{
                        printf("%d",j);
                    }
                }else if(j==0 && i!=0 && i!=HEIGHTAB-1){
                    if(i<10){
                        printf("%d ",i);
                    }else{
                        printf("%d",i);
                    }
                }else{
                    if(tab[i][j]=='P'){
                        //AffichImgSDL(pRenderer,myTexture.pTexturePisteur,0,0,j,i);
                    }
                    printf("%c ",tab[i][j]);

                }

            }
            printf("\n");
        }
    //}*/

}

//BUT:      Afficher la map de jeu
//ENTREE:   Le tab des traces du monstres et le tab affichage
//SORTIE:   Affichage de la map, des pisteurs et des traces trouvés
void AffichageTrace(int tabTrace[HEIGHTAB][WIDTHTAB],char tabAff[HEIGHTAB][WIDTHTAB]){
    /*int i=0;
    int j=0;
    for(i=0;i<HEIGHTAB;i++){
        for(j=0;j<WIDTHTAB;j++){
            if(tabTrace[i][j]==-1){
                printf("%c ",'*');
            }else if(tabAff[i][j]=='P'){
                printf("%c ",'P');
            }else if(tabAff[i][j]=='!'){
                printf("%c ",'!');
            }else if(tabAff[i][j]=='?'){
                printf("%c ",'?');
            }else if(tabTrace[i][j]=='&'){
                printf("%c ",'&');
            }else if(tabTrace[i][j]==16){
                printf("%c ",'M');
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
    }*/
}
