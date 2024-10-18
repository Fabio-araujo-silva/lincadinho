#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_caracter_nome 50
#define MAX_caracter_apelido 10

typedef struct usuario{
	char nome[MAX_caracter_nome];
	char apelido[MAX_caracter_apelido];
	struct usuario *prox;
	struct lista_amigos *lista_amigos;
} Usuario;

typedef struct amigo{
	Usuario *conexao;
	struct amigo *prox;
} Amigo;

typedef struct lista_amigos{
	Amigo *inf, *sup;
} ListaAmigos;

typedef struct lista_usuario{
	Usuario *inf, *sup;
} ListaUsuario;
