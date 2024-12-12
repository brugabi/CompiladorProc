#ifndef _FUNC_AUX_
#define _FUNC_AUX_

#include <stdbool.h>

enum MOVIM {AVANCA, MANTEM, RETROCEDE};

extern bool mostraArvore;
extern char TABS[200];
extern int contLinha;

void error(char msg[]);

#endif