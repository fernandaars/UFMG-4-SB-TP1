#ifndef UTILS_H
#define UTILS_H

#define INVALIDO -1

#define TAM_LINHA 64
#define TAM_INSTRUC 16
#define TAM_TABELA 256
#define TAM_MEMORIA 4096

#define NUM_REGISTRADORES 4

#define aberturaSegura(modulo, ponteiro, nome, modo) \
ponteiro = fopen(nome, modo); \
if (ponteiro == NULL) { \
    fprintf(stderr, "ERRO EM %s: ARQUIVO %s NAO PODE SER ABERTO \n", modulo, nome); \
    exit(1); \
}

#define confereParametros(modulo, argc, num) \
if (argc <= num) { \
	fprintf(stderr,"ERRO EM %s: PARAMETROS INCORRETOS \n", modulo);\
	exit(1); \
}

#endif
