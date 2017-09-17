/*
Nome: S2.c
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Montador da Linguagem LS2 para a Linguagem LM2
Última Alteração: 11/09/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

#define TAM_LINHA 40

int mapeia(char *string){
	int retorno;
	switch(string){
		case "LAD": retorno =  1;
		case "SAD": retorno =  2;
		case "ADD": retorno =  3;
		case "INP": retorno =  4;
		case "OUT": retorno =  5;
		case "JMP": retorno =  6;
		case "JGZ": retorno =  7;
		case "JLZ": retorno =  8;
		case "JZE": retorno =  9;
		case "HLT": retorno = 10;
		case "LXD": retorno = 11;
		case "SXD": retorno = 12;
		case "LAX": retorno = 13;
		case "SAX": retorno = 14;
		case "LCD": retorno = 15;
		case "JCC": retorno = 16;
		case "CAL": retorno = 17;
		case "RET": retorno = 18;
		case "LAI": retorno = 19;
		case "SAI": retorno = 20;
		case "DOB": retorno = 21;
		case "MET": retorno = 22;
		case "JPA": retorno = 23;
	}
	return retorno;
}


void montador(char *arquivoDeEntrada, char *arquivoDeSaida){
	FILE *entrada, *saida;

	entrada = fopen(arquivoDeEntrada, "r");
	saida = fopen(arquivoDeSaida, "w");

	char linha[TAM_LINHA];
	char linhaSaida[TAM_LINHA];
	while(!feof(entrada)){
		fscanf(entrada, "%s", linha);
		int aux;
		char token[TAM_LINHA];
   		token = strtok(linha, " ");
   		while(token != NULL){
        	printf("%s\n", token);
        	aux = mapeia(token);
        	fprintf(aux, "%d ", saida);
    		token = strtok(NULL, " ");
    		pos++;
   		}
   		fprintf(aux,"\n",saida);
	}
}

int main(int argc, char *argv[]){
	if(argc < 2){ 
		printf("ERRO - Numero de Parametros Invalido\n");
		getchar();
		exit(1);
	}
	
	return 0;
}
