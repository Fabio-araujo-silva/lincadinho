#include "pilha.h"

void Criar (Pilha* P)
{
    P->topo = NULL;
}

int Inserir(Pilha* P, elem* x)
{
    no *novo = (no*)malloc(sizeof(no));

    //Sem memoria
    if (novo == null) return 1;
    
    novo->info = *x;
    novo->prox = NULL;

    //Se a pilha está vazia
    if EstaVazia(P) P->topo = novo;

    //Se a pilha ja tem elementos
    else
    {
        novo->prox = P->topo;
        P->topo = novo;
    }
    
    free(no);
    
    return 0;
}

int Remover(Pilha *P, elem *x)
{
    no *novo = (no*)malloc(sizeof(no));
    
    //Se a pilha esta vazia
    if (EstaVazia(P)) return 1; 

    //Se a pilha ja tem elementos
    no = P->topo;
    *x = no;
    P->topo = P->topo->prox;
    free(no);

    return 0;
    

}

int EstaVazia(Pilha *P)
{
    return (P->topo == NULL) ? 1 : 0;
}

int Esvaziar()
{
    no *novo = (no*)malloc(sizeof(no));
    
    //Se a pilha esta vazia
    if (EstaVazia(P)) return 1; 

    while(!EstaVazia(P))
    {
        no = P->topo;
        P->topo = P->topo->prox;
        free(no);
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
