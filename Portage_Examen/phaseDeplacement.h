#ifndef PHASEDEPLACEMENT_H_INCLUDED
#define PHASEDEPLACEMENT_H_INCLUDED
#include "defineStruct.h"

//prototype
extern void phaseDeplacement(str_pisteur tabPisteur[], int tabTrace[HEIGHTAB][WIDTHTAB],int nbPisteur, char mapAffiche[HEIGHTAB][WIDTHTAB]);
extern void doDeplacement(str_pisteur *pisteur, int tabTrace[HEIGHTAB][WIDTHTAB], char mapAffiche[HEIGHTAB][WIDTHTAB]);
extern void addTrace(str_pisteur pisteur, int tabTrace[HEIGHTAB][WIDTHTAB], int sens, int depl);


#endif // PHASEDEPLACEMENT_H_INCLUDED
