#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50         // define o tamanho máximo para o nome de um usuário
#define MAX_APELIDO 10      // define o tamanho máximo para o apelido de um usuário
#define MAX_MENSAGEM 100    // define o tamanho máximo de uma mensagem

#define TRUE 1
#define FALSE 0

typedef struct Mensagem {
    char conteudo[MAX_MENSAGEM];   
    char remetente[MAX_APELIDO];   
    struct Mensagem *proxima;
} Mensagem;

typedef struct {
    Mensagem *topo;
} PilhaMensagens;

typedef struct Pedido {
    struct Usuario* solicitante;
    struct Pedido *proximo;
} Pedido;

typedef struct {
    Pedido *inicio, *fim;
} FilaPedidos;

typedef struct Amigo {
    struct Usuario *usuario;
    struct Amigo *proximo;
} Amigo;

typedef struct ListaAmigos {
    Amigo *inicio, *fim;
} ListaAmigos;

typedef struct Usuario {
    char nome[MAX_NOME];           
    char apelido[MAX_APELIDO];     // apelido unico
    ListaAmigos *amigos;           
    PilhaMensagens *mensagens;     
    FilaPedidos *pedidos;          
    struct Usuario *proximo;
} Usuario;

// Lista principal do programa
typedef struct {
    Usuario *inicio, *fim;
} ListaUsuarios;

// Inicializam as estruturas dinâmicas
void criarPilhaMensagens(PilhaMensagens *pilha);
void criarFilaPedidos(FilaPedidos *fila);
void criarListaUsuarios(ListaUsuarios *lista);
void criarListaAmigos(ListaAmigos *lista);

// Verificam se as estruturas estão vazias
int pilhaMensagensVazia(PilhaMensagens *pilha);
int filaPedidosVazia(FilaPedidos *fila);
int listaUsuariosVazia(ListaUsuarios *lista);
int listaAmigosVazia(ListaAmigos *lista);

// Funções auxiliares para lidar com os nós (usuários) da lista principal
int adicionarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char apelido[MAX_APELIDO]);
Usuario* encontrarUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]);
int cadastrarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char [MAX_APELIDO]);

// Função auxiliar que verifica se um usuário é amigo de outro
int saoAmigos(Usuario *remetente, Usuario *destinatario);

// Funções de usuário
int enviarMensagem(Usuario *remetente, Usuario *destinatario, char mensagem[MAX_MENSAGEM]);
int lerMensagens(Usuario *usuario);
int solicitarParceria(Usuario *solicitante, Usuario *destinatario);
void avaliarPedidosParceria(Usuario *usuario);
void sugerirParcerias(ListaUsuarios *lista, Usuario *usuario);
void mostrarAmigos(Usuario *usuario);
int removerAmigo(ListaUsuarios *lista, Usuario *usuario, char apelido[MAX_APELIDO]);

// Funções de administrador
void listarUsuarios(ListaUsuarios *lista);
int removerUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]);
void reinicializarSistema(ListaUsuarios *lista);
