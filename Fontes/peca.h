/***************************************************************************
*
*  $MCD Módulo de definição: PEC  peca
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
*  $HA Histórico de evolução:
*		Versão  Autor		Data		Observações
*		1		vh			25/04/2019	Definido o protótipo das funções e tipo enumerado
*
*  $ED Descrição do módulo
*     Cria um tipo abstrato peça.
*	  Uma peça possui um tipo enumerado Cor, e um inteiro Numero.
*	  Podem existir n peças simultaneamente.
*
*	  O modulo provém uma função que libera uma peça, dado que o usuário
*		forneça um ponteiro para uma struct peça.
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

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct peca Peca;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da peça
*
***********************************************************************/

typedef enum {

	PEC_condRetOk,
	/* Concluiu corretamente */

	PEC_condRetFaltouMemoria,
	/* Faltou memória ao tentar criar uma peça */

	PEC_condRetParametrosIncorretos
	/* Elemento da peça garavado incorretamente  */

}PEC_CondRet;

/***********************************************************************
*
*  $FC Função: PEC  &Criar Peça
*
*  $ED Descrição da função
*     Cria um espaco na memoria para uma struct peça.
*	  Atribui elementos da peça à ser criada.
*	  A constante Peça possue um numero de 1 à 4
*
*  $EP Parâmetros
*     peça -		ponteiro para um ponteiro para uma peça
*	  cor  -		uma constante enumerada especificando a
*						cor da peça
*	  numP -		uma constante de valor inteiro que especifica o
*						numero da peça
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
*  $FC Função: PEC  &Destruir Peça
*
*  $ED Descrição da função
*     Libera o espaco de memoria do tipo peça
*
*  $EP Parâmetros
*     peça -		ponteiro para um ponteiro para uma peça
*
*  $FV Valor retornado
*	  PEC_condRetOk
*	  PEC_condRetParametrosIncorretos
*
***********************************************************************/

PEC_CondRet PEC_destruirPeca(Peca* peca);


/***********************************************************************
*
*  $FC Função: PEC  &Retorna Numero da Peça
*
*  $ED Descrição da função
*     Acessa a struct e retorna o numero da peça
*
*  $EP Parâmetros
*     peça -		ponteiro para um ponteiro para uma peça
*	  num  -		ponteiro para uma constante de valor
						inteiro que especifica o numero da peça
*
*  $FV Valor retornado
*	  PEC_condRetOk
*
***********************************************************************/

PEC_CondRet PEC_retornaNum(Peca* peca,
	int* num);


/***********************************************************************
*
*  $FC Função: PEC  &Retorna Cor da Peça
*
*  $ED Descrição da função
*     Acessa a struct e retorna a cor da peça
*
*  $EP Parâmetros
*     peça -		ponteiro para um ponteiro para uma peça
*	  cor  -		ponteiro para uma constante enumerada
*					especificando a cor da peça
*
*  $FV Valor retornado
*	  PEC_condRetOk
*	  PEC_condRetParametrosIncorretos
*
***********************************************************************/

PEC_CondRet PEC_retornaCor(Peca* peca,
	COR_tpCor* cor);

/********** Fim do módulo de definição: PEC  peça **********/