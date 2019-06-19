/***************************************************************************
*  $MCI M�dulo de implementa��o: CIR Lista Circular Duplamente Encadeada
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
*  $HA Hist�rico de evolu��o:
*		Vers�o  Autor   Data		Observa��es
*		2		yz		11/05/2019	Corre��o de um acesso indevido em esvaziarLista
*		1		yz		28/04/2019	Implementa��o dos tipos estrurados e fun��es
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
*  $TC Tipo de dados: CIR Descritor da cabe�a de lista circular
*
*
***********************************************************************/

typedef struct CIR_tagLista {

	tpElemLista* pElemCorr;
	/* Ponteiro para o elemento corrente da lista */

	int numElem;
	/* N�mero de elementos da lista */

	void (*ExcluirValor) (void* pValor);
	/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */

} CIR_tpLista;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

static void LiberarElemento( CIR_tppLista   pLista,
							 tpElemLista* pElem   );

static tpElemLista* CriarElemento( CIR_tppLista pLista,
								   void* pValor		 );

static void LimparCabeca( CIR_tppLista pLista );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CIR  &Criar Lista Circular
*
*  ************************************************************************/

CIR_tppLista CIR_CriarLista(
	void   (*ExcluirValor) (void* pDado))
{

	CIR_tpLista* pLista = NULL;
	


	pLista = (CIR_tpLista*)malloc(sizeof(CIR_tpLista));
	if (pLista == NULL || ExcluirValor == NULL)
	{
		return NULL;
	} /* if */

	LimparCabeca(pLista);

	pLista->ExcluirValor = ExcluirValor;

	return pLista;

} /* Fim fun��o: CIR  &CIR_CriarLista */

/***************************************************************************
*
*  Fun��o: CIR  &Destruir Lista Circular
*
* *************************************************************************/

void CIR_DestruirLista(CIR_tppLista pLista)
{
	if (pLista != NULL) {
		CIR_EsvaziarLista(pLista);
		free(pLista);
	}

} /* Fim fun��o: CIR  &CIR_DestruirLista */

/***************************************************************************
*
*  Fun��o: CIR  &Esvaziar Lista Circular
*
*  ************************************************************************/

void CIR_EsvaziarLista(CIR_tppLista pLista)
{
	tpElemLista* pIni;
	tpElemLista* pElem;
	tpElemLista* pProx;

	if (pLista == NULL) {
		return;
	}

	pIni	= pLista->pElemCorr;
	if (pIni == NULL)/*Lista ja est� vazia*/ {
		return;
	}
	pElem	= pIni->pProx;
	while (pElem != pIni)
	{
		pProx = pElem->pProx;
		LiberarElemento(pLista, pElem);
		pElem = pProx;
	} /* while */
	LiberarElemento(pLista, pElem);
	LimparCabeca(pLista);

} /* Fim fun��o: CIR  &CIR_EsvaziarLista */

/***************************************************************************
*
*  Fun��o: CIR  &Inserir elemento antes
*
*  ************************************************************************/

CIR_tpCondRet CIR_InserirElementoAntes(CIR_tppLista pLista,
	void* pValor)
{

	tpElemLista* pElem;

	if (pLista == NULL || pValor == NULL) {
		return CIR_condRetParmIncorretos;
	}

	/* Criar elemento a inerir antes */

	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{
		return CIR_condRetFaltouMemoria;
	} /* if */

 /* Encadear o elemento antes do elemento corrente */
	if (pLista->pElemCorr == NULL) {
		pElem->pProx = pElem;
		pElem->pAnt	 = pElem;
	}
	else
	{
		if (pLista->pElemCorr->pAnt != pLista->pElemCorr)
		{
			pElem->pAnt = pLista->pElemCorr->pAnt;
			pLista->pElemCorr->pAnt->pProx = pElem;
		}
		else
		{
			pLista->pElemCorr->pProx = pElem;
			pElem->pAnt				 = pLista->pElemCorr;
		} /* if */

		pElem->pProx			= pLista->pElemCorr;
		pLista->pElemCorr->pAnt = pElem;
	} /* if */

	pLista->pElemCorr = pElem;
	return CIR_condRetOK;

} /* Fim fun��o: CIR  &CIR_InserirElementoAntes */


/***************************************************************************
*
*  Fun��o: CIR  &Inserir elemento ap�s
*
*  ************************************************************************/

CIR_tpCondRet CIR_InserirElementoApos(CIR_tppLista pLista,
	void* pValor)

{

	tpElemLista* pElem;

	
	if (pLista == NULL || pValor == NULL) {
		return CIR_condRetParmIncorretos;
	}

	/* Criar elemento a inserir ap�s */

	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{
		return CIR_condRetFaltouMemoria;
	} /* if */

 /* Encadear o elemento ap�s o elemento */

	if (pLista->pElemCorr == NULL)
	{
		pElem->pAnt  = pElem;
		pElem->pProx = pElem;
	}
	else
	{
		pElem->pProx					= pLista->pElemCorr->pProx;
		pLista->pElemCorr->pProx->pAnt	= pElem;
		pElem->pAnt						= pLista->pElemCorr;
		pLista->pElemCorr->pProx		= pElem;

	} /* if */

	pLista->pElemCorr = pElem;

	return CIR_condRetOK;

} /* Fim fun��o: CIR  &CIR_InserirElementoApos */




/***************************************************************************
*
*  Fun��o: CIR  &Obter refer�ncia para o valor contido no elemento
*
*  ************************************************************************/

void* CIR_ObterValor(CIR_tppLista pLista)
{

	if (pLista == NULL) {
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		return NULL;
	} /* if */

	return pLista->pElemCorr->pValor;

} /* Fim fun��o: CIR  &CIR_ObterValor */


/***************************************************************************
*
*  Fun��o: CIR  &Avan�ar elemento
*
*  ************************************************************************/

CIR_tpCondRet CIR_AvancarElementoCorrente(CIR_tppLista pLista,
	int numElem)
{

	int i;

	tpElemLista* pElem;
	
	if (pLista == NULL) {
		return CIR_condRetParmIncorretos;
	}

	/* Tratar lista vazia */

	if (pLista->pElemCorr == NULL)
	{

		return CIR_condRetListaVazia;

	} /* fim ativa: Tratar lista vazia */

 /* Tratar avan�ar para frente */

	if (numElem > 0)
	{

		pElem = pLista->pElemCorr;
		for (i = numElem; i > 0; i--)
		{
			pElem = pElem->pProx;
		} /* for */
		pLista->pElemCorr = pElem;
		return CIR_condRetOK;

	} /* fim ativa: Tratar avan�ar para frente */

 /* Tratar avan�ar para tr�s */

	else if (numElem < 0)
	{

		pElem = pLista->pElemCorr;
		for (i = numElem; i < 0; i++)
		{
			pElem = pElem->pAnt;
		} /* for */
		pLista->pElemCorr = pElem;
		return CIR_condRetOK;
	} /* fim ativa: Tratar avan�ar para tr�s */

 /* Tratar n�o avan�ar */

	return CIR_condRetOK;

} /* Fim fun��o: CIR  &CIR_AvancarElementoCorrente */

/***************************************************************************
*
*  Fun��o: CIR  &Excluir elemento
*
*  ************************************************************************/

CIR_tpCondRet CIR_ExcluirElemento(CIR_tppLista pLista)
{

	tpElemLista* pElem;

	if (pLista == NULL) {
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		return CIR_condRetListaVazia;
	} /* if */

	pElem = pLista->pElemCorr;

	if (pElem->pAnt != pElem)
	{
		pElem->pAnt->pProx = pElem->pProx;
		pElem->pProx->pAnt = pElem->pAnt;
		pLista->pElemCorr = pElem->pAnt;
	}
	else {
		pLista->pElemCorr = NULL;
	} /* if */



	LiberarElemento(pLista, pElem);

	return CIR_condRetOK;

} /* Fim fun��o: CIR  &CIR_ExcluirElemento */


/***************************************************************************
*
*  Fun��o: CIR  &Procurar elemento contendo valor
*
*  ************************************************************************/

CIR_tpCondRet CIR_ProcurarValor(CIR_tppLista pLista,
	void* pValor)
{

	tpElemLista* pElem, *pIni;
	pIni = pLista->pElemCorr;


	if (pLista == NULL || pValor == NULL) {
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		return CIR_condRetListaVazia;
	} /* if */

	if (pIni->pValor == pValor) {
		pLista->pElemCorr = pIni;
		return CIR_condRetOK;
	}

	for (pElem = pLista->pElemCorr->pProx;
		pElem != pIni;
		pElem = pElem->pProx)
	{
		if (pElem->pValor == pValor)
		{
			pLista->pElemCorr = pElem;
			return CIR_condRetOK;
		} /* if */
	} /* for */

	return CIR_condRetNaoAchou;

} /* Fim fun��o: CIR  &CIR_ProcurarValor */



/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: CIR  -Liberar elemento da lista circular
*

*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

void LiberarElemento(CIR_tppLista   pLista,
	tpElemLista * pElem)
{

	if (pLista == NULL || pElem == NULL) {
		return ;
	}

	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL))
	{
		pLista->ExcluirValor(pElem->pValor);
	} /* if */

	free(pElem);

	pLista->numElem--;

} /* Fim fun��o: CIR  -LiberarElemento */


/***********************************************************************
*
*  $FC Fun��o: CIR  -Criar o elemento
*
***********************************************************************/

tpElemLista* CriarElemento(CIR_tppLista pLista,
	void* pValor)
{

	tpElemLista* pElem;


	if (pLista == NULL || pValor == NULL) {
		return NULL;
	}

	pElem = (tpElemLista*)malloc(sizeof(tpElemLista));
	if (pElem == NULL)
	{
		return NULL;
	} /* if */

	pElem->pValor = pValor;
	pElem->pAnt = NULL;
	pElem->pProx = NULL;

	pLista->numElem++;
	return pElem;

} /* Fim fun��o: CIR  -CriarElementoo */


/***********************************************************************
*
*  $FC Fun��o: CIR  -Limpar a cabe�a da lista
*
***********************************************************************/

void LimparCabeca(CIR_tppLista pLista)
{
	if (pLista == NULL) {
		return;
	}
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;

} /* Fim fun��o: CIR  -LimparCabeca */

/********** Fim do m�dulo de implementa��o: CIR  Lista Circular Duplamente Encadeada **********/

