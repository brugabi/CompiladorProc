#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Funcaux.h"

void error(char msg[]) {
    printf("LINHA %d: %s\n", contLinha, msg);
    exit(1);
}