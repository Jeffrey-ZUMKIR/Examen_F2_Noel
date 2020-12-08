#ifndef PHASEINIT_H_INCLUDED
#define PHASEINIT_H_INCLUDED
#include "defineStruct.h"

//prototype
int nombrePisteur();

//extern void initMapAffBeginning(char tab[HEIGHTAB][WIDTHTAB]);
extern void initMapAff(char tab[HEIGHTAB][WIDTHTAB]);
extern void initPisteur(struct str_pisteur tabPisteur[],char mapAffich[HEIGHTAB][WIDTHTAB],int nbPisteur);

extern void initMonstre(str_monstre *monstre,char tab[HEIGHTAB][WIDTHTAB],int mapTraceMonstre[HEIGHTAB][WIDTHTAB]);
extern void initMapTrace(int tab[HEIGHTAB][WIDTHTAB]);



#endif // PHASEINIT_H_INCLUDED
