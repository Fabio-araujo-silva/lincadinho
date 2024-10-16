#include "lista.h"

void Criar(Lista *L)
{
	L->ini = NULL;
	L->fim = NULL;
}

int Inserir(Lista *L, elem *x)
{
	No *p;
	p = (No*)malloc(sizeof(No));
	
	//erro de alocação
	if (p == NULL) return 1;
	
	//nao tem elementos
	if (!EstaVazia(L))
	{
		p->indice = 0;
		L->ini = p;
		L->fim = p;
		p->prox = NULL;
		p->ant = NULL;
		p->info = *x;
	}
	
	//tem elementos
	else
	{
		p->indice = p->ant->indice++;
		p->prox = NULL;
		p->ant = L->fim
		p->ant->prox = p;
		L->fim = p;
		p->info = *x;
	}

	return 0;
}

//criar
//inserir
//remover
//estavazia
//esvaziar
//procurar
