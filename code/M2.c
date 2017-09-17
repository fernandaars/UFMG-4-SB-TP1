#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define TAM_MEMORIA 1024
#define TAM_INSTRUCAO 2
#define TAM_LINHA 40

int PC, AC;
int memoria[TAM_MEMORIA];

void carregador(char *nomeArquivoEntrada){
	FILE *arq;
	arq = fopen(nomeArquivoEntrada, "r");

	int pos = 0;
	char linha[TAM_LINHA];
	while(!feof(arq)){
		fgets(arq, "%s", linha);
		char token[TAM_LINHA];
   		token = strtok(linha, " ");
   		while(token != NULL){
        	printf("%s\n", token );
        	memoria[pos] = atoi(token);
    		token = strtok(NULL, " ");
    		pos++;
   		}
	}
	PC = AC = 0;
}

void simulador(){
	int i;
	for(i=0; i<TAM_MEMORIA; i++){
		int posAtual = PC;
		int conteudoAtual = memoria[posAtual];
		switch(posAtual){
			case 1: AC = memoria[posAtual+1];
			case 2: 
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
		}
	}
}

int main(int argc, char *argv[]){
	if(argc < 2){ 
		printf("ERRO - Numero de Parametros Invalido\n");
		getchar();
		exit(1);
	}
	carregador(argv[1]);
	simulador();
	return 0;
}