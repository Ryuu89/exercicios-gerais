
#include <stdlib.h>
#include <stdio.h>
#include "lesao.h"

Lesao *leLesao()
{
    Lesao *l = (Lesao *)malloc(sizeof(Lesao));
    l->id = (char *)malloc(sizeof(char) * TAM_ID);
    l->diag = (char *)malloc(sizeof(char) * TAM_DIAG);
    l->regiao = (char *)malloc(sizeof(char) * TAM_REG);

    scanf("%s\n", l->id);
    scanf("%[^\n]\n", l->diag);
    scanf("%[^\n]\n", l->regiao);
    scanf("%d\n", &l->malignidade);

    return l;
}

char *getIdLesao(Lesao *l)
{
    return l->id;
}

int precisaCirurgiaLesao(Lesao *l)
{
    if (l->malignidade > 50)
    {
        return 1;
    }
    return 0;
}

void liberaLesao(Lesao *l)
{
    if (l != NULL)
    {
        free(l->id);
        free(l->diag);
        free(l->regiao);
        free(l);
    }
}