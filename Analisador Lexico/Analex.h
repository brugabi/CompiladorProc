#ifndef ANALEX
#define ANALEX

#include <stdio.h>
#include <stdbool.h>

#define TAM_MAX_LEXEMA 31
#define TAM_PALAVRAS_RESERVADAS 28

//CT_ I = INTEIRO CT_R = REAL LT = STRING PR = PALAVRAS RESERVADAS SN = SINAIS
enum TOKEN_CAT {ID = 1, CT_I, CT_R, CT_C, LT, PALAVRAS_RESERVADAS, SN, FIM_EXPR, FIM_ARQ};

//OP_OR = OPERADOR OU "||" OP_AND = OPERADOR E "&&" 
enum SINAIS {ADICAO = 1, SUBTRACAO, MULTI, DIV, MAIOR, MAIOR_IGUAL, MENOR, MENOR_IGUAL, ATRIB, IGUALDADE, ABRE_PAR,
                FECHA_PAR, ABRE_COL, FECHA_COL, OP_OR, ECOM, OP_AND, VIRGULA, NEGACAO, DIF}; //ECOM = E COMERCIAL

typedef struct token{
    enum TOKEN_CAT cat; // deve receber o enum TOKEN_CAT
    bool processado; // Indica se o token foi processado
    union{
        int codPR;
        int codSN;
        char lexema[TAM_MAX_LEXEMA];
        char charcon;
        int valINT;
        float valREAL;

    };
    
} TOKEN;

typedef enum {
    CONST,
    PR,
    INIT,
    ENDP,
    CHAR,
    INT,
    REAL,
    BOOL,
    DO,
    WHILE,
    ENDW,
    VAR,
    FROM,
    TO,
    DT,
    BY,
    IF,
    ENDV,
    ELIF,
    ELSE,
    ENDI,
    GETOUT,
    GETINT,
    GETREAL,
    GETCHAR,
    PUTINT,
    PUTREAL,
    PUTCHAR,

} PalavrasReservadas;


// Função para verificar se e PR
int is_PR(const char* lexema);

/* VARIAVEIR GLOBAIS */
extern TOKEN tk;
extern FILE *fd;
extern int contLinha;
extern const char arrayPR[TAM_PALAVRAS_RESERVADAS][TAM_MAX_LEXEMA];

/* Assinaruras de funções */
TOKEN AnaLex(FILE *fd);

#endif