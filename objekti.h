#ifndef OBJEKTI_H
#define OBJEKTI_H

#include <stdbool.h>

typedef struct {
    float x;
    float z;
}Metak;


typedef struct {
    float x;
    float z;
    bool is_pogodjena;
}Prepreka;


void iscrtaj_ose(); 
void iscrtaj_pistolj();
void iscrtaj_metak();

#endif
