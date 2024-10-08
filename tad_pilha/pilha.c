#include "pilha.h"

void Criar (Pilha* P)
{
    P->topo = NULL;
}

int Inserir(Pilha* P, elem* x)
{
    No *novo = (No*)malloc(sizeof(No));

    //Sem memoria
    if (novo == NULL) return 1;
    
    novo->info = *x;
    novo->prox = NULL;

    //Se a pilha está vazia
    if (EstaVazia(P)) P->topo = novo;

    //Se a pilha ja tem elementos
    else
    {
        novo->prox = P->topo;
        P->topo = novo;
    }
    
    return 0;
}

int Remover(Pilha *P, elem *x)
{
    No *temp = P->topo;
    
    //Se a pilha esta vazia
    if (EstaVazia(P)) return 1; 

    //Se a pilha ja tem elementos
    *x = temp->info;
    P->topo = P->topo->prox;
    
    free(temp);

    return 0;
    

}

int EstaVazia(Pilha *P)
{
    return (P->topo == NULL) ? 1 : 0;
}

int Esvaziar(Pilha *P)
{
    
    //Se a pilha esta vazia
    if (EstaVazia(P)) return 1; 

    No *temp= P->topo;

    while(!EstaVazia(P))
    {
        P->topo = P->topo->prox;
        free(temp);
        temp = P->topo;
    }    

    return 0;
}

/*
Criar
Inserir
Remover
EstaVazia
Esvaziar
*/
