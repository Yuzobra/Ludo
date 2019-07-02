/***************************************************************************
*  $MCI M�dulo de implementa��o: PAR  partida
*
*  Arquivo gerado:              partida.c
*  Letras identificadoras:      PAR
*
*  Projeto: INF 1301 / Jogo de Ludo
*
*  Autores: yz - Yuri Zoel Brasil
*			jp - Juliana Heluy do Prado
*			vh - Victor Hugo Silva Lima
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4		yz		14/06/2019	Cria��o e corre��o da fun��o possuiTorreNaCasaSeguinte
*		3		yz		13/06/2019	Corre��o nas fun��es est�ticas do m�dulo 
*		2		yz		11/06/2019	Corre��o no tipo de retorno em rodada
*		1		yz		05/06/2019	Primeira vers�o das fun��es exportadas do m�dulo 
***************************************************************************/

#include "partida.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static int rodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor);
static COR_tpCor checaVitoria(int* casasAndadas); // retorna a cor do jogador vencedor, se n�o houver retorna COR_white
static int podeMover(int* casasAndadas, COR_tpCor cor,int valorDado);
static COR_tpCor ComerPeca(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor, int numPeca);  // retorna a cor da peca comida, se n�o houver retorna COR_white
static COR_tpCor possuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca); // retorna a cor da torre, se n�o houver retorna COR_white

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $TC Tipo de dados: PAR Elemento da partida
*
*
***********************************************************************/

typedef enum {
	
	PAR_naoPodeMover,
	
	PAR_tirarCasaInicial,

	PAR_moverNormal,

	PAR_tirarInicialEMoverNormal,

}PAR_tpMov;

/***********************************************************************
*
*  $TC Tipo de dados: PAR Elemento da Partida

*		$ED Descri��o do tipo
*		  - string que cont�m o diretorio em que o arquivo .bat est�
*
***********************************************************************/

char * pClearBat;

/***************************************************************************
*
*  Fun��o: PAR  &Iniciar Partida
*
*  ************************************************************************/

PAR_CondRet PAR_iniciarPartida() {
	char buffer[500];


	char* pDirName, * pModeConBat;

	int* pVetCores, quantJog, i, corJog, casasAndadas[16], rodadaAtual = 0;

	Tabuleiro *pTab;


	memset(casasAndadas, 0, 16*sizeof(int));


	if ((pDirName = _getcwd(buffer, 500)) != NULL) {
		printf("%s\n", pDirName);
	}/* if */
	pModeConBat = (char*)malloc(strlen(pDirName) + 23); /* 14 vem de \\Batches\\modeCon.bat + '\0'*/
	pClearBat = (char*)malloc(strlen(pDirName) + 21); /* 12 vem de \\Batches\\clear.bat + '\0'*/

	if (pModeConBat == NULL || pClearBat == NULL || pDirName == NULL) {
		return PAR_condRetFaltouMemoria;

	}/* if */

	srand(time(NULL));


	strcpy(pModeConBat, pDirName);
	strcpy(pClearBat, pDirName);
	strcat(pModeConBat, "\\Batches\\modeCon.bat");
	strcat(pClearBat, "\\Batches\\clear.bat");
	system(pModeConBat);

	TAB_criaTabuleiro(&pTab);

	printf("Quantas pessoas irao jogar?\n");
	scanf("%d", &quantJog);
	
	while (((buffer[0] = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/ 

	while(quantJog < 2 || quantJog > 4) {
		printf("Quantidade invalida de jogadores, devem haver no minimo 2 e no maximo 4:");
		scanf("%d", &quantJog);
		while (((buffer[0] = getchar()) != '\n')); 
	}/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/
	
	pVetCores = (int*)malloc(sizeof(int) * quantJog);

	system(pClearBat);
	printf("Sendo\n1-Vermelho\n2-Azul\n3-Verde\n4-Amarelo\n");

	for (i = 0; i < quantJog; i++) {
		int teste = 1;



		switch (i) {
		case 0:
			printf("Insira a cor do primeiro jogador:");
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5) {
				teste = 0;
			}/* if */
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5) {
					teste = 0;
				}/* if */
			}
			pVetCores[0] = corJog;
			break;
		case 1:

			while (((buffer[0] = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

			printf("Insira a cor do segundo jogador:"); 
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog) {
				teste = 0;
			}/* if */
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4 que ainda nao tenha sido escolhida:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog) {
					teste = 0;
				}/* if */
			}
			pVetCores[1] = corJog;
			break;
		case 2:

			while (((buffer[0] = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

			printf("Insira a cor do terceiro jogador:"); 
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog) {
				teste = 0;
			}/* if */
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4 que ainda nao tenha sido escolhida:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog) {
					teste = 0;
				}/* if */
			}
			pVetCores[2] = corJog;
			break;
		case 3:
			while (((buffer[0] = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

			printf("Insira a cor do quarto jogador:"); 
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog && pVetCores[2] != corJog) {
				teste = 0;
			}/* if */
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4 que ainda nao tenha sido escolhida:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog && pVetCores[2] != corJog) {
					teste = 0;
				}/* if */
			}
			pVetCores[3] = corJog;
			break;
		}
		
		
	}
	for (i = 0; i < quantJog; i++) {
		pVetCores[i]--;
	}

	system(pClearBat);

	TAB_criaTabuleiro(&pTab);

	TAB_montaTabuleiro(pTab, quantJog, pVetCores);


	do {
		int acao = rodada(pTab, casasAndadas, pVetCores[rodadaAtual++ % quantJog]);
		if (acao == -1) {
			system(pClearBat);
			printf("Ocorreu um erro inesperado, reinicie o jogo");
			system("pause");
		}/* if */


		else if (acao == 1) {
			COR_tpCor* jogRestantes = (COR_tpCor*)malloc(sizeof(COR_tpCor)*(quantJog-1));
			int cont = 0;
			for (i = 0; i < quantJog; i++) {
				if (i != (rodadaAtual-1) % quantJog) {
					jogRestantes[cont++]=pVetCores[i];
				}/* if */
			}
			free(pVetCores);
			pVetCores = jogRestantes;
			quantJog--;
			if (quantJog < 2) {
				switch (pVetCores[0]) {
				case COR_red:
					printf("Vitoria do jogador vermelho!\n");
					break;
				case COR_blue:
					printf("Vitoria do jogador azul!\n");
					break;
				case COR_green:
					printf("Vitoria do jogador verde!\n");
					break;
				case COR_yellow:
					printf("Vitoria do jogador amarelo!\n");
					break;
				}
				system("pause");
				return PAR_condRetOk;
			}/* if */
		}
	} while (checaVitoria(casasAndadas) == COR_white);




	switch (checaVitoria(casasAndadas)) {
	case COR_red:
		printf("Vitoria do jogador vermelho!\n");
		break;
	case COR_blue:
		printf("Vitoria do jogador azul!\n");
		break;
	case COR_green:
		printf("Vitoria do jogador verde!\n");
		break;
	case COR_yellow:
		printf("Vitoria do jogador amarelo!\n");
		break;
	}


	TAB_destroiTabuleiro(pTab);
	free(pModeConBat);
	free(pClearBat);
	return PAR_condRetOk;
}/* Fim fun��o: PAR  &PAR_iniciarPartida */

/***********************************************************************
*
*  $FC Fun��o: PAR  -Rodada
*
*  $ED Descri��o da fun��o
*		- gerencia os inputs do usu�rio
		- roda o dado
		- realiza as a��es desejadas
*
*  $FV Valor retornado
*     0 - se o jogador rodar o dado
*	  1 - se o jogaador saiu da partida
*	 -1 - se houver um erro de entrada
*
***********************************************************************/

static int rodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor){
	char acao,
		podeMoverPeca;

	int valorDado,
		i,
		numPeca;



	if (pTab == NULL || casasAndadas == NULL || cor < COR_MIN || cor > COR_MAX) {
		return -1;
	}/* if */

	printf("Jogador ");
	switch (cor) {
	case COR_red:
		printf("vermelho ");
		break;
	case COR_blue:
		printf("azul ");
		break;
	case COR_green:
		printf("verde ");
		break;
	case COR_yellow:
		printf("amarelo ");
		break;
	}
	printf("o que deseja fazer?\nR - Rodar o dado\nS - Sair da partida\n");

	while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/


	scanf("\n%c", &acao);

	while (acao != 'S' && acao != 's' && acao != 'R' && acao != 'r') {

		while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/


		printf("Comando invalido, insira um comando valido, sendo:\nR - Rodar o dado\nS - Sair da partida\n");
		scanf("\n%c", &acao);
	}
	if (acao == 'r') {
		acao = 'R';
	}else if(acao == 's') {
		acao = 'S';
	}/* if */

	switch (acao) {
	case 'R':
		system(pClearBat);
		valorDado = (rand() % 6) + 1;
		TAB_visualizaTabuleiro(pTab);
		podeMoverPeca = podeMover(casasAndadas,cor,valorDado);
		printf("Voce tirou %d no dado,", valorDado);

		

		if (podeMoverPeca != PAR_naoPodeMover) {
			printf(" voce pode:\n");
		}else  {
			printf(" voce nao pode fazer nada!\n");
			system("pause");
			system(pClearBat);
			return;
		}/* if */

		if (podeMoverPeca == PAR_moverNormal || podeMoverPeca == PAR_tirarInicialEMoverNormal) {
			printf("M - Mover alguma peca\n");
		}/* if */

		if (podeMoverPeca == PAR_tirarCasaInicial || podeMoverPeca == PAR_tirarInicialEMoverNormal) {
			printf("T - Tirar uma peca da casa inicial\n");
		}/* if */

		if (podeMoverPeca != PAR_naoPodeMover) {
			
			while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

			scanf("\n%c", &acao);
		}/* if */
		if (podeMoverPeca == PAR_tirarInicialEMoverNormal) {
			while (acao != 'M' && acao != 'm' && acao != 'T' && acao != 't') {

				while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/


				system(pClearBat);
				TAB_visualizaTabuleiro(pTab);
				printf("Comando invalido, insira um comando valido, sendo:\nM - Mover alguma peca\nT - Tirar uma peca da casa inicial\n");
				scanf("\n%c", &acao);
			}
		}else if (podeMoverPeca == PAR_moverNormal) {
			while (acao != 'M' && acao != 'm') {

				while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

				system(pClearBat);
				TAB_visualizaTabuleiro(pTab);
				printf("Comando invalido, insira um comando valido, sendo:\nM - Mover alguma peca\n");
				scanf("\n%c", &acao);
			}
		}else if (podeMoverPeca == PAR_tirarCasaInicial) {
			while (acao != 'T' && acao != 't') {

				while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

				system(pClearBat);
				TAB_visualizaTabuleiro(pTab);
				printf("Comando invalido, insira um comando valido, sendo:\nT - Tirar uma peca da casa inicial\n");
				scanf("\n%c", &acao);
			}
		}/* if */

		if (acao == 'm') {
			acao = 'M';
		}/* if */
		if (acao == 't') {
			acao = 'T';
		}/* if */
		switch (acao) {
		case 'M':
			while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/
			printf("Qual peca deseja mover? ");

			scanf("%d", &numPeca);


			while ((numPeca < PEC_MIN || numPeca > PEC_MAX) || casasAndadas[(cor * 4) + numPeca - 1] == 0) {
				if (numPeca < PEC_MIN || numPeca > PEC_MAX) {
					
					while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

					printf("\nValor invalido de peca, insira um valor entre 1 e 4: ");
					scanf("%d", &numPeca);
				}else {

					while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

					printf("\nEssa peca esta em um casa inicial, escolha uma que nao esteja: ");
					scanf("%d", &numPeca);
				}/* if */
			}

			if (casasAndadas[(cor * 4) + numPeca - 1] <= CASAS_ATE_ENTRADA) {
				int corTorre;
				for (i = 0; i < valorDado; i++) {
					corTorre = possuiTorreNaCasaSeguinte(casasAndadas, cor, numPeca-1);

					if (corTorre != cor && corTorre != COR_white) {
						break;
					}else {
						casasAndadas[(cor * 4) + numPeca - 1]++;
						TAB_moverPeca(pTab, 1, cor, numPeca);
					}/* if */
				}/* for */
			}else {
				TAB_moverPeca(pTab, valorDado, cor, numPeca);
				if (casasAndadas[(cor * 4) + numPeca - 1] + valorDado > 57) {
					casasAndadas[(cor * 4) + numPeca - 1] = 57 - ((casasAndadas[(cor * 4) + numPeca - 1] + valorDado) % 57); 
				}else {
					casasAndadas[(cor * 4) + numPeca - 1] += valorDado;
				}/* if */
			}/* if */



			/*Verificar se h� uma pe�a a ser comida*/
			
			ComerPeca(pTab,casasAndadas, cor, numPeca-1);
			


			break;



		case 'T':
			while (((acao = getchar()) != '\n'));// LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

			printf("Qual peca deseja tirar da casa inicial? ");
			
			scanf("%d", &numPeca);
			while ((numPeca < PEC_MIN || numPeca > PEC_MAX) || casasAndadas[(cor * 4) + numPeca - 1] != 0) {
				if (numPeca < PEC_MIN || numPeca > PEC_MAX){

					while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/

					printf("\nValor invalido de peca, insira um valor entre 1 e 4: ");
					scanf("%d", &numPeca);
				}else {

					while (((acao = getchar()) != '\n'));/*LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF*/


					printf("\nEssa peca nao esta em um casa inicial, escolha uma que esteja: ");
					scanf("%d", &numPeca);
				}/* if */
			}

			
			TAB_moverPeca(pTab, valorDado, cor, numPeca);
			casasAndadas[(cor * 4) + numPeca - 1] = 1;
			break;
		}

		system(pClearBat);

		if (valorDado == 1 || valorDado == 6) {
			printf("Voce tirou %d no dado! Tem direito a mais uma rodada.\n", valorDado);
			 return rodada(pTab, casasAndadas, cor);
		}/* if */
		return 0;
		break;
	case 'S':

		for (i = 0; i < 4; i++) {
			TAB_retornaPecaParaCasaInicial(pTab, cor, i+1);
			casasAndadas[(cor * 4) + i] = 0;
		}

		return 1;
	}

}/* Fim fun��o: PAR  -rodada */

/***************************************************************************
*
*  Fun��o: PAR  &Mover Peca
*
*  ************************************************************************/

static PAR_tpMov podeMover(int* casasAndadas, COR_tpCor cor, int valorDado) {
	int i ,
		podeMoverPeca			= 0,
		possuiPecaCasaInicial	= 0;

	
	for (i = 0; i < 4; i++) {
		if (casasAndadas[cor * 4 + i] != 0) {
			podeMoverPeca = 1;
		}else /* h� uma peca na casa inicial */ {
			possuiPecaCasaInicial = 1;
		}/* if */
	}/* for */

	if (podeMoverPeca && (possuiPecaCasaInicial && (valorDado == 1 || valorDado == 6))) {
		return PAR_tirarInicialEMoverNormal;
	}else if(podeMoverPeca){
		return PAR_moverNormal;
	}else if (possuiPecaCasaInicial && (valorDado == 1 || valorDado == 6)) {
		return PAR_tirarCasaInicial;
	}/* if */
	
	return PAR_naoPodeMover;
}/* Fim fun��o: PAR  &Mover Peca */

/***********************************************************************
*
*  $FC Fun��o: PAR  -Comer Peca
*
*  $ED Descri��o da fun��o
*	  verifica se a pe�a passada para a fun��o possui uma pe�aa para comer.
*	  verifica se h� alguma pe�a a ser comida na casa da pe�a passada,
*			se tiver, retorna a pe�a para a casa inicial e atualiza o vetor de casas andadas.
*
*  $EP Par�metros
*     pTab - ponteiro para tabuleiro
*	  casasAndadas - vetor de casas andadas
*	  cor - da pe�a que deseja saber a informa��o
*	  numPeca - da pe�a que deseja saber a informa��o
*
*  $FV Valor retornado
*		COR_white -  se nao houver retorna branco
*		i / 4 - cor da pe�a comida
*
***********************************************************************/

static COR_tpCor ComerPeca(Tabuleiro* pTab,int* casasAndadas, COR_tpCor cor, int numPeca) /* Tem que verificar se � uma casa segura */{
	int i;
	for (i = 0; i < 16; i++) { 
		if (i / 4 < cor)  /* Pe�a a ser comida de uma cor anterior a cor */ {
			if (casasAndadas[i] == (casasAndadas[(cor * 4) + numPeca] + 13 * (cor - (i / 4))) && casasAndadas[i] != 1) {

				// RETORNAR PRA CASA INICIAL
				TAB_retornaPecaParaCasaInicial(pTab, i / 4, (i % 4) + 1);
				casasAndadas[i] = 0;
				return i / 4;

			}/* if */
		}else if(i/4 > cor){
			if ((casasAndadas[i] + (13 * ((i / 4) - cor))) == casasAndadas[(cor * 4) + numPeca] && casasAndadas[i] != 1) {


				/*RETORNAR PARA CASA INICIAL*/
				TAB_retornaPecaParaCasaInicial(pTab, i / 4, (i % 4) + 1);
				casasAndadas[i] = 0;
				return i / 4;

			}/* if */
		}/* if */
	}/* for */
	return COR_white;
}/* Fim fun��o: PAR  -comer peca */

/***********************************************************************
*
*  $FC Fun��o: PAR  -Checar se Possui Torre na Casa Seguinte
*
*  $ED Descri��o da fun��o
*     Checa se possui torre na casa da frente
*
*  $EP Par�metros
*	  casasAndadas - vetor de casas andadas
*	  cor - da pe�a que deseja saber a informa��o
*	  numPeca - da pe�a que deseja saber a informa��o
*
*  $FV Valor retornado
*	   i / 4 -  se tiver uma torre na casa seguinte a pe�a
*	   COR_white - se nao tiver retorna branco
*
***********************************************************************/

static COR_tpCor possuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca) {
	int i,
		j,
		torre = 0;

	for (i = 0; i < 16; i++) {
		if (i / 4 < cor)  /* Torre de uma cor anterior a cor procurada */ {
			if (casasAndadas[i] == (casasAndadas[(cor * 4) + numPeca] + (13 * (cor - (i / 4)))+1) ) {
				for (j = 1; j < ((i / 4) * 4) + 4; j++) {
					if (casasAndadas[i] == casasAndadas[i + j]) {
						return i / 4;
					}/* if */
				}/* for */
			}/* if */
		}else {
			if (casasAndadas[i] - (13 * (cor - (i / 4)) == (casasAndadas[(cor * 4) + numPeca])+1) ) {
				for (j = 1; j < ((i / 4) * 4) + 4; j++) {
					if (casasAndadas[i] == casasAndadas[i + j]) {
						return i / 4;
					}/* if */
				}/* for */
			}/* if */
		}/* if */
	}/* for */

	return COR_white;
}/* Fim fun��o: PAR  -Checar se Possui Torre na Casa Seguinte */

/***********************************************************************
*
*  $FC Fun��o: PAR  -Checar se h� algum jogador vitorioso
*
*  $ED Descri��o da fun��o
*     Checa se h� alguma cor em que as quatro pe�as
*		andaram o numero total de casas do tabuleiro
*		retornando a cor do jogador vencedor
*
*  $EP Par�metros
*	  casasAndadas - vetor de casas andadas
*
*  $FV Valor retornado
*	  i - a cor do jogador vencedor
*	  COR_white - se nao tiver, retorna branco
*
***********************************************************************/

static COR_tpCor checaVitoria(int* casasAndadas) {
	int i,
		j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (casasAndadas[(4 * i) + j] > CASAS_ATE_ENTRADA && (casasAndadas[(4 * i) + j] - 51) % 6 == 0) {
				if (j == 3) {
					return i;
				}/* if */
			}else {
				break;
			}/* if */
		}/* for */
	}/* for */
	return COR_white;
}/* Fim fun��o: PAR  -Checar se h� algum jogador vitorioso */


/*****  conjunto de fun��es que servem somente para exportar fun��es est�ticas do m�dulo para chamar no m�dulo teste  *****/

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: PAR  -DEBUGrodada
*
*  ************************************************************************/

int _DEBUGrodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor);

/***************************************************************************
*
*  Fun��o: PAR  _DEBUGchecaVitoria
*
*  $ED Descri��o da fun��o
*		retorna a cor do jogador vencedor, se n�o houver retorna COR_white
*
*  ************************************************************************/

COR_tpCor _DEBUGchecaVitoria(int* casasAndadas) {
	return checaVitoria(casasAndadas);
}

int _DEBUGpodeMover(int* casasAndadas, COR_tpCor cor, int valorDado) {
	return podeMover(casasAndadas, cor, valorDado);
}

/***************************************************************************
*
*  Fun��o: PAR  _DEBUGchecaVitoria
*
*  $ED Descri��o da fun��o
*		retorna a cor da peca comida, se n�o houver retorna COR_white
*
*  ************************************************************************/

COR_tpCor _DEBUGComerPeca(int* casasAndadas, COR_tpCor cor, int numPeca) { 
	Tabuleiro* pTab = NULL;
	
	return ComerPeca(pTab, casasAndadas, cor, numPeca);
}

/***************************************************************************
*
*  Fun��o: PAR  _DEBUGchecaVitoria
*
*  $ED Descri��o da fun��o
*		retorna a cor da torre, se n�o houver retorna COR_white
*
*  ************************************************************************/

COR_tpCor _DEBUGpossuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca) { 
	return possuiTorreNaCasaSeguinte(casasAndadas,cor,numPeca);
}

#endif

/********** Fim do m�dulo de implementa��o : PAR partida **********/