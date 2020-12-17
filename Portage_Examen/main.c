#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "defineStruct.h"
#include "phaseInit.h"
#include "phaseVision.h"
#include "phaseDeplacement.h"
#include "phaseMonstre.h"

#include "Affich.h"
#include "voidSDL.h"

#include "trace.h"

#include "endGame.h"



void handleEvents(gameState *state,phase *thePhase,int *pisteurActif, int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB],struct str_pisteur tabPisteur[]);

int main(int argc,char *argv[])
{
    int pisteurActif=-1;

    //Déclaration variable SDL
    gameState state=stop;
    phase thePhase=init;
    renderer tRender;
    listTexture myTexture;

    //Init variable SDL
    tRender.pWindow=NULL;
    tRender.pWindow=CreateWindow("La traque de Monk C",0,40,WIDTHTAB*sizeImage,HEIGHTAB*sizeImage,SDL_WINDOW_SHOWN,tRender.pWindow);
    tRender.pRenderer=CreateRenderer(tRender.pWindow,-1,SDL_RENDERER_PRESENTVSYNC);
    initTexture(tRender.pRenderer,&myTexture);

    //Déclaration des variables
    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];
    int tabTraceVue[HEIGHTAB][WIDTHTAB];//Les traces qui ont été vue de manière temporaire
    char mapAffichage[HEIGHTAB][WIDTHTAB];

    str_monstre monstre;

    int good=0;
    int foundMonst=0;

    //Explication
    printf("Monk C s'est echappe! Nous avons besoin de vous et de votre groupe de pisteur. Combien de pisteur possedez-vous?\n");

    //Initialisation nombre pisteur
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    //Init de map
    initMapTrace(mapTraceMonstre);
    initMapTrace(tabTraceVue);
    initMapAff(mapAffichage);

    printf("Commencez par donner une position a chacun de vos pisteurs.\n");
    for(int i=0;i<nbPisteur;i++){
        initMapTrace(tabPisteur[i].mapTracePisteur);
    }

    AffichageInit(mapAffichage);
    //Initialisation pisteur
    initPisteur(tabPisteur,mapAffichage,nbPisteur);//Ajout sur windows de l'image
    //Initialisation monstre
    initMonstre(&monstre,mapAffichage,mapTraceMonstre);

    printf("Tous vos pisteurs sont en place, la traque peut donc demarrer! \nTrouvez et tuez la creature avant qu'elle ne devore tous vos pisteurs!\n");
    printf("Attention, Monk C possede un odorat tres developpe, lorsqu'il detectera votre presence, il se mettra a votre poursuite!\n");
    system("pause");
    system("cls");

    state=play;
    do{
        handleEvents(&state,&thePhase,&pisteurActif,nbPisteur,mapAffichage,tabPisteur);
        //Vérification si on arrive en phase init, afficher une première fois
        if(thePhase==init){
            thePhase=vision;
        }
        //Check entre passage phase de vision et phase de déplacement
        if(pisteurActif==(nbPisteur-1)){
            if(thePhase==deplacement){
                thePhase=vision;
            }else if(thePhase==vision){

                thePhase=deplacement;
            }
            pisteurActif=-1;
        }
        pisteurActif+=1;
        //Diminue la fraicheur des traces en début de tour de vision
        if(pisteurActif==0 && thePhase==vision){
            deleteTrace(mapTraceMonstre);
        }
        //Faire les actions seulement si le pisteur est vivant
        if(tabPisteur[pisteurActif].vivant==1){
        //Set Color
            SDL_SetRenderDrawColor(tRender.pRenderer,214,190,101,SDL_ALPHA_OPAQUE);
            //Clear Render
            SDL_RenderClear(tRender.pRenderer);
            //Phase Vision
            if(thePhase==vision){
                //Commencer la phase vision d'un pisteur
                printf("C'est le tour de vision du pisteur %d\n", pisteurActif+1);
                doVision(tabPisteur[pisteurActif],mapTraceMonstre,mapAffichage,&monstre, tabTraceVue, &foundMonst);

            }



            //Set modification affichage
            //Marquer le pisteur actif
            if(tabPisteur[pisteurActif].vivant==1){
                mapAffichage[tabPisteur[pisteurActif].pos.y][tabPisteur[pisteurActif].pos.x]='!';
            }


            //Afficher ce qui doit être affiché
            AffichImgSDL(tRender.pRenderer,myTexture,tabTraceVue,mapAffichage);

            //Remettre le pisteur en mode initial
            if(tabPisteur[pisteurActif].vivant==1){
                mapAffichage[tabPisteur[pisteurActif].pos.y][tabPisteur[pisteurActif].pos.x]='P';
            }


            //Afficher
            SDL_RenderPresent(tRender.pRenderer);

            //Si le monstre est là, enclencher le tir
            if(foundMonst==1){
                Tirer(&monstre);
                foundMonst=0;
            }

            //Phase déplacement
            if(thePhase==deplacement){
                //Commencer la phase déplacement d'un pisteur
                printf("C'est le tour de deplacement du pisteur %d\n", pisteurActif+1);
                doDeplacement(&tabPisteur[pisteurActif],mapAffichage);

                //Phase monstre
                if(pisteurActif==nbPisteur-1){
                    initMapTrace(tabTraceVue);
                    phaseMonstre(&monstre,mapTraceMonstre,tabPisteur,mapAffichage,nbPisteur,tabTraceVue);
                }
            }
            //Vérification de la condition de victoire
            CheckEndGame(monstre,tabPisteur,&good,nbPisteur);

            system("pause");
            //Clear screen
            system("cls");
            if(good!=0){
                state=stop;
            }
        }

    }while(state==play);

    if(good==1){
        printf("Vous avez terrasse le monstre!");
    }else if(good==2){
        printf("Le monstre a devore tout vos pisteurs!");
    }

    if(myTexture.pTextureArbre){
        SDL_DestroyTexture(myTexture.pTextureArbre);
    }
    if(myTexture.pTextureMonstre){
        SDL_DestroyTexture(myTexture.pTextureMonstre);
    }
    if(myTexture.pTexturePisteur){
        SDL_DestroyTexture(myTexture.pTexturePisteur);
    }
    if(myTexture.pTextureSang){
        SDL_DestroyTexture(myTexture.pTextureSang);
    }
    if(myTexture.pTextureTrace){
        SDL_DestroyTexture(myTexture.pTextureTrace);
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
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                *state=stop;
                break;
            default:
                break;
        }

    }
}
