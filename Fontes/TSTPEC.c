/***************************************************************************
*  $MCI Módulo de implementação: TSTPEC Teste Peca
*
*  Arquivo gerado:              TSTPEC.c
*  Letras identificadoras:      TSTPEC
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
*		Versão  Autor   Data		Observações
*		1		yz		09/05/2019	Implementação do módulo de testes
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>


#include    "Generico.h"
#include    "LerParm.h"
#include    "TST_Espc.h"
#include    "peca.h"


/***********************************************************************
*
*  $DC Dados Globais: TSTPEC
*
*		$ED Descrição do tipo
*			- comandos definidos para usar no scipt de teste
*
***********************************************************************/

static const char RESET_PECA_CMD[] = "=resetteste";
static const char CRIA_PECA_CMD[] = "=criapeca";
static const char RETORNA_NUM_CMD[] = "=retornanumpeca";
static const char RETORNA_COR_CMD[] = "=retornacorpeca";
static const char DESTROI_PECA_CMD[] = "=destroipeca";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PECA 25

/***********************************************************************
*
*  $TC Tipo de dados: TSTPEC Vetor de Peças
*
*		$ED Descrição do tipo
*			- vetor de peças para serem testados
*
***********************************************************************/


Peca * vtPecas[DIM_VT_PECA];


/***** Protótipos das funções encapsuladas no módulo *****/

static int validarInxPeca(int indexPeca, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TSTPEC &Testar Peca
*
*  $ED Descrição da função
*     Podem ser criadas até 25 casas, identificadas pelos indices de 0 à 25.
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de memória
*     =criapeca			        inxPeca
*     =retornanumero            inxPeca		intPecaEsp
*	  =retornacor				inxPeca		intCorEsperado
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {
	int indexPeca	= -1,
		numLidos	= -1,
		i			= -1,
		condRetEsp	= -1,
		numPeca		= -1;

	COR_tpCor cor;
	PEC_CondRet pecCondRet;
	/* Efetuar reset de teste de peca */

	if (strcmp(ComandoTeste, RESET_PECA_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_PECA; i++)
		{
			vtPecas[i] = NULL;
		} /* for */

		return TST_CondRetOK;
		/* fim ativa: Efetuar reset de teste de peca */
	}else if (strcmp(ComandoTeste, CRIA_PECA_CMD) == 0)
	{
		/* Testar CriaPeca*/
		numLidos = LER_LerParametros("iii",
			&indexPeca, &cor, &numPeca);

		if ((numLidos != 3)
			|| (!validarInxPeca(indexPeca, VAZIO)))
		{
			return TST_CondRetParm;
		}

		pecCondRet = PEC_criaPeca(&vtPecas[indexPeca], cor, numPeca);
		if (pecCondRet == PEC_condRetFaltouMemoria) {
			return TST_CondRetMemoria;
		}
		return TST_CompararPonteiroNulo(1, vtPecas[indexPeca],
			"Erro em ponteiro de nova Peca.");
		/* fim ativa: Testar CriaPeca' */
	} else if (strcmp(ComandoTeste, RETORNA_NUM_CMD) == 0)
	{
		/* Testar RetornaNum*/
		numLidos = LER_LerParametros("ii",
			&indexPeca, &condRetEsp);

		if ((numLidos != 2)
			|| (!validarInxPeca(indexPeca, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		}

		PEC_retornaNum(vtPecas[indexPeca], &numPeca);
		return TST_CompararInt(condRetEsp, numPeca,
			"Erro ao retornar numero da peca");
		/* fim ativa: Testar RetornaNum */
	} else if (strcmp(ComandoTeste, RETORNA_COR_CMD) == 0)
	{	
		/* Testar RetornaCor*/
		numLidos = LER_LerParametros("ii",
			&indexPeca, &condRetEsp);

		if ((numLidos != 2)
			|| (!validarInxPeca(indexPeca, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		PEC_retornaCor(vtPecas[indexPeca], &cor);
		return TST_CompararInt(condRetEsp, cor,
			"Erro ao retornar cor da peca");
		/* fim ativa: Testar RetornaCor */
	} else if (strcmp(ComandoTeste, DESTROI_PECA_CMD) == 0)
	{
		/* Testar DestroiPeca*/
		numLidos = LER_LerParametros("i",
			&indexPeca);

		if ((numLidos != 1)
			|| (!validarInxPeca(indexPeca, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		}

		pecCondRet = PEC_destruirPeca(vtPecas[indexPeca]);
		vtPecas[indexPeca] = NULL;
			

		return TST_CompararInt(PEC_condRetOk, pecCondRet,
			"Erro ao destruir casa.");

	}  /* if */ 
	/* fim ativa: Testar DestroiPeca */

	return TST_CondRetNaoConhec;
}/* Fim função: TSTPEC &TST_EfetuarComando */



/***********************************************************************
*
*  $FC Função: TSTPEC -Validar indice de Peca
*
***********************************************************************/

int validarInxPeca(int indexPeca, int Modo)
{

	if ((indexPeca < 0)
		|| (indexPeca >= DIM_VT_PECA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtPecas[indexPeca] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtPecas[indexPeca] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TSTPEC -Validar indice de peca */

/********** Fim do módulo de implementação: TSTPEC Teste Peca **********/