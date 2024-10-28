#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_caracter_nome 50
#define MAX_caracter_apelido 10
#define MAX_caracter_mensagem 100

#define True 1
#define False 0

typedef struct mensagem {
    char mensagem[MAX_caracter_mensagem];
    struct mensagem *prox;
} Mensagem;

typedef struct {
    Mensagem *topo;
} Pilha_de_mensagens;

typedef struct pedido {
    struct amigo* fonte;
} Pedido;

typedef struct {
    Pedido *inf, *sup;
} Fila_de_Pedidos;

typedef struct usuario{
	char nome[MAX_caracter_nome];
	char apelido[MAX_caracter_apelido];
	struct usuario *prox;
	struct lista_amigos *lista_amigos;
    Pilha_de_mensagens* pilha_de_mensagens;
    Fila_de_Pedidos* fila_de_pedidos;
} Usuario;

typedef struct amigo{
	Usuario *conexao;
	struct amigo *prox;
} Amigo;

typedef struct lista_amigos{
	Amigo *inf, *sup;
} ListaAmigos;

typedef struct lista_usuario{
	Usuario *inf, *sup;
} ListaUsuario;

void Criar_Pilha_de_Mensagens(Pilha_de_mensagens *PM);
int isEmpty_Pilha_de_Mensagens(Pilha_de_mensagens *PM);
void Criar_Fila_de_Pedidos(Fila_de_Pedidos *FP);
int isEmpty_Fila_de_Pedidos(Fila_de_Pedidos *FP);
void Criar_ListaUsuario(ListaUsuario* LU);
int isEmpty_ListaUsuario(ListaUsuario *LU);
void Criar_ListaAmigos(ListaAmigos * LA);
int isEmpty_ListaAmigos(ListaAmigos *LA);
int Adicionar_Usuario_Fim(ListaUsuario *LU, char nome[MAX_caracter_nome], char apelido[MAX_caracter_apelido]);
Usuario* Encontrar(ListaUsuario *LU, char apelido[MAX_caracter_apelido]);
int Sao_Amigos(Usuario *remetente, Usuario *destinatario);
int Enviar_Mensagem(ListaUsuario *LU, Usuario* remetente, char apelido_destinatario[MAX_caracter_apelido], char mensagem[MAX_caracter_mensagem]);
int Ler_Mensagem(Usuario *usuario);
