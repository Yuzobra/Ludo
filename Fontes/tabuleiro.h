/***************************************************************************
*
*  $MCD Módulo de definição: TAB  tabuleiro
*
*  Arquivo gerado:              tabuleiro.h
*  Letras identificadoras:      TAB
*
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data			Observações
*		1		yz		28/04/2019	Primeira versão das funções exportadas do módulo
*
*  $ED Descrição do módulo
*		Implementa um tipo abstrato tabuleiro.
*		Podem existir n tabuleiros por vez.
*		Uma struct Tabuleiro possui:
*			Vetor de casas ocupadas
*			Vetor de ponteiros para casas iniciais
*			Vetor de ponteiros para casas seguras
*			Lista circular
*			Vetor de listas
*
*		Provém uma função que libera um tabuleiro, dado que o usuário
*			forneça um ponteiro para uma struct tabuleiro.
*		Se houver tentativa de moção de uma peça que não existe, nenhuma
*			ação é realizada
*
***************************************************************************/
#pragma once
#define TAB_INTERVALOCASASIGUAIS 13
#define NUMJOG_MIN 2
#define NUMJOG_MAX 4
#include "peca.h"
#include "casa.h"
#include "LISTA.H"
#include "ListaCirc.h"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um tabuleiro */

typedef struct tabuleiro Tabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOk,
	/* Concluiu corretamente */

	TAB_CondRetFaltouMemoria,
	/* Faltou memória ao tentar criar um elemento do tabuleiro */

	TAB_CondRetParametrosIncorretos
	/* Elemento do tabuleiro garavado incorretamente  */

} TAB_CondRet;

/***********************************************************************
*
*  $FC Função: TAB  &Cria Tabuleiro
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct tabuleiro.
*	  Atribui elementos do tabuleiro à ser criado.
*
*  $EP Parâmetros
*     pTab -		ponteiro para um ponteiro para o tabuleiro
*
*  $FV Valor retornado
*	  TAB_CondRetOk
*     TAB_CondRetFaltouMemoria
*     TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_criaTabuleiro(Tabuleiro** pTab);



/***********************************************************************
*
*  $FC Função: TAB  &Destroi Tabuleiro
*
*  $ED Descrição da função
*     Libera o espaço de memoria do tipo tabuleiro
*
*  $EP Parâmetros
*     pTab -	ponteiro para um tabuleiro
*
*  $FV Valor retornado
*	  TAB_CondRetOk
*	  TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_destroiTabuleiro(Tabuleiro* pTab);



/***********************************************************************
*
*  $FC Função: TAB  &Monta Tabuleiro
*
*  $ED Descrição da função
*     Posiciona as peças no tabuleiro de acordo com o numero de jogadores
*	  Cria o numero de peças de acordo com o numero de jogadores
*
*  $EP Parâmetros
*     pTab   -	ponteiro para um tabuleiro
*	  numJog -	numero inteiro de 2 à 4
*	  vetCor -	vetor contendo as cores dos jogadores
*
*  $FV Valor retornado
*	  TAB_CondRetOk
*     TAB_CondRetFaltouMemoria
*	  TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_montaTabuleiro(Tabuleiro* pTab,
	int numJog,
	int* vetCor);


/***********************************************************************
*
*  $FC Função: TAB &Retorna Peca Para Casa Inicial
*
*  $ED Descrição da função
*     Altera o elemento casa na struct casa ocupada para Casa Inicial
*		da peça fornecida pelo usuário.
*
*  $EP Parâmetros
*     pTab -	ponteiro para um tabuleiro
*	  cor  -	tipo enumerado tipo cor
*	  numP -	numero inteiro da peca, de 1 à 4
*
*  $FV Valor retornado
*	  TAB_CondRetOk
*	  TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_retornaPecaParaCasaInicial(Tabuleiro* pTab,
	COR_tpCor cor,
	int numP);



/***********************************************************************
*
*  $FC Função: TAB  &Mover Peca
*
*  $ED Descrição da função
*     Altera o elemento casa na struct casa ocupada da peça
*		fornecida pelo usuário.
*
*  $EP Parâmetros
*     pTab     -	ponteiro para um tabuleiro
*	  numCasas -	numero inteiro de casas para mover a peça
*	  cor      -	tipo enumerado tipo cor
*	  numP     -	numero inteiro da peça, de 1 à 4
*
*  $FV Valor retornado
*	  TAB_CondRetOk
*	  TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_moverPeca(Tabuleiro* pTab,
	int numCasas,
	COR_tpCor cor,
	int numP);


/***********************************************************************
*
*  $FC Função: TAB  &Visualiza Tabuleiro
*
*  $ED Descrição da função
*     Imprime o tabuleiro.
*
*  $EP Parâmetros
*     pTab -	ponteiro para um tabuleiro
*
*  $FV Valor retornado
*	  TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_visualizaTabuleiro(Tabuleiro* pTab);

/********** Fim do módulo de definição: TAB  tabuleiro **********/