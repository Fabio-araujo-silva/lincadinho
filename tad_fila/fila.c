#include "fila.h"

void Cria(Fila* F)
{
    F->inf = NULL;
    F->sup = NULL;
}

int Inserir(Fila* F, elem* x)
{
    No* novo = (No*) malloc(sizeof(No));
    if(novo != NULL)
    {
        novo->info = *x;
        novo->prox = NULL;
        if(F->inf == NULL)
            F->inf = novo;
        else
            F->sup->prox = novo;
        F->sup = novo;
        return 0;
    }
    return 1;
}

int EstaVazia(Fila* F)
{
    return (F->inf == NULL? 1 : 0);
}

int Remover(Fila* F, elem* x)
{
    if(!EstaVazia(F))
    {
        *x = F->inf->info;
        No* temp = F->inf;
        F->inf = F->inf->prox;
        if(F->inf == NULL)
            F->sup = NULL;
        free(temp);
        return 0;
    }
    return 1;
}

int Esvaziar(Fila* F)
{
    if(!EstaVazia(F))
    {
        No* temp = F->inf;
        while(temp != NULL)
        {
            F->inf = F->inf->prox;
            free(temp);
            temp = F->inf;
        }
        return 0;
    }
    return 1;
}
