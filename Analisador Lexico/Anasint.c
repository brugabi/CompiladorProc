/*  Gramática livre de Contexto de Cálcula   
    
    <ARTIB> ::= ID = <EXPR>
	<EXPR> ::= <TERMO> <RESTO>
	<RESTO> ::= + <TERMO> <RESTO> |	- <TERMO> <RESTO> | e
	<TERMO> ::= <FATOR> <SOBRA>
	<SOBRA> ::= * <FATOR> <SOBRA> | / <FATOR> <SOBRA> | e
	<FATOR> ::= CT_I | ID | (<EXPR>)

   Símbolo de partida: <ATRIB>

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Analex.h"
#include "Anasint.h"
#include "Funcaux.h"


void Atrib() {
 
	if (tk.cat != ID) {
		erro("Identificador esperado!");
	}
	tk.processado = true;
	tk = AnaLex(fd);
	if (tk.cat != SN || tk.codSN != ATRIB) {
		erro("Sinal de atribuição esperado!");
	}
	tk.processado = true;
	Expr();  
}


void Expr() {

	Termo();
	Resto();
}

void Termo(){

	Fator();
	Sobra();
}

void Resto() {
 
	tk = AnaLex(fd);
	if (tk.cat == SN && (tk.codSN == ADICAO || tk.codSN == SUBTRACAO)) {
		tk.processado = true;
		Termo();
		Resto();
	}
}

void Sobra() {

	tk = AnaLex(fd);
	if(tk.cat == SN && (tk.codSN == DIV || tk.codSN == MULTI)) {
		tk.processado = true;
		Fator();
		Sobra();
	}
}

void Fator() {

	tk = AnaLex(fd);
	if (tk.cat == ID) { 
		tk.processado = true;
		/*TRATAR IDENTIFICADOR*/
	}
	else if (tk.cat == CT_I) {
		tk.processado = true; 
		/*TRATAR CONSTANTE INTEIRA*/
	}
	else if (tk.cat == SN && tk.codSN == ABRE_PAR) {
		tk.processado = true;
		Expr();
		if(tk.cat != SN || tk.codSN != FECHA_PAR) {
			erro("Fecha parênteses esperado!");
		}
		else {
			tk.processado = true;
		}
	}
	else {
		erro("Identificador, constante inteira ou abre parênteses esperado!");
	}
}
