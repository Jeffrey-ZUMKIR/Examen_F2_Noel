#include <stdio.h>
#include <stdlib.h>

#include "defineStruct.h"
#include "endGame.h"

//BUT:      vérifier si le monstre a encore des vies et si des pisteurs sont toujours vivant
//ENTREE:   Le monstre, la liste des pisteurs, la vérification de fin, le nombre de pisteur
//SORTIE:   Une valeur en fonction de quel fin est arrivé
void CheckEndGame(str_monstre monstre,str_pisteur tabPisteur[],int *good, int nbPisteur){
    int i=0;
    //Si le monstre est mort, renvoye 1
    if(monstre.PV<=0){
        *good=1;
    }else{
        *good=2;
        //Si tout les pisteurs sont morts, on renvoye 2
        for(i=0;i<nbPisteur;i++){
            //Si au moins un pisteur est encore en vie, la partie continu
            if(tabPisteur[i].vivant==1){
                *good=0;
            }
        }
    }
}
