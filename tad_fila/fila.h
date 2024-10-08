#include <stdio.h>

typedef elem int

typedef stuct no 
{
    elem info;
    node *prox;
} 
No;

typedef struct {
    Node *inf, *sup;
} Fila;

void Cria(Fila*);
int Inserir(Fila*, elem*);
int EstaVazia(Fila*);
int Remover(Fila*, elem*);
int Esvaziar(Fila*);
