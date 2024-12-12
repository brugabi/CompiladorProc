#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <stdbool.h>

// Estrutura para representar um símbolo
typedef struct Simbolo {
    char *lexema;
    char *escopo;
    char *tipo;
    char *categoria;
    char *passagem;
    bool zumbi;
    bool array;
    int dim1;
    int dim2;
    int endereco;
    char *rotulo;
    struct Simbolo *proximo;
} Simbolo;

// Estrutura para um quadro de escopo na pilha
typedef struct QuadroEscopo {
    Simbolo *simbolos;
    struct QuadroEscopo *anterior;
} QuadroEscopo;

// Estrutura para a pilha de escopos
typedef struct {
    QuadroEscopo *topo;
} PilhaEscopos;

// Funções para manipular a tabela de símbolos
PilhaEscopos* criarPilhaEscopos();
void destruirPilhaEscopos(PilhaEscopos *pilha);
void empilharEscopo(PilhaEscopos *pilha);
void desempilharEscopo(PilhaEscopos *pilha);
void adicionarSimbolo(PilhaEscopos *pilha, const char *lexema, const char *escopo, const char *tipo,
                      const char *categoria, const char *passagem, bool zumbi, bool array, int dim1,
                      int dim2, int endereco, const char *rotulo);
Simbolo* buscarSimbolo(PilhaEscopos *pilha, const char *lexema);

#endif // TABELA_SIMBOLOS_H
