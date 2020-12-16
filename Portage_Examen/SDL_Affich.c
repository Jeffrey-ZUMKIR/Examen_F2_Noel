#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "voidSDL.h"
#include "defineStruct.h"

void AffichImgSDL(SDL_Renderer *pRenderer,listTexture myTexture,int tabTrace[HEIGHTAB][WIDTHTAB],char tabAff[HEIGHTAB][WIDTHTAB]){
    SDL_Rect rectSource={0,0,25,25};
    SDL_Rect rectDest={0,0,25,25};
    int i=0;
    int j=0;
    //Afficher les bonnes textures en fonction de ce qui doit être affiché
    for(i=0;i<HEIGHTAB;i++){
        for(j=0;j<WIDTHTAB;j++){
            if(tabTrace[i][j]==-1){
                rectSource.x=0;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTextureArbre,&rectSource,&rectDest);
            }else if(tabAff[i][j]=='P'){
                //printf("%c ",'P');
                rectSource.x=0;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTexturePisteur,&rectSource,&rectDest);
            }else if(tabAff[i][j]=='!'){
                //printf("%c ",'!');
                rectSource.x=25;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTexturePisteur,&rectSource,&rectDest);
            }else if(tabAff[i][j]=='?'){
                //printf("%c ",'?');
                rectSource.x=50;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTexturePisteur,&rectSource,&rectDest);
            }else if(tabTrace[i][j]=='&'){
                //printf("%c ",'&');
                rectSource.x=0;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTextureSang,&rectSource,&rectDest);
            }else if(tabTrace[i][j]==16){
                //printf("%c ",'M');
                rectSource.x=0;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTextureMonstre,&rectSource,&rectDest);
            }else if(tabTrace[i][j]>0){
                rectSource.x=0;
                rectDest.x=j*sizeImage;
                rectDest.y=i*sizeImage;
                SDL_RenderCopy(pRenderer,myTexture.pTextureTrace,&rectSource,&rectDest);
            }
        }
    }
    /*SDL_Rect rectSource={source_x,source_y,sizeImage,sizeImage};
    SDL_Rect rectDest={dest_x*sizeImage,dest_y*sizeImage,sizeImage,sizeImage};
    SDL_RenderCopy(pRenderer,pTexture,&rectSource,&rectDest);*/
}
