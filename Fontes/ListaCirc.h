#if ! defined( LISTACIRC_ )
#define LISTACIRC_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: CIR  Lista circular duplamente encadeada
*
*  Arquivo gerado:              ListaCirc.h
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
*		1		yz		28/04/2019	Implementa��o da interface provida
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas circulares duplamente encadeadas.
*     Podem existir n listas circulares em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( LISTA_OWN )
#define LISTA_EXT
#else
#define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct CIR_tagLista * CIR_tppLista;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

typedef enum {

	CIR_condRetOK,
	/* Concluiu corretamente */

	CIR_condRetListaVazia,
	/* A lista n�o cont�m elementos */

	CIR_condRetNaoAchou,
	/* N�o encontrou o valor procurado */

	CIR_condRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento de lista */

	CIR_condRetParmIncorretos
	/* Parametros de entrada incorretos */

} CIR_tpCondRet;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista circular
*
*  $ED Descri��o da fun��o
*     Cria uma lista circular gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
***********************************************************************/

CIR_tppLista CIR_CriarLista(
	void(*ExcluirValor) (void * pDado));


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista circular
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*		estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*	  pLista -	 ponteiro para a lista
*
***********************************************************************/

void CIR_DestruirLista(CIR_tppLista pLista);


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista circular
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

void CIR_EsvaziarLista(CIR_tppLista pLista);


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     CIR_condRetOK
*     CIR_condRetFaltouMemoria
*
***********************************************************************/

CIR_tpCondRet CIR_InserirElementoAntes(CIR_tppLista pLista,
	void * pValor);


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*
*
*  $FV Valor retornado
*        CIR_condRetOK
*        CIR_condRetFaltouMemoria
*
***********************************************************************/

CIR_tpCondRet CIR_InserirElementoApos(CIR_tppLista pLista,
	void * pValor);

/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void * CIR_ObterValor(CIR_tppLista pLista);



/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a no sentido do proximo elemento
*     Se numElem for negativo avan�a no sentido do elemento anterior
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     CIR_condRetOK			- se numElem elementos tiverem sido andados
*     CIR_condRetListaVazia - se a lista est� vazia
*
***********************************************************************/

CIR_tpCondRet CIR_AvancarElementoCorrente(CIR_tppLista pLista,
	int numElem);


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     N�o sendo este o �nico elemento da lista, o elemento anterior se
*		torna o novo elemento corrente da lista.
*		Caso contrario o elemento corrente se torna NULL.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     CIR_condRetOK
*     CIR_condRetListaVazia
*
***********************************************************************/

CIR_tpCondRet CIR_ExcluirElemento(CIR_tppLista pLista);


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     CIR_condRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     CIR_condRetNaoAchou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     CIR_condRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

CIR_tpCondRet CIR_ProcurarValor(CIR_tppLista pLista,
	void * pValor);

#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: CIR  Lista Circular Duplamente Encadeada **********/


#else
#endif