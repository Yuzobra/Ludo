/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB  tabuleiro
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data			Observa��es
*		1		yz		28/04/2019	Primeira vers�o das fun��es exportadas do m�dulo
*
*  $ED Descri��o do m�dulo
*		Implementa um tipo abstrato tabuleiro.
*		Podem existir n tabuleiros por vez.
*		Uma struct Tabuleiro possui:
*			Vetor de casas ocupadas
*			Vetor de ponteiros para casas iniciais
*			Vetor de ponteiros para casas seguras
*			Lista circular
*			Vetor de listas
*
*		Prov�m uma fun��o que libera um tabuleiro, dado que o usu�rio
*			forne�a um ponteiro para uma struct tabuleiro.
*		Se houver tentativa de mo��o de uma pe�a que n�o existe, nenhuma
*			a��o � realizada
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

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um tabuleiro */

typedef struct tabuleiro Tabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do tabuleiro
*
***********************************************************************/

typedef enum {

	TAB_CondRetOk,
	/* Concluiu corretamente */

	TAB_CondRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar um elemento do tabuleiro */

	TAB_CondRetParametrosIncorretos
	/* Elemento do tabuleiro garavado incorretamente  */

} TAB_CondRet;

/***********************************************************************
*
*  $FC Fun��o: TAB  &Cria Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct tabuleiro.
*	  Atribui elementos do tabuleiro � ser criado.
*
*  $EP Par�metros
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
*  $FC Fun��o: TAB  &Destroi Tabuleiro
*
*  $ED Descri��o da fun��o
*     Libera o espa�o de memoria do tipo tabuleiro
*
*  $EP Par�metros
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
*  $FC Fun��o: TAB  &Monta Tabuleiro
*
*  $ED Descri��o da fun��o
*     Posiciona as pe�as no tabuleiro de acordo com o numero de jogadores
*	  Cria o numero de pe�as de acordo com o numero de jogadores
*
*  $EP Par�metros
*     pTab   -	ponteiro para um tabuleiro
*	  numJog -	numero inteiro de 2 � 4
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
*  $FC Fun��o: TAB &Retorna Peca Para Casa Inicial
*
*  $ED Descri��o da fun��o
*     Altera o elemento casa na struct casa ocupada para Casa Inicial
*		da pe�a fornecida pelo usu�rio.
*
*  $EP Par�metros
*     pTab -	ponteiro para um tabuleiro
*	  cor  -	tipo enumerado tipo cor
*	  numP -	numero inteiro da peca, de 1 � 4
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
*  $FC Fun��o: TAB  &Mover Peca
*
*  $ED Descri��o da fun��o
*     Altera o elemento casa na struct casa ocupada da pe�a
*		fornecida pelo usu�rio.
*
*  $EP Par�metros
*     pTab     -	ponteiro para um tabuleiro
*	  numCasas -	numero inteiro de casas para mover a pe�a
*	  cor      -	tipo enumerado tipo cor
*	  numP     -	numero inteiro da pe�a, de 1 � 4
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
*  $FC Fun��o: TAB  &Visualiza Tabuleiro
*
*  $ED Descri��o da fun��o
*     Imprime o tabuleiro.
*
*  $EP Par�metros
*     pTab -	ponteiro para um tabuleiro
*
*  $FV Valor retornado
*	  TAB_CondRetParametrosIncorretos
*
***********************************************************************/

TAB_CondRet TAB_visualizaTabuleiro(Tabuleiro* pTab);

/********** Fim do m�dulo de defini��o: TAB  tabuleiro **********/