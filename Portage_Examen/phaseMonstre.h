#ifndef PHASEMONSTRE_H_INCLUDED
#define PHASEMONSTRE_H_INCLUDED
#include "defineStruct.h"

extern void phaseMonstre(str_monstre *monstre, int tabTraceM[HEIGHTAB][WIDTHTAB], struct str_pisteur tabPisteur[], char mapAffiche[HEIGHTAB][WIDTHTAB],int nbPisteur,int tabTraceVue[HEIGHTAB][WIDTHTAB]);
extern int checkAutour(str_monstre *monstre, char mapAffiche[HEIGHTAB][WIDTHTAB], int *xgoto, int *ygoto);
extern int checkTraceActuelle(str_monstre *monstre, struct str_pisteur tabPisteur[], int nbPisteur);
extern int checkTraceAutour(str_monstre *monstre, struct str_pisteur tabPisteur[], int nbPisteur, int traceAct, int *xgoto, int *ygoto);
extern void deplacementRandom(int mapTraceMonstre[HEIGHTAB][WIDTHTAB], str_monstre *monstre, int *xgoto, int *ygoto);

#endif // PHASEMONSTRE_H_INCLUDED
