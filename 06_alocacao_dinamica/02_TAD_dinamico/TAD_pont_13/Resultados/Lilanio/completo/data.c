#include <stdio.h>
#include <stdlib.h>
#include "data.h"

tData* LeData(){
    tData *d = (tData*) calloc(1, sizeof(tData));
    scanf("%d/%d/%d\n", &d->dia, &d->mes, &d->ano);

    return d;
}

tData* CriaData(int dia, int mes, int ano){
    tData *d = (tData*) calloc(1, sizeof(tData));

    d->dia = dia;
    d->mes = mes;
    d->ano = ano;

    return d;
}

void LiberaData(tData *d){
    if (d != NULL){
        free(d);
    }
}

int CalculaIdadeData(tData* nascimento, tData* diacalc){
    int diff = diacalc->ano - nascimento->ano;

    if ((*diacalc).mes < nascimento->mes || (diacalc->mes == nascimento->mes && diacalc->dia < nascimento->dia)){
        diff--;
    }

    return diff;
}

void ImprimeData(tData* d){
    printf("%d/%d/%d\n", d->dia, d->mes, d->ano);
}