/***************************************************************************
*  $MCI Módulo de implementação: TSTLisCirc Teste lista de símbolos
*
*  Arquivo gerado:              TSTLisCirc.c
*  Letras identificadoras:      TSTLisCirc
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

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "ListaCirc.h"


static const char RESET_LISTA_CMD[] = "=resetteste";
static const char CRIAR_LISTA_CMD[] = "=criarlista";
static const char DESTRUIR_LISTA_CMD[] = "=destruirlista";
static const char ESVAZIAR_LISTA_CMD[] = "=esvaziarlista";
static const char INS_ELEM_ANTES_CMD[] = "=inselemantes";
static const char INS_ELEM_APOS_CMD[] = "=inselemapos";
static const char OBTER_VALOR_CMD[] = "=obtervalorelem";
static const char EXC_ELEM_CMD[] = "=excluirelem";
static const char AVANCAR_ELEM_CMD[] = "=avancarelem";


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISCIRC   25
#define DIM_VALOR     100

CIR_tppLista   vtLisCirc[DIM_VT_LISCIRC];

/***** Protótipos das funções encapsuladas no módulo *****/

static void DestruirValor(void * pValor);

static int ValidarIndexLisCirc(int indexLisCirc, int Modo);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TSTLisCirc &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 25 listas, identificadas pelos índices 0 a 24
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   indexLisCirc
*     =destruirlista                indexLisCirc
*     =esvaziarlista                indexLisCirc
*     =inselemantes                 indexLisCirc  string  CondRetEsp
*     =inselemapos                  indexLisCirc  string  CondRetEsp
*     =obtervalorelem               indexLisCirc  string  CondretPonteiro
*     =excluirelem                  indexLisCirc  CondRetEsp
*     =avancarelem                  indexLisCirc  numElem CondRetEsp
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char * ComandoTeste)
{

	int indexLisCirc = -1,
		numLidos = -1,
		CondRetEsp = -1;

	TST_tpCondRet CondRet;

	char   StringDado[DIM_VALOR];
	char * pDado;

	int ValEsp = -1;

	int i;

	int numElem = -1;

	StringDado[0] = 0;

	/* Efetuar reset de teste de lista circular */

	if (strcmp(ComandoTeste, RESET_LISTA_CMD) == 0)
	{

		for (i = 0; i < DIM_VT_LISCIRC; i++)
		{
			vtLisCirc[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de lista circular */

 /* Testar CriarListaCircular */

	else if (strcmp(ComandoTeste, CRIAR_LISTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i",
			&indexLisCirc);

		if ((numLidos != 1)
			|| (!ValidarIndexLisCirc(indexLisCirc, VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		vtLisCirc[indexLisCirc] =
			CIR_CriarLista(DestruirValor);

		return TST_CompararPonteiroNulo(1, vtLisCirc[indexLisCirc],
			"Erro em ponteiro de nova lista circular.");

	} /* fim ativa: Testar CriarListaCircular */

 /* Testar Esvaziar lista circular */

	else if (strcmp(ComandoTeste, ESVAZIAR_LISTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i",
			&indexLisCirc);

		if ((numLidos != 1)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CIR_EsvaziarLista(vtLisCirc[indexLisCirc]);

		return TST_CondRetOK;

	} /* fim ativa: Testar Esvaziar lista circular */

 /* Testar Destruir lista */

	else if (strcmp(ComandoTeste, DESTRUIR_LISTA_CMD) == 0)
	{

		numLidos = LER_LerParametros("i",
			&indexLisCirc);

		if ((numLidos != 1)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		CIR_DestruirLista(vtLisCirc[indexLisCirc]);
		vtLisCirc[indexLisCirc] = NULL;

		return TST_CondRetOK;

	} /* fim ativa: Testar Destruir lista circular */

 /* Testar inserir elemento antes */

	else if (strcmp(ComandoTeste, INS_ELEM_ANTES_CMD) == 0)
	{

		numLidos = LER_LerParametros("isi",
			&indexLisCirc, StringDado, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		pDado = (char *)malloc(strlen(StringDado) + 1);
		if (pDado == NULL)
		{
			return TST_CondRetMemoria;
		} /* if */

		strcpy(pDado, StringDado);


		CondRet = CIR_InserirElementoAntes(vtLisCirc[indexLisCirc], pDado);

		if (CondRet != CIR_condRetOK)
		{
			free(pDado);
		} /* if */

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao inserir antes.");

	} /* fim ativa: Testar inserir elemento antes */

 /* Testar inserir elemento apos */

	else if (strcmp(ComandoTeste, INS_ELEM_APOS_CMD) == 0)
	{

		numLidos = LER_LerParametros("isi",
			&indexLisCirc, StringDado, &CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		pDado = (char *)malloc(strlen(StringDado) + 1);
		if (pDado == NULL)
		{
			return TST_CondRetMemoria;
		} /* if */

		strcpy(pDado, StringDado);


		CondRet = CIR_InserirElementoApos(vtLisCirc[indexLisCirc], pDado);

		if (CondRet != CIR_condRetOK)
		{
			free(pDado);
		} /* if */

		return TST_CompararInt(CondRetEsp, CondRet,
			"Condicao de retorno errada ao inserir apos.");

	} /* fim ativa: Testar inserir elemento apos */

 /* Testar excluir simbolo */

	else if (strcmp(ComandoTeste, EXC_ELEM_CMD) == 0)
	{

		numLidos = LER_LerParametros("ii",
			&indexLisCirc, &CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(CondRetEsp,
			CIR_ExcluirElemento(vtLisCirc[indexLisCirc]),
			"Condição de retorno errada ao excluir.");

	} /* fim ativa: Testar excluir simbolo */

 /* Testar obter valor do elemento corrente */

	else if (strcmp(ComandoTeste, OBTER_VALOR_CMD) == 0)
	{

		numLidos = LER_LerParametros("isi",
			&indexLisCirc, StringDado, &ValEsp);

		if ((numLidos != 3)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		pDado = (char *)CIR_ObterValor(vtLisCirc[indexLisCirc]);

		if (ValEsp == 0)
		{
			return TST_CompararPonteiroNulo(0, pDado,
				"Valor não deveria existir.");
		} /* if */

		if (pDado == NULL)
		{
			return TST_CompararPonteiroNulo(1, pDado,
				"Dado tipo um deveria existir.");
		} /* if */

		return TST_CompararString(StringDado, pDado,
			"Valor do elemento errado.");

	} /* fim ativa: Testar obter valor do elemento corrente */

 /* TSTLisCirc  &Avançar elemento */

	else if (strcmp(ComandoTeste, AVANCAR_ELEM_CMD) == 0)
	{

		numLidos = LER_LerParametros("iii", &indexLisCirc, &numElem,
			&CondRetEsp);

		if ((numLidos != 3)
			|| (!ValidarIndexLisCirc(indexLisCirc, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		return TST_CompararInt(CondRetEsp,
			CIR_AvancarElementoCorrente(vtLisCirc[indexLisCirc], numElem),
			"Condicao de retorno errada ao avancar");

	} /* fim ativa: TSTLisCirc  &Avançar elemento */

	return TST_CondRetNaoConhec;

} /* Fim função: TSTLisCirc &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TSTLisCirc -Destruir valor
*
***********************************************************************/

void DestruirValor(void * pValor)
{

	free(pValor);

} /* Fim função: TSTLisCirc -Destruir valor */


/***********************************************************************
*
*  $FC Função: TSTLisCirc -Validar indice de lista
*
***********************************************************************/

int ValidarIndexLisCirc(int indexLisCirc, int Modo)
{

	if ((indexLisCirc < 0)
		|| (indexLisCirc >= DIM_VT_LISCIRC))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtLisCirc[indexLisCirc] != 0)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtLisCirc[indexLisCirc] == 0)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim função: TSTLisCirc -Validar indice de lista */

/********** Fim do módulo de implementação: TSTLisCirc Teste lista circular duplamente encadeada de símbolos **********/