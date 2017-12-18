#
#Nome: simulador.c
#Autor: Fernanda Aparecida Rodrigues Silva
#Disciplina: Software Básico
#Descrição: Makefile
#

# Varíaveis e Arquivos
CC = gcc
DEPENDENCIAS_M2 = utils.h M2.h M2.c
OBJETOS_M2 = M2.o

DEPENDENCIAS_R2 = utils.h R2.h R2.c
OBJETOS_R2 = R2.o

DEPENDENCIAS_S2 = utils.h S2.h S2.c
OBJETOS_S2 = S2.o

ALL: M2 R2 S2

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