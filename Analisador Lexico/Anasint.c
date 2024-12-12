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
	if (tk.cat != SN || tk.codigo != ATRIB) {
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
 
	t = Analex(fd);
	if (t.cat == SN && (t.codigo == ADICAO || t.codigo == SUBTRACAO)) {
		t.processado = true;
		Termo();
		Resto();
	}
}

void Sobra() {

	t = Analex(fd);
	if(t.cat == SN && (t.codigo == MULTIPLIC || t.codigo == DIVISAO)) {
		t.processado = true;
		Fator();
		Sobra();
	}
}

void Fator() {

	t = Analex(fd);
	if (t.cat == ID) { 
		t.processado = true;
		/*TRATAR IDENTIFICADOR*/
	}
	else if (t.cat == CT_I) {
		t.processado = true; 
		/*TRATAR CONSTANTE INTEIRA*/
	}
	else if (t.cat == SN && t.codigo == ABRE_PAR) {
		t.processado = true;
		Expr();
		if(t.cat != SN || t.codigo != FECHA_PAR) {
			erro("Fecha parênteses esperado!");
		}
		else {
			t.processado = true;
		}
	}
	else {
		erro("Identificador, constante inteira ou abre parênteses esperado!");
	}
}
