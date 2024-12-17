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

int MAX_ARRAY_DIM = 2;

void consomer(int esperado)
{
	if ((unsigned int)tk.cat = (unsigned int)esperado || (unsigned int)tk.codPR == (unsigned int)esperado || (unsigned int)tk.codSN == (unsigned int)esperado)
	{
		tk = AnaLex(fd);
	}
	else
	{
		error("Erro de sintaxe na linha");
	}
}

void op_relacional()
{
	bool eh_op_relacional;
	eh_op_relacional = tk.cat == SN && (tk.codSN == MAIOR || tk.codSN == MENOR || tk.codSN == IGUALDADE || tk.codSN == MAIOR || tk.codSN == MENOR || tk.codSN == MENOR_IGUAL || tk.codSN == MAIOR_IGUAL || tk.codSN == DIF || tk.codSN == ECOM || tk.codSN == OP_OR || tk.codSN == OP_AND);
	if (eh_op_relacional)
		consomer(tk.codSN);
}

void eh_tipo()
{
	bool eh_tipo;
	eh_tipo = (tk.cat == PR) && ((tk.codPR == INT) || (tk.codPR == REAL) || (tk.codPR == CHAR) || (tk.codPR == BOOL));
	if (!eh_tipo)
		erro("Tipo esperado.");
}

void decl_list_var()
{

	bool eh_const;
	int tipo;
	eh_const = ((tk.cat == PR) && (tk.codPR == CONST));

	if (eh_const)
		tk = AnaLex(fd);

	eh_tipo();

	tipo = tk.codPR;
	decl_var(tipo, eh_const);
	tk = AnaLex(fd);

	while ((tk.cat == SN) && (tk.codSN == VIRGULA))
	{
		tk = AnaLex(fd);
		decl_var(tipo, eh_const);
	}
}

void decl_var(int tipo, bool eh_const)
{

	int k, i;

	bool eh_array;

	int cont_dim = 0;

	int tam_dims[MAX_ARRAY_DIM];

	int catTk;

	if (tk.cat != ID)
		erro("Identificador esperado");

	k = consulta_tab_simb(tk.lexema);

	//if ((k != -1) && (ts[k].linha.escopo == escopo_atual))
	//	erro("Redeclaração de identificador");

	//k = insere_tab_simb(tk.lexema, escopo_atual); // parte fixa

	tk = AnaLex(fd);

	eh_array = ((tk.cat == SN) && (tk.codSN == ABRE_COL));

	if (eh_array)
	{

		while ((tk.cat == SN) && (tk.codSN == ABRE_COL))
		{

			cont_dim++;

			if (cont_dim > MAX_ARRAY_DIM)
				erro("Número de dimensões do array maior que limite!");

			tk = AnaLex(fd);

			if (tk.cat == CT_I)
			{

				tam_dims[cont_dim - 1] = tk.valINT;

				tk = AnaLex(fd);
			}

			else if (tk.cat == ID)
			{

				//w = consulta_tab_simb(tk.lexema);
				/*
				if (w == -1)
					erro("Identificado constante dimensão do array não declarado");

				if (ts[w].linha.eh_const == NAO)
					erro("Identificador dimensão array deve ser constante");

				if (ts[w].linha.tipo != INT)
					erro("Identificador dimensão array deve ser do tipo inteiro");

				tam_dims[cont_dim - 1] = ts[w].linha.valor_const.inteiro;
				*/
				tk = AnaLex(fd);
			}

			else
				erro("Dimensão de array identificador constante inteiro ou constante inteira esperada");

			if ((tk.cat != SN) && (tk.codSN == FECHA_COL))
				erro("Fecha colchete esperado");

			tk = AnaLex(fd);
		}

		//insere_tab_simb_decl_var_array(k, tipo, (escopo_atual == GBL ? VG : VL), cont_dim, tam_dims, eh_const); // parte variável
	}

	else
	{

		//insere_tab_simb_decl_var_escalar(k, tipo, (escopo_atual == GBL ? VG : VL), VS, eh_const);
	}

	if (eh_const)

		if (!((tk.cat == SN) && (tk.codSN == ATRIB)))
			erro("Declaração de identificador constante necessita inicialização");

	if ((tk.cat == SN) && (tk.codSN == ATRIB))
	{

		// processa sintaxe de inicialização de variável simples ou de array (atualiza tab. simb para valor de ident. constante)

		switch (tipo)
		{

		case INT:
			catTk = CT_I;
			break;

		case REAL:
			catTk = CT_R;
			break;

		case CHAR:
			catTk = CT_C;
			break;

		default:;
		}

		if (eh_array)
		{

			tk = AnaLex(fd);

			if (!(tk.cat == SN) && (tk.codSN == ABRE_CHAVES))
				erro("Incialização de array inválida");

			tk = AnaLex(fd);

			while (1)
			{

				if (tk.cat != catTk)
					erro("Tipo de dado de inicialização de array inválido");

				tk = AnaLex(fd);

				if ((tk.cat == SN) && (tk.codSN == VIRGULA))
				{

					tk = AnaLex(fd);

					continue;
				}

				else if ((tk.cat == SN) && (tk.codSN == FECHA_CHAVES))
				{

					break;
				}

				else
					erro("Vírgula ou fecha parênteses esperado");
			}
		}

		else
		{

			tk = AnaLex(fd);

			if (tk.cat != catTk)
				erro("Tipo de dado de inicialização de varável escalar inválido");
		}
	}

	tk = AnaLex(fd);
}