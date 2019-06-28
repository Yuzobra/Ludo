/***************************************************************************
*  $MCI M�dulo de implementa��o: TSTTAB Teste Tabuleiro
*
*  Arquivo gerado:              TSTTAB .c
*  Letras identificadoras:      TSTTAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		Vers�o  Autor   Data		Observa��es
*		1		yz		09/05/2019	Implementa��o do m�dulo de testes
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Tabuleiro.h"


/***********************************************************************
*
*  $DC Dados Globais: TSTTAB
*
*		$ED Descri��o do tipo
*			- comandos definidos para usar no scipt de teste
*
***********************************************************************/


static const char RESET_TABULEIRO_CMD			[] = "=resetteste";
static const char CRIA_TABULEIRO_CMD			[] = "=criatabuleiro";
static const char MONTA_TABULEIRO_CMD			[] = "=montatabuleiro";
static const char RETORNA_PECA_CASA_INICIAL_CMD	[] = "=retornacasainicial";
static const char MOVER_PECA_CMD				[] = "=moverpeca";
static const char DESTROI_TABULEIRO_CMD			[] = "=destroitabuleiro";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_TABULEIRO   25
#define DIM_VALOR     100

/***********************************************************************
*
*  $TC Tipo de dados: TSTTAB Vetor de Tabuleiros
*
*		$ED Descri��o do tipo
*			- vetor de tabuleiros para serem testados
*
***********************************************************************/

Tabuleiro * vtTabuleiros[DIM_VT_TABULEIRO];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int ValidarIndexTabuleiro(int indexTabuleiro, int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TSTTAB &Testar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 25 listas, identificadas pelos �ndices 0 a 24
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de mem�ria
*     =criatabuleiro		indexTab	CondRetEsp
*     =destroitabuleiro   	indexTab	CondRetEsp
*     =montatabuleiro		indexTab	numJogadores	cor1		cor2		cor3		cor4		CondRetEsp
*	  =moverpeca			indexTab	numCasas		corPeca		numPeca
*	  =retornapeca			indexTab	corPeca			numPeca		CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int indexTabuleiro	= -1,
		numLidos		= -1,
		CondRetEsp		= -1,
		numJogadores	= -1,
		numPeca			= -1,
		numCasas		= -1;

	TST_tpCondRet CondRet;

	COR_tpCor	cor,
				cores[4];

	char * pDado;

	int ValEsp = -1;

	int i;

	int numElem = -1;


	/* Efetuar reset de teste de tabuleiro */

	if (strcmp(ComandoTeste, RESET_TABULEIRO_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_TABULEIRO; i++)
		{
			vtTabuleiros[i] = NULL;
		} /* for */

		return TST_CondRetOK;
		/* fim ativa: Efetuar reset de teste de tabuleiro */
	}else if (strcmp(ComandoTeste, CRIA_TABULEIRO_CMD) == 0)
	{
		/* Testar CriarTabuleiro*/
		numLidos = LER_LerParametros("i",
			&indexTabuleiro);

		if ((numLidos != 1)
			|| (!ValidarIndexTabuleiro(indexTabuleiro, VAZIO)))
		{
			return TST_CondRetParm;
		}

		TAB_criaTabuleiro(&vtTabuleiros[indexTabuleiro]);

		return TST_CompararPonteiroNulo(1, vtTabuleiros[indexTabuleiro],
			"Erro em ponteiro de novo tabuleiro.");
		/* fim ativa: Testar CriarTabuleiro */
	}else if (strcmp(ComandoTeste, MONTA_TABULEIRO_CMD) == 0)
	{
		/* Testar MontaTabuleiro */
		numLidos = LER_LerParametros("iiiiiii",
			&indexTabuleiro, &numJogadores,&cores[0], &cores[1], &cores[2], &cores[3], &CondRetEsp);

		if ((numLidos != 7)
			|| (!ValidarIndexTabuleiro(indexTabuleiro, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		}

		CondRet = TAB_montaTabuleiro(vtTabuleiros[indexTabuleiro], numJogadores, cores);
		
		return TST_CompararInt(CondRetEsp, CondRet,
				"Erro ao montar tabuleiro");
		/* fim ativa: Testar MontaTabuleiro */
	}else if (strcmp(ComandoTeste, RETORNA_PECA_CASA_INICIAL_CMD) == 0)
	{	/* Testar RetornaPecaParaCasaInicial */
		numLidos = LER_LerParametros("iiii",
			&indexTabuleiro, &cor,  &numPeca,&CondRetEsp);

		if ((numLidos != 4)
			|| (!ValidarIndexTabuleiro(indexTabuleiro, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		}

		CondRet = TAB_retornaPecaParaCasaInicial(vtTabuleiros[indexTabuleiro], cor, numPeca);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Erro ao retornar peca para casa inicial.");
		/* fim ativa: Testar RetornaPecaParaCasaInicial */
	}else if (strcmp(ComandoTeste, MOVER_PECA_CMD) == 0)
	{ /* Testar MoverPeca */
		numLidos = LER_LerParametros("iiiii",
				&indexTabuleiro,&numCasas, &cor, &numPeca,&CondRetEsp);

		if ((numLidos != 5)
			|| (!ValidarIndexTabuleiro(indexTabuleiro, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		}

		CondRet = TAB_moverPeca(vtTabuleiros[indexTabuleiro],numCasas, cor, numPeca);

		return TST_CompararInt(CondRetEsp, CondRet,
			"Erro ao mover peca.");
		/* fim ativa: Testar MoverPeca */
	}else if (strcmp(ComandoTeste, DESTROI_TABULEIRO_CMD) == 0)
	{
		/* Testar Destruir tabuleiro */
		numLidos = LER_LerParametros("i",
			&indexTabuleiro);

		if ((numLidos != 1)
			|| (!ValidarIndexTabuleiro(indexTabuleiro, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} 

		TAB_destroiTabuleiro(vtTabuleiros[indexTabuleiro]);
		vtTabuleiros[indexTabuleiro] = NULL;

		return TST_CondRetOK;

	} /* if */ 
	/* fim ativa: Testar Destruir tabuleiro */

	return TST_CondRetNaoConhec;

} /* Fim fun��o: TSTTAB &Testar Tabuleiro */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TSTTAB -Validar indice de lista
*
***********************************************************************/

int ValidarIndexTabuleiro(int indexTabuleiro, int Modo)
{

	if ((indexTabuleiro < 0)
		|| (indexTabuleiro >= DIM_VT_TABULEIRO))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtTabuleiros[indexTabuleiro] != 0)
		{
			return FALSE;
		}
	}else
	{
		if (vtTabuleiros[indexTabuleiro] == 0)
		{
			return FALSE;
		}
	} /* if */

	return TRUE;

} /* Fim fun��o: TSTTAB -Validar indice de tabuleiros */


/********** Fim do m�dulo de implementa��o: TSTTAB Teste Tabuleiro **********/

