#include <stdio.h>
#include <stdlib.h>

typedef elem int;

typedef struct
{
    no *topo;
} Pilha;

typedef struct bloco
{
    elem info;
    struct bloco *prox;
}no;

void Criar (Pilha* P);
int Inserir(Pilha* P, elem* x);
int Remover(Pilha *P, elem *x);
int EstaVazia(Pilha *P);