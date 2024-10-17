#include <stdio.h>
#include <stdlib.h>

#define MAX_caracter_nome 50
#define MAX_caracter_apelido 10


typedef struct nousuario{
	char nome[MAX_caracter_nome];
	char apelido[MAX_caracter_apelido];
	//outras listas, pilhas e filas do usuario aqui	
	struct nousuario *prox, *ant;
} NoUsuario;

typedef struct{
	NoUsuario *inf, *sup;
} ListaUsuarios;

typedef struct{
	NoAmigo *topo;
} PilhaAmigos;
