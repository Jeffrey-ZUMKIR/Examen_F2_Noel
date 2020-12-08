#ifndef DEFINESTRUCT_H_INCLUDED
#define DEFINESTRUCT_H_INCLUDED

#define WIDTHTAB 30
#define HEIGHTAB 15

typedef struct coord{
    int x;
    int y;
}coord;

typedef struct str_pisteur{
    int vivant;
    coord pos;
    int mapTracePisteur[HEIGHTAB][WIDTHTAB];
}str_pisteur;

typedef struct str_monstre{
    int PV;
    coord pos;
}str_monstre;




#endif // DEFINESTRUCT_H_INCLUDED
