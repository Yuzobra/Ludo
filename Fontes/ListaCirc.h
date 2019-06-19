#if ! defined( LISTACIRC_ )
#define LISTACIRC_
/***************************************************************************
*
*  $MCD Módulo de definição: CIR  Lista circular duplamente encadeada
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
*  $HA Histórico de evolução:
*		Versão  Autor   Data		Observações
*		1		yz		28/04/2019	Implementação da interface provida
*
*  $ED Descrição do módulo
*     Implementa listas genéricas circulares duplamente encadeadas.
*     Podem existir n listas circulares em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( LISTA_OWN )
#define LISTA_EXT
#else
#define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct CIR_tagLista * CIR_tppLista;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

typedef enum {

	CIR_condRetOK,
	/* Concluiu corretamente */

	CIR_condRetListaVazia,
	/* A lista não contém elementos */

	CIR_condRetNaoAchou,
	/* Não encontrou o valor procurado */

	CIR_condRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento de lista */

	CIR_condRetParmIncorretos
	/* Parametros de entrada incorretos */

} CIR_tpCondRet;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista circular
*
*  $ED Descrição da função
*     Cria uma lista circular genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

CIR_tppLista CIR_CriarLista(
	void(*ExcluirValor) (void * pDado));


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista circular
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*		estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*	  pLista -	 ponteiro para a lista
*
***********************************************************************/

void CIR_DestruirLista(CIR_tppLista pLista);


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista circular
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

void CIR_EsvaziarLista(CIR_tppLista pLista);


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
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
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento após o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
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
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void * CIR_ObterValor(CIR_tppLista pLista);



/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança no sentido do proximo elemento
*     Se numElem for negativo avança no sentido do elemento anterior
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CIR_condRetOK			- se numElem elementos tiverem sido andados
*     CIR_condRetListaVazia - se a lista está vazia
*
***********************************************************************/

CIR_tpCondRet CIR_AvancarElementoCorrente(CIR_tppLista pLista,
	int numElem);


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Não sendo este o ùnico elemento da lista, o elemento anterior se
*		torna o novo elemento corrente da lista.
*		Caso contrario o elemento corrente se torna NULL.
*
*  $EP Parâmetros
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
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     CIR_condRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     CIR_condRetNaoAchou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     CIR_condRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

CIR_tpCondRet CIR_ProcurarValor(CIR_tppLista pLista,
	void * pValor);

#undef LISTA_EXT

/********** Fim do módulo de definição: CIR  Lista Circular Duplamente Encadeada **********/


#else
#endif