#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gerenciador.h"
#include "lesao.h"
#include "data.h"


/*
Função que cria uma estrutura Gerenciador (alocando toda memória necessária), inicializa o que for necessário
e retorna o ponteiro para a estrutura criada.
*/
Gerenciador *criaGerenciador()
{
    Gerenciador *g = (Gerenciador *)malloc(sizeof(Gerenciador));

    g->tamBancoAlocado = 2;
    g->tamBanco = 0;
    g->bancoPacientes = (Paciente **)malloc(sizeof(Paciente *) * g->tamBancoAlocado);

    return g;
}

/*
Função que adiciona um paciente ao banco de pacientes do gerenciador.
Se for necessário mais memória para alocar um novo paciente, essa função deve realocar a memória necessária.
*/
void adicionaPacienteBancoGerenciador(Gerenciador *g, Paciente *p)
{
    if (g->tamBanco == g->tamBancoAlocado)
    {
        g->tamBancoAlocado += 2;
        g->bancoPacientes = (Paciente **)realloc(g->bancoPacientes, sizeof(Paciente *) * g->tamBancoAlocado);
    }

    g->bancoPacientes[g->tamBanco] = p;
    g->tamBanco++;
}


/*
Função que busca e retorna um paciente (se existir) no banco de pacientes do gerenciador a partir do cartão do SUS.
Se não encontrar o paciente, retorna NULL.
*/
Paciente *getPacientePeloSUSBancoGerenciador(Gerenciador *g, char *sus)
{
    for (int i = 0; i < g->tamBanco; i++)
    {
        if (strcmp(getCartaoSusPaciente(g->bancoPacientes[i]), sus) == 0)
        {
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
void preencheBancoPacientesGerenciador(Gerenciador *ger)
{
    char opt;

    do
    {
        scanf("%c\n", &opt);
        if (opt == 'P')
        {
            Paciente *pac = lePaciente();
            adicionaPacienteBancoGerenciador(ger, pac);
        }
        else if (opt == 'L')
        {
            char cartao[TAM_SUS];
            scanf("%s\n", cartao);
            Lesao *les = leLesao();
            Paciente *p = getPacientePeloSUSBancoGerenciador(ger, cartao);
            if (p != NULL)
            {
                adicionaLesaoPaciente(p, les);
            }
            else
            {
                liberaLesao(les);
            }
        }

    } while (opt != 'F');
}


/*
Função que libera a memória alocada para a estrutura Gerenciador.
Ela verifica se o ponteiro passado é nulo antes de tentar liberar a memória.
*/
void liberaGerenciador(Gerenciador *g)
{
    if (g != NULL)
    {

        for (int i = 0; i < g->tamBanco; i++)
        {
            liberaPaciente(g->bancoPacientes[i]);
        }
        free(g->bancoPacientes);
        free(g);
    }
}

/*
Função que calcula a média de idade dos pacientes do banco de pacientes do gerenciador.
Para isso, é necessário calcular a idade de cada paciente em relação a data de referência.
*/
int calculaMediaIdadePacientesBancoGerenciador(Gerenciador *g)
{
    Data *ref = criaData(DIA_BASE, MES_BASE, ANO_BASE);
    int total = 0;
    for (int i = 0; i < g->tamBanco; i++)
    {
        total += calculaIdadePaciente(g->bancoPacientes[i], ref);
    }
    free(ref);

    if (g->tamBanco == 0)
    {
        return 0;
    }
    return total / g->tamBanco;
}

/*
Função que imprime os pacientes do banco de pacientes do gerenciador de acordo com a descrição.
*/
void imprimePacientesBancoGerenciador(Gerenciador *g)
{
    printf("LISTA DE PACIENTES:\n");
    for (int i = 0; i < g->tamBanco; i++)
    {
        imprimeIdLesoesPaciente(g->bancoPacientes[i]);
    }
}

/*
Função que calcula a quantidade total de lesões dos pacientes do banco de pacientes do gerenciador.
Se não houver pacientes ou lesões associadas, retorna 0.
*/
int calculaQtdLesoesPacientesBancoGerenciador(Gerenciador *g)
{
    int total = 0;

    for (int i = 0; i < g->tamBanco; i++)
    {
        total += getQtdLesoesPaciente(g->bancoPacientes[i]);
    }

    return total;
}

/*
Função que calcula a quantidade total de cirurgias necessárias para os pacientes do banco de pacientes do gerenciador.
Se não houver pacientes ou lesões que necessitam de cirurgia, retorna 0.
*/
int calculaQtdCirurgiaPacientesBancoGerenciador(Gerenciador *g)
{
    int total = 0;

    for (int i = 0; i < g->tamBanco; i++)
    {
        total += getQtdCirurgiasPaciente(g->bancoPacientes[i]);
    }

    return total;
}

/*
Função que imprime o relatório do gerenciador de acordo com a descrição da atividade.
*/
void imprimeRelatorioGerenciador(Gerenciador *g)
{
    printf("TOTAL PACIENTES: %d\n", g->tamBanco);
    printf("MEDIA IDADE (ANOS): %d\n", calculaMediaIdadePacientesBancoGerenciador(g));
    printf("TOTAL LESOES: %d\n", calculaQtdLesoesPacientesBancoGerenciador(g));
    printf("TOTAL CIRURGIAS: %d\n", calculaQtdCirurgiaPacientesBancoGerenciador(g));

    imprimePacientesBancoGerenciador(g);
}
