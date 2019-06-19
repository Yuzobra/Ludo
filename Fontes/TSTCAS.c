/***************************************************************************
*  $MCI Módulo de implementação: TSTCAS Teste Casa
*
*  Arquivo gerado:              TSTCAS.c
*  Letras identificadoras:      TSTCAS
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
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>


#include    "Generico.h"
#include    "LerParm.h"
#include    "TST_Espc.h"
#include    "casa.h"

static const char RESET_CASA_CMD[] = "=resetteste";
static const char CRIA_COMUM_CMD[] = "=criacomum";
static const char CRIA_SEGURA_CMD[] = "=criasegura";
static const char CRIA_INICIAL_CMD[] = "=criainicial";
static const char CRIA_FINAL_CMD[] = "=criafinal";
static const char CRIA_ENTRADA_CMD[] = "=criaentrada";
static const char RETORNA_TIPO_CMD[] = "=retornatipocasa";
static const char RETORNA_COR_CMD[] = "=retornacorcasa";
static const char DESTROI_CASA_CMD[] = "=destroicasa";

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CASA 25

Casa * vtCasas[DIM_VT_CASA];


/***** Protótipos das funções encapsuladas no módulo *****/

static int validarIndexCasa(int indexCasa, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TSTCAS &Testar Casa
*
*  $ED Descrição da função
*     Podem ser criadas até 25 casas, identificadas pelos indices de 0 à 25.
*
*     Comandos disponíveis:
*
*	  =resetteste
*           - anula o vetor de casas. Provoca vazamento de memória
*     =criasegura		indCasa		intCor
*	  =criafinal		indCasa		intCor
*	  =criainicial		indCasa
*	  =criaentrada		indCasa		intCor
*	  =destroicasa		indCasa
*	  =retornatipocasa	indCasa		intTipoEsperado
*	  =retornacorcasa	indCasa		intCorEsperado
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste) {
	int indexCasa = -1,
		numLidos = -1,
		i = -1,
		condRetEsp = -1;
	COR_tpCor cor;
	CAS_tpTipo tipo;
	CAS_CondRet casCondRet;

	/* Efetuar reset de teste de casa */

	if (strcmp(ComandoTeste, RESET_CASA_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_CASA; i++)
		{
			vtCasas[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de casa */

	  /* Testar CriaCasaComum*/

	else if (strcmp(ComandoTeste, CRIA_COMUM_CMD) == 0)
	{
		numLidos = LER_LerParametros("i",
			&indexCasa);

		if ((numLidos != 1)
			|| (!validarIndexCasa(indexCasa, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		casCondRet = CAS_criaCasaComum(&vtCasas[indexCasa]);
		if (casCondRet == CAS_condRetFaltouMemoria) {
			return TST_CondRetMemoria;
		}
		return TST_CompararPonteiroNulo(1, vtCasas[indexCasa],
			"Erro em ponteiro de nova casa Comum.");

	} /* fim ativa: Testar CriarCasaComum */

	 /* Testar CriaCasaInicial*/

	else if (strcmp(ComandoTeste, CRIA_INICIAL_CMD) == 0)
	{

		numLidos = LER_LerParametros("i",
			&indexCasa);

		if ((numLidos != 1)
			|| (!validarIndexCasa(indexCasa, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		casCondRet = CAS_criaCasaInicial(&vtCasas[indexCasa]);
		if (casCondRet == CAS_condRetFaltouMemoria) {
			return TST_CondRetMemoria;
		}
		return TST_CompararPonteiroNulo(1, vtCasas[indexCasa],
			"Erro em ponteiro de nova casa Inicial.");

	} /* fim ativa: Testar CriarCasaInicial */

	/* Testar CriaCasaSegura*/

	else if (strcmp(ComandoTeste, CRIA_SEGURA_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&indexCasa, &cor);

		if ((numLidos != 2)
			|| (!validarIndexCasa(indexCasa, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		casCondRet = CAS_criaCasaSegura(&vtCasas[indexCasa], cor);
		if (casCondRet == CAS_condRetFaltouMemoria) {
			return TST_CondRetMemoria;
		}
		return TST_CompararPonteiroNulo(1, vtCasas[indexCasa],
			"Erro em ponteiro de nova casa Segura.");

	} /* fim ativa: Testar CriarCasaSegura */

	/* Testar CriaCasaFinal*/

	else if (strcmp(ComandoTeste, CRIA_FINAL_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&indexCasa, &cor);

		if ((numLidos != 2)
			|| (!validarIndexCasa(indexCasa, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		casCondRet = CAS_criaCasaFinal(&vtCasas[indexCasa], cor);
		if (casCondRet == CAS_condRetFaltouMemoria) {
			return TST_CondRetMemoria;
		}
		return TST_CompararPonteiroNulo(1, vtCasas[indexCasa],
			"Erro em ponteiro de nova casa Final.");

	} /* fim ativa: Testar CriarCasaFinal */


	/* Testar CriaCasaEntrada*/

	else if (strcmp(ComandoTeste, CRIA_ENTRADA_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&indexCasa, &cor);

		if ((numLidos != 2)
			|| (!validarIndexCasa(indexCasa, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		casCondRet = CAS_criaEntrada(&vtCasas[indexCasa], cor);
		if (casCondRet == CAS_condRetFaltouMemoria) {
			return TST_CondRetMemoria;
		}
		return TST_CompararPonteiroNulo(1, vtCasas[indexCasa],
			"Erro em ponteiro de nova casa Entrada.");

	} /* fim ativa: Testar CriarCasaEntrada */


	/* Testar RetornaTipo*/

	else if (strcmp(ComandoTeste, RETORNA_TIPO_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&indexCasa, &condRetEsp);

		if ((numLidos != 2)
			|| (!validarIndexCasa(indexCasa, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CAS_retornaTipo(vtCasas[indexCasa], &tipo);

		return TST_CompararInt(condRetEsp, tipo,
			"Condiçao de retorno errada ao retornar o tipo.");

	} /* fim ativa: Testar RetornaTipo */

	/* Testar RetornaCor*/

	else if (strcmp(ComandoTeste, RETORNA_COR_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&indexCasa, &condRetEsp);

		if ((numLidos != 2)
			|| (!validarIndexCasa(indexCasa, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CAS_retornaCor(vtCasas[indexCasa], &cor);

		return TST_CompararInt(condRetEsp, cor,
			"Condiçao de retorno errada ao retornar cor da casa.");

	} /* fim ativa: Testar RetornaCor */

	/* Testar DestroiCasa*/

	else if (strcmp(ComandoTeste, DESTROI_CASA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i",
			&indexCasa);

		if ((numLidos != 1)
			|| (!validarIndexCasa(indexCasa, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		casCondRet = CAS_destruirCasa(vtCasas[indexCasa]);

		return TST_CompararInt(CAS_condRetOk, casCondRet,
			"Erro ao destruir casa.");

	} /* fim ativa: Testar RetornaCor */

	return TST_CondRetNaoConhec;
}

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TSTCAS -Validar indice de peca
*
***********************************************************************/

int validarIndexCasa(int indexCasa, int Modo)
{

	if ((indexCasa < 0)
		|| (indexCasa >= DIM_VT_CASA))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtCasas[indexCasa] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtCasas[indexCasa] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TSTCAS -Validar indice de peca */

/********** Fim do módulo de implementação: TLTCAS Teste Casa **********/