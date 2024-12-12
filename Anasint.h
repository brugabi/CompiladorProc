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

void prog();
void cmd();
void decl_def_proc();
void decl_list_var();
void decl_var();

#endif // ANASINT