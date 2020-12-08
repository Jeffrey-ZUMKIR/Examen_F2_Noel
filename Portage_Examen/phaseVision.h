#ifndef PHASEVISION_H_INCLUDED
#define PHASEVISION_H_INCLUDED
#include "defineStruct.h"

//prototype

extern void phaseVision(str_pisteur tabPisteur[], int tabTraceMonstre[HEIGHTAB][WIDTHTAB], char tabAffiche[HEIGHTAB][WIDTHTAB], int nbPisteur, str_monstre *monstre, int tabTraceVue[HEIGHTAB][WIDTHTAB]);

extern void doVision(str_pisteur pisteur, int tabTraceMonstre[HEIGHTAB][WIDTHTAB],
                     char tabAffiche[HEIGHTAB][WIDTHTAB], str_monstre *monstre,int tabTraceVue[HEIGHTAB][WIDTHTAB]);
extern void Tirer(str_monstre *monstre);



#endif // PHASEVISION_H_INCLUDED
