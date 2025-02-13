
#include <stdlib.h>
#include <stdio.h>
#include "data.h"

Data *criaData(int dia, int mes, int ano)
{
    Data *d = (Data *)malloc(sizeof(Data));
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
    return d;
}

Data *leData()
{
    Data *d = (Data *)malloc(sizeof(Data));
    scanf("%d/%d/%d ", &d->dia, &d->mes, &d->ano);
    return d;
}

void imprimeData(Data *d)
{
    printf("%d/%d/%d\n", d->dia, d->mes, d->ano);
}

int calculaDiffAnosData(Data *d, Data *atual)
{
    int diff = atual->ano - d->ano;

    if (atual->mes < d->mes)
    {
        diff--;
    }
    else if (atual->mes == d->mes)
    {
        if (atual->dia < d->dia)
        {
            diff--;
        }
    }

    return diff;
}

void liberaData(Data *d)
{
    free(d);
}
