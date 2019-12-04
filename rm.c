#include "string.h"
#include "stdio.h"
#include "stdlib.h"


void rm_con(char* entrada,char* saida){
	FILE *output = fopen(saida, "a+");
	FILE *input  = fopen(entrada, "r");
	char *linha;
	if (input == NULL) exit(1);
	while (getline(&linha,0,input) != -1){                             //pra cada linha:
		if (linha[4] != 'c')fprintf(output,"%s\n",linha);          //escreve a linha em novo arquivo se n for removida
	}
	fclose(output);
	fclose(input);
}


void rm_Mai(char* entrada,char* saida){
	FILE *output = fopen(saida, "a+");
	FILE *input  = fopen(entrada, "r");
	char *linha;
	if (input == NULL) exit(1);
	while (getline(&linha,0,input) != -1){                  //pra cada linha:
	if (linha[2] != 'M')	fprintf(output,"%s\n",linha);                      //escreve a linha em novo arquivo
	}
	fclose(output);
	fclose(input);
}


void rm_min(char* entrada,char* saida){
	FILE *output = fopen(saida, "a+");
	FILE *input  = fopen(entrada, "r");
	char *linha;
	if (input == NULL) exit(1);
	while (getline(&linha,0,input) != -1){                  //pra cada linha:
		if (linha[2] != 'm')fprintf(output,"%s\n",linha);                      //escreve a linha em novo arquivo
	}
	fclose(output);
	fclose(input);
}


void rm_vog(char* entrada,char* saida){
	FILE *output = fopen(saida, "a+");
	FILE *input  = fopen(entrada, "r");
	char *linha;
	if (input == NULL) exit(1);
	while (getline(&linha,0,input) != -1){                  //pra cada linha:
		if (linha[4] != 'v') fprintf(output,"%s\n",linha);                      //escreve a linha em novo arquivo
	}
	fclose(output);
	fclose(input);
}

void rm_dupla(char* entrada, char* saida, char cv, char mm){
	FILE *output = fopen(saida, "a+");
	FILE *input  = fopen(entrada, "r");
	char *linha;
	if (input == NULL) exit(1);
	while (getline(&linha,0,input) != -1){                  //pra cada linha:
		if (linha[4] != cv && linha[2] != mm) fprintf(output,"%s\n",linha);                      //escreve a linha em novo arquivo
	}
	fclose(output);
	fclose(input);
}

void rm_letra(char* entrada,char* saida,char letra){
	FILE *output = fopen(saida, "a+");
	FILE *input  = fopen(entrada, "r");
	char *linha;
	if (input == NULL) exit(1);
	while (getline(&linha,0,input) != -1){                  //pra cada linha:
		if (linha[0] != letra) fprintf(output,"%s\n",linha);  
								//escreve a linha em novo arquivo
	}
	fclose(output);
	fclose(input);
}

