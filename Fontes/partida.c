#include "partida.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


static int rodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor);
static COR_tpCor checaVitoria(int* casasAndadas); // retorna a cor do jogador vencedor, se não houver retorna COR_white
static int podeMover(int* casasAndadas, COR_tpCor cor,int valorDado);
static COR_tpCor ComerPeca(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor, int numPeca);  // retorna a cor da peca comida, se não houver retorna COR_white
static COR_tpCor possuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca); // retorna a cor da torre, se não houver retorna COR_white


typedef enum {
	
	PAR_naoPodeMover,
	
	PAR_tirarCasaInicial,

	PAR_moverNormal,

	PAR_tirarInicialEMoverNormal,

}PAR_tpMov;

char * pClearBat;

PAR_CondRet PAR_iniciarPartida() {
	char buffer[500];


	char* pDirName, * pModeConBat;

	int* pVetCores, quantJog, i, corJog, casasAndadas[16], rodadaAtual = 0;

	Tabuleiro *pTab;


	memset(casasAndadas, 0, 16*sizeof(int));


	if ((pDirName = _getcwd(buffer, 500)) != NULL) {
		printf("%s\n", pDirName);
	}
	pModeConBat = (char*)malloc(strlen(pDirName) + 14); /* 14 vem de \\modeCon.bat + '\0'*/
	pClearBat = (char*)malloc(strlen(pDirName) + 12); /* 12 vem de \\clear.bat + '\0'*/

	if (pModeConBat == NULL || pClearBat == NULL || pDirName == NULL) {
		return PAR_condRetFaltouMemoria;

	}

	srand(time(NULL));


	strcpy(pModeConBat, pDirName);
	strcpy(pClearBat, pDirName);
	strcat(pModeConBat, "\\modeCon.bat");
	strcat(pClearBat, "\\clear.bat");
	system(pModeConBat);

	TAB_criaTabuleiro(&pTab);

	printf("Quantas pessoas irao jogar?\n");
	scanf("%d", &quantJog);

	while (((buffer[0] = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

	while(quantJog < 2 || quantJog > 4) {
		printf("Quantidade invalida de jogadores, devem haver no minimo 2 e no maximo 4:");
		scanf("%d", &quantJog);
		while (((buffer[0] = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF
	}
	
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
			}
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5) {
					teste = 0;
				}
			}
			pVetCores[0] = corJog;
			break;
		case 1:

			while (((buffer[0] = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

			printf("Insira a cor do segundo jogador:"); 
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog) {
				teste = 0;
			}
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4 que ainda nao tenha sido escolhida:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog) {
					teste = 0;
				}
			}
			pVetCores[1] = corJog;
			break;
		case 2:

			while (((buffer[0] = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

			printf("Insira a cor do terceiro jogador:"); 
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog) {
				teste = 0;
			}
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4 que ainda nao tenha sido escolhida:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog) {
					teste = 0;
				}
			}
			pVetCores[2] = corJog;
			break;
		case 3:
			while (((buffer[0] = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

			printf("Insira a cor do quarto jogador:"); 
			scanf("%d", &corJog);
			if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog && pVetCores[2] != corJog) {
				teste = 0;
			}
			while (teste) {
				printf("Cor invalida, insira um valor entre 1 e 4 que ainda nao tenha sido escolhida:");
				scanf("%d", &corJog);
				if (corJog > 0 && corJog < 5 && pVetCores[0] != corJog && pVetCores[1] != corJog && pVetCores[2] != corJog) {
					teste = 0;
				}
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
		}


		else if (acao == 1) {
			COR_tpCor* jogRestantes = (COR_tpCor*)malloc(sizeof(COR_tpCor)*(quantJog-1));
			int cont = 0;
			for (i = 0; i < quantJog; i++) {
				if (i != (rodadaAtual-1) % quantJog) {
					jogRestantes[cont++]=pVetCores[i];
				}
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
			}
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
}

static int rodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor) /*Retorna 0 se rodar o dado, 1 se sair da partida, -1 se houver um erro de entrada*/{
	char acao, podeMoverPeca;

	int valorDado, i,numPeca;



	if (pTab == NULL || casasAndadas == NULL || cor < COR_MIN || cor > COR_MAX) {
		return -1;
	}

	printf("\n");
	for (i = 0; i < 16; i++)printf("%d ", casasAndadas[i]);



	printf("\nJogador ");
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

	while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF


	scanf("\n%c", &acao);

	while (acao != 'S' && acao != 's' && acao != 'R' && acao != 'r') {

		while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF


		printf("Comando invalido, insira um comando valido, sendo:\nR - Rodar o dado\nS - Sair da partida\n");
		scanf("\n%c", &acao);
	}
	if (acao == 'r') {
		acao = 'R';
	}
	else if(acao == 's') {
		acao = 'S';
	}
	switch (acao) {
	case 'R':
		system(pClearBat);
		valorDado = (rand() % 6) + 1;
		TAB_visualizaTabuleiro(pTab);
		podeMoverPeca = podeMover(casasAndadas,cor,valorDado);
		printf("Voce tirou %d no dado,", valorDado);

		

		if (podeMoverPeca != PAR_naoPodeMover) {
			printf(" voce pode:\n");
		}
		else  {
			printf(" voce nao pode fazer nada!\n");
			system("pause");
			system(pClearBat);
			return;
		}

		if (podeMoverPeca == PAR_moverNormal || podeMoverPeca == PAR_tirarInicialEMoverNormal) {
			printf("M - Mover alguma peca\n");
		}

		if (podeMoverPeca == PAR_tirarCasaInicial || podeMoverPeca == PAR_tirarInicialEMoverNormal) {
			printf("T - Tirar uma peca da casa inicial\n");
		}

		if (podeMoverPeca != PAR_naoPodeMover) {
			
			while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

			scanf("\n%c", &acao);
		}
		if (podeMoverPeca == PAR_tirarInicialEMoverNormal) {
			while (acao != 'M' && acao != 'm' && acao != 'T' && acao != 't') {

				while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF


				system(pClearBat);
				TAB_visualizaTabuleiro(pTab);
				printf("Comando invalido, insira um comando valido, sendo:\nM - Mover alguma peca\nT - Tirar uma peca da casa inicial\n");
				scanf("\n%c", &acao);
			}

		}
		else if (podeMoverPeca == PAR_moverNormal) {
			while (acao != 'M' && acao != 'm') {

				while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

				system(pClearBat);
				TAB_visualizaTabuleiro(pTab);
				printf("Comando invalido, insira um comando valido, sendo:\nM - Mover alguma peca\n");
				scanf("\n%c", &acao);
			}
		}
		else if (podeMoverPeca == PAR_tirarCasaInicial) {
			while (acao != 'T' && acao != 't') {

				while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

				system(pClearBat);
				TAB_visualizaTabuleiro(pTab);
				printf("Comando invalido, insira um comando valido, sendo:\nT - Tirar uma peca da casa inicial\n");
				scanf("\n%c", &acao);
			}
		}

		if (acao == 'm') {
			acao = 'M';
		}
		if (acao == 't') {
			acao = 'T';
		}
		switch (acao) {
		case 'M':
			while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF
			printf("Qual peca deseja mover? ");

			scanf("%d", &numPeca);


			while ((numPeca < PEC_MIN || numPeca > PEC_MAX) || casasAndadas[(cor * 4) + numPeca - 1] == 0) {
				if (numPeca < PEC_MIN || numPeca > PEC_MAX) {
					
					while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

					printf("\nValor invalido de peca, insira um valor entre 1 e 4: ");
					scanf("%d", &numPeca);
				}
				else {

					while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

					printf("\nEssa peca esta em um casa inicial, escolha uma que nao esteja: ");
					scanf("%d", &numPeca);
				}
			}

			if (casasAndadas[(cor * 4) + numPeca - 1] <= CASAS_ATE_ENTRADA) {
				int corTorre;
				for (i = 0; i < valorDado; i++) {
					corTorre = possuiTorreNaCasaSeguinte(casasAndadas, cor, numPeca-1);

					if (corTorre != cor && corTorre != COR_white) {
						break;
					}
					else {
						casasAndadas[(cor * 4) + numPeca - 1]++;
						TAB_moverPeca(pTab, 1, cor, numPeca);
					}
				}
			}
			else {
				TAB_moverPeca(pTab, valorDado, cor, numPeca);
				if (casasAndadas[(cor * 4) + numPeca - 1] + valorDado > 57) {
					casasAndadas[(cor * 4) + numPeca - 1] = 57 - ((casasAndadas[(cor * 4) + numPeca - 1] + valorDado) % 57); 
				}
				else {
					casasAndadas[(cor * 4) + numPeca - 1] += valorDado;
				}
			}



			/*Verificar se há uma peça a ser comida*/
			
			ComerPeca(pTab,casasAndadas, cor, numPeca-1);
			


			break;



		case 'T':
			while (((acao = getchar()) != '\n'));// LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

			printf("Qual peca deseja tirar da casa inicial? ");
			
			scanf("%d", &numPeca);
			while ((numPeca < PEC_MIN || numPeca > PEC_MAX) || casasAndadas[(cor * 4) + numPeca - 1] != 0) {
				if (numPeca < PEC_MIN || numPeca > PEC_MAX){

					while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF

					printf("\nValor invalido de peca, insira um valor entre 1 e 4: ");
					scanf("%d", &numPeca);
				}
				else {

					while (((acao = getchar()) != '\n')); // LIMPAR O BUFFER DE ENTRADA PARA IMPEDIR CONFLITO COM O PROXIMO SCANF


					printf("\nEssa peca nao esta em um casa inicial, escolha uma que esteja: ");
					scanf("%d", &numPeca);
				}
			}

			
			TAB_moverPeca(pTab, valorDado, cor, numPeca);
			casasAndadas[(cor * 4) + numPeca - 1] = 1;
			break;
		}

		system(pClearBat);

		if (valorDado == 1 || valorDado == 6) {
			printf("Voce tirou %d no dado! Tem direito a mais uma rodada.\n", valorDado);
			 return rodada(pTab, casasAndadas, cor);
		}
		return 0;
		break;
	case 'S':

		for (i = 0; i < 4; i++) {
			TAB_retornaPecaParaCasaInicial(pTab, cor, i+1);
			casasAndadas[(cor * 4) + i] = 0;
		}

		return 1;
	}

}

static PAR_tpMov podeMover(int* casasAndadas, COR_tpCor cor, int valorDado) {
	int i , podeMoverPeca = 0, possuiPecaCasaInicial = 0;

	
	for (i = 0; i < 4; i++) {
		if (casasAndadas[cor * 4 + i] != 0) {
			podeMoverPeca = 1;
		}
		else /* há uma peca na casa inicial */ {
			possuiPecaCasaInicial = 1;
		}
	}

	if (podeMoverPeca && (possuiPecaCasaInicial && (valorDado == 1 || valorDado == 6))) {
		return PAR_tirarInicialEMoverNormal;
	}
	else if(podeMoverPeca){
		return PAR_moverNormal;
	}

	else if (possuiPecaCasaInicial && (valorDado == 1 || valorDado == 6)) {
		return PAR_tirarCasaInicial;
	}
	
	return PAR_naoPodeMover;
}

static COR_tpCor ComerPeca(Tabuleiro* pTab,int* casasAndadas, COR_tpCor cor, int numPeca) /* Tem que verificar se é uma casa segura */{
	int i;
	for (i = 0; i < 16; i++) { 
		if (i / 4 < cor)  /* Peça a ser comida de uma cor anterior a cor */ {
			if (casasAndadas[i] == (casasAndadas[(cor * 4) + numPeca] + 13 * (cor - (i / 4))) && casasAndadas[i] != 1) {

				// RETORNAR PRA CASA INICIAL
				TAB_retornaPecaParaCasaInicial(pTab, i / 4, (i % 4) + 1);
				casasAndadas[i] = 0;
				return i / 4;

			}
		}
		else if(i/4 > cor){
			if ((casasAndadas[i] + (13 * ((i / 4) - cor))) == casasAndadas[(cor * 4) + numPeca] && casasAndadas[i] != 1) {


				// RETORNAR PARA CASA INICIAL
				TAB_retornaPecaParaCasaInicial(pTab, i / 4, (i % 4) + 1);
				casasAndadas[i] = 0;
				return i / 4;

			}
		}

	}
	return COR_white;
}

static COR_tpCor possuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca) {
	int i, j, torre = 0;

	for (i = 0; i < 16; i++) {
		if (i / 4 < cor)  /* Torre de uma cor anterior a cor procurada */ {
			if (casasAndadas[i] == (casasAndadas[(cor * 4) + numPeca] + (13 * (cor - (i / 4)))+1) ) {
				for (j = 1; j < ((i / 4) * 4) + 4; j++) {
					if (casasAndadas[i] == casasAndadas[i + j]) {
						return i / 4;
					}
				}
			}
		}
		else {
			if (casasAndadas[i] - (13 * (cor - (i / 4)) == (casasAndadas[(cor * 4) + numPeca])+1) ) {
				for (j = 1; j < ((i / 4) * 4) + 4; j++) {
					if (casasAndadas[i] == casasAndadas[i + j]) {
						return i / 4;
					}
				}
			}

		}
	}

	return COR_white;
}

static COR_tpCor checaVitoria(int* casasAndadas) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (casasAndadas[(4 * i) + j] > CASAS_ATE_ENTRADA && (casasAndadas[(4 * i) + j] - 51) % 6 == 0) {
				if (j == 3) {
					return i;
				}
			}
			else {
				break;
			}
		}
	}
	return COR_white;
}



#ifdef _DEBUG


int _DEBUGrodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor); // ?


COR_tpCor _DEBUGchecaVitoria(int* casasAndadas) { // retorna a cor do jogador vencedor, se não houver retorna COR_white
	return checaVitoria(casasAndadas);
}

int _DEBUGpodeMover(int* casasAndadas, COR_tpCor cor, int valorDado) {
	return podeMover(casasAndadas, cor, valorDado);
}

COR_tpCor _DEBUGComerPeca(int* casasAndadas, COR_tpCor cor, int numPeca) {  // retorna a cor da peca comida, se não houver retorna COR_white
	Tabuleiro* pTab = NULL;
	
	return ComerPeca(pTab, casasAndadas, cor, numPeca);
}

COR_tpCor _DEBUGpossuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca) { // retorna a cor da torre, se não houver retorna COR_white
	return possuiTorreNaCasaSeguinte(casasAndadas,cor,numPeca);
}

#endif