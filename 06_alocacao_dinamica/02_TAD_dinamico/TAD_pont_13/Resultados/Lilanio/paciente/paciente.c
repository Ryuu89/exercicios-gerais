#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Retorna o número do cartão SUS do paciente.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente contendo as informações do paciente.
 * @return Retorna uma string contendo o número do cartão SUS do paciente.
 */
char* GetCartaoSusPaciente(tPaciente* p){
    return p->sus;
}

/**
 * @brief Retorna a quantidade de lesões do paciente.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente contendo as informações do paciente.
 * @return Retorna a quantidade de lesões do paciente.
 */
int GetQtdLesoesPaciente(tPaciente* p){
    return p->qtdLesao;
}

/**
 * @brief Retorna a quantidade de cirurgias necessárias para tratar as lesões do paciente.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente contendo as informações do paciente.
 * @return Retorna a quantidade de cirurgias necessárias para tratar as lesões do paciente.
 */
int GetQtdCirurgiasPaciente(tPaciente* p){
    int qtdCir = 0;

    for (int i = 0; i < p->qtdLesoes; i++){
        if(PrecisaCirurgiaLesao(p->listaLesao[i])){
            qtdCir++;
        }
    }

    return qtdCir;
}

/**
 * @brief Retorna a data de nascimento do paciente.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente contendo as informações do paciente.
 * @return Retorna a data de nascimento do paciente.
 */
tData* GetNascimentoPaciente(tPaciente* p){
    return p->nascimento;
}

/**
 * @brief Cria uma estrutura do tipo tPaciente
 * 
 * @return Retorna um ponteiro para a estrutura de dados tPaciente
 */
tPaciente* CriaPaciente(){
    tPaciente *p = (tPaciente*) calloc(1, sizeof(tPaciente));

    p->nome = (char*) calloc(TAM_NOME, sizeof(char));
    p->cartaoSus = (char*) calloc(TAM_CSUS, sizeof(char));
    p->listaLesao = (tLesao**) calloc(QTD_LESAO, sizeof(tLesao*));
    p->qtdLesoes = 0;
    p->maxLesoes = QTD_LESAO;
    return p;
}

/**
 * @brief Lê informações sobre um paciente do usuário.
 * 
 * @return Retorna um ponteiro para a estrutura de dados tPaciente contendo as informações lidas.
 */
void LePaciente(tPaciente* p){
    scanf("^[\n]\n", p->nome);
    p->nascimento = leData();
    scanf("^[\n]\n", p->cartaoSus);
    scanf("%c\n", p->genero);
}

/**
 * @brief Imprime as informações de um paciente na saída padrão.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente contendo as informações do paciente.
 */
void ImprimePaciente(tPaciente* p){
    if (p->qtdLesoes > 0){
        printf("- %s -", p->nome);
        for (int i = 0; i < p->qtdLesoes; i++){
            printf(" %s\n", p->listaLesao[i]);
        }
    }
}

/**
 * @brief Libera a memória alocada para uma estrutura de dados tPaciente.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente a ser liberada.
 */
void LiberaPaciente(tPaciente* p){
    if (p != NULL){
        free(p->nome);
        free(p->cartaoSus);
        for (int i = 0; i < p->qtdLesoes; i++){
            LiberaLesao(p->ListaLesao[i]);
        }
        
        free(p->ListaLesao);
        free(p->nascimento);
        free(p);
    }
}


/**
 * @brief Adiciona uma lesão à lista de lesões do paciente.
 * 
 * @param p Ponteiro para a estrutura de dados tPaciente contendo as informações do paciente.
 * @param l Ponteiro para a estrutura de dados tLesao contendo as informações da lesão.
*/
void AdicionaLesaoPaciente(tPaciente* p, tLesao* l){
    if (p->qtdLesoes < p->maxLesoes){
        p->listaLesao[p->qtdLesoes] = l;
        p->qtdLesoes++;
    }
}