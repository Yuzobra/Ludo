/***************************************************************************
*  $MCI Módulo de implementação: CIR Lista Circular Duplamente Encadeada
*
*  Arquivo gerado:              ListaCirc.c
*  Letras identificadoras:      CIR
*
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Histórico de evolução:
*		Versão  Autor   Data		Observações
*		2		yz		11/05/2019	Correção de um acesso indevido em esvaziarLista
*		1		yz		28/04/2019	Implementação dos tipos estrurados e funções
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "CONTA.H"

#define LISTA_OWN
#include "ListaCirc.h"
#undef LISTA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: CIR Elemento da lista circular
*
*
***********************************************************************/

typedef struct tagElemLista {

	void* pValor;
	/* Ponteiro para o valor contido no elemento */

	struct tagElemLista* pAnt;
	/* Ponteiro para o elemento predecessor */

	struct tagElemLista* pProx;
	/* Ponteiro para o elemento sucessor */

} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: CIR Descritor da cabeça de lista circular
*
*
***********************************************************************/

typedef struct CIR_tagLista {

	tpElemLista* pElemCorr;
	/* Ponteiro para o elemento corrente da lista */

	int numElem;
	/* Número de elementos da lista */

	void (*ExcluirValor) (void* pValor);
	/* Ponteiro para a função de destruição do valor contido em um elemento */

} CIR_tpLista;

/***** Protótipos das funções encapsuladas no módulo *****/

static void LiberarElemento( CIR_tppLista   pLista,
							 tpElemLista* pElem   );

static tpElemLista* CriarElemento( CIR_tppLista pLista,
								   void* pValor		 );

static void LimparCabeca( CIR_tppLista pLista );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CIR  &Criar Lista Circular
*
*  ************************************************************************/

CIR_tppLista CIR_CriarLista(
	void   (*ExcluirValor) (void* pDado))
{
	CNT_CONTAR("Cria lista vazia");
	CIR_tpLista* pLista = NULL;
	


	pLista = (CIR_tpLista*)malloc(sizeof(CIR_tpLista));
	if (pLista == NULL || ExcluirValor == NULL)
	{
		CNT_CONTAR("Falta memoria para criacao");
		return NULL;
	} /* if */

	CNT_CONTAR("Lista criada com sucesso");
	LimparCabeca(pLista);

	pLista->ExcluirValor = ExcluirValor;

	return pLista;

} /* Fim função: CIR  &CIR_CriarLista */

/***************************************************************************
*
*  Função: CIR  &Destruir Lista Circular
*
* *************************************************************************/

void CIR_DestruirLista(CIR_tppLista pLista)
{
	CNT_CONTAR("");
	if (pLista != NULL) {
		CNT_CONTAR("");                        //AQUIR
		CIR_EsvaziarLista(pLista);
		free(pLista);
	}

} /* Fim função: CIR  &CIR_DestruirLista */

/***************************************************************************
*
*  Função: CIR  &Esvaziar Lista Circular
*
*  ************************************************************************/

void CIR_EsvaziarLista(CIR_tppLista pLista)
{
	CNT_CONTAR("");                        //AQUIR
	tpElemLista* pIni;
	tpElemLista* pElem;
	tpElemLista* pProx;

	if (pLista == NULL) {
		CNT_CONTAR("");                        //AQUIR
		return;
	}
	CNT_CONTAR("");                        //AQUIR
	pIni	= pLista->pElemCorr;
	if (pIni == NULL)/*Lista ja está vazia*/ {
		CNT_CONTAR("");                        //AQUIR
		return;
	}
	CNT_CONTAR("");                        //AQUIR
	pElem	= pIni->pProx;
	while (pElem != pIni)
	{
		CNT_CONTAR("");                        //AQUIR
		pProx = pElem->pProx;
		LiberarElemento(pLista, pElem);
		pElem = pProx;
	} /* while */
	CNT_CONTAR("");                        //AQUIR
	LiberarElemento(pLista, pElem);
	LimparCabeca(pLista);

} /* Fim função: CIR  &CIR_EsvaziarLista */

/***************************************************************************
*
*  Função: CIR  &Inserir elemento antes
*
*  ************************************************************************/

CIR_tpCondRet CIR_InserirElementoAntes(CIR_tppLista pLista,
	void* pValor)
{
	CNT_CONTAR("Insercao de elemento antes");
	tpElemLista* pElem;

	if (pLista == NULL || pValor == NULL) {
		CNT_CONTAR("Parametros de entrada incorretos");
		return CIR_condRetParmIncorretos;
	}

	/* Criar elemento a inerir antes */

	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{	
		CNT_CONTAR("Falta memoria para criacao");
		return CIR_condRetFaltouMemoria;
	} /* if */

 /* Encadear o elemento antes do elemento corrente */
	if (pLista->pElemCorr == NULL) {
		CNT_CONTAR("Insercao quando elemento corrente nulo");
		pElem->pProx = pElem;
		pElem->pAnt	 = pElem;
	}
	else
	{	
		CNT_CONTAR("Elemento corrente nao nulo");                                    // AQUIR
		if (pLista->pElemCorr->pAnt != pLista->pElemCorr)
		{
			CNT_CONTAR("Insercao quando a lista tem mais de um elemento");                               // AQUIR
			pElem->pAnt = pLista->pElemCorr->pAnt;
			pLista->pElemCorr->pAnt->pProx = pElem;
		}
		else
		{
			CNT_CONTAR("Insercao quando a lista possui apenas um elemento");                                //AQUIR
			pLista->pElemCorr->pProx = pElem;
			pElem->pAnt				 = pLista->pElemCorr;
		} /* if */
		CNT_CONTAR("Religacao da lista");                                     //AQUIR
		pElem->pProx			= pLista->pElemCorr;
		pLista->pElemCorr->pAnt = pElem;
	} /* if */
	CNT_CONTAR("Elemento inserido com sucesso");                                          //AQUIR
	pLista->pElemCorr = pElem;
	return CIR_condRetOK;

} /* Fim função: CIR  &CIR_InserirElementoAntes */


/***************************************************************************
*
*  Função: CIR  &Inserir elemento após
*
*  ************************************************************************/

CIR_tpCondRet CIR_InserirElementoApos(CIR_tppLista pLista,
	void* pValor)

{
	CNT_CONTAR("Insercao de elemento apos");                        //AQUIR
	tpElemLista* pElem;

	
	if (pLista == NULL || pValor == NULL) {
		CNT_CONTAR("Parametros de entrada incorretos");                        //AQUIR
		return CIR_condRetParmIncorretos;
	}

	/* Criar elemento a inserir após */
	CNT_CONTAR("Criacao do elemento");                        //AQUIR
	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{
		CNT_CONTAR("Falta memoria para criacao");                        //AQUIR
		return CIR_condRetFaltouMemoria;
	} /* if */

 /* Encadear o elemento após o elemento */

	if (pLista->pElemCorr == NULL)
	{
		CNT_CONTAR("Insercao quando elemento corrente nulo");                        //AQUIR
		pElem->pAnt  = pElem;
		pElem->pProx = pElem;
	}
	else
	{
		CNT_CONTAR("Insercao quando elemento corrente nao nulo");                        //AQUIR
		pElem->pProx					= pLista->pElemCorr->pProx;
		pLista->pElemCorr->pProx->pAnt	= pElem;
		pElem->pAnt						= pLista->pElemCorr;
		pLista->pElemCorr->pProx		= pElem;

	} /* if */

	CNT_CONTAR("Elemento inserido com sucesso");                        //AQUIR
	pLista->pElemCorr = pElem;

	return CIR_condRetOK;

} /* Fim função: CIR  &CIR_InserirElementoApos */




/***************************************************************************
*
*  Função: CIR  &Obter referência para o valor contido no elemento
*
*  ************************************************************************/

void* CIR_ObterValor(CIR_tppLista pLista)
{

	if (pLista == NULL) {
		CNT_CONTAR("Parametros de entrada incorretos");                        //AQUIR
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		CNT_CONTAR("Lista vazia");                        //AQUIR
		return NULL;
	} /* if */

	CNT_CONTAR("Valor obtido com sucesso");                        //AQUIR
	return pLista->pElemCorr->pValor;

} /* Fim função: CIR  &CIR_ObterValor */


/***************************************************************************
*
*  Função: CIR  &Avançar elemento
*
*  ************************************************************************/

CIR_tpCondRet CIR_AvancarElementoCorrente(CIR_tppLista pLista,
	int numElem)
{
	CNT_CONTAR("Avanca para o proximo elemento");                        //AQUIR
	int i;

	tpElemLista* pElem;
	
	if (pLista == NULL) {
		CNT_CONTAR("Parametros de entrada incorretos");                        //AQUIR
		return CIR_condRetParmIncorretos;
	}

	/* Tratar lista vazia */

	if (pLista->pElemCorr == NULL)
	{
		CNT_CONTAR("");                        //AQUIR
		return CIR_condRetListaVazia;

	} /* fim ativa: Tratar lista vazia */

 /* Tratar avançar para frente */

	if (numElem > 0)
	{
		CNT_CONTAR("");                        //AQUIR
		pElem = pLista->pElemCorr;
		for (i = numElem; i > 0; i--)
		{
			CNT_CONTAR("");                        //AQUIR
			pElem = pElem->pProx;
		} /* for */
		CNT_CONTAR("");                        //AQUIR
		pLista->pElemCorr = pElem;
		return CIR_condRetOK;

	} /* fim ativa: Tratar avançar para frente */

 /* Tratar avançar para trás */

	else if (numElem < 0)
	{
		CNT_CONTAR("");                        //AQUIR
		pElem = pLista->pElemCorr;
		for (i = numElem; i < 0; i++)
		{
			CNT_CONTAR("");                        //AQUIR
			pElem = pElem->pAnt;
		} /* for */
		CNT_CONTAR("");                        //AQUIR
		pLista->pElemCorr = pElem;
		return CIR_condRetOK;
	} /* fim ativa: Tratar avançar para trás */

 /* Tratar não avançar */
	CNT_CONTAR("");                        //AQUIR
	return CIR_condRetOK;

} /* Fim função: CIR  &CIR_AvancarElementoCorrente */

/***************************************************************************
*
*  Função: CIR  &Excluir elemento
*
*  ************************************************************************/

CIR_tpCondRet CIR_ExcluirElemento(CIR_tppLista pLista)
{
	CNT_CONTAR("");                        //AQUIR
	tpElemLista* pElem;

	if (pLista == NULL) {
		CNT_CONTAR("");                        //AQUIR
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		CNT_CONTAR("");                        //AQUIR
		return CIR_condRetListaVazia;
	} /* if */

	CNT_CONTAR("");                        //AQUIR
	pElem = pLista->pElemCorr;

	if (pElem->pAnt != pElem)
	{
		CNT_CONTAR("");                        //AQUIR
		pElem->pAnt->pProx = pElem->pProx;
		pElem->pProx->pAnt = pElem->pAnt;
		pLista->pElemCorr = pElem->pAnt;
	}
	else {
		CNT_CONTAR("");                        //AQUIR
		pLista->pElemCorr = NULL;
	} /* if */


	CNT_CONTAR("");                        //AQUIR
	LiberarElemento(pLista, pElem);

	return CIR_condRetOK;

} /* Fim função: CIR  &CIR_ExcluirElemento */


/***************************************************************************
*
*  Função: CIR  &Procurar elemento contendo valor
*
*  ************************************************************************/

CIR_tpCondRet CIR_ProcurarValor(CIR_tppLista pLista,
	void* pValor)
{
	CNT_CONTAR("");                        //AQUIR
	tpElemLista* pElem, *pIni;
	pIni = pLista->pElemCorr;


	if (pLista == NULL || pValor == NULL) {
		CNT_CONTAR("");                        //AQUIR
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		CNT_CONTAR("");                        //AQUIR
		return CIR_condRetListaVazia;
	} /* if */

	if (pIni->pValor == pValor) {
		CNT_CONTAR("");                        //AQUIR
		pLista->pElemCorr = pIni;
		return CIR_condRetOK;
	}

	for (pElem = pLista->pElemCorr->pProx;
		pElem != pIni;
		pElem = pElem->pProx)
	{
		CNT_CONTAR("");                        //AQUIR
		if (pElem->pValor == pValor)
		{
			CNT_CONTAR("");                        //AQUIR
			pLista->pElemCorr = pElem;
			return CIR_condRetOK;
		} /* if */
	} /* for */
	CNT_CONTAR("");                        //AQUIR
	return CIR_condRetNaoAchou;

} /* Fim função: CIR  &CIR_ProcurarValor */



/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: CIR  -Liberar elemento da lista circular
*

*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do elemento e o
*     próprio elemento.
*
***********************************************************************/

void LiberarElemento(CIR_tppLista   pLista,
	tpElemLista * pElem)
{

	if (pLista == NULL || pElem == NULL) {
		CNT_CONTAR("");                        //AQUIR
		return ;
	}

	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL))
	{
		CNT_CONTAR("");                        //AQUIR
		pLista->ExcluirValor(pElem->pValor);
	} /* if */

	CNT_CONTAR("");                        //AQUIR
	free(pElem);

	pLista->numElem--;

} /* Fim função: CIR  -LiberarElemento */


/***********************************************************************
*
*  $FC Função: CIR  -Criar o elemento
*
***********************************************************************/

tpElemLista* CriarElemento(CIR_tppLista pLista,
	void* pValor)
{
	CNT_CONTAR("");                        //AQUIR
	tpElemLista* pElem;


	if (pLista == NULL || pValor == NULL) {
		CNT_CONTAR("");                        //AQUIR
		return NULL;
	}
	CNT_CONTAR("");                        //AQUIR
	pElem = (tpElemLista*)malloc(sizeof(tpElemLista));
	if (pElem == NULL)
	{
		CNT_CONTAR("");                        //AQUIR
		return NULL;
	} /* if */

	CNT_CONTAR("");                        //AQUIR
	pElem->pValor = pValor;
	pElem->pAnt = NULL;
	pElem->pProx = NULL;

	pLista->numElem++;
	return pElem;

} /* Fim função: CIR  -CriarElementoo */


/***********************************************************************
*
*  $FC Função: CIR  -Limpar a cabeça da lista
*
***********************************************************************/

void LimparCabeca(CIR_tppLista pLista)
{
	if (pLista == NULL) {
		CNT_CONTAR("");                        //AQUIR
		return;
	}
	CNT_CONTAR("");                        //AQUIR
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;

} /* Fim função: CIR  -LimparCabeca */

/********** Fim do módulo de implementação: CIR  Lista Circular Duplamente Encadeada **********/

