#include <stdio.h>
#include <stdlib.h>

#include "defineStruct.h"
#include "trace.h"


void deleteTrace(int mapTraceMonstre[HEIGHTAB][WIDTHTAB]){
    int i=0;
    int j=0;
    for(i=0;i<HEIGHTAB;i++){
        for(j=0;j<WIDTHTAB;j++){
            if(mapTraceMonstre[i][j]>0){
                mapTraceMonstre[i][j]-=1;
            }
        }
    }
}


