/***************************************************************************
*
*  $MCD M�dulo de defini��o: PAR  Partida
*
*  Arquivo gerado:              partida.h
*  Letras identificadoras:      PAR
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
*		
*		
*
*
*  $ED Descri��o do m�dulo
*     Controla a execu��o das rodadas
*
***************************************************************************/

#include "tabuleiro.h"

#define CASAS_ATE_ENTRADA 51

#define _DEBUG

/***** Declara��es exportadas pelo m�dulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es de partida
*
***********************************************************************/

typedef enum {

	PAR_condRetOk,
	/* Concluiu corretamente */

	PAR_condRetFaltouMemoria,
	/* Faltou mem�ria */

} PAR_CondRet;


/***********************************************************************
*
*  $FC Fun��o: CAS  &Criar Casa do tipo Comum
*
*  $ED Descri��o da fun��o
*     Controla a execu��o das rodadas
*
*  $FV Valor retornado
*	  PAR_condRetOk;
*	  PAR_condRetFaltouMemoria;
*
***********************************************************************/

PAR_CondRet PAR_iniciarPartida();


/*****  conjunto de fun��es que servem somente para exportar fun��es est�ticas do m�dulo para chamar no m�dulo teste  *****/

#ifdef _DEBUG

int _DEBUGrodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor);
COR_tpCor _DEBUGchecaVitoria(int* casasAndadas);
int _DEBUGpodeMover(int* casasAndadas, COR_tpCor cor, int valorDado);
COR_tpCor _DEBUGComerPeca(int* casasAndadas, COR_tpCor cor, int numPeca);
COR_tpCor _DEBUGpossuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca);

#endif

/********** Fim do m�dulo de defini��o: PAR partida **********/