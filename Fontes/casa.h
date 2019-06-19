/***************************************************************************
*
*  $MCD Módulo de definição: CAS  Casa
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
*  $HA Histórico de evolução:
*		Versão	Autor	Data			Observações
*		2		jp		01/05/2019		Redefinição do tipo enumerado
*		1		jp		26/04/2019		Primeira implementação das funções do módulo casa
*
*
*  $ED Descrição do módulo
*     Cria um tipo abstrato casa.
*	  Uma casa possui um tipo enumerado Tipo, e um tipo enumerado Cor.
*	  Podem existir n casas simultaneamente.
*
*	  Provém uma função que libera uma casa, dado que usuário
*		forneça um ponteiro para um ponteiro para uma struct casa.
*	  O Tipo da casa é determinada pelo usuário, uma vez criado,
*		seu Tipo não poderá ser trocado.
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

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

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
*  $TC Tipo de dados: CAS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da casa
*
***********************************************************************/

typedef enum {

	CAS_condRetOk,
	/* Concluiu corretamente */

	CAS_condRetFaltouMemoria,
	/* Faltou memória ao tentar criar uma casa */

	CAS_condRetParametrosIncorretos
	/* Elemento da casa garavado incorretamente  */

} CAS_CondRet;

/***********************************************************************
*
*  $FC Função: CAS  &Criar Casa do tipo Comum
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa à ser criada.
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Criar Casa do tipo Segura
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa à ser criada.
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Criar Casa do tipo Inicial
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa à ser criada.
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Criar Casa do tipo Final
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa à ser criada.
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Destruir Casa
*
*  $ED Descrição da função
*     Libera o espaco de memoria do tipo casa
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Criar Casa do tipo Entrada
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa à ser criada.
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Retornar Tipo da Casa
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct casa.
*	  Atribui elementos da casa à ser criada.
*
*  $EP Parâmetros
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
*  $FC Função: CAS  &Retornar Tipo da Casa
*
*  $ED Descrição da função
*     Retorna o tipo da casa à partir do ponteiro para uma casa
*		passado pelo usuário
*
*  $EP Parâmetros
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

/********** Fim do módulo de definição: CAS  casa **********/