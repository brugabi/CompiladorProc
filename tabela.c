#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

// Função para criar uma nova pilha de escopos
PilhaEscopos* criarPilhaEscopos() {
    PilhaEscopos *pilha = (PilhaEscopos *)malloc(sizeof(PilhaEscopos));
    pilha->topo = NULL;
    return pilha;
}

// Função para destruir a pilha de escopos
void destruirPilhaEscopos(PilhaEscopos *pilha) {
    while (pilha->topo != NULL) {
        desempilharEscopo(pilha);
    }
    free(pilha);
}

// Empilhar um novo escopo
void empilharEscopo(PilhaEscopos *pilha) {
    QuadroEscopo *novoQuadro = (QuadroEscopo *)malloc(sizeof(QuadroEscopo));
    novoQuadro->simbolos = NULL;
    novoQuadro->anterior = pilha->topo;
    pilha->topo = novoQuadro;
}

// Desempilhar o escopo atual
void desempilharEscopo(PilhaEscopos *pilha) {
    if (pilha->topo == NULL) return;

    QuadroEscopo *topoAtual = pilha->topo;
    Simbolo *simboloAtual = topoAtual->simbolos;

    while (simboloAtual != NULL) {
        Simbolo *temp = simboloAtual;
        simboloAtual = simboloAtual->proximo;
        free(temp->lexema);
        free(temp->escopo);
        free(temp->tipo);
        free(temp->categoria);
        free(temp->passagem);
        free(temp->rotulo);
        free(temp);
    }

    pilha->topo = topoAtual->anterior;
    free(topoAtual);
}

// Adicionar um símbolo ao escopo atual
void adicionarSimbolo(PilhaEscopos *pilha, const char *lexema, const char *escopo, const char *tipo,
                      const char *categoria, const char *passagem, bool zumbi, bool array, int dim1,
                      int dim2, int endereco, const char *rotulo) {
    if (pilha->topo == NULL) {
        empilharEscopo(pilha);
    }

    Simbolo *novoSimbolo = (Simbolo *)malloc(sizeof(Simbolo));
    novoSimbolo->lexema = strdup(lexema);
    novoSimbolo->escopo = strdup(escopo);
    novoSimbolo->tipo = strdup(tipo);
    novoSimbolo->categoria = strdup(categoria);
    novoSimbolo->passagem = strdup(passagem);
    novoSimbolo->zumbi = zumbi;
    novoSimbolo->array = array;
    novoSimbolo->dim1 = dim1;
    novoSimbolo->dim2 = dim2;
    novoSimbolo->endereco = endereco;
    novoSimbolo->rotulo = strdup(rotulo);
    novoSimbolo->proximo = pilha->topo->simbolos;

    pilha->topo->simbolos = novoSimbolo;
}

// Buscar um símbolo em todos os escopos
Simbolo* buscarSimbolo(PilhaEscopos *pilha, const char *lexema) {
    QuadroEscopo *quadroAtual = pilha->topo;

    while (quadroAtual != NULL) {
        Simbolo *simboloAtual = quadroAtual->simbolos;

        while (simboloAtual != NULL) {
            if (strcmp(simboloAtual->lexema, lexema) == 0) {
                return simboloAtual;
            }
            simboloAtual = simboloAtual->proximo;
        }

        quadroAtual = quadroAtual->anterior;
    }

    return NULL;
}
