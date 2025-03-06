#include "servidor.h"
#include <stdio.h>
#include <stdlib.h>

/*
Função que lê todos os registros de partidas de um servidor a partir da entrada padrão e retorna um servidor
com todos os registros de partidas lidos. Conforme a especificação da atividade.

@return Servidor: Servidor com todos os registros de partidas lidos
*/
Servidor leRegistrosServidor(){
    Servidor serv;

    scanf("%d\n", &serv.nPartidas);

    for (int i = 0; i < serv.nPartidas; i++){
        serv.partidas[i] = leRegistro(i, PASTA_LOGS);
    }

    return serv;
}

/*
Função que recebe um servidor já preenchido com os dados de todas as partidas e um ID de jogador.
A partir dessas informações, ela busca as estatísticas do jogador em todas as partidas que ele participou.
Se o jogar não for encontrado, um jogador com ID -1 é criado e retornado.
Se o jogador for encontrado em apenas uma partida, ele é retornado.
Se o jogador for encontrado em mais de uma partida, suas estatísticas são agregadas e o jogador é retornado.

@param s: Servidor
@param idJog: ID do jogador
*/
Jogador buscaDadosJogadorServidor(Servidor s, int idJog){
    Jogador jogAtual = inicializaJogador(-1);
    Jogador jogFinal = inicializaJogador(-1);
    int nPartidasJogador = 0;

    for (int i = 0; i < s.nPartidas; i++){
        jogAtual = buscaJogadorRegistro(s.partidas[i], idJog);
        if (getIdJogador(jogAtual) != -1){
            jogFinal = atualizaJogador(jogFinal, getIdJogador(jogAtual), getKillsJogador(jogAtual), getDeathsJogador(jogAtual), getAssistsJogador(jogAtual));
            nPartidasJogador++;
        }
    }

    return jogFinal;
}

/*
Função que recebe um servidor já criado e preenchido e imprime um relatório com as estatísticas de um conjunto de jogadores
solicitados a partir da entrada padrão. O relatório é impresso conforme o formato especificado na descrição da atividade.
*/
void criaRelatorioServidor(Servidor s){
    int qtdJogs;
    scanf("%d\n", &qtdJogs);

    for (int i = 0; i < qtdJogs; i++){
        int idJog;
        scanf("%d\n", &idJog);

        Jogador jog = buscaDadosJogadorServidor(s, idJog);

        if (getIdJogador(jog) == -1){
            printf("Jogador %d: -\n", idJog);
        }else {
            printaJogador(jog);
        }
    }
}
