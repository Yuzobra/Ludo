#include "tabuleiro.h"

#define CASAS_ATE_ENTRADA 51


typedef enum {

	PAR_condRetOk,
	/* Concluiu corretamente */

	PAR_condRetFaltouMemoria,
	/* Faltou memória */

} PAR_CondRet;



PAR_CondRet PAR_iniciarPartida();