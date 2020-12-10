#ifndef PHASEDEPLACEMENT_H_INCLUDED
#define PHASEDEPLACEMENT_H_INCLUDED
#include "defineStruct.h"

//prototype

extern void phaseDeplacement(str_pisteur tabPisteur[],int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB],int tabTraceVue[HEIGHTAB][WIDTHTAB],str_monstre monstre);

extern void doDeplacement(str_pisteur *pisteur, char mapAffiche[HEIGHTAB][WIDTHTAB]);

extern void addTrace(str_pisteur *pisteur, int sens, int depl);


#endif // PHASEDEPLACEMENT_H_INCLUDED
