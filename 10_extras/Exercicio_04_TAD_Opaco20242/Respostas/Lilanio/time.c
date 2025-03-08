#include "time.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_TIME_NOME 33

struct _Time{
  char nome[MAX_TIME_NOME];
  int partidas;
  int pontos;
  int vitorias;
  int derrotas;
  int empates;
  int goalScored;
  int goalConceded;
  int saldo;
};

/** 
 * @brief Construtor do tipo time. Deve ler um nome pela entrada padrao.
*/
tTime* LeTime(){
  tTime *time = (tTime*)calloc(1, sizeof(tTime));

  scanf("%[^\n]\n", time->nome);

  time->partidas = 0;
  time->pontos = 0;
  time->vitorias = 0;
  time->derrotas = 0;
  time->empates = 0;
  time->goalScored = 0;
  time->goalConceded = 0;
  time->saldo = 0;

  return time;
}

/**
 * @brief Retona o numero de vitorias do time.
*/
int ObtemVitorias(tTime *t){
  return t->vitorias;
}

/**
 * @brief Retona o numero de partidas.
*/
int ObtemPartidas(tTime *t){
  return t->partidas;
}

/**
 * @brief Retona o numero de derrotas do time.
*/
int ObtemDerrotas(tTime *t){
  return t->derrotas;
}

/**
 * @brief Retona a string do nome do time.
*/
char* ObtemNomeTime(tTime *t){
  return t->nome;
}

/**
 * @brief Retona o saldo de gols da equipe.
*/
int ObtemSaldo(tTime *t){
  return t->saldo;
}

/**
 * @brief Aumenta o numero de vitorias em 1.
*/
void AtualizaVitorias(tTime *t){
  t->vitorias++;
  t->pontos += 3;
}

/**
 * @brief Aumenta o numero de empates em 1.
*/
void AtualizaEmpates(tTime *t){
  t->empates++;
  t->pontos += 1;
}

/**
 * @brief Aumenta o numero de derrotas em 1.
*/
void AtualizaDerrotas(tTime *t){
  t->derrotas++;
}

/**
 * @brief Aumenta a quantidade de gols marcados.
*/
void AtualizaGolsMarcados(tTime *t, int gols){
  t->goalScored += gols;
  t->saldo = t->goalScored - t->goalConceded;
}

/**
 * @brief Aumenta a quantidade de gols sofridos.
*/
void AtualizaGolsSofridos(tTime *t, int gols){
  t->goalConceded += gols;
  t->saldo = t->goalScored - t->goalConceded;
}

/**
 * @brief Retorna a pontuacao do time.
*/
int ObtemPontos(tTime* t){
  return t->pontos;
}

/**
 * @brief Usa os criterios de classificacao para indicar qual time possui melhor colocacao. Retorna -1 para t1, 1 para t2.
*/
int DesempataTimes(tTime *t1, tTime *t2){
  if (t1->pontos > t2->pontos){
    return -1;
  }
  if (t1->pontos == t2->pontos){
    if (t1->vitorias > t2->vitorias){
      return -1;
    }
    if (t1->vitorias == t2->vitorias){
      if (t1->saldo > t2->saldo){
        return -1;
      }
    }
  }
  return 1;
}

/**
 * @brief Imprime os dados do time na ordem: Nome | Pontos | Vitorias | Derrotas | Empates | Saldo.
 * Dica: Use a seguinte formatacao no printf: "%-12s | %02d | %02d | %02d | %02d | %+03d\n".
*/
void ImprimeTime(tTime *t){
  printf("%-12s | %02d | %02d | %02d | %02d | %+03d\n", t->nome, t->pontos, t->vitorias, t->derrotas, t->empates, t->saldo);
}

/**
 * @brief Libera a memoria alocada para time.
*/
void DesalocaTime(tTime *t){
  free(t);
}