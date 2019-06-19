/***************************************************************************
*  $MCI Módulo de implementação: TAB  tabuleiro
*
*  Arquivo gerado:              tabuleiro.c
*  Letras identificadoras:      TAB
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data			Observações
*		3		yz		11/05/2019	Correção de um loop infinito em montaTabuleiro
*		2		yz		29/04/2019	Correção do moverPeca e funções estáticas de impressão
*		1		yz		28/04/2019	Primeira versão das funções exportadas do módulo
***************************************************************************/

#include "tabuleiro.h"
#include <stdlib.h>
#include <string.h>

/***********************************************************************
*
*  $TC Tipo de dados: TAB Elemento da lista
*
*
***********************************************************************/

typedef struct casaOcupada CasaOcupada;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Elemento da lista
*
***********************************************************************/

struct casaOcupada {
	Casa* casa;
	Peca* peca;
};

/***********************************************************************
*
*  $TC Tipo de dados: TAB Elemento do tabuleiro
*
*  $ED Descrição do tipo
*     CasaOcupada - um ponteiro para um tipo struct
*
***********************************************************************/

struct tabuleiro {

	CasaOcupada *casasOcupadas;
	/*Ponteiro para vetor de casas ocupadas*/

	Casa **casasIniciais;
	/*Vetor de ponteiros*/

	Casa **casasSeguras;
	/*Vetor de ponteiros*/

	CIR_tppLista casas;
	/*Lista circular*/

	LIS_tppLista *retasFinais;
	/*Vetor de listas*/
};

/***** Protótipos das funções encapuladas no módulo *****/


static TAB_CondRet colocaPeca(Tabuleiro* pTab,
	Casa* casa,
	Peca* peca);

static TAB_CondRet criaJogador(Tabuleiro* pTab,
	COR_tpCor cor);

static Peca* retornaPeca(Tabuleiro* pTab,
	COR_tpCor cor,
	int numP);

static Casa* retornaCasaDaPeca(Tabuleiro* pTab,
	Peca* peca);

static TAB_CondRet criaRetaFinal(LIS_tppLista * lista,
	COR_tpCor cor);

static char* retornaStringPeca(Tabuleiro * pTab,
	int posReq);

static char* retornaStringPecaRetaFinal(Tabuleiro* pTab,
	int posReq,
	COR_tpCor cor);

static char* retornaStringPecaCasaInicial(Tabuleiro* pTab,
	COR_tpCor cor,
	int numCasa);

static TAB_CondRet imprimeCasaNormal(Tabuleiro* pTab,
	int linha);

static TAB_CondRet imprimeCasaRetaFinal(Tabuleiro* pTab,
	int linha,
	COR_tpCor cor);

static int quantPecasNaCasa(Tabuleiro* pTab,
	Casa* casa);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Cria Tabuleiro
*
*  ************************************************************************/


TAB_CondRet TAB_criaTabuleiro(Tabuleiro** pTab) {
	Tabuleiro		*pT;
	Casa			*casa;
	CasaOcupada		*casasOcupadas;
	Casa			**casasIniciais;
	Casa			**casasSeguras;
	CIR_tppLista	lCasas;
	LIS_tppLista	*retasFinais;
	int i,
		ret;

	lCasas = CIR_CriarLista(CAS_destruirCasa);

	if (lCasas == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */

	casasSeguras = (Casa * *)malloc(sizeof(Casa*) * 4);

	if (casasSeguras == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */

	pT = (Tabuleiro*)malloc(sizeof(Tabuleiro));

	if (pT == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */

	casasIniciais = (Casa **)malloc(sizeof(Casa*) * 16);

	if (casasIniciais == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */

	casasOcupadas = (CasaOcupada *)malloc(sizeof(CasaOcupada) * 16);

	if (casasOcupadas == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */

	retasFinais = (LIS_tppLista *)malloc(4 * sizeof(LIS_tppLista)); /* 4 Retas finais */

	if (retasFinais == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */

	for (i = 0; i < 52; i++) /* 52 casas na lista circular */ {

		if (i % TAB_INTERVALOCASASIGUAIS == 0)
		{
			/*É uma casa CAS_segura*/
			ret = CAS_criaCasaSegura(&casa, i / TAB_INTERVALOCASASIGUAIS);
			if (ret == CAS_condRetOk) {
				CIR_InserirElementoApos(lCasas, casa);
				casasSeguras[i / TAB_INTERVALOCASASIGUAIS] = casa;
			}
			else if (ret == CAS_condRetFaltouMemoria) {
				return TAB_CondRetFaltouMemoria;
			}
			else if (ret == CAS_condRetParametrosIncorretos) {
				return TAB_CondRetParametrosIncorretos;
			}/* if */


		}
		else if (i % (TAB_INTERVALOCASASIGUAIS) == 11) {
			/*É uma CAS_entrada */
			ret = CAS_criaEntrada(&casa, i % 11 == 6 ? 0 : ((i % 11) / 2) + 1);

			if (ret == CAS_condRetOk) {
				CIR_InserirElementoApos(lCasas, casa);
			}
			else if (ret == CAS_condRetFaltouMemoria) {
				return TAB_CondRetFaltouMemoria;
			}
			else if (ret == CAS_condRetParametrosIncorretos) {
				return TAB_CondRetParametrosIncorretos;
			}/* if */

		}
		else {
			ret = CAS_criaCasaComum(&casa);
			if (ret == CAS_condRetOk) {
				CIR_InserirElementoApos(lCasas, casa);
			}
			else if (ret == TAB_CondRetFaltouMemoria) {
				return TAB_CondRetFaltouMemoria;
			}/* if */

		}/* if */

	}/* for */

	for (i = 0; i < 4; i++) {
		ret = criaRetaFinal(&retasFinais[i], i);

		if (ret == TAB_CondRetFaltouMemoria) {
			return TAB_CondRetFaltouMemoria;
		}
		else if (ret == TAB_CondRetParametrosIncorretos) {
			return TAB_CondRetParametrosIncorretos;
		}
		else if (ret == TAB_CondRetParametrosIncorretos) {
			return TAB_CondRetParametrosIncorretos;
		}/* if */

	}/* for */

	for (i = 0; i < 16; i++) {
		ret = CAS_criaCasaInicial(&casa);

		if (ret == CAS_condRetOk) {
			casasIniciais[i] = casa;
		}
		else if (ret == CAS_condRetFaltouMemoria) {
			return TAB_CondRetFaltouMemoria;
		}/* if */

	}/* for */

	for (i = 0; i < 16; i++) {
		casasOcupadas[i].casa = NULL;
		casasOcupadas[i].peca = NULL;
	}/* for */


	pT->casas = lCasas;
	pT->casasIniciais = casasIniciais;
	pT->casasOcupadas = casasOcupadas;
	pT->casasSeguras = casasSeguras;
	pT->retasFinais = retasFinais;

	*pTab = pT;

	return TAB_CondRetOk;

} /* Fim função: TAB  &TAB_criaTabuleiro */

/***************************************************************************
*
*  Função: TAB  &Destroi Tabuleiro
*
*  ************************************************************************/

TAB_CondRet TAB_destroiTabuleiro(Tabuleiro* pTab) {
	int i;
	if (pTab == NULL) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	
	/*Limpar casas iniciais*/

	for (i = 0; i < 16; i++) {
		CAS_destruirCasa(pTab->casasIniciais[i]);
	}/* for */

	/*Limpar casas comuns e CAS_seguras*/

	CIR_DestruirLista(pTab->casas);

	/* Limpar retas finais*/

	for (i = 0; i < 4; i++) {
		LIS_DestruirLista(pTab->retasFinais[i]);
	}/* for */

	for (i = 0; i < 16; i++) {
		PEC_destruirPeca(pTab->casasOcupadas[i].peca);
	}/* for */

	/*Limpar casas ocupadas*/

	free(pTab->casasOcupadas);
	free(pTab);
	return TAB_CondRetOk;

}/* Fim função: TAB  &TAB_destroiTabuleiro */

/***************************************************************************
*
*  Função: TAB  &Monta Tabuleiro
*
*  ************************************************************************/

TAB_CondRet TAB_montaTabuleiro(Tabuleiro* pTab, int numJog, int* vetCor) {
	int i,
		ret;

	if (numJog < NUMJOG_MIN || numJog > NUMJOG_MAX || vetCor == NULL) {
		return TAB_CondRetParametrosIncorretos;
	} /* if */

	for (i = 0; i < numJog; i++) {
		ret = criaJogador(pTab, vetCor[i]);

		if (ret == TAB_CondRetFaltouMemoria) {
			return TAB_CondRetFaltouMemoria;
		} /* if */
		else if (ret == TAB_CondRetParametrosIncorretos) {
			return TAB_CondRetParametrosIncorretos;
		}
	}/* for */

	return TAB_CondRetOk;

} /* Fim função: TAB  &TAB_montaTabuleiro */

/***************************************************************************
*
*  Função: TAB  &Retorna Peca Para Casa Inicial
*
*  ************************************************************************/

TAB_CondRet TAB_retornaPecaParaCasaInicial(Tabuleiro* pTab, COR_tpCor cor, int numP) {
	int i,
		j,
		ret,
		verif = 0;
	Peca	*	peca = retornaPeca(pTab,
		cor,
		numP);
	Casa	*	casaIni = retornaCasaDaPeca(pTab,
		peca);
	CAS_tpTipo tipo;

	if (pTab == NULL || cor < COR_MIN || cor > COR_MAX || numP < PEC_MIN || numP > PEC_MAX) {
		return TAB_CondRetParametrosIncorretos;
	}  /* if */

	ret = CAS_retornaTipo(casaIni,
		&tipo);

	if (ret == CAS_condRetParametrosIncorretos) {
		return TAB_CondRetParametrosIncorretos;
	} /* if */

	if (tipo == CAS_inicial) {
		return TAB_CondRetOk;
	} /* if */

	for (i = cor * 4; i < (cor * 4) + 1; i++) {
		verif = 1;

		for (j = cor * 4; j < (cor * 4) + 1; j++) { // checa qual casa inicial i está vazia, vendo cada um das pecas j
			if (pTab->casasIniciais[i] == pTab->casasOcupadas[j].casa) {
				verif = 0;
			} /* if */

		}/* for */

		if (verif) {
			ret = colocaPeca(pTab, pTab->casasIniciais[i], peca);
			return ret;
		} /* if */

	}/* for */

}/* Fim função: TAB  &TAB_retornaPecaParaCasaInicial */

/***************************************************************************
*
*  Função: TAB  &Mover Peca
*
*  ************************************************************************/

TAB_CondRet TAB_moverPeca(Tabuleiro* pTab, int numCasas, COR_tpCor cor, int numP) {
	Peca	*peca = retornaPeca(pTab, cor, numP);
	int i,
		ret;

	CAS_tpTipo	    tipo;
	COR_tpCor		corCasa;
	Casa*	    	casaIni = retornaCasaDaPeca(pTab, peca);

	if (pTab == NULL || cor < COR_MIN || cor > COR_MAX || numP < PEC_MIN || numP > PEC_MAX || peca == NULL || numCasas <= 0) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	ret = CAS_retornaTipo(casaIni, &tipo);

	if (ret == CAS_condRetParametrosIncorretos) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	/*peca esta na casa inicial*/
	if (tipo == CAS_inicial) {

		if (numCasas == 1 || numCasas == 6) {
			ret = colocaPeca(pTab, pTab->casasSeguras[cor], peca);
		}/* if */

		return ret;
	}
	else {
		for (i = 0; i < numCasas; i++) {
			switch (tipo)
			{
			case CAS_comum:

				CIR_ProcurarValor(pTab->casas, casaIni);
				CIR_AvancarElementoCorrente(pTab->casas, 1);
				casaIni = CIR_ObterValor(pTab->casas);

				break;

			case CAS_segura:

				CIR_ProcurarValor(pTab->casas, casaIni);
				CIR_AvancarElementoCorrente(pTab->casas, 1);
				casaIni = CIR_ObterValor(pTab->casas);

				break;

			case CAS_final:

				IrFinalLista(pTab->retasFinais[cor]);

				if (LIS_ObterValor(pTab->retasFinais[cor]) == casaIni) {
					LIS_AvancarElementoCorrente(pTab->retasFinais[cor], -(numCasas - i));
					casaIni = LIS_ObterValor(pTab->retasFinais[cor]);
					ret = colocaPeca(pTab, casaIni, peca);
					return ret;
				}
				else {
					IrInicioLista(pTab->retasFinais[cor]);
					LIS_ProcurarValor(pTab->retasFinais[cor], casaIni);
					LIS_AvancarElementoCorrente(pTab->retasFinais[cor], 1);
					casaIni = LIS_ObterValor(pTab->retasFinais[cor]);
				}/* if */

				break;

			case CAS_entrada:
				ret = CAS_retornaCor(casaIni, &corCasa);

				if (ret == CAS_condRetParametrosIncorretos) {
					return TAB_CondRetParametrosIncorretos;
				}/* if */

				if (corCasa == cor) {
					IrInicioLista(pTab->retasFinais[cor]);
					casaIni = LIS_ObterValor(pTab->retasFinais[cor]);
				}
				else {
					CIR_ProcurarValor(pTab->casas, casaIni);
					CIR_AvancarElementoCorrente(pTab->casas, 1);
					casaIni = CIR_ObterValor(pTab->casas);
				}/* if */

				break;

			}/* switch */

		}/* for */

		if (numCasas > 0) {
			ret = colocaPeca(pTab, casaIni, peca);
			if (ret == TAB_CondRetParametrosIncorretos) {
				return ret;
			}/* if */

		}/* if */

	}/* if */

	return TAB_CondRetOk;

}/* Fim função: TAB  &TAB_moverPeca*/

/***************************************************************************
*
*  Função: TAB  &Visualiza Tabuleiro
*
*  ************************************************************************/

TAB_CondRet TAB_visualizaTabuleiro(Tabuleiro* pTab) {
	int i,
		j;

	if (pTab == NULL) {
		return TAB_CondRetParametrosIncorretos;
	} /* if */

	for (i = 0; i < 141; i++) {
		printf("-");
	}/* for */

	printf("\n%s%140s\n", "|", "|");

	/*Linha 1:*/
	printf("|  ");
	for (i = 0; i < 135; i++) {
		printf("-");
	}/* for */

	printf("  |");
	printf("\n");

	/*Linha 2:*/
	printf("|%3s", "|");


	printf("%31s%23s", "Vermelho", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[1]);
	CIR_AvancarElementoCorrente(pTab->casas, -3);


	for (i = 0; i < 3; i++) {
		imprimeCasaNormal(pTab, 0);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
	}/* for */

	printf("|%29s%26s%3s", "Azul", "|", "|");

	/*Linha 3:*/

	printf("\n|%3s%54s", "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -3);
	for (i = 0; i < 3; i++) {
		imprimeCasaNormal(pTab, 1);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
	}/* for */
	printf("|%55s%3s", "|", "|");

	/*Linha 4:*/

	printf("\n|%3s%54s", "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -3);
	for (i = 0; i < 3; i++) {
		imprimeCasaNormal(pTab, 2);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
	}/* for */
	printf("|%55s%3s", "|", "|");

	/*Linha 5:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|%3s", " ", "|");

	/*Linha 6:*/

	printf("\n|%3s%12s|%6s%17s%6s%12s", "|", " ", "|", "|", "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -4);
	imprimeCasaNormal(pTab, 0);
	IrInicioLista(pTab->retasFinais[COR_blue]);
	imprimeCasaRetaFinal(pTab, 0, COR_blue);
	CIR_AvancarElementoCorrente(pTab->casas, 4);
	imprimeCasaNormal(pTab, 0);
	printf("%s%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|", "|");


	/*Linha 7:*/

	printf("\n|%3s%13s%4s%2s%17s", "|", "|", retornaStringPecaCasaInicial(pTab, COR_red, 0), "|", "|");
	printf("%4s%2s%12s", retornaStringPecaCasaInicial(pTab, COR_red, 1), "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -4);
	imprimeCasaNormal(pTab, 1);
	imprimeCasaRetaFinal(pTab, 1, COR_blue);
	CIR_AvancarElementoCorrente(pTab->casas, 4);
	imprimeCasaNormal(pTab, 1);
	printf("|%13s%4s%2s%17s", "|", retornaStringPecaCasaInicial(pTab, COR_blue, 0), "|", "|");
	printf("%4s%2s%13s%3s", retornaStringPecaCasaInicial(pTab, COR_blue, 1), "|", "|", "|");


	/*Linha 8:*/

	printf("\n|%3s%13s%6s%17s%6s%12s", "|", "|", "|", "|", "|", " ");

	CIR_AvancarElementoCorrente(pTab->casas, -4);
	imprimeCasaNormal(pTab, 2);
	imprimeCasaRetaFinal(pTab, 2, COR_blue);
	CIR_AvancarElementoCorrente(pTab->casas, 4);
	imprimeCasaNormal(pTab, 2);
	printf("|%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|");

	/*Linha 9:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%13s", "|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("%13s%3s", "|", "|");

	/*Linha 10-12:*/

	CIR_AvancarElementoCorrente(pTab->casas, -5);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_blue], 1);

	for (i = 0; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");
		imprimeCasaNormal(pTab, i);
		imprimeCasaRetaFinal(pTab, i, COR_blue);
		CIR_AvancarElementoCorrente(pTab->casas, 6);
		imprimeCasaNormal(pTab, i);
		CIR_AvancarElementoCorrente(pTab->casas, -6);
		printf("|%55s%3s", "|", "|");
	}/* for */

	/*Linha 13:*/

	printf("\n|%3s%12s", "|", " ");
	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}
	/* for */
	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|%3s", " ", "|");

	/*Linha 14:*/

	printf("\n|%3s%12s|%6s%17s%6s%12s", "|", " ", "|", "|", "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -1);
	imprimeCasaNormal(pTab, 0);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_blue], 1);
	imprimeCasaRetaFinal(pTab, 0, COR_blue);
	CIR_AvancarElementoCorrente(pTab->casas, 8);
	imprimeCasaNormal(pTab, 0);
	printf("%s%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|", "|");


	/*Linha 15:*/

	printf("\n|%3s%13s%4s%2s%17s", "|", "|", retornaStringPecaCasaInicial(pTab, COR_red, 2), "|", "|");
	printf("%4s%2s%12s", retornaStringPecaCasaInicial(pTab, COR_red, 3), "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -8);
	imprimeCasaNormal(pTab, 1);
	imprimeCasaRetaFinal(pTab, 1, COR_blue);
	CIR_AvancarElementoCorrente(pTab->casas, 8);
	imprimeCasaNormal(pTab, 1);
	printf("|%13s%4s%2s%17s", "|", retornaStringPecaCasaInicial(pTab, COR_blue, 2), "|", "|");
	printf("%4s%2s%13s%3s", retornaStringPecaCasaInicial(pTab, COR_blue, 3), "|", "|", "|");


	/*Linha 16:*/

	printf("\n|%3s%13s%6s%17s%6s%12s", "|", "|", "|", "|", "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, -8);
	imprimeCasaNormal(pTab, 2);
	imprimeCasaRetaFinal(pTab, 2, COR_blue);
	CIR_AvancarElementoCorrente(pTab->casas, 8);
	imprimeCasaNormal(pTab, 2);
	printf("|%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|");

	/*Linha 17:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%13s", "|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%13s%3s", "|", "|");

	/*Linha 18-20:*/

	CIR_AvancarElementoCorrente(pTab->casas, -9);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_blue], 1);

	for (i = 0; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");
		imprimeCasaNormal(pTab, i);
		imprimeCasaRetaFinal(pTab, i, COR_blue);
		CIR_AvancarElementoCorrente(pTab->casas, 10);
		imprimeCasaNormal(pTab, i);
		CIR_AvancarElementoCorrente(pTab->casas, -10);
		printf("|%55s%3s", "|", "|");
	}/* for */

	/*Linha 21:*/

	printf("\n|%3s%55s", "|", "|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */


	printf("|");
	printf("%55s%3s", "|", "|");


	/*Linha 22-24:*/

	CIR_AvancarElementoCorrente(pTab->casas, -1);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_blue], 1);

	for (i = 0; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");
		imprimeCasaNormal(pTab, i);
		imprimeCasaRetaFinal(pTab, i, COR_blue);
		CIR_AvancarElementoCorrente(pTab->casas, 12);
		imprimeCasaNormal(pTab, i);
		CIR_AvancarElementoCorrente(pTab->casas, -12);
		printf("|%55s%3s", "|", "|");
	}/* for */

	/*Linha 25:*/

	printf("\n|%3s", "|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 23; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("%s%3s", "|", "|");


	/*Linha 26:*/

	printf("\n|%2s", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -1);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 0);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
		printf(" ");
	}/* for */

	IrFinalLista(pTab->retasFinais[COR_blue]);
	printf(" |\\%6s", retornaStringPecaRetaFinal(pTab, 0, COR_blue));
	printf("%6s", retornaStringPecaRetaFinal(pTab, 1, COR_blue));
	printf("%8s%2s", retornaStringPecaRetaFinal(pTab, 2, COR_blue), "/");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_blue]);
	CIR_AvancarElementoCorrente(pTab->casas, 5);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 0);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
		printf(" ");
	}/* for */

	printf("%2s%3s", "|", "|");

	/*Linha 27:*/

	printf("\n|%2s", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -1);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 1);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
		printf(" ");
	}/* for */

	printf("%2s%3s%9s%9s%2s", "|", "\\", "Az", "/", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_blue]);
	CIR_AvancarElementoCorrente(pTab->casas, 5);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 1);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
		printf(" ");
	}/* for */

	printf("%2s%3s", "|", "|");

	/*Linha 28:*/

	printf("\n|%2s", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -1);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 2);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
		printf(" ");
	}/* for */

	IrFinalLista(pTab->retasFinais[COR_red]);


	printf("%2s%2s", "|", retornaStringPecaRetaFinal(pTab, 0, COR_red));
	printf("%2s%8s%6s", "\\", retornaStringPecaRetaFinal(pTab, 3, COR_blue), "/");

	IrFinalLista(pTab->retasFinais[COR_green]);



	printf("%4s", retornaStringPecaRetaFinal(pTab, 0, COR_green));


	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_blue]);
	CIR_AvancarElementoCorrente(pTab->casas, 5);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 2);
		CIR_AvancarElementoCorrente(pTab->casas, 1);
		printf(" ");
	}/* for */

	printf("%2s%3s", "|", "|");


	/*Linha 29:*/

	printf("\n|%3s", "|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%7s%10s%7s", "\\", "/", "|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("%s%3s", "|", "|");

	/*Linha 30:*/

	printf("\n|%2s", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -2);
	imprimeCasaNormal(pTab, 0);
	printf(" ");
	IrInicioLista(pTab->retasFinais[COR_red]);

	for (i = 0; i < 5; i++) {
		imprimeCasaRetaFinal(pTab, 0, COR_red);
		LIS_AvancarElementoCorrente(pTab->retasFinais[COR_red], 1);
		printf(" ");
	}/* for */

	printf(" |%9s%6s%8s", "\\", "/", " ");

	for (i = 0; i < 5; i++) {
		LIS_AvancarElementoCorrente(pTab->retasFinais[COR_green], -1);
		imprimeCasaRetaFinal(pTab, 0, COR_green);
		printf(" ");
	}/* for */

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_green]);
	CIR_AvancarElementoCorrente(pTab->casas, -2);
	imprimeCasaNormal(pTab, 0);
	printf("%3s%3s", "|", "|");

	/*Linha 31:*/

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -2);
	printf("\n|%2s", " ");
	imprimeCasaNormal(pTab, 1);
	printf(" ");
	IrInicioLista(pTab->retasFinais[COR_red]);

	for (i = 0; i < 5; i++) {
		imprimeCasaRetaFinal(pTab, 1, COR_red);
		LIS_AvancarElementoCorrente(pTab->retasFinais[COR_red], 1);
		printf(" ");
	}/* for */

	printf(" |%s", retornaStringPecaRetaFinal(pTab, 1, COR_red));
	IrFinalLista(pTab->retasFinais[COR_green]);
	printf("%3s%4s\\%2s", "Vm", retornaStringPecaRetaFinal(pTab, 2, COR_red), "/");
	printf("%s%3s", retornaStringPecaRetaFinal(pTab, 1, COR_green), "Vd");
	printf("%4s", retornaStringPecaRetaFinal(pTab, 2, COR_green));

	for (i = 0; i < 5; i++) {
		LIS_AvancarElementoCorrente(pTab->retasFinais[COR_green], -1);
		imprimeCasaRetaFinal(pTab, 1, COR_green);
		printf(" ");
	}/* for */

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_green]);
	CIR_AvancarElementoCorrente(pTab->casas, -2);
	imprimeCasaNormal(pTab, 1);
	printf("%3s%3s", "|", "|");

	/*Linha 32:*/

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -2);
	printf("\n|%2s", " ");
	imprimeCasaNormal(pTab, 2);
	printf(" ");
	IrInicioLista(pTab->retasFinais[COR_red]);

	for (i = 0; i < 5; i++) {
		imprimeCasaRetaFinal(pTab, 2, COR_red);
		LIS_AvancarElementoCorrente(pTab->retasFinais[COR_red], 1);
		printf(" ");
	}/* for */

	printf("%2s%11s%2s%10s", "|", "/", "\\", " ");
	IrFinalLista(pTab->retasFinais[COR_green]);

	for (i = 0; i < 5; i++) {
		LIS_AvancarElementoCorrente(pTab->retasFinais[COR_green], -1);
		imprimeCasaRetaFinal(pTab, 2, COR_green);
		printf(" ");
	}/* for */

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_green]);
	CIR_AvancarElementoCorrente(pTab->casas, -2);
	imprimeCasaNormal(pTab, 2);
	printf("%3s%3s", "|", "|");

	/*Linha 33:*/

	printf("\n|%3s", "|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("|%9s%6s%9s", "/", "\\", "|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("|%3s", "|");


	/*Linha 34:*/

	printf("\n|%2s", " ");

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -3);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 0);
		CIR_AvancarElementoCorrente(pTab->casas, -1);
		printf(" ");
	}/* for */

	IrFinalLista(pTab->retasFinais[COR_red]);
	IrFinalLista(pTab->retasFinais[COR_yellow]);
	printf("%2s%s%4s", "|", retornaStringPecaRetaFinal(pTab, 3, COR_red), "/");

	printf("%6s%4s", retornaStringPecaRetaFinal(pTab, 0, COR_yellow), "\\");

	IrFinalLista(pTab->retasFinais[COR_green]);
	printf("%6s", retornaStringPecaRetaFinal(pTab, 3, COR_green));
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_green]);
	CIR_AvancarElementoCorrente(pTab->casas, 4);
	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 0);
		CIR_AvancarElementoCorrente(pTab->casas, -1);
		printf(" ");
	}/* for */

	printf("%2s%3s", "|", "|");

	/*Linha 35:*/

	printf("\n|%2s", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -3);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 1);
		CIR_AvancarElementoCorrente(pTab->casas, -1);
		printf(" ");
	}/* for */
	printf("%2s%5s%7s%7s%4s", "|", "/", "Am", "\\", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_green]);
	CIR_AvancarElementoCorrente(pTab->casas, 4);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 1);
		CIR_AvancarElementoCorrente(pTab->casas, -1);
		printf(" ");
	}/* for */

	printf("%2s%3s", "|", "|");

	/*Linha 36:*/

	printf("\n|%2s", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_red]);
	CIR_AvancarElementoCorrente(pTab->casas, -3);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 2);
		CIR_AvancarElementoCorrente(pTab->casas, -1);
		printf(" ");
	}/* for */

	printf("%2s%3s%4s", "|", "/", retornaStringPecaRetaFinal(pTab, 1, COR_yellow));
	printf("%6s", retornaStringPecaRetaFinal(pTab, 2, COR_yellow));
	printf("%7s\\%2s", retornaStringPecaRetaFinal(pTab, 3, COR_yellow), " ");

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_green]);
	CIR_AvancarElementoCorrente(pTab->casas, 4);

	for (i = 0; i < 6; i++) {
		imprimeCasaNormal(pTab, 2);
		CIR_AvancarElementoCorrente(pTab->casas, -1);
		printf(" ");
	}/* for */

	printf("%2s%3s", "|", "|");

	/*Linha 37:*/

	printf("\n|%3s", "|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("|");
	for (i = 0; i < 23; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 54; i++) {
		printf("-");
	}/* for */

	printf("%s%3s", "|", "|");

	/*Linha 38:*/

	printf("\n|%3s", "|");


	printf("%30s%24s", "Amarelo", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_yellow]);
	CIR_AvancarElementoCorrente(pTab->casas, 4);
	imprimeCasaNormal(pTab, 0);
	IrFinalLista(pTab->retasFinais[COR_yellow]);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_yellow], -1);
	imprimeCasaRetaFinal(pTab, 0, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -12);
	imprimeCasaNormal(pTab, 0);
	printf("|%29s%26s%3s", "Verde", "|", "|");


	/*Linha 39-40:*/

	CIR_AvancarElementoCorrente(pTab->casas, 12);
	for (i = 1; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");
		imprimeCasaNormal(pTab, i);
		imprimeCasaRetaFinal(pTab, i, COR_yellow);
		CIR_AvancarElementoCorrente(pTab->casas, -12);
		imprimeCasaNormal(pTab, i);
		CIR_AvancarElementoCorrente(pTab->casas, 12);
		printf("|%55s%3s", "|", "|");
	}/* for */

	/*Linha 41:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|%3s", " ", "|");

	/*Linha 42:*/

	printf("\n|%3s%12s|%6s%17s%6s%12s", "|", " ", "|", "|", "|", " ");
	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_yellow]);
	CIR_AvancarElementoCorrente(pTab->casas, 3);
	imprimeCasaNormal(pTab, 0);
	IrInicioLista(pTab->retasFinais[COR_yellow]);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_yellow], 3);
	imprimeCasaRetaFinal(pTab, 0, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -10);
	imprimeCasaNormal(pTab, 0);
	printf("%s%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|", "|");


	/*Linha 43:*/


	printf("\n|%3s%13s%4s%2s%17s", "|", "|", retornaStringPecaCasaInicial(pTab, COR_yellow, 0), "|", "|");
	printf("%4s%2s%12s", retornaStringPecaCasaInicial(pTab, COR_yellow, 1), "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, 10);
	imprimeCasaNormal(pTab, 1);
	imprimeCasaRetaFinal(pTab, 1, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -10);
	imprimeCasaNormal(pTab, 1);
	printf("|%13s%4s%2s%17s", "|", retornaStringPecaCasaInicial(pTab, COR_green, 0), "|", "|");
	printf("%4s%2s%13s%3s", retornaStringPecaCasaInicial(pTab, COR_green, 1), "|", "|", "|");

	/*Linha 44:*/

	printf("\n|%3s%13s%6s%17s%6s%12s", "|", "|", "|", "|", "|", " ");

	CIR_AvancarElementoCorrente(pTab->casas, 10);
	imprimeCasaNormal(pTab, 2);
	imprimeCasaRetaFinal(pTab, 2, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -10);
	imprimeCasaNormal(pTab, 2);
	printf("|%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|");

	/*Linha 45:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|", " ");
	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("%12s|%3s", " ", "|");

	/*Linha 46-48:*/

	CIR_AvancarElementoCorrente(pTab->casas, 9);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_yellow], -1);
	for (i = 0; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");
		imprimeCasaNormal(pTab, i);
		imprimeCasaRetaFinal(pTab, i, COR_yellow);
		CIR_AvancarElementoCorrente(pTab->casas, -8);
		imprimeCasaNormal(pTab, i);
		CIR_AvancarElementoCorrente(pTab->casas, 8);
		printf("|%55s%3s", "|", "|");
	}/* for */


	/*Linha 49:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|", " ");
	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("%12s|%3s", " ", "|");

	/*Linhas 50*/

	CIR_AvancarElementoCorrente(pTab->casas, -1);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_yellow], -1);
	printf("\n|%3s%12s|%6s%17s%6s%12s", "|", " ", "|", "|", "|", " ");
	imprimeCasaNormal(pTab, 0);
	imprimeCasaRetaFinal(pTab, 0, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -6);
	imprimeCasaNormal(pTab, 0);
	printf("%s%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|", "|");

	/*Linha 51:*/

	printf("\n|%3s%13s%4s%2s%17s", "|", "|", retornaStringPecaCasaInicial(pTab, COR_yellow, 2), "|", "|");
	printf("%4s%2s%12s", retornaStringPecaCasaInicial(pTab, COR_yellow, 3), "|", " ");
	CIR_AvancarElementoCorrente(pTab->casas, 6);
	imprimeCasaNormal(pTab, 1);
	imprimeCasaRetaFinal(pTab, 1, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -6);
	imprimeCasaNormal(pTab, 1);
	printf("|%13s%4s%2s%17s", "|", retornaStringPecaCasaInicial(pTab, COR_green, 2), "|", "|");
	printf("%4s%2s%13s%3s", retornaStringPecaCasaInicial(pTab, COR_green, 3), "|", "|", "|");

	/*Linha 52:*/

	CIR_AvancarElementoCorrente(pTab->casas, 6);
	printf("\n|%3s%12s|%6s%17s%6s%12s", "|", " ", "|", "|", "|", " ");
	imprimeCasaNormal(pTab, 2);
	imprimeCasaRetaFinal(pTab, 2, COR_yellow);
	CIR_AvancarElementoCorrente(pTab->casas, -6);
	imprimeCasaNormal(pTab, 2);
	printf("%s%13s%6s%17s%6s%13s%3s", "|", "|", "|", "|", "|", "|", "|");

	/*Linha 53:*/

	printf("\n|%3s%12s", "|", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%12s|", " ");
	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%12s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("%16s", " ");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */
	printf("%12s|%3s", " ", "|");


	/*Linha 54-56:*/

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_yellow]);
	LIS_AvancarElementoCorrente(pTab->retasFinais[COR_yellow], -1);

	for (i = 0; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");
		imprimeCasaNormal(pTab, i);
		imprimeCasaRetaFinal(pTab, i, COR_yellow);
		CIR_AvancarElementoCorrente(pTab->casas, -4);
		imprimeCasaNormal(pTab, i);
		CIR_AvancarElementoCorrente(pTab->casas, 4);
		printf("|%55s%3s", "|", "|");
	}/* for */

	/*Linha 57:*/

	printf("\n|%3s%55s", "|", "|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");

	for (i = 0; i < 7; i++) {
		printf("-");
	}/* for */

	printf("|");
	printf("%55s%3s", "|", "|");



	/*Linha 58-60:*/

	CIR_ProcurarValor(pTab->casas, pTab->casasSeguras[COR_yellow]);
	CIR_AvancarElementoCorrente(pTab->casas, -1);

	for (i = 0; i < 3; i++) {
		printf("\n|%3s%54s", "|", " ");

		for (j = 0; j < 3; j++) {
			imprimeCasaNormal(pTab, i);
			CIR_AvancarElementoCorrente(pTab->casas, -1);
		}/* for */

		CIR_AvancarElementoCorrente(pTab->casas, 3);
		printf("|%55s%3s", "|", "|");

	}/* for */

	printf("\n|  ");

	for (i = 0; i < 135; i++) {
		printf("-");
	}/* for */

	printf("  |");
	printf("\n%s%140s","|","|");


	printf("\n");
	for (i = 0; i < 141; i++) {
		printf("-");
	}/* for */

	printf("\n\n");

	for (i = 0; i < 4; i++) {
		IrInicioLista(pTab->retasFinais[i]);
	}/* for */

}/* Fim função: TAB  &TAB_visualizaTabuleiro */

/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TAB  -Colocar peca no tabuleiro
*
***********************************************************************/


static TAB_CondRet colocaPeca(Tabuleiro* pTab, Casa* casa, Peca* peca) {
	PEC_CondRet ret;
	COR_tpCor cor;
	int num;
	if (pTab == NULL || casa == NULL || peca == NULL) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	ret = PEC_retornaNum(peca, &num);

	if (ret == PEC_condRetParametrosIncorretos) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	ret = PEC_retornaCor(peca, &cor);

	if (ret == PEC_condRetParametrosIncorretos) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	pTab->casasOcupadas[(cor * 4) + num - 1].casa = casa;
	return TAB_CondRetOk;

} /* Fim função: TAB  -colocaPeca */

/***********************************************************************
*
*  $FC Função: TAB  -Criar Jogador
*
***********************************************************************/

static TAB_CondRet criaJogador(Tabuleiro* pTab, COR_tpCor cor) {
	int			i;
	Peca		*peca;
	PEC_CondRet ret;

	if (cor < COR_MIN || cor > COR_MAX) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	if (pTab->casasOcupadas[cor * 4].peca != NULL)/*Um jogador com essa cor já existe*/ {
		return TAB_CondRetParametrosIncorretos;
	}/* if */

	for (i = 0; i < 4; i++) {
		ret = PEC_criaPeca(&peca, cor, i + 1);

		if (ret == PEC_condRetFaltouMemoria) {
			return TAB_CondRetFaltouMemoria;
		}
		else if (ret == PEC_condRetParametrosIncorretos) {
			return TAB_CondRetParametrosIncorretos;
		}/* if */

		pTab->casasOcupadas[cor * 4 + i].casa = pTab->casasIniciais[(cor * 4) + i];
		pTab->casasOcupadas[cor * 4 + i].peca = peca;
	}/* for */

	return TAB_CondRetOk;

}/* Fim função: TAB  -criaJogador */

/***********************************************************************
*
*  $FC Função: TAB  -Retorna peca
*
***********************************************************************/

static Peca* retornaPeca(Tabuleiro* pTab, COR_tpCor cor, int numP) {
	if (pTab == NULL || cor < COR_MIN || cor > COR_MAX || numP < PEC_MIN || numP > PEC_MAX ) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */
	return pTab->casasOcupadas[(cor * 4) + numP - 1].peca;

}/* Fim função: TAB  -retornaPeca */

/***********************************************************************
*
*  $FC Função: TAB  -Retorna Casa da peca
*
***********************************************************************/

static Casa* retornaCasaDaPeca(Tabuleiro* pTab, Peca* peca) {
	PEC_CondRet ret;
	int			num;
	COR_tpCor	cor;
	if (pTab == NULL || peca == NULL) {
		return NULL;
	}/* if */

	ret = PEC_retornaNum(peca, &num);

	if (ret == PEC_condRetParametrosIncorretos) {
		return NULL;
	}/* if */

	ret = PEC_retornaCor(peca, &cor);

	if (ret == PEC_condRetParametrosIncorretos) {
		return NULL;
	}/* if */

	if (cor != -1 && num != -1) {
		return pTab->casasOcupadas[cor * 4 + num - 1].casa;
	}
	else {
		return NULL;
	}/* if */

} /* Fim função: TAB  -retornaCasaDaPeca */

/***********************************************************************
*
*  $FC Função: TAB  -Cria Casa Final
*
***********************************************************************/

static TAB_CondRet criaRetaFinal(LIS_tppLista *lista, COR_tpCor cor) {
	Casa			*casa;
	CAS_CondRet		ret;
	int				i;

	if (cor < COR_MIN || cor > COR_MAX) {
		return TAB_CondRetParametrosIncorretos;
	}/* if */
	*lista = LIS_CriarLista(CAS_destruirCasa);

	if (*lista == NULL) {
		return TAB_CondRetFaltouMemoria;
	}/* if */


	for (i = 0; i < 6; i++) {
		ret = CAS_criaCasaFinal(&casa, cor);

		if (ret == CAS_condRetOk) {

			if (LIS_InserirElementoApos(*lista, casa) != LIS_CondRetOK) {
				return TAB_CondRetFaltouMemoria;
			}/* if */

		}
		else if (ret == CAS_condRetFaltouMemoria) {
			return TAB_CondRetFaltouMemoria;
		}
		else if (ret == CAS_condRetParametrosIncorretos) {
			return TAB_CondRetParametrosIncorretos;
		}/* if */

	}/* for */

	return TAB_CondRetOk;
} /* Fim função: TAB  -criaRetaFinal */

/***********************************************************************
*
*  $FC Função: TAB  -Retorna String da Peça Requirida da Casa
*
*  $ED	Descrição da função
*		retorna uma string de tamanho 3 contendo os dados de ocupação
*			da casa na posição requirida
*		Casa é um elemento corrente da lista circular do tabuleiro
*
*  $EP Parâmetros
*		posReq	- vai de 0 a 3
*		pTab	- ponteiro para o tabuleiro
*
*  $FV Valor retornado
*		""		-	caso os parametros estejam incorretos
*		string	-	informação da peça requirida
*
***********************************************************************/

static char* retornaStringPeca(Tabuleiro * pTab, int posReq) {

	Casa		*casa;
	Peca		*pecas[4];
	static char	 string[4];
	int quantPecas = 0,
		i;

	if (posReq < 0 || posReq > 3) {
		return "";
	}/* if */

	casa = CIR_ObterValor(pTab->casas);
	strcpy(string, "");

	for (i = 0; i < 16; i++) {

		if (casa == pTab->casasOcupadas[i].casa) {
			pecas[quantPecas] = pTab->casasOcupadas[i].peca;
			quantPecas++;
		}/* if */

	}/* for */

	if (quantPecas == 0 || posReq + 1 > quantPecas) {
		return strcpy(string, "   ");
	}
	else {
		int num;
		PEC_CondRet ret;
		COR_tpCor cor;
		ret = PEC_retornaCor(pecas[posReq], &cor);

		if (ret == PEC_condRetParametrosIncorretos) {
			return "";
		}/* if */

		switch (cor) {
		case 0:
			strcpy(string, "Vm");
			break;
		case 1:
			strcpy(string, "Az");
			break;
		case 2:
			strcpy(string, "Vd");
			break;
		case 3:
			strcpy(string, "Am");
			break;
		}/* switch */

		ret = PEC_retornaNum(pecas[posReq], &num);

		if (ret == PEC_condRetParametrosIncorretos) {
			return "";
		}/* if */

		switch (num) {
		case 1:
			strcat(string, "1");
			break;
		case 2:
			strcat(string, "2");
			break;
		case 3:
			strcat(string, "3");
			break;
		case 4:
			strcat(string, "4");
			break;
		}/* switch */

		return string;

	}/* if */

} /* Fim função: TAB  -retornaStringPeca */

/***********************************************************************
*
*  $FC Função: TAB  -Retorna String da Peça Requirida  da Reta Final
*
*  $ED	Descrição da função
*		retorna uma string de tamanho 3 contendo os dados de ocupação
*			da casa na posição requirida
*		Casa é um elemento corrente da lista duplamente encadeada
*			do tabuleiro
*
*  $EP Parâmetros
*		posReq	- vai de 0 a 3
*		pTab	- ponteiro para o tabuleiro
*		cor		- tipo enumerado cor
*
*  $FV Valor retornado
*		""		-	caso os parametros estejam incorretos
*		string	-	informação da peça requirida
*
***********************************************************************/

static char* retornaStringPecaRetaFinal(Tabuleiro* pTab, int posReq, COR_tpCor cor) {
	Casa			*casa;
	Peca			*pecas[4];
	static char		string[4];
	int				quantPecas = 0,
					i;
	if (posReq < 0 || posReq > 3) {
		return "";
	}/* if */

	casa = LIS_ObterValor(pTab->retasFinais[cor]);
	strcpy(string, "");
	

	for (i = 0; i < 16; i++) {
		if (casa == pTab->casasOcupadas[i].casa) {
			pecas[quantPecas] = pTab->casasOcupadas[i].peca;
			quantPecas++;
		}/* if */
	}/* for */

	if (quantPecas == 0 || posReq + 1 > quantPecas) {
		return strcpy(string, "   ");
	}
	else {

		int num;
		PEC_CondRet ret;
		ret = PEC_retornaCor(pecas[posReq], &cor);

		if (ret == PEC_condRetParametrosIncorretos) {
			return "";
		} /* if */

		switch (cor) {

		case 0:
			strcpy(string, "Vm");
			break;
		case 1:
			strcpy(string, "Az");
			break;
		case 2:
			strcpy(string, "Vd");
			break;
		case 3:
			strcpy(string, "Am");
			break;
		}/* switch */

		ret = PEC_retornaNum(pecas[posReq], &num);

		if (ret == PEC_condRetParametrosIncorretos) {
			return NULL;
		}/* if */

		switch (num) {

		case 1:
			strcat(string, "1");
			break;
		case 2:
			strcat(string, "2");
			break;
		case 3:
			strcat(string, "3");
			break;
		case 4:
			strcat(string, "4");
			break;
		}/* switch */
		return string;
	} /* if */

} /* Fim função: TAB  -retornaStringPecaRetaFinal */

/***********************************************************************
*
*  $FC Função: TAB  -Retorna String das Peças Requiridas da Casa Final
*
*  $ED	Descrição da função
*		retorna uma string de tamanho 3 contendo os dados de ocupação
*			da casa na posição requirida
*		acessa diretamente a casa que se deseja saber a informação
*
*  $EP Parâmetros
*		pTab	- ponteiro para o tabuleiro
*		cor		- tipo enumerado cor
*		numCasa	- numero inteiro da casa de 0 a 3
*
*  $FV Valor retornado
*		""		-	caso os parametros estejam incorretos
*		string	-	informação da peça requirida
*
***********************************************************************/

static char* retornaStringPecaCasaInicial(Tabuleiro* pTab, COR_tpCor cor, int numCasa) {
	static char string[4];
	Casa		*casa;
	Peca		*peca = NULL;
	int			i;
	if (cor < COR_MIN || cor > COR_MAX || numCasa < 0 || numCasa > 3) {
		return "";
	}/* if */

	casa = pTab->casasIniciais[(cor * 4) + numCasa];
	strcpy(string, "");
	

	for (i = 0; i < 16; i++) {
		if (casa == pTab->casasOcupadas[i].casa) {
			peca = pTab->casasOcupadas[i].peca;
		}/* if */
	}/* for */

	if (peca == NULL) {
		return "   ";
	}
	else {
		int num;
		PEC_CondRet ret;
		switch (cor) {
		case COR_red:
			strcpy(string, "Vm");
			break;
		case COR_blue:
			strcpy(string, "Az");
			break;
		case COR_green:
			strcpy(string, "Vd");
			break;
		case COR_yellow:
			strcpy(string, "Am");
			break;
		}/* switch */

		ret = PEC_retornaNum(peca, &num);

		if (ret == PEC_condRetParametrosIncorretos) {
			return NULL;
		}/* if */

		switch (num) {
		case 1:
			strcat(string, "1");
			break;
		case 2:
			strcat(string, "2");
			break;
		case 3:
			strcat(string, "3");
			break;
		case 4:
			strcat(string, "4");
			break;
		}/* switch */

		return string;

	}/* if */

} /* Fim função: TAB  -retornaStringPecaCasaInicial */

/***********************************************************************
*
*  $FC Função: TAB  -Imprime uma Liha da Casa Normal
*  $ED	Descrição da função
*		imprime a linha requirida da casa
*		casa desejada deve ser elemento corrente da lista circular
*
***********************************************************************/

static TAB_CondRet imprimeCasaNormal(Tabuleiro* pTab, int linha) {
	CAS_tpTipo	tipo;
	CAS_CondRet ret;
	COR_tpCor	cor;
	switch (linha) {

	case 0:
		printf("|%s", retornaStringPeca(pTab, 0));

		if (quantPecasNaCasa(pTab, CIR_ObterValor(pTab->casas)) == -1) {
			return TAB_CondRetParametrosIncorretos;
		}
		else if (quantPecasNaCasa(pTab, CIR_ObterValor(pTab->casas)) > 1) {
			printf("+%3s", retornaStringPeca(pTab, 1));
		}
		else {
			printf("%4s", retornaStringPeca(pTab, 1));
		}/* if */

		break;
	case 1:
		ret = CAS_retornaTipo(CIR_ObterValor(pTab->casas), &tipo);
		if (ret == CAS_condRetParametrosIncorretos) {
			return TAB_CondRetParametrosIncorretos;
		}/* if */
		if (tipo == CAS_segura) {
			ret = CAS_retornaCor(CIR_ObterValor(pTab->casas), &cor);
			if (ret == CAS_condRetParametrosIncorretos) {
				return TAB_CondRetParametrosIncorretos;
			}/* if */
			switch (cor) {
			case 0:
				printf("|%4s%3s", "Vm", " ");
				break;
			case 1:
				printf("|%4s%3s", "Az", " ");
				break;
			case 2:
				printf("|%4s%3s", "Vd", " ");
				break;
			case 3:
				printf("|%4s%3s", "Am", " ");
				break;

			}/* switch */
		}
		else {
			printf("|%7s", " ");
		}/* if */
		break;
	case 2:
		printf("|%s", retornaStringPeca(pTab, 2));
		if (quantPecasNaCasa(pTab, CIR_ObterValor(pTab->casas)) == -1) {
			return TAB_CondRetParametrosIncorretos;
		}
		else if (quantPecasNaCasa(pTab, CIR_ObterValor(pTab->casas)) > 3) {
			printf("+%3s", retornaStringPeca(pTab, 3));
		}
		else {
			printf("%4s", retornaStringPeca(pTab, 3));
		}/* if */
		break;
	}/* switch */

	return TAB_CondRetOk;

} /* Fim função: TAB  -imprimeCasaNormal */

/***********************************************************************
*
*  $FC Função: TAB  -Imprime uma Liha da Reta Final
*  $ED	Descrição da função
*		imprime a linha requirida da casa
*		casa desejada deve ser elemento corrente da lista duplamente
*			encadeada
*
***********************************************************************/

static TAB_CondRet imprimeCasaRetaFinal(Tabuleiro* pTab, int linha, COR_tpCor cor) {
	switch (linha) {
	case 0:

		printf("|%s", retornaStringPecaRetaFinal(pTab, 0, cor));
		if (quantPecasNaCasa(pTab, LIS_ObterValor(pTab->retasFinais[cor])) == -1) {
			return TAB_CondRetParametrosIncorretos;
		}
		else if (quantPecasNaCasa(pTab, LIS_ObterValor(pTab->retasFinais[cor])) > 1) {
			printf("+%3s", retornaStringPecaRetaFinal(pTab, 1, cor));
		}
		else {
			printf("%4s", retornaStringPecaRetaFinal(pTab, 1, cor));
		}/* if */
		break;

	case 1:
		switch (cor) {
		case 0:
			printf("|%4s%3s", "Vm", " ");
			break;
		case 1:
			printf("|%4s%3s", "Az", " ");
			break;
		case 2:
			printf("|%4s%3s", "Vd", " ");
			break;
		case 3:
			printf("|%4s%3s", "Am", " ");
			break;
		}/* switch */
		break;
	case 2:
		printf("|%s", retornaStringPecaRetaFinal(pTab, 2, cor));
		if (quantPecasNaCasa(pTab, LIS_ObterValor(pTab->retasFinais[cor])) == -1) {
			return TAB_CondRetParametrosIncorretos;
		}
		else if (quantPecasNaCasa(pTab, LIS_ObterValor(pTab->retasFinais[cor])) > 1) {
			printf("+%3s", retornaStringPecaRetaFinal(pTab, 3, cor));
		}
		else {
			printf("%4s", retornaStringPecaRetaFinal(pTab, 3, cor));
		}/* if */

		break;
	}/* switch */

	return TAB_CondRetOk;

} /* Fim função: TAB  -imprimeCasaRetaFinal */

/***********************************************************************
*
*  $FC Função: TAB  -Quantidade de Peças na Casa
*  $FV Valor retornado
*	-1	-	se o ponteiro para o tabuleiro ou o ponteiro para a casa
*				for NULL
*
***********************************************************************/

static int quantPecasNaCasa(Tabuleiro* pTab, Casa* casa) {
	int quantPecas = 0,
		i;
	if (pTab == NULL || casa == NULL) {
		return -1;
	} /* if */
	
	for (i = 0; i < 16; i++) {
		if (casa == pTab->casasOcupadas[i].casa) {
			quantPecas++;
		}/* if */
	}/* for */
	return quantPecas;
} /* Fim função: TAB  -quantPecasNaCasa */

/********** Fim do módulo de implementação: TAB  tabuleiro **********/