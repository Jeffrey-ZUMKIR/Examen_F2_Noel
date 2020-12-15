#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "phaseInit.h"
#include "defineStruct.h"
#include "phaseVision.h"
#include "phaseDeplacement.h"
#include "Affich.h"
#include "phaseMonstre.h"
#include "trace.h"
#include "endGame.h"
#include "voidSDL.h"


void handleEvents(gameState *state,phase *thePhase);

int main(int argc,char *argv[])
{
    //D�claration variable SDL
    gameState state=stop;
    phase thePhase=none;

    //Mettre dans un type struct
    renderer tRender;

    listTexture myTexture;

    tRender.pWindow=NULL;
    tRender.pWindow=CreateWindow("La traque de Monk C",475,50,WIDTHTAB*sizeImage,HEIGHTAB*sizeImage,SDL_WINDOW_SHOWN,tRender.pWindow);
    tRender.pRenderer=CreateRenderer(tRender.pWindow,-1,SDL_RENDERER_PRESENTVSYNC);

    initTexture(tRender.pRenderer,&myTexture);

    //D�claration des variables
    str_monstre monstre;

    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];
    int tabTraceVue[HEIGHTAB][WIDTHTAB];//Les traces qui ont �t� vue de mani�re temporaire

    char mapAffichage[HEIGHTAB][WIDTHTAB];
    int good=0;

    //Explication
    printf("Monk C s'est echappe! Nous avons besoin de vous et de votre groupe de pisteur. Combien de pisteur possedez-vous?\n");
    //Initialisation
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    initMapTrace(mapTraceMonstre);
    printf("Commencez par donner une position a chacun de vos pisteurs.\n");
    for(int i=0;i<nbPisteur;i++){
        initMapTrace(tabPisteur[i].mapTracePisteur);
    }
    initMapTrace(tabTraceVue);
    initMapAff(mapAffichage);

    AffichageInit(mapAffichage);

    initPisteur(tabPisteur,mapAffichage,nbPisteur);//Ajout sur windows de l'image

    initMonstre(&monstre,mapAffichage,mapTraceMonstre);

    printf("Tous vos pisteurs sont en place, la traque peut donc demarrer! \nTrouvez et tuez la creature avant qu'elle ne devore tous vos pisteurs!\n");
    printf("Attention, Monk C possede un odorat tres developpe, lorsqu'il detectera votre presence, il se mettra a votre poursuite!\n");
    system("pause");
    system("cls");

    state=play;
    do{
        handleEvents(&state,&thePhase);
        //Set Color
        SDL_SetRenderDrawColor(tRender.pRenderer,205,92,92,SDL_ALPHA_OPAQUE);
        //Clear Render
        SDL_RenderClear(tRender.pRenderer);

        //Diminue la fraicheur des traces
        deleteTrace(mapTraceMonstre);//Une seul fois
        //Phase Vision
        phaseVision(tabPisteur,mapTraceMonstre,mapAffichage,nbPisteur,&monstre,tabTraceVue);//Modification de l'image+ajout trace



        //Phase Deplacement
        phaseDeplacement(tabPisteur,nbPisteur,mapAffichage,tabTraceVue,monstre);//Clear plus nouvelle emplacement
        //Reset les traces vues
        initMapTrace(tabTraceVue);
        //Phase monstre
        phaseMonstre(&monstre,mapTraceMonstre,tabPisteur,mapAffichage,nbPisteur,tabTraceVue);
        //V�rification de la condition de victoire
        CheckEndGame(monstre,tabPisteur,&good,nbPisteur);//clear + ajout pisteur si vivant

        //Set modification affichage
        AffichImgSDL(tRender.pRenderer,myTexture,tabTraceVue,mapAffichage);
        SDL_RenderPresent(tRender.pRenderer);

        system("pause");
        //Clear screen
        system("cls");

        if(good!=0){
            state=stop;
        }

    //Affichage de fin

    }while(state==play);

    if(good==1){
        printf("Vous avez terrasse le monstre!");
    }else if(good==2){
        printf("Le monstre a devore tout vos pisteurs!");
    }
    if(tRender.pRenderer){
        SDL_DestroyRenderer(tRender.pRenderer);
    }

    if(tRender.pWindow){
      SDL_DestroyWindow(tRender.pWindow);
    }

    SDL_Quit();



    return 0;
}


void handleEvents(gameState *state,phase *thePhase){

    SDL_Event event;

    if(SDL_PollEvent(&event)){

        /*switch (event.type){
            case SDL_QUIT : *state=stop;break;
            case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                                case SDLK_LEFT:*control=left;break;
                                case SDLK_RIGHT:*control=right;break;

                        }break;



        default:*control=none;break;
        }*/

    }

}
