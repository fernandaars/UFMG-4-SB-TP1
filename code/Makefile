# Varíaveis e Arquivos
CC = gcc
DEPENDENCIAS_M2 = LISTA.h GRAFO.h FLUXO.h main.c
OBJETOS_M2 = main.o LISTA.o GRAFO.o FLUXO.o

DEPENDENCIAS_R2 = LISTA.h GRAFO.h FLUXO.h main.c
OBJETOS_R2 = main.o LISTA.o GRAFO.o FLUXO.o

DEPENDENCIAS_S2 = LISTA.h GRAFO.h FLUXO.h main.c
OBJETOS_S2 = main.o LISTA.o GRAFO.o FLUXO.o

DEPENDENCIAS_M4 = LISTA.h GRAFO.h FLUXO.h main.c
OBJETOS_M4 = main.o LISTA.o GRAFO.o FLUXO.o

# Compilação do Simulador
%.o: %.c $(DEPENDENCIAS_M2)
	$(CC) -c -o $@ $<
M2: $(OBJETOS_M2)
	gcc -o $@ $^ -lm -Wall -Wextra -Werror -std=c99

# Compilação do Linker
%.o: %.c $(DEPENDENCIAS_R2)
	$(CC) -c -o $@ $<
R2: $(OBJETOS_R2)
	gcc -o $@ $^ -lm -Wall -Wextra -Werror -std=c99

# Compilação do Montador
%.o: %.c $(DEPENDENCIAS_S2)
	$(CC) -c -o $@ $<
S2: $(OBJETOS_S2)
	gcc -o $@ $^ -lm -Wall -Wextra -Werror -std=c99

# Compilação do Editor de Macros
%.o: %.c $(DEPENDENCIAS_M4)
	$(CC) -c -o $@ $<
M4: $(OBJETOS_M4)
	gcc -o $@ $^ -lm -Wall -Wextra -Werror -std=c99