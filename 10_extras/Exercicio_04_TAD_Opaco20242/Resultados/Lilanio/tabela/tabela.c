#include "tabela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Tabela{
  int nTimesAloc;
  int maxTimes;
  tTime **times;
};

/**
 * @brief Construtor do tipo tabela. Deve criar os times.
 * @param numTimes Numero de times a serem criados.
*/
tTabela* CriaTabela(int numTimes){
  tTabela *tabela = (tTabela*)calloc(1, sizeof(tTabela));
  tabela->times = (tTime**)calloc(numTimes, sizeof(tTime*));

  tabela->maxTimes = numTimes;
  tabela->nTimesAloc = 0;
  
  for (int i = 0; i < tabela->maxTimes; i++){
    tabela->times[i] = LeTime();
    if (tabela->times[i] != NULL){
      tabela->nTimesAloc++;
    }
  }
  
  return tabela;
}

/**
 * @brief Libera a memoria alocada para a tabela e seus times.
*/
void DesalocaTabela(tTabela* tabela){
  for (int i = 0; i < tabela->nTimesAloc; i++){
    DesalocaTime(tabela->times[i]);
  }
  free(tabela->times);
  free(tabela);
}

/**
 * @brief Ordena a tabela de acordo com os criterios definidos.
*/
void OrdenaTabela(tTabela* tabela){
  for (int i = 0; i < tabela->maxTimes-1; i++){
    for (int j = 0; j < tabela->maxTimes-1-i; j++){
      if (DesempataTimes(tabela->times[j], tabela->times[j+1]) == 1){
        tTime *temp = tabela->times[j];
        tabela->times[j] = tabela->times[j + 1];
        tabela->times[j + 1] = temp;
      }
    }
  }
}

/**
 * @brief Dado um nome, retorna o time correspondente.
*/
tTime* ObtemTimeTabela(tTabela* tabela, char* time){
  for (int i = 0; i < tabela->maxTimes; i++){
    if (strcmp(ObtemNomeTime(tabela->times[i]), time) == 0){
      return tabela->times[i];
    }
  }
  return NULL;
}

/**
 * @brief Dado um nome, desaloca e remove o time correspondente da tabela.
*/
void RemoveTimeTabela(tTabela* tabela, char* time){
  
  for (int i = 0; i < tabela->maxTimes; i++){
    if (strcmp(ObtemNomeTime(tabela->times[i]), time) == 0){
      tTime *temp = tabela->times[i];
      tabela->times[i] = tabela->times[tabela->maxTimes-1];
      tabela->times[tabela->maxTimes-1] = temp;
      tabela->maxTimes--;
    }
  }
}

/**
 * @brief Imprime a tela de premiacao no final do campeonato.
*/
void ImprimePremiacao(tTabela* tabela, float valorPremio){
  if (tabela->maxTimes == 0){
    printf("Premio de R$%.2f acumulado para a proxima edicao\n", valorPremio);
  }
  else if (tabela->maxTimes >= 3){
    printf("1º lugar - %s: R$%.2f\n", ObtemNomeTime(tabela->times[0]), valorPremio*0.5);
    printf("2º lugar - %s: R$%.2f\n", ObtemNomeTime(tabela->times[1]), valorPremio*0.3);
    printf("3º lugar - %s: R$%.2f\n", ObtemNomeTime(tabela->times[2]), valorPremio*0.2);
  }
  else if (tabela->maxTimes == 2){
    printf("1º lugar - %s: R$%.2f\n", ObtemNomeTime(tabela->times[0]), valorPremio*0.6);
    printf("2º lugar - %s: R$%.2f\n", ObtemNomeTime(tabela->times[1]), valorPremio*0.4);
  }
  else {
    printf("Nenhum ganhador.");
  }
}

/**
 * @brief Imprime todos os times da tabela.
*/
void ImprimeTabela(tTabela* tabela){
  printf("Classificação:\n");
  printf("Nome | Pontos | Vitorias | Derrotas | Empates | Saldo\n");
  for (int i = 0; i < tabela->maxTimes; i++){
    ImprimeTime(tabela->times[i]);
  }
  printf("\n");
}
