#include <stdio.h>
#include <stdlib.h>

#include "phaseInit.h"
#include "defineStruct.h"
#include "phaseVision.h"
#include "phaseDeplacement.h"
#include "Affich.h"
#include "phaseMonstre.h"
#include "trace.h"
#include "endGame.h"

int main(int argc,char *argv[])
{
    //Déclaration des variables
    str_monstre monstre;

    int mapTraceMonstre[HEIGHTAB][WIDTHTAB];
    int tabTraceVue[HEIGHTAB][WIDTHTAB];//Les traces qui ont été vue de manière temporaire

    char mapAffichage[HEIGHTAB][WIDTHTAB];

    //Explication
    printf("Monk C s'est echappe! Nous avons besoin de vous et de votre groupe de pisteur. Combien de pisteur possedez-vous?\n");
    //Initialisation
    int nbPisteur=nombrePisteur();
    struct str_pisteur tabPisteur[nbPisteur];

    initMapTrace(mapTraceMonstre);
    printf("Commencez par donner une position a chacun de vos pisteurs.\n");
    for(int i=0;i<nbPisteur;i++){
        initMapTrace(tabPisteur[i].mapTracePisteur);
    }
    initMapTrace(tabTraceVue);
    initMapAff(mapAffichage);

    AffichageInit(mapAffichage);

    initPisteur(tabPisteur,mapAffichage,nbPisteur);

    initMonstre(&monstre,mapAffichage,mapTraceMonstre);

    printf("Tous vos pisteurs sont en place, la traque peut donc demarrer! \nTrouvez et tuez la creature avant qu'elle ne devore tous vos pisteurs!\n");
    printf("Attention, Monk C possede un odorat tres developpe, lorsqu'il detectera votre presence, il se mettra a votre poursuite!\n");
    system("pause");
    system("cls");

    int good=0;
    do{
        //Diminue la fraicheur des traces
        deleteTrace(mapTraceMonstre);
        //Phase Vision
        phaseVision(tabPisteur,mapTraceMonstre,mapAffichage,nbPisteur,&monstre,tabTraceVue);
        //Phase Deplacement
        phaseDeplacement(tabPisteur,nbPisteur,mapAffichage,tabTraceVue,monstre);
        //Reset les traces vues
        initMapTrace(tabTraceVue);
        //Phase monstre
        phaseMonstre(&monstre,mapTraceMonstre,tabPisteur,mapAffichage,nbPisteur,tabTraceVue);
        //Vérification de la condition de victoire
        CheckEndGame(monstre,tabPisteur,&good,nbPisteur);
        system("pause");
        //Clear screen
        system("cls");
    }while(good==0);
    //Affichage de fin
    if(good==1){
        printf("Vous avez terrasse le monstre!");
    }else if(good==2){
        printf("Le monstre a devore tout vos pisteurs!");
    }



    return 0;
}
