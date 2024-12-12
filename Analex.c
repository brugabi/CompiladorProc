#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Analex.h"
#include "Funcaux.h"

#define TAM_LEXEMA 31
#define TAM_NUM 30
#define TAM_MAX_PALAVRAS_RESERVADAS 32

TOKEN AnaLex (FILE *fd) {
    int estado = 0;
    char lexema[TAM_MAX_LEXEMA] = "";
    int tamL = 0;
    char digitos[TAM_NUM] = "";
    int tamD = 0;

    if (!tk.processado == true) return tk; // O token atual ainda não foi processado

    tk.processado = false;
    while (1){
        char c = fgetc(fd);
        switch (estado){
        case 0:
            if (c == ' ' || c == '\t') estado = 0;
            //SINAIS
            else if (c == '+') { estado = 1; tk.cat = SN; tk.codSN = ADICAO; return tk;}
            else if (c == '-') { estado = 2; tk.cat = SN; tk.codSN = SUBTRACAO; return tk;}
            else if (c == '*') { estado = 3; tk.cat = SN; tk.codSN = MULTI; return tk;}
            else if (c == '/') { estado = 4;} //divisao ou comentariio
            else if (c == '>') { estado = 7;} //maior ou maior igual
            else if (c == '<') { estado = 10;} //menor ou menor igual
            else if (c == '=') {estado = 13;} //atribuicao ou igualdade
            else if (c == '(') { estado = 16; tk.cat = SN; tk.codSN = ABRE_PAR; return tk;}
            else if (c == ')') { estado = 17; tk.cat = SN; tk.codSN = FECHA_PAR; return tk;}
            else if (c == '[') { estado = 18; tk.cat = SN; tk.codSN = ABRE_COL; return tk;}
            else if (c == ']') { estado = 19; tk.cat = SN; tk.codSN = FECHA_COL; return tk;}
            else if (c == '|') {estado = 20;} //talvez operador ou
            else if (c == '&') { estado = 22;} // operador and ou endereco
            else if (c == ',') { estado = 25; tk.cat = SN; tk.codSN = VIRGULA; return tk;}
            else if (c == '!') { estado = 26;} //diferenca ou negacao
            else if (c == EOF) { tk.cat = FIM_ARQ; return tk; } // FIM DO ARQUIVO
            else if (c == '\n') {tk.cat = FIM_EXPR; contLinha++; return tk;} //FIM DE LINHA
            else if (c == '{') {estado = 47; tk.cat = SN; tk.codSN = ABRE_CHAVES; return tk;}
            else if (c == '}') {estado = 48; tk.cat = SN; tk.codSN = FECHA_CHAVES; return tk;}
            //ID
            else if (c == '_') {
                estado = 29;
                lexema[tamL++] = c;
                lexema[tamL] = '\0';
            }
            else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                estado = 30;
                lexema[tamL++] = c;
                lexema[tamL] = '\0';
            }
            //DIGITO
            else if (c >= '0' && c <='9') {
                estado = 32;
                digitos[tamD++] = c;
                digitos[tamD]= '\0';
            }
            //CHAR
            else if (c == '\'')estado = 37; //pode ser um char, um \n ou um \0
            //STRING
            else if (c == '"') estado = 43; //ESTADO PARA STRING
            else error("CARACTER INVALIDO NA LINHA");
            break;
        case 4: //COMENTARIO OU DIVISAO
            if (c == '/') estado = 5; // COMENTARIO
            else {
                //DIVISAO
                estado = 6;
                ungetc(c,fd);
                tk.cat = SN;
                tk.codSN = DIV;
                return tk;
            }
            break;
        case 5: //COMENTARIO
            if (c == '\n') {
                estado = 0;
                ungetc(c,fd);
            }
            break;
        case 7:
            if (c == '=') {estado = 8; tk.cat = SN; tk.codSN = MAIOR_IGUAL; return tk;} //MAIOR IGUAL
            else {estado = 9; ungetc(c,fd); tk.cat = SN; tk.codSN = MAIOR; return tk;} //MAIOR
            break;
        case 10:
            if (c == '=') {estado = 11; tk.cat = SN; tk.codSN = MENOR_IGUAL; return tk;} //MENOR IGUAL
            else {estado = 12; ungetc(c,fd); tk.cat = SN; tk.codSN = MENOR; return tk;} //MENOR
            break;
        case 13: //ATRIB OU IGUALDADE
            if (c == '=') {estado = 14; tk.cat = SN; tk.codSN = IGUALDADE; return tk;} //IGUALDADE
            else {estado = 15; ungetc(c,fd); tk.cat = SN; tk.codSN = ATRIB; return tk;} //ATRIBUICAO
            break;
        case 20:
            if (c == '|') {estado = 21; tk.cat = SN; tk.codSN = OP_OR; return tk;} //OPERADOR OR
            else error("CARACTER INVALIDO NA LINHA");
            break;
        case 22:
            if (c == '&') {estado = 23; tk.cat = SN; tk.codSN = OP_AND; return tk;} //OPERADOR AND
            else { // E COMERCIAL
                estado = 24;
                ungetc(c, fd);
                tk.cat = SN;
                tk.codSN = ECOM;
                return tk;
            }
            break;
        case 26:
            if (c == '=') {estado = 27; tk.cat = SN; tk.codSN = DIF; return tk;} //DIFERENCA
            else {estado = 28; ungetc(c,fd); tk.cat = SN; tk.codSN = NEGACAO; return tk;} //NEGACAO
            break;
        //CASOS DE ID
        case 29: //UNDERLINE OPCIONAL
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                estado = 30;
                lexema[tamL++] = c;
                lexema[tamL] = '\0'; 
            }
            else {
                estado = 29;
                lexema[tamL++] = c;
                lexema[tamL] = '\0'; 
            }
            break;
        case 30: //CASO NECESSÁRIO DE LETRA
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_') {
                lexema[tamL++] = c;
                lexema[tamL] = '\0'; 
            }
            else{
                estado = 31; //ACABOU O ID
                ungetc(c, fd);
                int checkPR = is_PR(lexema);
                //VERIFICAR PALAVRA RESERVADA
                if (checkPR >= 0) {
                    tk.cat = PALAVRAS_RESERVADAS;
                    tk.codPR = checkPR;
                    return tk;
                }
                else {tk.cat = ID;}
                strcpy(tk.lexema, lexema);
                return tk;
            }
            break;
        case 32: //INT OU REAL
            if (c >= '0' && c <= '9') {
                estado = 32;
                digitos[tamD++] = c;
                digitos[tamD]= '\0';
            }
            else if (c == '.') { //REAL
                estado=34;
                digitos[tamD++] = c;
                digitos[tamD]= '\0';
            }
            else { //ACABOU O INT
                estado = 33;
                ungetc(c, fd);
                tk.cat = CT_I;
                tk.valINT = atoi(digitos);
                return tk;
            }
            break;
        case 34: //CASO DO REAL
            if (c >= '0' && c <= '9') {
                estado = 35;
                digitos[tamD++] = c;
                digitos[tamD]= '\0';
            }
            break;
        case 35:
            if (c >= '0' && c <= '9') {
                estado = 35;
                digitos[tamD++] = c;
                digitos[tamD]= '\0';
            }
            else { //ACABOU O REAL
                estado = 36;
                ungetc(c, fd);
                tk.cat = CT_R;
                tk.valREAL = atof(digitos);
                return tk; 
            }
            break;
        case 37: //CHAR
            if (c == '\\') { estado = 40; } //CHAR COM \n ou \0
            else if (isprint(c) && c != '\'') { //CHAR COM QUALQUER CACATER ASCII MENOS O APOSTOFRO
                estado = 38;
                lexema[tamL++] = c;
                lexema[tamL] = '\0'; 
            }
            break;
        case 38: 
            if(c =='\'') { //ACABOU O CHAR COM 1 CARACTER
            estado = 39;
            tk.cat = CT_C;
            tk.charcon = lexema[0];
            return tk;
            }
            else error("ERROR: LEXEMA CHAR INVALIDO NA LINHA NA LINHA");
            break;
        case 40:
            if (c == 'n') estado = 41;  //CHAR COM \n
            else if (c == '0') estado = 42; //CHAR COM \0
            else error("ERROR: LEXEMA CHAR INVALIDO NA LINHA NA LINHA");
            break;
        case 41: 
            if (c =='\'') { //ACABOU O CHAR COM \n
                estado=45; 
                tk.cat = CT_C;
                tk.charcon = '\n';
                return tk;
                } 
            else error("ERROR: LEXEMA CHAR INVALIDO NA LINHA NA LINHA");
            break;
        case 42: 
            if (c =='\'') {
                estado=46; //ACABOU O CHAR COM \0
                tk.cat = CT_C;
                tk.charcon = '\0'; 
                return tk;
                }
            else error("ERROR: LEXEMA CHAR INVALIDO NA LINHA NA LINH");
            break;
        case 43: //STRING
            if (c == '"') {
                estado = 44;
                tk.cat = LT;
                strcpy(tk.lexema, lexema);
                return tk;
            }
            else if(isprint(c) && c != '\n') { //ACABOU A STRING
                estado = 43;
                lexema[tamL++] = c;
                lexema[tamL] = '\0';
            }
            else error("ERROR: LEXEMA STRING INVALIDO NA LINHA NA LINH");
            break;
        }
    }
    
}


const char arrayPR[TAM_MAX_PALAVRAS_RESERVADAS][31] = {
    "const",
    "pr",
    "init",
    "endp",
    "char",
    "int",
    "real",
    "bool",
    "do",
    "while",
    "endw",
    "var",
    "from",
    "to",
    "dt",
    "by",
    "if",
    "endv",
    "elif",
    "else",
    "endi",
    "getout",
    "getint",
    "getreal",
    "getchar",
    "putint",
    "putreal",
    "putchar",
    "putstring",
    "getstring",
    "prot",
    "def" 
};

int is_PR(const char* lexema) {
        
    for (int i = 0; i < TAM_PALAVRAS_RESERVADAS; i++) {

        if (strcmp(lexema, arrayPR[i]) == 0) {
            return i; // É uma palavra reservada
        }
    }
    return -1; // Não é uma palavra reservada
}