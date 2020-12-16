#ifndef DEFINESTRUCT_H_INCLUDED
#include <SDL2/SDL.h>
#define DEFINESTRUCT_H_INCLUDED

#define WIDTHTAB 31
#define HEIGHTAB 16

#define sizeImage 25

typedef struct coord{
    int x;
    int y;
}coord;

typedef struct str_pisteur{
    int vivant;
    coord pos;
    int mapTracePisteur[HEIGHTAB][WIDTHTAB];
}str_pisteur;

typedef struct str_monstre{
    int PV;
    coord pos;
    int saignement;
}str_monstre;

typedef struct listTexture{
    SDL_Texture *pTexturePisteur;
    SDL_Texture *pTextureMonstre;
    SDL_Texture *pTextureTrace;
    SDL_Texture *pTextureSang;
    SDL_Texture *pTextureArbre;
}listTexture;

typedef struct renderer{

    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;

}renderer;

//Etats jeu
typedef enum gameState{

    play,
    stop,
    pause

}gameState;

//Etats phase
typedef enum phase{

        init,
        vision,
        deplacement,
        none

}phase;




#endif // DEFINESTRUCT_H_INCLUDED
