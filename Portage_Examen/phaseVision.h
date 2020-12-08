#ifndef PHASEVISION_H_INCLUDED
#define PHASEVISION_H_INCLUDED
#include "defineStruct.h"

//prototype
extern void phaseVision(str_pisteur pisteur[], int tabTraceMonstre[HEIGHTAB][WIDTHTAB], int tabTracePisteur[HEIGHTAB][WIDTHTAB]
                        , char tabAff[HEIGHTAB][WIDTHTAB], int nbPisteur, str_monstre *monstre);
extern void doVision(str_pisteur pisteur, int tabTraceMonstre[HEIGHTAB][WIDTHTAB], int tabTracePisteur[HEIGHTAB][WIDTHTAB],
                     char tabAff[HEIGHTAB][WIDTHTAB], str_monstre *monstre);
extern void Tirer(str_monstre *monstre);



#endif // PHASEVISION_H_INCLUDED
