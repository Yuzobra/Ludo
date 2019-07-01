/***************************************************************************
*
*  $MCD Módulo de definição: PAR  Partida
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
*  $HA Histórico de evolução:
*		Versão	Autor	Data			Observações
*		
*		
*
*
*  $ED Descrição do módulo
*     Controla a execução das rodadas
*
***************************************************************************/

#include "tabuleiro.h"

#define CASAS_ATE_ENTRADA 51

#define _DEBUG

/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções de partida
*
***********************************************************************/

typedef enum {

	PAR_condRetOk,
	/* Concluiu corretamente */

	PAR_condRetFaltouMemoria,
	/* Faltou memória */

} PAR_CondRet;


/***********************************************************************
*
*  $FC Função: CAS  &Criar Casa do tipo Comum
*
*  $ED Descrição da função
*     Controla a execução das rodadas
*
*  $FV Valor retornado
*	  PAR_condRetOk;
*	  PAR_condRetFaltouMemoria;
*
***********************************************************************/

PAR_CondRet PAR_iniciarPartida();


/*****  conjunto de funções que servem somente para exportar funções estáticas do módulo para chamar no módulo teste  *****/

#ifdef _DEBUG

int _DEBUGrodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor);
COR_tpCor _DEBUGchecaVitoria(int* casasAndadas);
int _DEBUGpodeMover(int* casasAndadas, COR_tpCor cor, int valorDado);
COR_tpCor _DEBUGComerPeca(int* casasAndadas, COR_tpCor cor, int numPeca);
COR_tpCor _DEBUGpossuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca);

#endif

/********** Fim do módulo de definição: PAR partida **********/