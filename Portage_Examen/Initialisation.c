#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "phaseInit.h"
#include "defineStruct.h"
#include "Affich.h"

#define NBMAXPIS 10
#define NBMINPIS 1

//BUT:      Savoir le nombre de pisteur présent durant cette partie
//ENTREE:   /
//SORTIE:   Le nombre de pisteur
int nombrePisteur(){
    int good=0;
    int nbPisteur=0;
    //Demander le nombre de pisteur
    do{
        printf("Veuillez choisir un nombre de pisteur (entre 1 et 10) :\n");
        scanf("%d",&nbPisteur);
        //Vérifie si ce trouve dans la limite de pisteur
        if(nbPisteur>=NBMINPIS && nbPisteur<=NBMAXPIS){
            good=1;
        }else{
            printf("Veuillez saisir un autre nombre de pisteur!\n");
        }
        fflush(stdin);
    }while(good==0);
    return nbPisteur;
}

//BUT:      Initialiser les variables de pisteur et leur positon
//ENTREE:   La liste des pisteurs, le tableau à afficher, le nombre de pisteur
//SORTIE:   La liste de pisteur initialisé et les pisteurs positionnés
void initPisteur(struct str_pisteur tabPisteur[],char mapAffich[HEIGHTAB][WIDTHTAB],int nbPisteur){
    int good=0;
    int ok=0;
    int x=0;
    int y=0;
    int i=0;
    //Initialiser chaque pisteur
    for(i=0;i<nbPisteur;i++){
        tabPisteur[i].vivant=1;
        //demander les coordonnes du pisteur
        printf("Ou souhaitez-vous placer le pisteur numero %d ?\n",i+1);
        do{
            //Vérif si x se trouve dans le cadre
            do{
                printf("Dans quel colonne?\n");
                scanf("%d",&x);
                if(x>0 && x<WIDTHTAB){
                    ok=1;
                }else{
                    printf("Cette colonne n'existe pas!\n");
                }
                fflush(stdin);
            }while(ok==0);
            ok=0;
            //Vérif si y se trouve dans le cadre
            do{
                printf("Dans quel ligne?\n");
                scanf("%d",&y);
                if(y>0 && y<HEIGHTAB){
                    ok=1;
                }else{
                    printf("Cette ligne n'existe pas!\n");
                }
                fflush(stdin);
            }while(ok==0);
            //Vérif si un pisteur si trouve déjà
            if(mapAffich[y][x]!='P'){
                mapAffich[y][x]='P';
                tabPisteur[i].pos.x=x;
                tabPisteur[i].pos.y=y;
                good=1;
            }

        }while(good==0);
        good=0;
        system("cls");
        //Afficher la map avec le pisteur
        AffichageInit(mapAffich);
    }
}

//BUT:      Initialiser le tableau à afficher
//ENTREE:   Le tableau
//SORTIE:   Le tableau initialiser
void initMapAff(char tab[HEIGHTAB][WIDTHTAB]){
    int i=0;
    int j=0;
    for(i=0;i<HEIGHTAB;i++){
        for(j=0;j<WIDTHTAB;j++){
            //Poser le cadre
            if((i==0)||(j==0)||(i==HEIGHTAB-1)||(j==WIDTHTAB-1)){
                tab[i][j]='*';
            }else{
                tab[i][j]=' ';
            }
        }
    }
}

//BUT:      Initialiser les maps avec les traces
//ENTREE:   Les tabs des traces
//SORTIE:   Les tabs des traces initialisés
void initMapTrace(int tab[HEIGHTAB][WIDTHTAB]){
    int i=0;
    int j=0;
    for(i=0;i<HEIGHTAB;i++){
        for(j=0;j<WIDTHTAB;j++){
            //Poser le cadre
            if((i==0)||(j==0)||(i==HEIGHTAB-1)||(j==WIDTHTAB-1)){
                tab[i][j]=-1;
            }else{
                tab[i][j]=0;
            }
        }
    }
}

//BUT:      Initialiser la variable du monstre
//ENTREE:   Le monstre
//SORTIE:   Le monstre initialiser
void initMonstre(str_monstre *monstre,char tab[HEIGHTAB][WIDTHTAB],int mapTraceMonstre[HEIGHTAB][WIDTHTAB]){
    monstre->PV=4;
    monstre->saignement=0;

    srand(time(NULL));

    int Min=1;
    int MaxX=WIDTHTAB-2;
    int MaxY=HEIGHTAB-2;

    int x=0;
    int y=0;
    int good=0;
    do{
        x=(rand()%(MaxX + 1 - Min))+Min;
        y=(rand()%(MaxY + 1 - Min))+Min;
        //x=6;
        //y=6;

        good=1;
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(tab[y+i][x+j]=='P'){
                    good=0;
                }
            }
        }
        if(good==1){
            tab[y][x]='M';
            mapTraceMonstre[y][x]=17;
            monstre->pos.x=x;
            monstre->pos.y=y;
        }
    }while(good==0);
}

//BUT:      Créer une fenêtre
//ENTREE:   Le titre, la position x et y, la hauteur, la largeur et le drapeau
//SORTIE:   Une fenêtre
SDL_Window *CreateWindow(const char* title, int x, int y, int w, int h, Uint32 windowFlag,SDL_Window *pWindow){
    //SDL_Window *pWindow;
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        //Afficher les erreurs arrivés
        SDL_Log("Unbale to initialize SDL: %s", SDL_GetError());
        //Détruire toute les données relatives à la SDL
        SDL_Quit();
        //Sortir du programme
        //return 1;
    }else{
        //Création d'une fenêtre
        pWindow=SDL_CreateWindow(title,x,y,w,h,windowFlag);
    }
    return pWindow;
}

//BUT:      Créer un renderer
//ENTREE:   La fenêtre, un index et un drapeau
//SORTIE:   Un renderer
SDL_Renderer *CreateRenderer(SDL_Window *pWindow, int index, Uint32 flags){
    SDL_Renderer *pRenderer=NULL;
    if(pWindow){
        pRenderer=SDL_CreateRenderer(pWindow,index,flags);
        return pRenderer;
    }
    return pRenderer;
}

//BUT:      Initialiser les textures pour chacune des images
//ENTREE:   Le renderer et la liste des textures
//SORTIE:   Les textures initialisées
void initTexture(SDL_Renderer *pRenderer, listTexture *myTexture){
    SDL_Surface *pSurface=NULL;
    pSurface=IMG_Load("./assets/pisteur.png");
    //Set image pisteur
    if(!pSurface){
        SDL_Log("Unable to set surface: %s", SDL_GetError());
        //return 1;
    }else{
        myTexture->pTexturePisteur=SDL_CreateTextureFromSurface(pRenderer,pSurface);
        SDL_FreeSurface(pSurface);

        //Si pas de reference
        if(!myTexture->pTexturePisteur){
            SDL_Log("Unable to set texture: %s", SDL_GetError());
            //return 1;
        }
    }
    //Set image monstre
    pSurface=IMG_Load("./assets/Monk_C.png");
    if(!pSurface){
        SDL_Log("Unable to set surface: %s", SDL_GetError());
        //return 1;
    }else{
        myTexture->pTextureMonstre=SDL_CreateTextureFromSurface(pRenderer,pSurface);
        SDL_FreeSurface(pSurface);

        //Si pas de reference
        if(!myTexture->pTextureMonstre){
            SDL_Log("Unable to set texture: %s", SDL_GetError());
            //return 1;
        }
    }
    //Set image trace
    pSurface=IMG_Load("./assets/Trace.png");
    if(!pSurface){
        SDL_Log("Unable to set surface: %s", SDL_GetError());
        //return 1;
    }else{
        myTexture->pTextureTrace=SDL_CreateTextureFromSurface(pRenderer,pSurface);
        SDL_FreeSurface(pSurface);

        //Si pas de reference
        if(!myTexture->pTextureTrace){
            SDL_Log("Unable to set texture: %s", SDL_GetError());
            //return 1;
        }
    }
    //Set image sang
    pSurface=IMG_Load("./assets/Blood.png");
    if(!pSurface){
        SDL_Log("Unable to set surface: %s", SDL_GetError());
        //return 1;
    }else{
        myTexture->pTextureSang=SDL_CreateTextureFromSurface(pRenderer,pSurface);
        SDL_FreeSurface(pSurface);

        //Si pas de reference
        if(!myTexture->pTextureSang){
            SDL_Log("Unable to set texture: %s", SDL_GetError());
            //return 1;
        }
    }
    //Set image arbre
    pSurface=IMG_Load("./assets/Arbre.png");
    if(!pSurface){
        SDL_Log("Unable to set surface: %s", SDL_GetError());
        //return 1;
    }else{
        myTexture->pTextureArbre=SDL_CreateTextureFromSurface(pRenderer,pSurface);
        SDL_FreeSurface(pSurface);

        //Si pas de reference
        if(!myTexture->pTextureArbre){
            SDL_Log("Unable to set texture: %s", SDL_GetError());
            //return 1;
        }
    }

}
