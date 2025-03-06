
#include "servidor.h"


int main() {

    Servidor serv = leRegistrosServidor();
    criaRelatorioServidor(serv);

    return 0;
}