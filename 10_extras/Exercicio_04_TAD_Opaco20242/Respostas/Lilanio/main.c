#include "brasileirao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    BRA *br = CriaCamp();
    RealizaCamp(br);
    FinalizaCamp(br);

    return 0;
}