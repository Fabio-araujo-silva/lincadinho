#include <stdio.h>
#include <stdlib.h>

#define MAX_caracter_nome 50
#define MAX_caracter_apelido 10


typedef struct nousuario{
	char nome[MAX_caracter_nome];
	char apelido[MAX_caracter_apelido];
	//outras listas, pilhas e filas do usuario aqui	
	struct usuario *prox, *ant;
} NoUsuario;

typedef struct{
	NoUsuario *inf, *sup;
} ListaUsuarios;

typedef struct noamigo{
	int Id;
	struct noamigo *ant;
} NoAmigos;

typedef struct{
	NoAmigo *topo;
} PilhaAmigos;
