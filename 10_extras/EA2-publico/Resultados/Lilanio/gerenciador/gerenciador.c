#include "gerenciador.h"
#include "paciente.h"
#include "lesao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Função que cria uma estrutura Gerenciador (alocando toda memória necessária), inicializa o que for necessário
e retorna o ponteiro para a estrutura criada.
*/
Gerenciador *criaGerenciador(){
    Gerenciador *g = (Gerenciador*)calloc(1, sizeof(Gerenciador));
    if (!g) {
        return NULL;
    }

    g->bancoPacientes = (Paciente**)calloc(1, sizeof(Paciente*));
    if (!g->bancoPacientes) {
        free(g);
        return NULL;
    }

    g->tamBanco = 0;
    g->tamBancoAlocado = 1;
    
    return g;
}

/*
Função que adiciona um paciente ao banco de pacientes do gerenciador.
Se for necessário mais memória para alocar um novo paciente, essa função deve realocar a memória necessária.
*/
void adicionaPacienteBancoGerenciador(Gerenciador *g, Paciente *p){
    if (!g || !p) return;

    if (g->tamBanco == g->tamBancoAlocado) {
        size_t novoTamanho = g->tamBancoAlocado * 2;
        Paciente **temp = (Paciente**)realloc(g->bancoPacientes, 
                                            novoTamanho * sizeof(Paciente*));
        if (!temp) return;
        
        g->bancoPacientes = temp;
        g->tamBancoAlocado = novoTamanho;
    }
    
    g->bancoPacientes[g->tamBanco++] = p;
}

/*
Função que busca e retorna um paciente (se existir) no banco de pacientes do gerenciador a partir do cartão do SUS.
Se não encontrar o paciente, retorna NULL.
*/
Paciente *getPacientePeloSUSBancoGerenciador(Gerenciador *g, char *sus){
    if (!g || !sus){
        return NULL;
    }

    for (int i = 0; i < g->tamBanco; i++) {
        if (g->bancoPacientes[i] && 
            strcmp(getCartaoSusPaciente(g->bancoPacientes[i]), sus) == 0) {
            return g->bancoPacientes[i];
        }
    }
    return NULL;
}

/*
Função que le os dados de pacientes e lesões a partir da entrada padrão e preenche o banco de
pacientes do gerenciador. Essa leitura seguem as regras descritas na descrição.
Perceba que o banco salva apenas os pacientes, as lesões são salvas nos pacientes.
*/
void preencheBancoPacientesGerenciador(Gerenciador *ger){
    if (!ger) return;
    
    int numPacientes;
    scanf("%d%*c", &numPacientes);
    
    for (int i = 0; i < numPacientes; i++) {
        Paciente *p = lePaciente();
        if (!p) continue;
        
        int numLesoes;
        scanf("%d%*c", &numLesoes);
        
        for (int j = 0; j < numLesoes; j++) {
            Lesao *l = leLesao();
            if (l) {
                adicionaLesaoPaciente(p, l);
            }
        }
        adicionaPacienteBancoGerenciador(ger, p);
    }
}

/*
Função que libera a memória alocada para a estrutura Gerenciador.
Ela verifica se o ponteiro passado é nulo antes de tentar liberar a memória.
*/
void liberaGerenciador(Gerenciador *g){
    if (!g) return;

    if (g->bancoPacientes) {
        for (int i = 0; i < g->tamBanco; i++) {
            if (g->bancoPacientes[i]) {
                liberaPaciente(g->bancoPacientes[i]);
            }
        }
        free(g->bancoPacientes);
    }
    free(g);
}

/*
Função que calcula a média de idade dos pacientes do banco de pacientes do gerenciador.
Para isso, é necessário calcular a idade de cada paciente em relação a data de referência.
*/
int calculaMediaIdadePacientesBancoGerenciador(Gerenciador *g){
    if (!g || g->tamBanco == 0) return 0;

    Data *dataRef = criaData(DIA_BASE, MES_BASE, ANO_BASE);
    if (!dataRef) return 0;

    int somaIdades = 0;
    int pacientesValidos = 0;
    
    for (int i = 0; i < g->tamBanco; i++) {
        if (g->bancoPacientes[i]) {
            somaIdades += calculaIdadePaciente(g->bancoPacientes[i], dataRef);
            pacientesValidos++;
        }
    }

    liberaData(dataRef);
    return pacientesValidos > 0 ? somaIdades / pacientesValidos : 0;
}

/*
Função que imprime os pacientes do banco de pacientes do gerenciador de acordo com a descrição.
*/
void imprimePacientesBancoGerenciador(Gerenciador *g){
    if (!g || g->tamBanco == 0) {
        return;
    }

    for (int i = 0; i < g->tamBanco; i++) {
        if (!g->bancoPacientes[i]) continue;
        
        // Imprime as informações do paciente usando apenas funções disponíveis
        imprimeIdLesoesPaciente(g->bancoPacientes[i]);
    }
}

/*
Função que calcula a quantidade total de lesões dos pacientes do banco de pacientes do gerenciador.
Se não houver pacientes ou lesões associadas, retorna 0.
*/
int calculaQtdLesoesPacientesBancoGerenciador(Gerenciador *g){
    if (!g){
        return 0;
    }

    int totalLesoes = 0;
    for (int i = 0; i < g->tamBanco; i++) {
        if (g->bancoPacientes[i]) {
            totalLesoes += getQtdLesoesPaciente(g->bancoPacientes[i]);
        }
    }
    return totalLesoes;
}

/*
Função que calcula a quantidade total de cirurgias necessárias para os pacientes do banco de pacientes do gerenciador.
Se não houver pacientes ou lesões que necessitam de cirurgia, retorna 0.
*/
int calculaQtdCirurgiaPacientesBancoGerenciador(Gerenciador *g){
    if (!g){
        return 0;
    }

    int totalCirurgias = 0;
    for (int i = 0; i < g->tamBanco; i++) {
        if (g->bancoPacientes[i]) { // Verificação adicional
            totalCirurgias += getQtdCirurgiasPaciente(g->bancoPacientes[i]);
        }
    }
    return totalCirurgias;
}

/*
Função que imprime o relatório do gerenciador de acordo com a descrição da atividade.
*/
void imprimeRelatorioGerenciador(Gerenciador *g){
    if (!g) return;

    int mediaIdade = calculaMediaIdadePacientesBancoGerenciador(g);
    int totalLesoes = calculaQtdLesoesPacientesBancoGerenciador(g);
    int totalCirurgias = calculaQtdCirurgiaPacientesBancoGerenciador(g);

    printf("TOTAL PACIENTES: %d\n", g->tamBanco);
    printf("MEDIA IDADE (ANOS): %d\n", mediaIdade);
    printf("TOTAL LESOES: %d\n", totalLesoes);
    printf("TOTAL CIRURGIAS: %d\n", totalCirurgias);
    printf("LISTA DE PACIENTES:\n");

    imprimePacientesBancoGerenciador(g);
}