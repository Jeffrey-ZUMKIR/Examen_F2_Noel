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


void handleEvents(gameState *state,phase *thePhase,int *pisteurActif, int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB],struct str_pisteur tabPisteur[]);

int main(int argc,char *argv[])
{
    int pisteurActif=-1;

    //Déclaration variable SDL
    gameState state=stop;
    phase thePhase=init;

    //Mettre dans un type struct
    renderer tRender;

    listTexture myTexture;

    tRender.pWindow=NULL;
    tRender.pWindow=CreateWindow("La traque de Monk C",475,50,WIDTHTAB*sizeImage,HEIGHTAB*sizeImage,SDL_WINDOW_SHOWN,tRender.pWindow);
    tRender.pRenderer=CreateRenderer(tRender.pWindow,-1,SDL_RENDERER_PRESENTVSYNC);

    initTexture(tRender.pRenderer,&myTexture);

    //Déclaration des variables
    str_monstre monstre;

    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];
    int tabTraceVue[HEIGHTAB][WIDTHTAB];//Les traces qui ont été vue de manière temporaire

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
        handleEvents(&state,&thePhase,&pisteurActif,nbPisteur,mapAffichage,tabPisteur);

        /*if(thePhase==init){
            thePhase=vision;

        }
        if(pisteurActif==(nbPisteur-1)){
            if(thePhase==deplacement){
                printf("Debut vision\n");
                thePhase=vision;
            }else if(thePhase==vision){
                printf("Debut deplacement\n");
                thePhase=deplacement;
            }
            pisteurActif=-1;
        }
        pisteurActif+=1;*/


        //Set Color
        SDL_SetRenderDrawColor(tRender.pRenderer,205,92,92,SDL_ALPHA_OPAQUE);
        //Clear Render
        SDL_RenderClear(tRender.pRenderer);
        //Phase Vision
        if(thePhase==vision){
            if(pisteurActif==0){
                //Diminue la fraicheur des traces
                deleteTrace(mapTraceMonstre);
            }
            printf("C'est le tour du pisteur %d\n", pisteurActif);
            doVision(tabPisteur[pisteurActif],mapTraceMonstre,mapAffichage,&monstre, tabTraceVue);
        }

        if(thePhase==deplacement){
            if(pisteurActif==0){
                initMapTrace(tabTraceVue);
            }
            printf("C'est le tour de deplacement du pisteur %d\n", pisteurActif);
            doDeplacement(&tabPisteur[pisteurActif],mapAffichage);
            if(pisteurActif==nbPisteur-1){
                phaseMonstre(&monstre,mapTraceMonstre,tabPisteur,mapAffichage,nbPisteur,tabTraceVue);
            }
        }
        //Vérification de la condition de victoire
        //CheckEndGame(monstre,tabPisteur,&good,nbPisteur);



        //Phase Deplacement
        //Clear plus nouvelle emplacement
        //Reset les traces vues

        //Phase monstre


        //clear + ajout pisteur si vivant

        //Set modification affichage

        AffichImgSDL(tRender.pRenderer,myTexture,tabTraceVue,mapAffichage);
        SDL_RenderPresent(tRender.pRenderer);

        system("pause");
        //SDL_FlushEvent(SDL_WINDOWEVENT);
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


void handleEvents(gameState *state,phase *thePhase,int *pisteurActif, int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB],struct str_pisteur tabPisteur[]){

    SDL_Event event;
    fflush(stdin);
    printf("CC\n");
    if(SDL_PollEvent(&event)){
        printf("Le pisteur actif %d\n", *pisteurActif);

        if(*thePhase==init){
            *thePhase=vision;

        }

        if(*pisteurActif==(nbPisteur-1)){
            if(*thePhase==deplacement){
                printf("Debut vision\n");
                *thePhase=vision;
            }else if(*thePhase==vision){
                printf("Debut deplacement\n");
                *thePhase=deplacement;
            }
            *pisteurActif=-1;
        }
        *pisteurActif+=1;

    }
    SDL_FlushEvent(SDL_WINDOWEVENT);




}
