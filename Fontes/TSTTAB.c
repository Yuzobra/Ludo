/***************************************************************************
*  $MCI Módulo de implementação: TSTTAB Teste Tabuleiro
*
*  Arquivo gerado:              TSTTAB .c
*  Letras identificadoras:      TSTTAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		Versão  Autor   Data		Observações
*		1		yz		09/05/2019	Implementação do módulo de testes
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
*		$ED Descrição do tipo
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
*		$ED Descrição do tipo
*			- vetor de tabuleiros para serem testados
*
***********************************************************************/

Tabuleiro * vtTabuleiros[DIM_VT_TABULEIRO];

/***** Protótipos das funções encapuladas no módulo *****/

static int ValidarIndexTabuleiro(int indexTabuleiro, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TSTTAB &Testar Tabuleiro
*
*  $ED Descrição da função
*     Podem ser criadas até 25 listas, identificadas pelos índices 0 a 24
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
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

} /* Fim função: TSTTAB &Testar Tabuleiro */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TSTTAB -Validar indice de lista
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

} /* Fim função: TSTTAB -Validar indice de tabuleiros */


/********** Fim do módulo de implementação: TSTTAB Teste Tabuleiro **********/

