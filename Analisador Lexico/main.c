#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "Analex.h"
#include "Anasint.h"
#include "Funcaux.h"

FILE *fd;
TOKEN tk;
int contLinha;
char TABS[200] = "";

void TestaAnalex()
{

    if ((fd = fopen("expressao.dat", "r")) == NULL)
        error("ARQUIVO DE EXPRESSAO NAO ENCONTRADO!!");

    printf("\nLINHA %d\n", contLinha);
    tk.processado = true; // Garante que o proximo token seja processado
    while (1)
    {
        tk = AnaLex(fd);

        if (tk.cat == FIM_ARQ)
        {
            error("Fim do arquivo fonte encontrado!\n");
            break;
        }

        switch (tk.cat)
        {
        case SN:
            switch (tk.codSN)
            {
            case ADICAO:
                printf("<SN, ADICAO>");
                break;
            case SUBTRACAO:
                printf("<SN, SUBTRACAO>");
                break;
            case MULTI:
                printf("<SN, MULTIPLICACAO>");
                break;
            case DIV:
                printf("<SN, DIVISAO>");
                break;
            case MAIOR_IGUAL:
                printf("<SN, MAIOR_IGUAL>");
                break;
            case MAIOR:
                printf("<SN, MAIOR>");
                break;
            case MENOR_IGUAL:
                printf("<SN, MENOR_IGUAL>");
                break;
            case MENOR:
                printf("<SN, MENOR>");
                break;
            case ATRIB:
                printf("<SN, ATRIBUICAO>");
                break;
            case IGUALDADE:
                printf("<SN, IGUALDADE>");
                break;
            case ABRE_PAR:
                printf("<SN, ABRE_PARENTESES>");
                break;
            case FECHA_PAR:
                printf("<SN, FECHA_PARENTESES>");
                break;
            case ABRE_COL:
                printf("<SN, ABRE_COLCHETES>");
                break;
            case FECHA_COL:
                printf("<SN, FECHA_COLCHETES>");
                break;
            case OP_OR:
                printf("<SN, OPERADOR_OR>");
                break;
            case OP_AND:
                printf("<SN, OPERADOR_AND>");
                break;
            case ECOM:
                printf("<SN, E_COMERCIAL>");
                break;
            case VIRGULA:
                printf("<SN, VIRGULA>");
                break;
            case DIF:
                printf("<SN, DIFERENCA>");
                break;
            case NEGACAO:
                printf("<SN, NEGACAO>");
                break;
            }
            break;
        case ID:
            printf("<ID, %s>", tk.lexema);
            break;
        case PALAVRAS_RESERVADAS:
            switch (tk.codPR)
            {
            case CONST:
                printf("<PR, CONST>");
                break;
            case PR:
                printf("<PR, PR>");
                break;
            case INIT:
                printf("<PR, INIT>");
                break;
            case ENDP:
                printf("<PR, ENDP>");
                break;
            case CHAR:
                printf("<PR, CHAR>");
                break;
            case INT:
                printf("<PR, INT>");
                break;
            case REAL:
                printf("<PR, REAL>");
                break;
            case BOOL:
                printf("<PR, BOOL>");
                break;
            case DO:
                printf("<PR, DO>");
                break;
            case WHILE:
                printf("<PR, WHILE>");
                break;
            case ENDW:
                printf("<PR, ENDW>");
                break;
            case VAR:
                printf("<PR, VAR>");
                break;
            case FROM:
                printf("<PR, FROM>");
                break;
            case TO:
                printf("<PR, TO>");
                break;
            case DT:
                printf("<PR, DT>");
                break;
            case BY:
                printf("<PR, BY>");
                break;
            case IF:
                printf("<PR, IF>");
                break;
            case ENDV:
                printf("<PR, ENDV>");
                break;
            case ELIF:
                printf("<PR, ELIF>");
                break;
            case ELSE:
                printf("<PR, ELSE>");
                break;
            case ENDI:
                printf("<PR, ENDI>");
                break;
            case GETOUT:
                printf("<PR, GETOUT>");
                break;
            case GETINT:
                printf("<PR, GETINT>");
                break;
            case GETREAL:
                printf("<PR, GETREAL>");
                break;
            case GETCHAR:
                printf("<PR, GETCHAR>");
                break;
            case PUTINT:
                printf("<PR, PUTINT>");
                break;
            case PUTREAL:
                printf("<PR, PUTREAL>");
                break;
            case PUTCHAR:
                printf("<PR, PUTCHAR>");
                break;
            }
            break;
        case CT_I:
            printf("<CT_I, %d>", tk.valINT);
            break;
        case CT_R:
            printf("<CT_R, %f>", tk.valREAL);
            break;
        case CT_C:
            printf("<CT_C, %c>", tk.charcon);
            break;
        case LT:
            printf("<LT, %s>", tk.lexema);
            break;
        case FIM_EXPR:
            printf("<FIM DA EXPRESSAO ENCONTRADA>\n");
            break;
        case FIM_ARQ:
            printf("<FIM DO ARQUIVO ENCONTRADO>\n");
            break;
        }

        if (tk.cat == FIM_ARQ) {break;} // break do while
        tk.processado = true;
    }
    fclose(fd);
}

void TestaAnasint() {

    if ((fd = fopen("expressao.txt", "r")) == NULL) {
        error("Arquivo de expressao nao encontrado!");
    }

    tk.processado = true; // Garante que o primeiro token seja lido

    while (true) {
        tk = AnaLex(fd);
        if (tk.cat == FIM_ARQ) {break;} // break do while
        //Atrib();
        if(tk.cat == FIM_EXPR) {
            printf("Linha %d: expressão sintaticamente correta!\n\n", contLinha);
        } else {
            error("Expressão sintaticamente incorreta!\n\n");
        }
        tk.processado = true;
    }
    fclose(fd);
}

int main()
{

    //system("chp 65001"); // Troca a codificação para UTF-8

    contLinha = 1;
    printf("\n\n[-------------------Análise Léxica -------------------]\n");
    TestaAnalex();

    contLinha = 1;
    printf("\n\n[-------------------Análise Sintática ----------------]\n");

    return 0;
}
