#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "phaseInit.h"
#include "defineStruct.h"

int main(int argc,char *argv[])
{
    str_monstre monstre;
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    int mapTracePisteur[HEIGHTAB][WIDTHTAB];
    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];

    char mapAffichage[HEIGHTAB][WIDTHTAB];

    initMapAff(mapAffichage);
    Affichage(mapAffichage);
    initPisteur(tabPisteur,mapAffichage,nbPisteur);

    initMonstre(&monstre,mapAffichage);
    //Affichage(mapAffichage);

    return 0;
}
