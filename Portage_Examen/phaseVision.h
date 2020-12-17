#ifndef PHASEVISION_H_INCLUDED
#define PHASEVISION_H_INCLUDED
#include "defineStruct.h"

//prototype

extern void doVision(str_pisteur pisteur, int tabTraceMonstre[HEIGHTAB][WIDTHTAB],
                     char tabAffiche[HEIGHTAB][WIDTHTAB], str_monstre *monstre,int tabTraceVue[HEIGHTAB][WIDTHTAB],int *foundMonst);
extern void Tirer(str_monstre *monstre);



#endif // PHASEVISION_H_INCLUDED
