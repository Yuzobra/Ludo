/***************************************************************************
*
*  $MCD M�dulo de defini��o: PEC  peca
*
*  Arquivo gerado:              peca.h
*  Letras identificadoras:      PEC
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Hist�rico de evolu��o:
*		Vers�o  Autor		Data		Observa��es
*		1		vh			25/04/2019	Definido o prot�tipo das fun��es e tipo enumerado
*
*  $ED Descri��o do m�dulo
*     Cria um tipo abstrato pe�a.
*	  Uma pe�a possui um tipo enumerado Cor, e um inteiro Numero.
*	  Podem existir n pe�as simultaneamente.
*
*	  O modulo prov�m uma fun��o que libera uma pe�a, dado que o usu�rio
*		forne�a um ponteiro para uma struct pe�a.
*
***************************************************************************/
#define PEC_MIN 1
#define PEC_MAX 4
#if!defined _COR
#define _COR
#define COR_MIN 0
#define COR_MAX 4
typedef enum {
	COR_red,
	COR_blue,
	COR_green,
	COR_yellow,
	COR_white
} COR_tpCor;

#endif


#pragma once
#include <stdlib.h>
#include <stdio.h>

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pe�a */

typedef struct peca Peca;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da pe�a
*
***********************************************************************/

typedef enum {

	PEC_condRetOk,
	/* Concluiu corretamente */

	PEC_condRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar uma pe�a */

	PEC_condRetParametrosIncorretos
	/* Elemento da pe�a garavado incorretamente  */

}PEC_CondRet;

/***********************************************************************
*
*  $FC Fun��o: PEC  &Criar Pe�a
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct pe�a.
*	  Atribui elementos da pe�a � ser criada.
*	  A constante Pe�a possue um numero de 1 � 4
*
*  $EP Par�metros
*     pe�a -		ponteiro para um ponteiro para uma pe�a
*	  cor  -		uma constante enumerada especificando a
*						cor da pe�a
*	  numP -		uma constante de valor inteiro que especifica o
*						numero da pe�a
*
*  $FV Valor retornado
*	  PEC_condRetOk
*     PEC_condRetFaltouMemoria
*     PEC_condRetParametrosIncorretos
*
***********************************************************************/

PEC_CondRet PEC_criaPeca(Peca ** peca,
	COR_tpCor cor,
	int numP);


/***********************************************************************
*
*  $FC Fun��o: PEC  &Destruir Pe�a
*
*  $ED Descri��o da fun��o
*     Libera o espaco de memoria do tipo pe�a
*
*  $EP Par�metros
*     pe�a -		ponteiro para um ponteiro para uma pe�a
*
*  $FV Valor retornado
*	  PEC_condRetOk
*	  PEC_condRetParametrosIncorretos
*
***********************************************************************/

PEC_CondRet PEC_destruirPeca(Peca* peca);


/***********************************************************************
*
*  $FC Fun��o: PEC  &Retorna Numero da Pe�a
*
*  $ED Descri��o da fun��o
*     Acessa a struct e retorna o numero da pe�a
*
*  $EP Par�metros
*     pe�a -		ponteiro para um ponteiro para uma pe�a
*	  num  -		ponteiro para uma constante de valor
						inteiro que especifica o numero da pe�a
*
*  $FV Valor retornado
*	  PEC_condRetOk
*
***********************************************************************/

PEC_CondRet PEC_retornaNum(Peca* peca,
	int* num);


/***********************************************************************
*
*  $FC Fun��o: PEC  &Retorna Cor da Pe�a
*
*  $ED Descri��o da fun��o
*     Acessa a struct e retorna a cor da pe�a
*
*  $EP Par�metros
*     pe�a -		ponteiro para um ponteiro para uma pe�a
*	  cor  -		ponteiro para uma constante enumerada
*					especificando a cor da pe�a
*
*  $FV Valor retornado
*	  PEC_condRetOk
*	  PEC_condRetParametrosIncorretos
*
***********************************************************************/

PEC_CondRet PEC_retornaCor(Peca* peca,
	COR_tpCor* cor);

/********** Fim do m�dulo de defini��o: PEC  pe�a **********/