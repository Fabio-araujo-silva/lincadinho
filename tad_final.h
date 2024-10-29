/*
LISTA DE ERROS:

Cadastrar usuario:
0 - sucesso
1 - apelido ja usado
2 - erro ao cadastrar

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50       // Define o número máximo de caracteres para o nome do usuário
#define MAX_APELIDO 10    // Define o número máximo de caracteres para o apelido do usuário
#define MAX_MENSAGEM 100  // Define o número máximo de caracteres para uma mensagem

#define TRUE 1            // Define uma constante para verdadeiro
#define FALSE 0           // Define uma constante para falso

// Estrutura para armazenar mensagens em uma pilha de mensagens
typedef struct Mensagem {
    char conteudo[MAX_MENSAGEM];   // Conteúdo da mensagem
    struct Mensagem *proxima;      // Ponteiro para a próxima mensagem na pilha
} Mensagem;

// Estrutura para gerenciar a pilha de mensagens de um usuário
typedef struct {
    Mensagem *topo;   // Ponteiro para o topo da pilha de mensagens
} PilhaMensagens;

// Estrutura para armazenar pedidos de parceria em uma fila de pedidos
typedef struct Pedido {
    struct Usuario* solicitante;   // Usuário que enviou o pedido de parceria
    struct Pedido *proximo;        // Próximo pedido na fila
} Pedido;

// Estrutura para gerenciar a fila de pedidos de parceria de um usuário
typedef struct {
    Pedido *inicio, *fim;   // Ponteiros para o início e o fim da fila de pedidos
} FilaPedidos;

// Estrutura para armazenar cada amigo de um usuário
typedef struct Amigo {
    struct Usuario *usuario;   // Ponteiro para o usuário que é amigo
    struct Amigo *proximo;     // Próximo amigo na lista de amigos
} Amigo;

// Estrutura para gerenciar a lista de amigos de um usuário
typedef struct ListaAmigos {
    Amigo *inicio, *fim;   // Ponteiros para o início e o fim da lista de amigos
} ListaAmigos;

// Estrutura para representar cada usuário no sistema
typedef struct Usuario {
    char nome[MAX_NOME];           // Nome do usuário
    char apelido[MAX_APELIDO];     // Apelido único do usuário
    ListaAmigos *amigos;           // Lista de amigos do usuário
    PilhaMensagens *mensagens;     // Pilha de mensagens recebidas pelo usuário
    FilaPedidos *pedidos;          // Fila de pedidos de parceria pendentes
    struct Usuario *proximo;       // Próximo usuário na lista de usuários
} Usuario;

// Estrutura para gerenciar a lista de todos os usuários no sistema
typedef struct {
    Usuario *inicio, *fim;   // Ponteiros para o início e o fim da lista de usuários
} ListaUsuarios;

// Prototipação das funções para gerenciamento do sistema
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
void sugerirNovasParcerias(ListaUsuarios *lista, Usuario *usuario);
void mostrarAmigos(Usuario *usuario);
