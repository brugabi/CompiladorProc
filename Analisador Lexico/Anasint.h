#ifndef _ANASINT_
#define _ANASINT_

#include <stdio.h>
#include <stdbool.h>
#include "Analex.h"


/* Variaveis globais */
extern TOKEN tk;
extern FILE *fd;
extern int contLinha;

extern char TABS[200];

/* Assinaturas das funcoes */
void Atrib();
void Expr();
void Termo();
void Resto();
void Sobra();
void Fator();

#endif // ANASINT