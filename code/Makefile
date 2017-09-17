CC = gcc
DEPENDENCIAS = LISTA.h GRAFO.h FLUXO.h main.c
OBJETOS = main.o LISTA.o GRAFO.o FLUXO.o
%.o: %.c $(DEPENDENCIAS)
	$(CC) -c -o $@ $<
tp1: $(OBJETOS)
	gcc -o $@ $^ -lm -Wall -Wextra -Werror -std=c99
