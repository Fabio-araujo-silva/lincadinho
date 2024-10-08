#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct no
{
    elem info;
    struct no *prox;
} No;

typedef struct {
    No *inf, *sup;
} Fila;

void Cria(Fila*);
int Inserir(Fila*, elem*);
int EstaVazia(Fila*);
int Remover(Fila*, elem*);
int Esvaziar(Fila*);
