/*
Nome: S2.h
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Montador da Linguagem LS2 para a Linguagem LM2
*/

#ifndef S2_H
#define S2_H

// Bibliotecas Próprias
#include "utils.h"

typedef enum{ CONST, LABEL } SType;

typedef struct Simbolo{
    unsigned offset;
    SType type;
} Simbolo;

typedef Simbolo tabelaDeSimbolo[TAM_MEMORIA];

// Procedimentos e Funções
unsigned whitespace_offset(char*);
unsigned mapeia(char*);
bool analisaLinha(char*, unsigned, char*, char[TAM_INSTRUC], char*);
void preencheSimbolos(FILE*, FILE*, tabelaDeSimbolo);
void montador(FILE*, FILE*, tabelaDeSimbolo);
int main(int, char*[]);

#endif
