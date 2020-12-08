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
    //D�claration des variables
    str_monstre monstre;
    //str_monstre *pmonstre = &monstre;
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    int mapTracePisteur[HEIGHTAB][WIDTHTAB];
    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];

    char mapAffichage[HEIGHTAB][WIDTHTAB];

    //Initialisation
    initMapTrace(mapTraceMonstre);
    initMapTrace(mapTracePisteur);

    initMapAff(mapAffichage);
    AffichageInit(mapAffichage);
    initPisteur(tabPisteur,mapAffichage,nbPisteur);

    initMonstre(&monstre,mapAffichage,mapTraceMonstre);


    //Phase Vision
    /*phaseVision(tabPisteur,mapTraceMonstre,mapTracePisteur,mapAffichage,nbPisteur,&monstre);
    printf("%d",monstre.PV);

    //Pahse D�placement
    phaseDeplacement(tabPisteur,mapTracePisteur,nbPisteur,mapAffichage);
    //AffichageInit(mapAffichage);
    AffichageTrace(mapTracePisteur,mapAffichage);*/
    //printf("%d",tabPisteur[0].pos.y);
    return 0;
}
