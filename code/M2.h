/*
Nome: M2.h
Autor: Fernanda Aparecida Rodrigues Silva
Disciplina: Software Básico
Descrição: Simulador e Carregador de Arquivos em LM2
*/

#ifndef M2_H
#define M2_H

// Bibliotecas Padrão
#include <stdio.h>

// Bibliotecas Próprias
#include "utils.h"

// Procedimentos e Funções
void simulador(int[], int[], unsigned, unsigned);
unsigned carregador(FILE*, int[], unsigned);

#endif
