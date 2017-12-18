/*
Nome: R2.c
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Linker de Arquivos em Linguagem LR2 e LM2
*/

// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Bibliotecas Próprias
#include "R2.h"

// Definições
#define DEBUG 0

void linker(FILE *input, unsigned idx, unsigned mapaDeIdx[],
                  Entrada tabelaDeSimbolos[]) {
    
    int inst, param;
    bool header = true;
    unsigned n, offset, pc;
    offset = pc = 0;
    char label, linha[TAM_LINHA] = "";

    n = 1;
    while(fgets(linha, TAM_LINHA, input) != NULL){
        if (header){
            if (linha[0] == '#'){
                header = false;
                continue;
            }
            sscanf(linha, "%c %u", &label, &offset);
            if (tabelaDeSimbolos[label].offset == INVALIDO) {
                Entrada entrada = {offset, idx};
                tabelaDeSimbolos[label] = entrada;
            }else{
                fprintf(stderr, "ERRO EM R2 - DEFINICAO INCORRETA\n");
            }
        }else{
        	bool flag = true;
        	switch(linha[0]){
        		case '!':
        			pc += 2; flag = false;
        		case '*':
        			pc += 1;
        		default:
        			pc += 2; flag = false;
        	}
        	if(sscanf(linha, "%d %d", &inst, &param) != 2 && flag){
        		pc += 1;
        	}
        }
        n++;
    }

    mapaDeIdx[idx] = pc + (idx > 1 ? mapaDeIdx[idx-1] : 0);
}

int main(int argc, char **argv) {
	confereParametros("R2", argc, 3)
  
    unsigned i, n, inst, param, data, pc;
    unsigned enderecoDeCarregamento = atoi(argv[argc-1]);
    unsigned endereco, enderecoNovo;
    unsigned mapaDeIdx[argc-2];
    mapaDeIdx[0] = 0;

    bool header = true;
    char linha[TAM_LINHA] = "\0";
    char label;

    if(DEBUG) printf("R2: CARREGANDO A PARTIR DE %u\n", enderecoDeCarregamento);

    
    Entrada tabelaDeSimbolos[TAM_TABELA];
    for (i = 0; i < TAM_TABELA; i++)
        tabelaDeSimbolos[i].offset = INVALIDO;
        tabelaDeSimbolos[i].idx = INVALIDO;

    FILE *input, *output;
    aberturaSegura("R2", output, argv[argc-2], "w+");

    for (i = 1; i < (argc-2); i++) {
        aberturaSegura("R2", input, argv[i], "r");
        linker(input, i, mapaDeIdx, tabelaDeSimbolos);
        fclose(input);

        if(DEBUG) printf("R2: ARQUIVO %s LIDO\n", argv[i]);
    }

    for (i = 1; i < (argc-2); i++) {
        aberturaSegura("R2", input, argv[i], "r");

        header = true;
        n = 1;
        while(fgets(linha, TAM_LINHA, input) != NULL){
            switch(linha[0]){
            	case '#': 
            		if(header){
            			header = false; continue;
            		}
            		break;
            	case '*':
                	pc += 1;
                	sscanf(linha, "* %u", &endereco);
                	enderecoNovo = enderecoDeCarregamento+endereco+mapaDeIdx[i-1];
                	fprintf(output, "%u\n", enderecoNovo);

                	if(DEBUG) printf("R2: %u %u %u %u\n", endereco,
                       enderecoNovo, enderecoDeCarregamento, mapaDeIdx[i-1]);
                	break;

            	case '!':
                	pc += 2;
                	sscanf(linha, "! %c", &label);
                	Entrada aux = tabelaDeSimbolos[label];
                	if (aux.idx != INVALIDO) {
                    	enderecoNovo = aux.offset + mapaDeIdx[aux.idx-1] - pc;
						fprintf(output, "18 %d\n", enderecoNovo);

						if(DEBUG){
							printf("R2: %d %d %d\n", aux.offset, mapaDeIdx[aux.idx-1], pc);
                    		printf("R2: %c (=> %d (+= %d - %d))\n", label, enderecoNovo, mapaDeIdx[aux.idx-1], pc);
						}
					}else{
						fprintf(stderr, "ERRO EM R2: LABEL DESCONHECIDO '%c' (%s, linha %d).\n", label, argv[i], n);
                    	exit(1);
					}
					break;
                
                default:
                    if (sscanf(linha, "%d %d", &inst, &param) == 2) {
                		pc += 2;
                		fprintf(output, "%d %d\n", inst, param);
            		} else if (sscanf(linha, "%d", &data) == 1) {
                		pc += 1;
                		fprintf(output, "%d\n", data);
            		}

            }
            n++; 
        }

        fclose(input);
        if(DEBUG) printf("R2: %s foi linkado \n", argv[i]);
    }
    fclose(output);
    return 0;
}
