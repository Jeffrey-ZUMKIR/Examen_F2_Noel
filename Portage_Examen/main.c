#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "phaseInit.h"
#include "defineStruct.h"
#include "phaseVision.h"
#include "Affich.h"

int main(int argc,char *argv[])
{
    //Déclaration des variables
    str_monstre monstre;
    //str_monstre *pmonstre = &monstre;
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];
    int tabTraceVue[HEIGHTAB][WIDTHTAB];//Les traces qui ont été vue de manière temporaire

    char mapAffichage[HEIGHTAB][WIDTHTAB];

    //Initialisation
    initMapTrace(mapTraceMonstre);
    for(int i=0;i<nbPisteur;i++){
        initMapTrace(tabPisteur[i].mapTracePisteur);
    }

    initMapTrace(tabTraceVue);

    initMapAff(mapAffichage);
    AffichageInit(mapAffichage);
    initPisteur(tabPisteur,mapAffichage,nbPisteur);

    initMonstre(&monstre,mapAffichage,mapTraceMonstre);
    system("cls");
    //AffichageTrace(tabTraceVue,mapAffichage);
    //Phase Vision
    phaseVision(tabPisteur,mapTraceMonstre,mapAffichage,nbPisteur,&monstre,tabTraceVue);
    //Pahse Déplacement


    phaseDeplacement(tabPisteur,nbPisteur,mapAffichage,tabTraceVue);



    //AffichageInit(mapAffichage);
    //AffichageTrace(mapTracePisteur,mapAffichage);
    //printf("%d",tabPisteur[0].pos.y);

    /*do{
        initMapTrace(tabTraceVue);

    }while;*/
    return 0;
}
