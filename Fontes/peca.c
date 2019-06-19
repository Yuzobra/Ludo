/***************************************************************************
*  $MCI M�dulo de implementa��o: PEC  Pe�a
*
*  Arquivo gerado:              peca.c
*  Letras identificadoras:      PEC
*
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Hist�rico de evolu��o:
*		Vers�o  Autor	Data		Observa��es
*		3		vh		12/05/2019	Corre��o no tipo de retorno em retornaCor e retornaNum
*		2		vh		28/04/2019	Adi��o de teste de entradas e adi��o de condi��o de retorno
*		1		vh		27/04/2019	Implementa��o das fun��es
*
***************************************************************************/

#include "peca.h"

/***********************************************************************
*
*  $TC Tipo de dados: PEC Elemento da casa
*
*
***********************************************************************/

struct peca {
	int cor;
	int numP;
};

/***************************************************************************
*
*  Fun��o: PEC  &Criar Peca
*
*  ************************************************************************/

PEC_CondRet PEC_criaPeca(Peca **pecaI, COR_tpCor cor, int numP) {
	Peca* peca;

	if (numP > PEC_MAX || numP < PEC_MIN || cor < COR_MIN || cor > COR_MAX)
	{
		return PEC_condRetParametrosIncorretos;
	}/* if */

	peca = (Peca*)malloc(sizeof(Peca));

	if (peca == NULL)
	{
		return PEC_condRetFaltouMemoria;
	}/* if */

	peca->cor = cor;
	peca->numP = numP;
	*pecaI = peca;

	return PEC_condRetOk;

}/* Fim fun��o: PEC  &PEC_criaPeca */

/***************************************************************************
*
*  Fun��o: PEC  &Destruir Peca
*
*  ************************************************************************/

PEC_CondRet PEC_destruirPeca(Peca* peca) {

	if (peca != NULL)
	{
		free(peca);
	}/* if */

	return PEC_condRetOk;

}/* Fim fun��o: PEC  &PEC_destruirPeca */

/***************************************************************************
*
*  Fun��o: PEC  &Retornar Numero da Peca
*
*  ************************************************************************/

PEC_CondRet PEC_retornaNum(Peca* peca, int *num) {

	if (peca != NULL && num != NULL)
	{
		*num = peca->numP;
		return PEC_condRetOk;
	}/* if */

	return PEC_condRetParametrosIncorretos;

}/* Fim fun��o: PEC  &PEC_retornaNum */

/***************************************************************************
*
*  Fun��o: PEC  &Retornar Cor da Peca
*
*  ************************************************************************/

PEC_CondRet PEC_retornaCor(Peca* peca, COR_tpCor*cor) {

	if (peca != NULL && cor != NULL)
	{
		*cor = peca->cor;
		return PEC_condRetOk;
	}/* if */

	return PEC_condRetParametrosIncorretos;

}/* Fim fun��o: PEC  &PEC_retornaCor */

/********** Fim do m�dulo de implementa��o: PEC peca **********/