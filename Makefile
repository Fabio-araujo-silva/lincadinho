# Definindo o compilador e as flags de compilação
CC = gcc
CFLAGS = -Wall

# Alvo principal para compilar tudo
all: programa

# Compilando o executável `programa` a partir dos objetos Main.o e lincadinhos.o
programa: Main.o lincadinho.o
	$(CC) $(CFLAGS) -o programa Main.o lincadinho.o

# Compilar o arquivo objeto Main.o a partir do fonte Main.c
Main.o: Main.c lincadinho.h
	$(CC) $(CFLAGS) -c Main.c

# Compilar o arquivo objeto lincadinho.o a partir do fonte lincadinho.c
lincadinho.o: lincadinho.c lincadinho.h
	$(CC) $(CFLAGS) -c lincadinho.c

# Alvo para rodar o programa
run: all
	./programa

# Limpar os arquivos compilados para recompilar do zero
clean:
	rm -f programa *.o
