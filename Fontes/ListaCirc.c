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
*		3		vh		29/06		Instrumentação do módulo com o CONTA
*		2		yz		11/05/2019	Correção de um acesso indevido em esvaziarLista
*		1		yz		28/04/2019	Implementação dos tipos estrurados e funções
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>


#ifdef _DEBUG
	#include "GENERICO.h"
	#include "CONTA.h"
#endif

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

	
	CIR_tpLista* pLista = NULL;
	#ifdef _DEBUG
		CNT_CONTAR("Cria lista vazia");
	#endif

	pLista = (CIR_tpLista*)malloc(sizeof(CIR_tpLista));
	if (pLista == NULL || ExcluirValor == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Falta memoria1");
		#endif
		return NULL;
	} /* if */
	#ifdef _DEBUG
		CNT_CONTAR("Lista criada com sucesso");
	#endif
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
	#ifdef _DEBUG
		CNT_CONTAR("Destruir lista");
	#endif
	if (pLista != NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Destruindo lista nao vazia");         
		#endif
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
	tpElemLista* pIni;
	tpElemLista* pElem;
	tpElemLista* pProx;
	#ifdef _DEBUG
		CNT_CONTAR("Esvaziar lista");
	#endif 


	if (pLista == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos1");    
		#endif
		return;
	}
	#ifdef _DEBUG
		CNT_CONTAR("Iniciar a lista");              
	#endif
	pIni	= pLista->pElemCorr;
	if (pIni == NULL)/*Lista ja está vazia*/ {
		#ifdef _DEBUG
			CNT_CONTAR("Lista vazia1");              
		#endif
		return;
	}
	#ifdef _DEBUG
		CNT_CONTAR("Correr a lista1"); 
	#endif
	pElem	= pIni->pProx;
	while (pElem != pIni)
	{
		#ifdef _DEBUG
				CNT_CONTAR("Corre a lista liberando os elementos");                        
		#endif
		pProx = pElem->pProx;
		LiberarElemento(pLista, pElem);
		pElem = pProx;
	} /* while */
	#ifdef _DEBUG
		CNT_CONTAR("Lista esvaziada");                        
	#endif
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

	tpElemLista* pElem;
	#ifdef _DEBUG
		CNT_CONTAR("Insercao de elemento antes");
	#endif
	if (pLista == NULL || pValor == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos2");
		#endif
		return CIR_condRetParmIncorretos;
	}

	/* Criar elemento a inerir antes */

	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{	
		#ifdef _DEBUG
			CNT_CONTAR("Falta memoria2");
		#endif
		return CIR_condRetFaltouMemoria;
	} /* if */

 /* Encadear o elemento antes do elemento corrente */
	if (pLista->pElemCorr == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Insercao quando elemento corrente nulo1");
		#endif
		pElem->pProx = pElem;
		pElem->pAnt	 = pElem;
	}
	else
	{	
		#ifdef _DEBUG
			CNT_CONTAR("Elemento corrente nao nulo");                                    
		#endif
		if (pLista->pElemCorr->pAnt != pLista->pElemCorr)
		{
			#ifdef _DEBUG
				CNT_CONTAR("Insercao quando a lista tem mais de um elemento");                               
			#endif		
			pElem->pAnt = pLista->pElemCorr->pAnt;
			pLista->pElemCorr->pAnt->pProx = pElem;
		}
		else
		{
			#ifdef _DEBUG
				CNT_CONTAR("Insercao quando a lista possui apenas um elemento");                                
			#endif	
			pLista->pElemCorr->pProx = pElem;
			pElem->pAnt				 = pLista->pElemCorr;
		} /* if */
		#ifdef _DEBUG
			CNT_CONTAR("Religacao da lista");                                     
		#endif
		pElem->pProx = pLista->pElemCorr;
		pLista->pElemCorr->pAnt = pElem;
	} /* if */
	#ifdef _DEBUG
		CNT_CONTAR("Elemento inserido com sucesso1");                                          
	#endif
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

	tpElemLista* pElem;

	#ifdef _DEBUG
		CNT_CONTAR("Insercao de elemento apos");     
	#endif
	if (pLista == NULL || pValor == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos3");                        
		#endif
		return CIR_condRetParmIncorretos;
	}

	/* Criar elemento a inserir após */
	#ifdef _DEBUG
		CNT_CONTAR("Criacao do elemento1");                        
	#endif
	pElem = CriarElemento(pLista, pValor);
	if (pElem == NULL)
	{
	#ifdef _DEBUG
		CNT_CONTAR("Falta memoria3");                        
	#endif
		return CIR_condRetFaltouMemoria;
	} /* if */

 /* Encadear o elemento após o elemento */

	if (pLista->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Insercao quando elemento corrente nulo2");                        
		#endif
		pElem->pAnt  = pElem;
		pElem->pProx = pElem;
	}
	else
	{
		#ifdef _DEBUG
			CNT_CONTAR("Insercao quando elemento corrente nao nulo");                        
		#endif
		pElem->pProx					= pLista->pElemCorr->pProx;
		pLista->pElemCorr->pProx->pAnt	= pElem;
		pElem->pAnt						= pLista->pElemCorr;
		pLista->pElemCorr->pProx		= pElem;

	} /* if */
	#ifdef _DEBUG
		CNT_CONTAR("Elemento inserido com sucesso2");                        
	#endif
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
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos4");                        
		#endif
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Lista vazia2");                        
		#endif
		return NULL;
	} /* if */

	#ifdef _DEBUG
		CNT_CONTAR("Valor obtido com sucesso");                        
	#endif
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
	int i;
	tpElemLista* pElem;

	#ifdef _DEBUG
		CNT_CONTAR("Avanca para o proximo elemento");
	#endif

	if (pLista == NULL) {
		#ifdef _DEBUG
				CNT_CONTAR("Parametros de entrada incorretos5");                        
		#endif
		return CIR_condRetParmIncorretos;
	}

	/* Tratar lista vazia */

	if (pLista->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Lista vazia3");                        
		#endif
		return CIR_condRetListaVazia;

	} /* fim ativa: Tratar lista vazia */

 /* Tratar avançar para frente */

	if (numElem > 0)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Avanca para frente");                        
		#endif
		pElem = pLista->pElemCorr;
		for (i = numElem; i > 0; i--)
		{
			#ifdef _DEBUG
				CNT_CONTAR("Passa para o proximo elemento");                        
			#endif
			pElem = pElem->pProx;
		} /* for */
		#ifdef _DEBUG
			CNT_CONTAR("Avanco concluido com sucesso1");                        
		#endif
		pLista->pElemCorr = pElem;
		return CIR_condRetOK;

	} /* fim ativa: Tratar avançar para frente */

 /* Tratar avançar para trás */

	else if (numElem < 0)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Avanca para tras");                        
		#endif
		pElem = pLista->pElemCorr;
		for (i = numElem; i < 0; i++)
		{
			#ifdef _DEBUG
				CNT_CONTAR("Passa para o elemento anterior");                        
			#endif
			pElem = pElem->pAnt;
		} /* for */
		#ifdef _DEBUG
			CNT_CONTAR("Avanco concluido com sucesso2");                        
		#endif
		pLista->pElemCorr = pElem;
		return CIR_condRetOK;
	} /* fim ativa: Tratar avançar para trás */

 /* Tratar não avançar */
	#ifdef _DEBUG
		CNT_CONTAR("Avanco concluido com sucesso3");                        
	#endif
	return CIR_condRetOK;

} /* Fim função: CIR  &CIR_AvancarElementoCorrente */

/***************************************************************************
*
*  Função: CIR  &Excluir elemento
*
*  ************************************************************************/

CIR_tpCondRet CIR_ExcluirElemento(CIR_tppLista pLista)
{
	tpElemLista* pElem;
	#ifdef _DEBUG
		CNT_CONTAR("Excluir elemento");                        
	#endif
	if (pLista == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos6");                        
		#endif
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Lista vazia4");                        
		#endif	
		return CIR_condRetListaVazia;
	} /* if */
	#ifdef _DEBUG
		CNT_CONTAR("Correr a lista2");                        
	#endif
	pElem = pLista->pElemCorr;

	if (pElem->pAnt != pElem)
	{
		#ifdef _DEBUG
				CNT_CONTAR("Lista tem mais de um elemento");                        
		#endif
		pElem->pAnt->pProx = pElem->pProx;
		pElem->pProx->pAnt = pElem->pAnt;
		pLista->pElemCorr = pElem->pAnt;
	}
	else {
		#ifdef _DEBUG
			CNT_CONTAR("Lista tem apenas um elemento");                        
		#endif
		pLista->pElemCorr = NULL;
	} /* if */


	#ifdef _DEBUG
		CNT_CONTAR("Elemento excluido com sucesso");                        
	#endif
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

	tpElemLista* pElem, *pIni;
	#ifdef _DEBUG
		CNT_CONTAR("Procurar valor");                        
	#endif
	pIni = pLista->pElemCorr;
	if (pLista == NULL || pValor == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos7");                        
		#endif
		return CIR_condRetParmIncorretos;
	}

	if (pLista->pElemCorr == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Lista vazia5");                        
		#endif
		return CIR_condRetListaVazia;
	} /* if */

	if (pIni->pValor == pValor) {
		#ifdef _DEBUG
			CNT_CONTAR("Valor encontrado com sucesso1");                        
		#endif
		pLista->pElemCorr = pIni;
		return CIR_condRetOK;
	}

	for (pElem = pLista->pElemCorr->pProx;
		pElem != pIni;
		pElem = pElem->pProx)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Correr a lista3");                        
		#endif
		if (pElem->pValor == pValor)
		{
			#ifdef _DEBUG
				CNT_CONTAR("Valor encontrado com sucesso2");                        
			#endif
			pLista->pElemCorr = pElem;
			return CIR_condRetOK;
		} /* if */
	} /* for */
	#ifdef _DEBUG
		CNT_CONTAR("Valor nao encontrado");                        
	#endif
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
	#ifdef _DEBUG
		CNT_CONTAR("Parametros de entrada incorretos8");                        
	#endif
		return ;
	}

	if ((pLista->ExcluirValor != NULL)
		&& (pElem->pValor != NULL))
	{
		#ifdef _DEBUG
			CNT_CONTAR("Valor removido");                        
		#endif
		pLista->ExcluirValor(pElem->pValor);
	} /* if */

	#ifdef _DEBUG
		CNT_CONTAR("Espaco de memoria liberado");                        
	#endif
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

	tpElemLista* pElem;
	#ifdef _DEBUG
		CNT_CONTAR("Criar Elemento");                        
	#endif

	if (pLista == NULL || pValor == NULL) {
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos9");                        
		#endif
		return NULL;
	}
	#ifdef _DEBUG
		CNT_CONTAR("Alocar espaço para elemento");                        
	#endif
	pElem = (tpElemLista*)malloc(sizeof(tpElemLista));
	if (pElem == NULL)
	{
		#ifdef _DEBUG
			CNT_CONTAR("Falta memoria4");                        
		#endif
		return NULL;
	} /* if */

	#ifdef _DEBUG
		CNT_CONTAR("Elemento criado com sucesso");                        
	#endif
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
		#ifdef _DEBUG
			CNT_CONTAR("Parametros de entrada incorretos10");                        
		#endif
		return;
	}
	#ifdef _DEBUG
		CNT_CONTAR("Cabeca da lista limpada com sucesso");                        
	#endif
	pLista->pElemCorr = NULL;
	pLista->numElem = 0;

} /* Fim função: CIR  -LimparCabeca */

/********** Fim do módulo de implementação: CIR  Lista Circular Duplamente Encadeada **********/

