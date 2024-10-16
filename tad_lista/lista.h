#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef int chave;

typedef struct bloco
{
	elem info;
	chave indice;
	struct bloco *prox, *ant;
} No;

typedef struct
{
	No *ini, *fim;
} Lista;
