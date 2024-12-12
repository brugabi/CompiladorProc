#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Funcaux.h"

void erro(char msg[]) {
    printf("LINHA %d: %s\n", contLinha, msg);
    exit(1);
}