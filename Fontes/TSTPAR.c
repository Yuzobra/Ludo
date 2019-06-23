/***************************************************************************
*  $MCI M�dulo de implementa��o: TSTPAR Teste Partida
*
*  Arquivo gerado:              TSTPAR .c
*  Letras identificadoras:      TSTPAR
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		Vers�o  Autor   Data		Observa��es
*				yz		//2019	 Implementa��o do m�dulo de testes
*
***************************************************************************/


#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "partida.h"

//DEVEM SER SUBSTITUIDOS POR INICIAR PARTIDA E TERMINAR PARTIDA?

static const char RESET_VETORES_CMD[] = "=resetteste";
static const char INICIALIZAR_VETOR_CMD[] = "=inicializarvetorcasasandadas";
static const char PREENCHER_VETOR_CMD[] = "=preenchervetorcasasandadas";
static const char CHECA_VITORIA_CMD[] = "=checavitoria";
static const char PODE_MOVER_CMD[] = "=podemover";
static const char COMER_PECA_CMD[] = "=comerpeca";
static const char POSSUI_TORRE_NA_CASA_SEGUINTE_CMD[] = "=possuitorrenacasaseguinte";
//static const char DESTROI_TABULEIRO_CMD[] = "=destroitabuleiro";




#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define QUANT_VT_CASAS_ANDADAS   25
#define DIM_VT_CASAS_ANDADAS     16

int * vtCasasAndadas[QUANT_VT_CASAS_ANDADAS];

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

int ValidarIndexCasasAndadas(int indexCasasAndadas, int Modo);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TSTPAR &Testar Partida
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 25 vetores de casas andadas, identificadas pelos �ndices 0 a 24.
*	  Estes vetores tem 16 espa�os para inteiros,identificadas pelos �ndices 0 a 15. Sendo do 0 ao 3 as casas
*	  andadas pelas pe�as vermelhas, do 4 ao 7 das pe�as azuis, do 8 ao 11 das pe�as verdes e do 12 ao 15 das pe�as
*	  amarelas.
*
*     Comandos dispon�veis:
*	  =resetteste
*	  =inicializarvetorcasasandadas
*	  =preenchervetorcasasandadas
*	  =checavitoria
*	  =podemover
*	  =comerpeca
*	  =possuitorrenacasaseguinte
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando(char* ComandoTeste)
{

	int indexCasasAndadas = -1,
		numLidos = -1,
		CondRetEsp = -1,
		numPeca = -1,
		valorDado = -1,
		Aux[16];
	TST_tpCondRet CondRet;

	PAR_CondRet ParCondRet;


	COR_tpCor	cor,
		cores[4];

	char* pDado;

	int ValEsp = -1;

	int i;

	int numElem = -1;


	/* Efetuar reset de teste de partida */

	if (strcmp(ComandoTeste, RESET_VETORES_CMD) == 0)
	{

		for (i = 0; i < QUANT_VT_CASAS_ANDADAS; i++)
		{
			vtCasasAndadas[i] = NULL;
		} /* for */

		return TST_CondRetOK;

	} /* fim ativa: Efetuar reset de teste de partida */


	/* Inicializar vetor*/

	else if (strcmp(ComandoTeste, INICIALIZAR_VETOR_CMD) == 0)
	{
		numLidos = LER_LerParametros("i",
			&indexCasasAndadas);

		if ((numLidos != 1)
			|| (indexCasasAndadas < 0)
			|| (indexCasasAndadas >= QUANT_VT_CASAS_ANDADAS))
		{
			return TST_CondRetParm;
		} /* if */

		vtCasasAndadas[indexCasasAndadas] = (int*)malloc(sizeof(int) * DIM_VT_CASAS_ANDADAS);

		return TST_CompararPonteiroNulo(1, vtCasasAndadas[indexCasasAndadas],
			"Erro em ponteiro de nova casa Andada.");

	} /* fim ativa: Inicializar vetor */






	/* Preencher vetor */

	else if (strcmp(ComandoTeste, PREENCHER_VETOR_CMD) == 0)
	{
		numLidos = LER_LerParametros("iiiiiiiiiiiiiiiii",
			&indexCasasAndadas,
			&Aux[0],
			&Aux[1],
			&Aux[2],
			&Aux[3],
			&Aux[4],
			&Aux[5],
			&Aux[6],
			&Aux[7],
			&Aux[8],
			&Aux[9],
			&Aux[10],
			&Aux[11],
			&Aux[12],
			&Aux[13],
			&Aux[14],
			&Aux[15]
			);

		for (i = 0; i < DIM_VT_CASAS_ANDADAS; i++) {
			vtCasasAndadas[indexCasasAndadas][i] = Aux[i];
		}

		if ((numLidos != 17)
			|| (!ValidarIndexCasasAndadas(indexCasasAndadas, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */

		
		return TST_CompararEspaco(Aux,vtCasasAndadas[indexCasasAndadas],sizeof(int)*DIM_VT_CASAS_ANDADAS,
			"Erro em preencher vetor de casas andadas");

	} /* fim ativa: Preencher vetor */
	  
	 
	/* Testar ChecaVitoria*/

	else if (strcmp(ComandoTeste, CHECA_VITORIA_CMD) == 0)
	{
		numLidos = LER_LerParametros("ii",
			&indexCasasAndadas,&CondRetEsp);

		if ((numLidos != 2)
			|| (!ValidarIndexCasasAndadas(indexCasasAndadas, NAO_VAZIO)))
		{
			return TST_CondRetParm;
		} /* if */



		cor = _DEBUGchecaVitoria(vtCasasAndadas[indexCasasAndadas]);


		return TST_CompararInt(CondRetEsp, cor,
			"Erro em checa vitoria.");

	} /* fim ativa: Testar checaVitoria */


	/* Testar PodeMover*/

	else if (strcmp(ComandoTeste, PODE_MOVER_CMD) == 0)
	{
	numLidos = LER_LerParametros("iiii",
		&indexCasasAndadas,&cor,&valorDado,&CondRetEsp);

	if ((numLidos != 4)
		|| (!ValidarIndexCasasAndadas(indexCasasAndadas, NAO_VAZIO)))
	{
		return TST_CondRetParm;
	} /* if */



	ParCondRet = _DEBUGpodeMover(vtCasasAndadas[indexCasasAndadas],cor,valorDado);


	return TST_CompararInt(CondRetEsp, ParCondRet,
		"Erro em teste de pode mover.");

	} /* fim ativa: Testar PodeMover */
	


	/* Testar comer pe�a*/

	else if (strcmp(ComandoTeste, COMER_PECA_CMD) == 0)
	{
	numLidos = LER_LerParametros("iiii",
		&indexCasasAndadas, &cor, &numPeca, &CondRetEsp);

	if ((numLidos != 4)
		|| (!ValidarIndexCasasAndadas(indexCasasAndadas, NAO_VAZIO)))
	{
		return TST_CondRetParm;
	} /* if */


	cor = _DEBUGComerPeca(vtCasasAndadas[indexCasasAndadas], cor, numPeca-1);


	return TST_CompararInt(CondRetEsp, cor,
		"Erro em teste de comer peca.");

	} /* fim ativa: Testar comer pe�a*/

	/* Testar PossuiTorreNaCasaSeguinte*/

	else if (strcmp(ComandoTeste, POSSUI_TORRE_NA_CASA_SEGUINTE_CMD) == 0)
	{
	numLidos = LER_LerParametros("iiii",
		&indexCasasAndadas, &cor, &numPeca, &CondRetEsp);

	if ((numLidos != 4)
		|| (!ValidarIndexCasasAndadas(indexCasasAndadas, NAO_VAZIO)))
	{
		return TST_CondRetParm;
	} /* if */


	cor = _DEBUGpossuiTorreNaCasaSeguinte(vtCasasAndadas[indexCasasAndadas], cor, numPeca - 1);


	return TST_CompararInt(CondRetEsp, cor,
		"Erro em teste de possuiTorreNaCasaSeguinte.");

	} /* fim ativa: Testar PossuiTorreNaCasaSeguinte*/









} /* Fim fun��o: TLIS &Testar Partida */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

int ValidarIndexCasasAndadas(int indexCasasAndadas, int Modo){

	if ((indexCasasAndadas < 0)
		|| (indexCasasAndadas >= QUANT_VT_CASAS_ANDADAS))
	{
		return FALSE;
	} /* if */

	if (Modo == VAZIO)
	{
		if (vtCasasAndadas[indexCasasAndadas][0] != -1)
		{
			return FALSE;
		} /* if */
	}
	else
	{
		if (vtCasasAndadas[indexCasasAndadas][0] == -1)
		{
			return FALSE;
		} /* if */
	} /* if */

	return TRUE;

} /* Fim fun��o: TTAB -Validar indice de tabuleiros */


/********** Fim do m�dulo de implementa��o: TSTTAB Teste Tabuleiro **********/

