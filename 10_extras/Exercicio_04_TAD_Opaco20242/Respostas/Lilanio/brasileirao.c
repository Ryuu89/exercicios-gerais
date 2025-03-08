#include "brasileirao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _BRA{
  int qtdTimes;
  int qtdTimesRemovidos;
  int premio;
  int qtdPartidas;
  tTabela *tabela;
};

/**
 * @brief Construtor do campeonato. Le da entrada padrao numero de times, numero de rodadas e pontuacao.
*/
BRA *CriaCamp(){
    BRA *camp = (BRA*)calloc(1, sizeof(BRA));
    printf("Insira o num de times, rodadas e premio total:\n");
    scanf("%d %d %d\n", &camp->qtdTimes, &camp->qtdPartidas, &camp->premio);
    camp->tabela = CriaTabela(camp->qtdTimes);

    return camp;
}

/**
 * @brief Le da entrada padrao as partidas da rodada, computa os resultados e atualiza a tabela.
*/
void RealizaRodada(BRA *br){
    char time1[50], time2[50];
    int gols1, gols2;
    tTime *t1, *t2;

    scanf("\n%s %d x %d %s", time1, &gols1, &gols2, time2);
    t1 = ObtemTimeTabela(br->tabela, time1);
    t2 = ObtemTimeTabela(br->tabela, time2);

    if (time1 != NULL && time2 != NULL){
        AtualizaGolsMarcados(t1, gols1);
        AtualizaGolsMarcados(t2, gols2);

        AtualizaGolsSofridos(t1, gols2);
        AtualizaGolsSofridos(t2, gols1);

        if (gols1 > gols2){
            AtualizaVitorias(t1);
            AtualizaDerrotas(t2);
        }
        else if (gols1 < gols2){
            AtualizaDerrotas(t1);
            AtualizaVitorias(t2);
        }
        else if (gols1 == gols2){
            AtualizaEmpates(t1);
            AtualizaEmpates(t2);
        }
    }
}

/**
 * @brief Imprime o menu e trata cada opcao.
*/
void RealizaCamp(BRA *br){
    int partidas = 0;
    char op;

    while (1){
        printf("Menu:\n");
        printf("C - Continuar\n");
        printf("R - Retirar 2 times e seguir\n");
        printf("F - Finalizar\n\n");

        scanf("\n%c", &op);
        if (op == 'C'){
            for(int i = 0; i < ((br->qtdTimes - br->qtdTimesRemovidos) / 2); i++){
                RealizaRodada(br);
            }
            OrdenaTabela(br->tabela);
            ImprimeTabela(br->tabela);
            partidas++;
        }
        else if (op == 'R'){
            printf("Times a serem retirados:\n");
            RemoveTimesCamp(br);
        }
        if (op == 'F' || partidas == br->qtdPartidas){
            printf("Esta foi a tabela final:\n");
            OrdenaTabela(br->tabela);
            ImprimeTabela(br->tabela);
            break;
        }
        if (br->qtdTimes == br->qtdTimesRemovidos){
            break;
        }
    }
}

/**
 * @brief Le 2 nomes da entrada padrao e remove os times correspondentes da competicao.
*/
void RemoveTimesCamp(BRA *br){
    char t1[MAX_TIME_NOME], t2[MAX_TIME_NOME];
    scanf("\n%s %s", t1, t2);

    RemoveTimeTabela(br->tabela, t1);
    RemoveTimeTabela(br->tabela, t2);

    printf("Os times %s e %s se retiraram do campeonato\n", t1, t2);
    br->qtdTimesRemovidos += 2;
    if (br->qtdTimes - br->qtdTimesRemovidos > 1){
        RealizaRodada(br);
        OrdenaTabela(br->tabela);
        ImprimeTabela(br->tabela);
    }
}

/**
 * @brief Libera a memoria do campeonato.
*/
void DesalocaCamp(BRA *br){
    DesalocaTabela(br->tabela);
    free(br);
}

/**
 * @brief Imprime a tabela final, premiacao e desaloca o campeonato.
*/
void FinalizaCamp(BRA *br){
    OrdenaTabela(br->tabela);
    ImprimePremiacao(br->tabela, br->premio);

    printf("Fim do campeonato\n");

    DesalocaCamp(br);
}