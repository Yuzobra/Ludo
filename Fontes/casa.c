/***************************************************************************
*  $MCI Módulo de implementação: CAS  casa
*
*  Arquivo gerado:              casa.c
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
*		Versão	Autor   Data			Observações
*		3		jp		01/05/2019		Redefinição do tipo enumerado
*		2		jp		28/04/2019		Adição de condição de retorno nas funções de criação de casa
*		1		jp		26/04/2019		Primeira implementação das funções do módulo casa
*
*
***************************************************************************/

#include "casa.h"

/***********************************************************************
*
*  $TC Tipo de dados: CAS Elemento da casa
*
*
***********************************************************************/

struct casa {
	CAS_tpTipo tipo;
	COR_tpCor cor;
};

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: CAS  &Criar Casa do Tipo Comum
*
*  ************************************************************************/

CAS_CondRet CAS_criaCasaComum(Casa** casaI) {
	Casa* casa;
	casa = (Casa*)malloc(sizeof(Casa));

	if (casa == NULL) {
		return CAS_condRetFaltouMemoria;
	}/* if */

	casa->tipo = CAS_comum;
	casa->cor = COR_white;
	*casaI = casa;
	return CAS_condRetOk;

}/* Fim função: CAS  &CAS_criaCasaComum */

/***************************************************************************
*
*  Função: CAS  &Criar Casa do Tipo Segura
*
*  ************************************************************************/

CAS_CondRet CAS_criaCasaSegura(Casa** casaI, COR_tpCor cor) {
	Casa* casa;

	if (cor < COR_MIN || cor > COR_MAX) {
		return CAS_condRetParametrosIncorretos;
	}/* if */

	casa = (Casa*)malloc(sizeof(Casa));

	if (casa == NULL) {
		return CAS_condRetFaltouMemoria;
	}/* if */

	casa->tipo = CAS_segura;
	casa->cor = cor;
	*casaI = casa;

	return CAS_condRetOk;

}/* Fim função: CAS  &CAS_criaCasaSegura */

/***************************************************************************
*
*  Função: CAS  &Criar Casa do Tipo Inicial
*
*  ************************************************************************/

CAS_CondRet CAS_criaCasaInicial(Casa** casaI) {
	Casa* casa;
	casa = (Casa*)malloc(sizeof(Casa));

	if (casa == NULL) {
		return CAS_condRetFaltouMemoria;
	}/* if */

	casa->tipo = CAS_inicial;
	casa->cor = COR_white;
	*casaI = casa;

	return CAS_condRetOk;

}/* Fim função: CAS  &CAS_criaCasaInicial */

/***************************************************************************
*
*  Função: CAS  &Criar Casa do Tipo Final
*
*  ************************************************************************/

CAS_CondRet CAS_criaCasaFinal(Casa** casaI, COR_tpCor cor) {

	Casa* casa;

	if (cor < COR_MIN || cor > COR_MAX) {
		return CAS_condRetParametrosIncorretos;
	}/* if */

	casa = (Casa*)malloc(sizeof(Casa));
	if (casa == NULL) {
		return CAS_condRetFaltouMemoria;
	}/* if */

	casa->tipo = CAS_final;
	casa->cor = cor;
	*casaI = casa;

	return CAS_condRetOk;

}/* Fim função: CAS  &CAS_criaCasaFinal */

/***************************************************************************
*
*  Função: CAS  &Criar Casa do Tipo Entrada
*
*  ************************************************************************/

CAS_CondRet CAS_criaEntrada(Casa** casaI, COR_tpCor cor) {
	Casa* casa;

	if (cor < COR_MIN || cor > COR_MAX) {
		return CAS_condRetParametrosIncorretos;
	}/* if */

	casa = (Casa*)malloc(sizeof(Casa));

	if (casa == NULL) {
		return CAS_condRetFaltouMemoria;
	}/* if */

	casa->tipo = CAS_entrada;
	casa->cor = cor;
	*casaI = casa;

	return CAS_condRetOk;

}/* Fim função: CAS  &CAS_criaEntrada */

/***************************************************************************
*
*  Função: CAS  &Desctruir Casa
*
*  ************************************************************************/

CAS_CondRet CAS_destruirCasa(Casa* casa) {

	if (casa != NULL) {
		free(casa);
	}/* if */

	return CAS_condRetOk;

}/* Fim função: CAS  &CAS_destruirCasa */

/***************************************************************************
*
*  Função: CAS  &Retornar Tipo da Casa
*
*  ************************************************************************/

CAS_CondRet CAS_retornaTipo(Casa* casa, CAS_tpTipo* tipo) {
	if (casa != NULL && tipo != NULL) {
		*tipo = casa->tipo;
		return CAS_condRetOk;
	}
	else {
		return CAS_condRetParametrosIncorretos;
	}/* if */

}/* Fim função: CAS  &CAS_retornaTipo */

/***************************************************************************
*
*  Função: CAS  &Retornar Cor da Casa
*
*  ************************************************************************/

CAS_CondRet CAS_retornaCor(Casa* casa, COR_tpCor* cor) {

	if (casa != NULL && cor != NULL) {
		*cor = casa->cor;
		return CAS_condRetOk;
	}
	else {
		return CAS_condRetParametrosIncorretos;
	}/* if */

}/* Fim função: CAS  &CAS_retornaCor */

/********** Fim do módulo de implementação: CAS casa **********/