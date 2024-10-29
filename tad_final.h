#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50       // tamanho max do nome do usuario
#define MAX_APELIDO 10    // tamanho max do apelido do usuario
#define MAX_MENSAGEM 100  // tamanho max da mensagem

#define TRUE 1            // definicao pra verdadeiro
#define FALSE 0           // definicao pra falso

// estrutura pra guardar cada mensagem com o conteudo e quem mandou
typedef struct Mensagem {
    char conteudo[MAX_MENSAGEM];   // texto da mensagem
    char remetente[MAX_APELIDO];   // quem enviou a mensagem
    struct Mensagem *proxima;      // proxima mensagem na pilha
} Mensagem;

// estrutura pra gerenciar a pilha das mensagens
typedef struct {
    Mensagem *topo;   // topo da pilha
} PilhaMensagens;

// estrutura pra guardar pedidos de amizade
typedef struct Pedido {
    struct Usuario* solicitante;   // usuario que pediu amizade
    struct Pedido *proximo;        // proximo pedido
} Pedido;

// estrutura pra gerenciar fila dos pedidos de amizade
typedef struct {
    Pedido *inicio, *fim;   // inicio e fim da fila dos pedidos
} FilaPedidos;

// estrutura que guarda cada amigo de um usuario
typedef struct Amigo {
    struct Usuario *usuario;   // amigo do usuario
    struct Amigo *proximo;     // proximo amigo na lista
} Amigo;

// estrutura pra lista de amigos
typedef struct ListaAmigos {
    Amigo *inicio, *fim;   // inicio e fim da lista de amigos
} ListaAmigos;

// estrutura de cada usuario no sistema
typedef struct Usuario {
    char nome[MAX_NOME];           // nome do usuario
    char apelido[MAX_APELIDO];     // apelido unico
    ListaAmigos *amigos;           // lista dos amigos do usuario
    PilhaMensagens *mensagens;     // pilha de mensagens do usuario
    FilaPedidos *pedidos;          // fila de pedidos de amizade
    struct Usuario *proximo;       // proximo usuario na lista
} Usuario;

// estrutura pra lista de todos usuarios no sistema
typedef struct {
    Usuario *inicio, *fim;   // inicio e fim da lista de usuarios
} ListaUsuarios;

// funcoes pra gerenciamento do sistema
void criarPilhaMensagens(PilhaMensagens *pilha);
int pilhaMensagensVazia(PilhaMensagens *pilha);
void criarFilaPedidos(FilaPedidos *fila);
int filaPedidosVazia(FilaPedidos *fila);
void criarListaUsuarios(ListaUsuarios *lista);
int listaUsuariosVazia(ListaUsuarios *lista);
void criarListaAmigos(ListaAmigos *lista);
int listaAmigosVazia(ListaAmigos *lista);
int adicionarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char apelido[MAX_APELIDO]);
Usuario* encontrarUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]);
int cadastrarUsuario(ListaUsuarios *lista, char *nome, char *apelido);
int saoAmigos(Usuario *remetente, Usuario *destinatario);
int enviarMensagem(Usuario *remetente, Usuario *destinatario, char mensagem[MAX_MENSAGEM]);
int lerMensagens(Usuario *usuario);
void listarUsuarios(ListaUsuarios *lista);
void reinicializarSistema(ListaUsuarios *lista);
int solicitarParceria(Usuario *solicitante, Usuario *destinatario);
void avaliarPedidosParceria(Usuario *usuario);
void sugerirParcerias(ListaUsuarios *lista, Usuario *usuario);
void mostrarAmigos(Usuario *usuario);
int removerAmigo(ListaUsuarios *lista, Usuario *usuario, char apelido[MAX_APELIDO]);
int removerUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]);
