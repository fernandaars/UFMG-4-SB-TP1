#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

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
		bool parar = false;
		int posAtual = PC;
		int conteudoAtual = memoria[posAtual];

		PC += 2;
		switch(posAtual){
			case 1 : AC = memoria[posAtual];
			case 2 : memoria[posAtual] = AC;
			case 3 : AC += memoria[posAtual];
			case 4 : AC -= memoria[posAtual];
			case 5 : scanf("%d", &memoria[posAtual]);
			case 6 : printf("%d\n", memoria[posAtual]);
			case 7 : PC = memoria[posAtual];
			case 8 : PC = (AC > 0) ? memoria[posAtual] : PC; 
			case 9 : PC = (AC < 0) ? memoria[posAtual] : PC;	
			case 10: PC = (AC == 0)? memoria[posAtual] : PC;
			case 11: parar = true;
		}
		if(flag == true) break;
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