#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "paciente.h"
#include "lesao.h"
#include "data.h"

Paciente *lePaciente()
{

    Paciente *p = (Paciente *)malloc(sizeof(Paciente));
    p->nome = (char *)malloc(sizeof(char) * TAM_NOME);
    p->cartaoSus = (char *)malloc(sizeof(char) * TAM_SUS);

    scanf("%[^\n]\n", p->nome);
    p->dataNasc = leData();
    scanf("%[^\n]\n", p->cartaoSus);
    scanf("%c\n", &p->genero);

    p->qtdLesoesAlocadas = 2;
    p->qtdLesoes = 0;
    p->lesoes = (Lesao **)malloc(sizeof(Lesao *) * p->qtdLesoesAlocadas);

    return p;
}

void liberaPaciente(Paciente *p)
{

    if (p != NULL)
    {
        free(p->nome);
        free(p->cartaoSus);
        liberaData(p->dataNasc);
        for (int i = 0; i < p->qtdLesoes; i++)
        {
            liberaLesao(p->lesoes[i]);
        }
        free(p->lesoes);
        free(p);
    }
}

void adicionaLesaoPaciente(Paciente *p, Lesao *l)
{

    if (p->qtdLesoes == p->qtdLesoesAlocadas)
    {
        p->qtdLesoesAlocadas += 2;
        p->lesoes = (Lesao **)realloc(p->lesoes, sizeof(Lesao *) * p->qtdLesoesAlocadas);
    }

    p->lesoes[p->qtdLesoes] = l;
    p->qtdLesoes++;
}

int getQtdCirurgiasPaciente(Paciente *p)
{
    int total = 0;
    for (int i = 0; i < p->qtdLesoes; i++)
    {
        total += precisaCirurgiaLesao(p->lesoes[i]);
    }
    return total;
}

int calculaIdadePaciente(Paciente *p, Data *ref)
{
    return calculaDiffAnosData(p->dataNasc, ref);
}

char *getCartaoSusPaciente(Paciente *p)
{
    return p->cartaoSus;
}

Data *getDataNascPaciente(Paciente *p)
{
    return p->dataNasc;
}

int getQtdLesoesPaciente(Paciente *p)
{
    return p->qtdLesoes;
}

void imprimeIdLesoesPaciente(Paciente *p)
{
    if (p->qtdLesoes > 0)
    {
        printf("- %s - ", p->nome);
        for (int i = 0; i < p->qtdLesoes; i++)
        {
            printf("%s ", getIdLesao(p->lesoes[i]));
        }
        printf("\n");
    }
}
