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


}
