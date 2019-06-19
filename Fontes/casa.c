/***************************************************************************
*  $MCI M�dulo de implementa��o: CAS  casa
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
*  $HA Hist�rico de evolu��o:
*		Vers�o	Autor   Data			Observa��es
*		3		jp		01/05/2019		Redefini��o do tipo enumerado
*		2		jp		28/04/2019		Adi��o de condi��o de retorno nas fun��es de cria��o de casa
*		1		jp		26/04/2019		Primeira implementa��o das fun��es do m�dulo casa
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

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: CAS  &Criar Casa do Tipo Comum
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

}/* Fim fun��o: CAS  &CAS_criaCasaComum */

/***************************************************************************
*
*  Fun��o: CAS  &Criar Casa do Tipo Segura
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

}/* Fim fun��o: CAS  &CAS_criaCasaSegura */

/***************************************************************************
*
*  Fun��o: CAS  &Criar Casa do Tipo Inicial
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

}/* Fim fun��o: CAS  &CAS_criaCasaInicial */

/***************************************************************************
*
*  Fun��o: CAS  &Criar Casa do Tipo Final
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

}/* Fim fun��o: CAS  &CAS_criaCasaFinal */

/***************************************************************************
*
*  Fun��o: CAS  &Criar Casa do Tipo Entrada
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

}/* Fim fun��o: CAS  &CAS_criaEntrada */

/***************************************************************************
*
*  Fun��o: CAS  &Desctruir Casa
*
*  ************************************************************************/

CAS_CondRet CAS_destruirCasa(Casa* casa) {

	if (casa != NULL) {
		free(casa);
	}/* if */

	return CAS_condRetOk;

}/* Fim fun��o: CAS  &CAS_destruirCasa */

/***************************************************************************
*
*  Fun��o: CAS  &Retornar Tipo da Casa
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

}/* Fim fun��o: CAS  &CAS_retornaTipo */

/***************************************************************************
*
*  Fun��o: CAS  &Retornar Cor da Casa
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

}/* Fim fun��o: CAS  &CAS_retornaCor */

/********** Fim do m�dulo de implementa��o: CAS casa **********/