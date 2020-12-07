#include <stdio.h>
#include <stdlib.h>

#include "phaseInit.h"
#include "defineStruct.h"

//BUT:      Afficher le tableau
//ENTREE:   Le tableau
//SORTIE:   Le tableau affiché
void Affichage(char tab[HEIGHTAB][WIDTHTAB]){
    for(int i=0;i<HEIGHTAB;i++){
        for(int j=0;j<WIDTHTAB;j++){
            printf("%c ",tab[i][j]);
        }
        printf("\n");
    }
}
