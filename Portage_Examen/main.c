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

int main(int argc,char *argv[])
{
    //D�claration des variables
    str_monstre monstre;
    //str_monstre *pmonstre = &monstre;
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];
    int tabTraceVue[HEIGHTAB][WIDTHTAB];//Les traces qui ont �t� vue de mani�re temporaire

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
    //phaseVision(tabPisteur,mapTraceMonstre,mapAffichage,nbPisteur,&monstre,tabTraceVue);
    //Phase D�placement


    //phaseDeplacement(tabPisteur,nbPisteur,mapAffichage,tabTraceVue);

    //Phase monstre




    //AffichageInit(mapAffichage);
    //AffichageTrace(mapTracePisteur,mapAffichage);
    //printf("%d",tabPisteur[0].pos.y);
    int good=0;
    do{
        deleteTrace(mapTraceMonstre);

        phaseVision(tabPisteur,mapTraceMonstre,mapAffichage,nbPisteur,&monstre,tabTraceVue);

        phaseDeplacement(tabPisteur,nbPisteur,mapAffichage,tabTraceVue);
        initMapTrace(tabTraceVue);
        phaseMonstre(&monstre,mapTraceMonstre,tabPisteur,mapAffichage,nbPisteur,tabTraceVue);
        //printf("x: %d ",monstre.pos.x);
        //printf("y: %d\n",monstre.pos.y);
        //AffichageTrace(tabPisteur[0].mapTracePisteur,mapAffichage);
        //AffichageTrace(mapTraceMonstre,mapAffichage);
        system("pause");
        system("cls");
    }while(good==0);
    return 0;
}
