/***************************************************************************
*
*  $MCD M�dulo de defini��o: CAS  Casa
*
*  Arquivo gerado:              casa.h
*  Letras identificadoras:      CAS
*
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Hist�rico de evolu��o:
*		Vers�o	Autor	Data			Observa��es
*		2		jp		01/05/2019		Redefini��o do tipo enumerado
*		1		jp		26/04/2019		Primeira implementa��o das fun��es do m�dulo casa
*
*
*  $ED Descri��o do m�dulo
*     Cria um tipo abstrato casa.
*	  Uma casa possui um tipo enumerado Tipo, e um tipo enumerado Cor.
*	  Podem existir n casas simultaneamente.
*
*	  Prov�m uma fun��o que libera uma casa, dado que usu�rio
*		forne�a um ponteiro para um ponteiro para uma struct casa.
*	  O Tipo da casa � determinada pelo usu�rio, uma vez criado,
*		seu Tipo n�o poder� ser trocado.
*
***************************************************************************/

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

#include <stdio.h>
#include <stdlib.h>

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct casa Casa;

typedef enum {
	CAS_comum,
	CAS_inicial,
	CAS_segura,
	CAS_final,
	CAS_entrada
} CAS_tpTipo;

/***********************************************************************
*
*  $TC Tipo de dados: CAS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da casa
*
***********************************************************************/

typedef enum {

	CAS_condRetOk,
	/* Concluiu corretamente */

	CAS_condRetFaltouMemoria,
	/* Faltou mem�ria ao tentar criar uma casa */

	CAS_condRetParametrosIncorretos
	/* Elemento da casa garavado incorretamente  */

} CAS_CondRet;

/***********************************************************************
*
*  $FC Fun��o: CAS  &Criar Casa do tipo Comum
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa � ser criada.
*
*  $EP Par�metros
*     casa -		ponteiro para um ponteiro para uma casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*     CAS_condRetFaltouMemoria
*
***********************************************************************/

CAS_CondRet CAS_criaCasaComum(Casa** casa);


/***********************************************************************
*
*  $FC Fun��o: CAS  &Criar Casa do tipo Segura
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa � ser criada.
*
*  $EP Par�metros
*     casa -		ponteiro para um ponteiro para uma casa
*	  cor  -		uma constante enumerada especificando a
*						cor da casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*     CAS_condRetFaltouMemoria
*	  CAS_condRetParametrosIncorretos
*
***********************************************************************/

CAS_CondRet CAS_criaCasaSegura(Casa** casa,
	COR_tpCor cor);


/***********************************************************************
*
*  $FC Fun��o: CAS  &Criar Casa do tipo Inicial
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa � ser criada.
*
*  $EP Par�metros
*     casa -		ponteiro para um ponteiro para uma casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*     CAS_condRetFaltouMemoria
*
***********************************************************************/

CAS_CondRet CAS_criaCasaInicial(Casa** casa);



/***********************************************************************
*
*  $FC Fun��o: CAS  &Criar Casa do tipo Final
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa � ser criada.
*
*  $EP Par�metros
*     casa -		ponteiro para um ponteiro para uma casa
*	  cor  -		uma constante enumerada especificando a
*						cor da casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*     CAS_condRetFaltouMemoria
*	  CAS_condRetParametrosIncorretos
*
***********************************************************************/

CAS_CondRet CAS_criaCasaFinal(Casa** casa,
	COR_tpCor cor);

/***********************************************************************
*
*  $FC Fun��o: CAS  &Destruir Casa
*
*  $ED Descri��o da fun��o
*     Libera o espaco de memoria do tipo casa
*
*  $EP Par�metros
*     casa -		ponteiro para uma casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*     CAS_condRetFaltouMemoria
*	  CAS_condRetParametrosIncorretos
*
***********************************************************************/

CAS_CondRet CAS_destruirCasa(Casa* casa);



/***********************************************************************
*
*  $FC Fun��o: CAS  &Criar Casa do tipo Entrada
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa � ser criada.
*
*  $EP Par�metros
*     casa -		ponteiro para um ponteiro para uma casa
*	  cor  -		uma constante enumerada especificando a
*						cor da casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*     CAS_condRetFaltouMemoria
*
***********************************************************************/

CAS_CondRet CAS_criaEntrada(Casa** casa,
	COR_tpCor cor);


/***********************************************************************
*
*  $FC Fun��o: CAS  &Retornar Tipo da Casa
*
*  $ED Descri��o da fun��o
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa � ser criada.
*
*  $EP Par�metros
*     casa -		ponteiro para uma casa
*	  tipo -		ponteiro para uma constante enumerada especificando o
*					tipo da casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*	  CAS_condRetParametrosIncorretos
*
***********************************************************************/

CAS_CondRet CAS_retornaTipo(Casa* casa,
	CAS_tpTipo* tipo);


/***********************************************************************
*
*  $FC Fun��o: CAS  &Retornar Tipo da Casa
*
*  $ED Descri��o da fun��o
*     Retorna o tipo da casa � partir do ponteiro para uma casa
*		passado pelo usu�rio
*
*  $EP Par�metros
*     casa -		ponteiro para uma casa
*	  cor  -		ponteiro para uma constante enumerada
*					especificando a cor da casa
*
*  $FV Valor retornado
*	  CAS_condRetOk
*	  CAS_condRetParametrosIncorretos
*
***********************************************************************/

CAS_CondRet CAS_retornaCor(Casa* casa,
	COR_tpCor* cor);

/********** Fim do m�dulo de defini��o: CAS  casa **********/