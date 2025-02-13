#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Função que cria uma estrutura Paciente (alocando memória para o que for necessário), lê os valores da entrada padrão
de acordo com a descrição, e retorna o ponteiro para a estrutura criada.
*/
Paciente *lePaciente(){
    Paciente *pac = (Paciente*)calloc(1, sizeof(Paciente));

    pac->nome = (char*)calloc(TAM_NOME, sizeof(char));
    pac->cartaoSus = (char*)calloc(TAM_SUS, sizeof(char));
    pac->lesoes = (Lesao**)calloc(1, sizeof(Lesao*));
    pac->qtdLesoes = 0;
    pac->qtdLesoesAlocadas = 1;

    scanf("%[^\n]\n", pac->nome);
    pac->dataNasc = leData();
    scanf("%[^\n]\n", pac->cartaoSus);
    scanf("%c\n", &pac->genero);

    return pac;
}

/*
Função que libera toda a memória alocada para a estrutura Paciente.
Ela verifica se o ponteiro passado é nulo antes de tentar liberar a memória.
*/
void liberaPaciente(Paciente *p){
    if (p == NULL){
        return;
    }
    for (int i = 0; i < p->qtdLesoes; i++){
        liberaLesao(p->lesoes[i]);
    }

    free(p->lesoes);
    free(p->nome);
    liberaData(p->dataNasc);
    free(p->cartaoSus);
    free(p);
}

/*
Função que recebe um paciente e uma lesão e adiciona a lesão ao paciente no grupo de lesões que ele possui.
Se for necessário mais memória para alocar uma nova lesão, essa função deve realocar a memória necessária.
*/
void adicionaLesaoPaciente(Paciente *p, Lesao *l){
    if (p->qtdLesoes == p->qtdLesoesAlocadas){
        p->qtdLesoesAlocadas *= 2;
        p->lesoes = (Lesao**)realloc(p->lesoes, p->qtdLesoesAlocadas * sizeof(Lesao*));
    }
    p->lesoes[p->qtdLesoes++] = l;
}

/*
Função que calcula a idade do paciente em relação a uma data de referência informada.
*/
int calculaIdadePaciente(Paciente *p, Data *ref){
    return calculaDiffAnosData(p->dataNasc, ref);
}

/*
Função que retorna a quantidade de cirurgias associadas a este paciente de acordo com as regras
descritas na descrição.
*/
int getQtdCirurgiasPaciente(Paciente *p){
    int k = 0;
    
    for (int i = 0; i < p->qtdLesoes; i++){
        if (precisaCirurgiaLesao(p->lesoes[i])){
            k++;
        }

    }
    return k;
}

/*
Função que retorna o cartão do sus do paciente.
*/
char *getCartaoSusPaciente(Paciente *p){
    return p->cartaoSus;
}

/*
Função que retorna a data de nascimento do paciente.
*/
Data *getDataNascPaciente(Paciente *p){
    return p->dataNasc;
}

/*
Função que retorna a quantidade de lesões do paciente
*/
int getQtdLesoesPaciente(Paciente *p){
    return p->qtdLesoes;
}

/*
Função que imprime o nome do paciente, seguido do IDs das lesões associadas a ele.
Ela verifica se existe lesão. Se não existir, nada é impresso.
Essa impressão segue o padrão da descrição.
*/
void imprimeIdLesoesPaciente(Paciente *p){
    if (p->qtdLesoes == 0){
        return;
    }
    printf("- %s - ", p->nome);
    for (int i = 0; i < p->qtdLesoes; i++){
        printf("%s ", p->lesoes[i]->id);
    }
    printf("\n");
}