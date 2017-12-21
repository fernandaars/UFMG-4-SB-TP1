/*
Nome: S2.c
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Montador da Linguagem LS2 para a Linguagem LM2
*/

// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Bibliotecas Próprias
#include "S2.h"

// Definições
#define DEBUG 0

unsigned whitespace_offset(char *line) {
    unsigned i = 0;
    while (line[i] == ' ')
        i++;
    return i;
}

unsigned mapeia(char *string){
	if (!strcmp(string,"END")) return  0;
    if (!strcmp(string,"LAD")) return  1;
    if (!strcmp(string,"SAD")) return  2;
    if (!strcmp(string,"ADD")) return  3;
    if (!strcmp(string,"SUB")) return  4;
    if (!strcmp(string,"INP")) return  5;
    if (!strcmp(string,"OUT")) return  6;
    if (!strcmp(string,"JMP")) return  7;
    if (!strcmp(string,"JGZ")) return  8;
    if (!strcmp(string,"JLZ")) return  9;
    if (!strcmp(string,"JZE")) return 10;
    if (!strcmp(string,"HLT")) return 11;
    if (!strcmp(string,"LXD")) return 12;
    if (!strcmp(string,"SXD")) return 13;
    if (!strcmp(string,"LAX")) return 14;
    if (!strcmp(string,"SAX")) return 15;
    if (!strcmp(string,"LCD")) return 16;
    if (!strcmp(string,"JCC")) return 17;
    if (!strcmp(string,"CAL")) return 18;
    if (!strcmp(string,"RET")) return 19;
    if (!strcmp(string,"LAI")) return 20;
    if (!strcmp(string,"SAI")) return 21;
    if (!strcmp(string,"DOB")) return 22;
    if (!strcmp(string,"MET")) return 23;
    if (!strcmp(string,"JPA")) return 24;
    if (!strcmp(string,"DA"))  return 50;
    if (!strcmp(string,"DC"))  return 51;
    if (!strcmp(string,"DS"))  return 52;
	
    return INVALIDO;
}

bool analisaLinha(char *wline, unsigned n, char *label, char inst[TAM_INSTRUC], char *param) {
    char *line = wline + whitespace_offset(wline);
    char tokens[3][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    sscanf(line, "%[a-zA-Z] %[a-zA-Z] %[-a-zA-Z0-9]",
           tokens[0], tokens[1], tokens[2]);

    unsigned lens[3] = {
        strlen(tokens[0]),
        strlen(tokens[1]),
        strlen(tokens[2])
    };

    if (lens[0] == 0) return false;

    *label = '\0';
    *param = '\0';
    if (lens[0] == 1) {
        *label = *tokens[0];
        if (lens[1] == 3 || lens[1] == 2) {
            strcpy(inst, tokens[1]);
        } else {
            exit(1);
        }

        strcpy(param, tokens[2]);
    } else if (lens[0] == 3 || lens[0] == 2) {
        // Unlabeled

        if (lens[0] == 3 || lens[0] == 2) {
            strcpy(inst, tokens[0]);
        } else {
            exit(1);
        }

        strcpy(param, tokens[1]);
    }

    return true;
}

void preencheSimbolos(FILE *input, FILE *output, tabelaDeSimbolo tabela) {
    char label;
    char param[16];
    char linha[TAM_LINHA] = "";
    char inst[TAM_INSTRUC] = "";

    unsigned n = 1, pc = 0;
    while(fgets(linha, TAM_LINHA, input) != NULL){

        if (analisaLinha(linha, n, &label, inst, param)) {
            if (label != '\0') 
                tabela[label].offset = pc;
                
            if (!strcmp(inst, "DC") || !strcmp(inst, "DA")){
                pc += 1;
            } else {
                if (strcmp(inst, "DS")) {
                    pc += atoi(param);
                } else {
                    if (label != '\0')
                        fprintf(output, "%c %d\n", label, pc);
                    pc += 2;
                }
            }

            if (DEBUG) printf("S2: Simbolo '%c' guardado na tabela \n", label);
        }
    }

    fprintf(output, "#\n");
}

void montador(FILE *input, FILE *output, tabelaDeSimbolo tabela) {
    
    int num;
    bool fim = false;
    char label, param[16];
    char linha[TAM_LINHA] = "";
    char inst[TAM_INSTRUC] = "";
    unsigned i, n, x, oper, endereco, pc = 0;

    n = 1;
    while(fgets(linha, TAM_LINHA, input) != NULL && !fim){
        if (!analisaLinha(linha, n, &label, inst, param)) continue;

        if (DEBUG) printf("%s", linha);
        oper = mapeia(inst);

        if (oper == 0){
            if(!strcmp(inst, "END")) fim = true;
            if(!strcmp(inst, "DC")){ 
                pc += 1; num = atoi(param);
                fprintf(output, "%d\n", num);
            }
            if(!strcmp(inst, "DA")){
                pc += 1;
                if (tabela[param[0]].offset != INVALIDO) {
                    endereco = tabela[param[0]].offset;
                    fprintf(output, "* %d\n", endereco);
                } else {
                    fprintf(stderr, "ERRO EM S2: '%c' nao encontrado (linha %u)\n", param[0], n);
                    exit(1);
                }
            }
            if(!strcmp(inst, "DS")){
                num = atoi(param);
                pc += n;
                int i;
                for (i = 0; i < num; i++)
                    fprintf(output, "0%s", i != num-1 ? "\n" : "");
                fprintf(output, "\n");
            }
        } else {
            pc += 2;

            if (param[0] != '\0') {
                if (strcmp(inst, "CAL")) {
                    fprintf(output, "! %c\n", param[0]);
                } else if (tabela[param[0]].offset != INVALIDO) {
                    endereco = tabela[param[0]].offset - pc;
                    fprintf(output, "%u %d\n", oper, endereco);
                } else {
                    exit(1);
                }
            } else {
                fprintf(output, "%u 0\n", oper);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    confereParametros("S2", argc, 2);

    int i;
    FILE *input, *output;
    aberturaSegura("S2", input, argv[1], "r");
    aberturaSegura("S2", output, argv[2], "w");

    tabelaDeSimbolo tabela;
    for (i = 0; i < TAM_TABELA; i++) {
        tabela[i].offset = INVALIDO;
        tabela[i].type = INVALIDO;
    }

    preencheSimbolos(input, output, tabela);
    fseek(input, 0, SEEK_SET);
    montador(input, output, tabela);

    fclose(input);
    fclose(output);
    printf("S2: Arquivo montado! \n");

    return 0;
}
