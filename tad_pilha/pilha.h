#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

typedef int elem;

typedef struct bloco
{
    elem info;
    struct bloco *prox;
} No;

typedef struct
{
    No *topo;
} Pilha;


void Criar (Pilha*);
int Inserir(Pilha*, elem*);
int Remover(Pilha*, elem*);
int EstaVazia(Pilha*);
int Esvaziar(Pilha*);