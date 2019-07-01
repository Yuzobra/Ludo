/***************************************************************************
*  $MCI M�dulo de implementa��o: TSTPEC Teste Peca
*
*  Arquivo gerado:              TSTPEC.c
*  Letras identificadoras:      TSTPEC
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
*		Vers�o  Autor   Data		Observa��es
*		1		yz		09/05/2019	Implementa��o do m�dulo de testes
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
*		$ED Descri��o do tipo
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
*  $TC Tipo de dados: TSTPEC Vetor de Pe�as
*
*		$ED Descri��o do tipo
*			- vetor de pe�as para serem testados
*
***********************************************************************/


Peca * vtPecas[DIM_VT_PECA];


/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

static int validarInxPeca(int indexPeca, int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TSTPEC &Testar Peca
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 25 casas, identificadas pelos indices de 0 � 25.
*
*     Comandos dispon�veis:
*
*     =resetteste
*           - anula o vetor de pecas. Provoca vazamento de mem�ria
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
}/* Fim fun��o: TSTPEC &TST_EfetuarComando */



/***********************************************************************
*
*  $FC Fun��o: TSTPEC -Validar indice de Peca
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

} /* Fim fun��o: TSTPEC -Validar indice de peca */

/********** Fim do m�dulo de implementa��o: TSTPEC Teste Peca **********/