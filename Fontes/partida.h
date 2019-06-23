#include "tabuleiro.h"

#define CASAS_ATE_ENTRADA 51

#define _DEBUG

typedef enum {

	PAR_condRetOk,
	/* Concluiu corretamente */

	PAR_condRetFaltouMemoria,
	/* Faltou memória */

} PAR_CondRet;



PAR_CondRet PAR_iniciarPartida();




#ifdef _DEBUG

int _DEBUGrodada(Tabuleiro* pTab, int* casasAndadas, COR_tpCor cor);
COR_tpCor _DEBUGchecaVitoria(int* casasAndadas); // retorna a cor do jogador vencedor, se não houver retorna COR_white
int _DEBUGpodeMover(int* casasAndadas, COR_tpCor cor, int valorDado);
COR_tpCor _DEBUGComerPeca(int* casasAndadas, COR_tpCor cor, int numPeca);  // retorna a cor da peca comida, se não houver retorna COR_white
COR_tpCor _DEBUGpossuiTorreNaCasaSeguinte(int* casasAndadas, COR_tpCor cor, int numPeca); // retorna a cor da torre, se não houver retorna COR_white

#endif
