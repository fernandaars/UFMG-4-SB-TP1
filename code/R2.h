/*
Nome: R2.h
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Linker de Arquivos em Linguagem LR2 e LM2
*/

#ifndef R2_H
#define R2_H

// Bibliotecas Próprias
#include "utils.h"

typedef struct Entrada{
    unsigned offset, idx;
} Entrada;

// Procedimentos e Funções
void linker(FILE*, unsigned, unsigned[], Entrada[]);

#endif
