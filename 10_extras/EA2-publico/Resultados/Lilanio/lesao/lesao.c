#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lesao.h"

/*
Função que cria uma estrutura Lesao (alocando memória para o que for necessário), lê os valores da entrada padrão
de acordo com a descrição, e retorna o ponteiro para a estrutura criada.
*/
Lesao *leLesao(){
    Lesao *l = (Lesao*)calloc(1, sizeof(Lesao));
    l->id = (char*)calloc(TAM_ID, sizeof(char));
    l->diag = (char*)calloc(TAM_DIAG, sizeof(char));
    l->regiao = (char*)calloc(TAM_REG, sizeof(char));

    scanf("%[^\n]\n", l->id);
    scanf("%[^\n]\n", l->diag);
    scanf("%[^\n]\n", l->regiao);
    scanf("%d\n", &l->malignidade);

    return l;
}

/*
Função que libera a memória alocada para a estrutura Lesao.
Ela verifica se o ponteiro passado é nulo antes de tentar liberar a memória.
*/
void liberaLesao(Lesao *l){
    free(l->id);
    free(l->diag);
    free(l->regiao);
    free(l);
}

/*
Função que retorna o Id da lesão passada como parâmetro.
*/
char *getIdLesao(Lesao *l){
    return l->id;
}

/*
Função que calcula se a lesão passada como parâmetro precisa de cirurgia de acordo com a regra
informada na descrição.
*/
int precisaCirurgiaLesao(Lesao *l){
    if (l->malignidade > 50){
        return 1;
    }
    return 0;
}