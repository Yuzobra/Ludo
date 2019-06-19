#include "partida.h"
#include <direct.h>
#include <string.h>


void teste();





int main(void) {
	PAR_iniciarPartida();
	//teste();
}







void teste() {
	char buffer[500];
	char* dirName, * modeConBat, * clearBat;
	if ((dirName = _getcwd(buffer, 500)) != NULL) {
		printf("%s\n", dirName);
	}
	modeConBat = (char*)malloc(strlen(dirName) + 14); /* 14 vem de \\modeCon.bat + '\0'*/
	clearBat = (char*)malloc(strlen(dirName) + 12); /* 12 vem de \\clear.bat + '\0'*/
	strcpy(modeConBat, dirName);
	strcpy(clearBat, dirName);
	strcat(modeConBat, "\\modeCon.bat");
	strcat(clearBat, "\\clear.bat");
	printf("%s\n", modeConBat);
	printf("%s\n", clearBat);
	system(modeConBat);

	Tabuleiro* tab;
	TAB_criaTabuleiro(&tab);
	int vetCor[] = { 0,1,3 }, i, ini, quant;
	TAB_montaTabuleiro(tab, 3, vetCor);
	printf("valor ini:");
	scanf("%d", &ini);


	
	TAB_moverPeca(tab, 1, COR_red, 1);
	TAB_moverPeca(tab, 1, COR_red, 2);
	TAB_moverPeca(tab, 1, COR_red, 3);
	TAB_moverPeca(tab, 1, COR_red, 4);
	TAB_moverPeca(tab, 1, COR_blue, 1);
	TAB_moverPeca(tab, 1, COR_blue, 2);
	TAB_moverPeca(tab, 1, COR_blue, 3);
	TAB_moverPeca(tab, 1, COR_blue, 4);
	TAB_moverPeca(tab, 1, COR_yellow, 1);
	TAB_moverPeca(tab, 1, COR_yellow, 2);
	TAB_moverPeca(tab, 1, COR_yellow, 3);
	TAB_moverPeca(tab, 1, COR_yellow, 4);

	TAB_moverPeca(tab, ini, COR_red, 1);
	TAB_moverPeca(tab, ini, COR_red, 2);
	TAB_moverPeca(tab, ini, COR_red, 3);
	TAB_moverPeca(tab, ini, COR_red, 4);
	TAB_moverPeca(tab, ini, COR_blue, 1);
	TAB_moverPeca(tab, ini, COR_blue, 2);
	TAB_moverPeca(tab, ini, COR_blue, 3);
	TAB_moverPeca(tab, ini, COR_blue, 4);
	TAB_moverPeca(tab, ini, COR_yellow, 1);
	TAB_moverPeca(tab, ini, COR_yellow, 2);
	TAB_moverPeca(tab, ini, COR_yellow, 3);
	TAB_moverPeca(tab, ini, COR_yellow, 4);
	




	for (i = ini; i < 65; i++) {
		system(clearBat);
		printf("i: %d\n", i);
		TAB_visualizaTabuleiro(tab);
		scanf("%d", &ini);
		TAB_moverPeca(tab, ini, COR_red, 1);
		TAB_moverPeca(tab, 1, COR_red, 2);
		TAB_moverPeca(tab, 1, COR_red, 3);
		TAB_moverPeca(tab, 1, COR_red, 4);
		TAB_moverPeca(tab, 1, COR_blue, 1);
		TAB_moverPeca(tab, 1, COR_blue, 2);
		TAB_moverPeca(tab, 1, COR_blue, 3);
		TAB_moverPeca(tab, 1, COR_blue, 4);
		TAB_moverPeca(tab, 1, COR_yellow, 1);
		TAB_moverPeca(tab, 1, COR_yellow, 2);
		TAB_moverPeca(tab, 1, COR_yellow, 3);
		TAB_moverPeca(tab, 1, COR_yellow, 4);
		system("pause");


	}
	free(dirName);
	system("pause");
	TAB_destroiTabuleiro(tab);
	return 0;
}