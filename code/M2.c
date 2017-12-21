/*
Nome: M2.c
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Simulador e Carregador de Arquivos em LM2
*/

// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>

// Bibliotecas Próprias
#include "M2.h"

// Definições
#define DEBUG 1

void simulador(int regitradores[], int memoria[], unsigned inicio, unsigned fim){
    int instrucao, code, param;

    int *pc = &regitradores[0];
    int *ac = &regitradores[1];
    int *rx = &regitradores[2];
    int *rc = &regitradores[3];

    *pc = inicio;
    while (*pc < TAM_MEMORIA && *pc < fim) {
        code = memoria[*pc];
        param = memoria[*pc+1];

        if (code == 0){ (*pc)++; }
        else{
            *pc += 2;
            param += *pc;

            switch(code){
            	case  1: *ac = memoria[param]; break;
            	case  2: memoria[param] = *ac; break;
            	case  3: *ac += memoria[param]; break;
            	case  4: *ac -= memoria[param]; break;
            	case  5: scanf("%d", &memoria[param]); break;
            	case  6: printf("%d\n", memoria[param]); break;
            	case  7: *pc = param; break;
            	case  8: *pc = (*ac >  0)? param : *pc; break;
            	case  9: *pc = (*ac <  0)? param : *pc; break;
            	case 10: *pc = (*ac == 0)? param : *pc; break;
            	case 11: exit(0); 
            	case 12: *rx = memoria[param]; break;
            	case 13: memoria[param] = *rx; break;
            	case 14: *ac = memoria[(*rx)++]; break;
            	case 15: memoria[(*rx)++] = *ac; break;
            	case 16: *rc = memoria[param]; break;
            	case 17: *pc = (((*rc)--) > 0)? param : *pc; break;
            	case 18: *rx = *pc; *pc = param; break;
            	case 19: *pc = *rx; break;
            	case 20: *ac = memoria[memoria[(*rx)++]]; break;
            	case 21: memoria[memoria[(*rx)++]] = *ac; break;
            	case 22: memoria[param] *= 2; *ac = memoria[param]; break;
            	case 23: memoria[param] /= 2; *ac = memoria[param]; break;
            	case 24: *pc = (*ac % 2 == 0)? param : *pc; break;
      			
      			default:
            		fprintf(stderr, "ERRO EM M2: CODIGO NAO SUPORTADO '%d' EM %d \n", code, *pc);
                	exit(1);
        	}
        }
    }
    printf("M2: Arquivo foi simulado! \n");
}

unsigned carregador(FILE *programa, int memoria[], unsigned inicio){
    unsigned code, i = inicio;
    while (fscanf(programa, "%d", &code) != EOF && i < TAM_MEMORIA)
        memoria[i++] = code;
    return i;
    printf("M2: Arquivo foi carregado! \n");
}

int main(int argc, char **argv) {
    confereParametros("M2", argc, 2)

    // Variáveis
    unsigned inicio, fim;
    int registradores[NUM_REGISTRADORES] = {0, 0, 0, 0};
    int memoria[TAM_MEMORIA];
    FILE *programa;

    aberturaSegura("M2", programa, argv[1], "r+");
    sscanf(argv[2], "%u", &inicio);

    fim = carregador(programa, memoria, inicio);
    simulador(registradores, memoria, inicio, fim);

    fclose(programa);
    return 0;
}