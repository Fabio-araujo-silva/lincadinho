#include <stdio.h>
#include "fila.h"

void Cria(Fila* F) {
  F->inf = NULL;
  F->sup = NULL;
}

int Inserir(Fila* F, elem* x) {
  Node *novo = (Node*) malloc(sizeof(Node));
  if(novo != NULL) {
    novo->info = *x;
    novo->prox = 

    
    return 0;
  }
  return 1;
}

Criar
Inserir
Remover
EstaVazia
Esvaziar
