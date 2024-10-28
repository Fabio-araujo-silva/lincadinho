#include "usuario.h"

void Criar_Pilha_de_Mensagens(Pilha_de_mensagens *PM) 
{
    PM->topo = NULL;
}

int isEmpty_Pilha_de_Mensagens(Pilha_de_mensagens *PM) 
{
    return (PM->topo == NULL ? True : False);
}

void Criar_Fila_de_Pedidos(Fila_de_Pedidos *FP) 
{
    FP->inf = NULL;
    FP->sup = NULL;
}

int isEmpty_Fila_de_Pedidos(Fila_de_Pedidos *FP) 
{
    return (FP->inf == NULL ? True : False);
}

void Criar_ListaUsuario(ListaUsuario* LU) 
{
    LU->inf = NULL;
    LU->sup = NULL;
}

int isEmpty_ListaUsuario(ListaUsuario *LU) 
{
    return (LU->inf == NULL ? True : False);
}

void Criar_ListaAmigos(ListaAmigos * LA) 
{
    LA->inf = NULL;
    LA->sup = NULL;
}

int isEmpty_ListaAmigos(ListaAmigos *LA) 
{
    return (LA->inf == NULL ? True : False);
}

int Adicionar_Usuario_Fim(ListaUsuario *LU, char nome[MAX_caracter_nome], char apelido[MAX_caracter_apelido]) 
{
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    if(novo == NULL)
    {
        return 1;
    }
    
    strpcy(novo->nome, nome);
    strcpy(novo->apelido, apelido);

    ListaAmigos *L;
    Criar_ListaAmigos(L);
    novo->lista_amigos = L;

    Pilha_de_mensagens* P;
    Criar_Pilha_de_Mensagens(P);
    novo->pilha_de_mensagens = P;

    Fila_de_Pedidos* F;
    Criar_Fila_de_Pedidos(F);
    novo->fila_de_pedidos = F;
    
    novo->prox = NULL;

    if(isEmpty_ListaUsuario(LU))
    {
        LU->inf = novo;
    }

    LU->sup->prox = novo;
    LU->sup = novo;

    return 0;
}

// Esta função retorna um ponteiro para um usuário dado seu apelido
Usuario* Encontrar(ListaUsuario *LU, char apelido[MAX_caracter_apelido])
{
    // Retorna um ponteiro nulo caso não haja usuários
    if(isEmpty_ListaUsuario(LU))
    {
        return NULL;
    }

    // Itera sobre a lista de usuários até encontrar o usuário com o apelido dado
    Usuario *temp = LU->inf;
    // Lembre-se que strcmp(<str1>, <str2>) retorna 0 se str1 == str2
    while(temp != NULL && strcmp(temp->apelido, apelido) != 0)
    {
        temp = temp->prox;
    }

    // Note que caso o usuário procurado não estiver na lista, a função retorna NULL
    return (temp);
}

// Esta é uma função auxiliar para tratar o caso em que um remetente não é amigo de seu destinatário
int Sao_Amigos(Usuario *remetente, Usuario *destinatario) 
{
    // Itera sobre a lista de amigos procurando pelo apelido do destinatario
    Amigo *temp = remetente->lista_amigos->inf;
    while(temp != NULL && strcmp(temp->conexao->apelido, destinatario->apelido) != 0)
    {
        temp = temp->prox;
    }

    // Retorna 0 se temp == NULL e 1 se temp != NULL
    return (temp != NULL);
}

int Enviar_Mensagem(ListaUsuario *LU, Usuario* remetente, char apelido_destinatario[MAX_caracter_apelido], char mensagem[MAX_caracter_mensagem])
{
    Usuario *destinatario = Encontrar(LU, apelido_destinatario);
    
    if (destinatario == NULL || !Sao_Amigos(remetente, destinatario)) 
    {
        // Nao sao amigos ou o destinatario nao existe
        return 1;
    }

    Mensagem *nova_mensagem = (Mensagem *)malloc(sizeof(Mensagem));
    if (nova_mensagem == NULL) 
    {
        // Sem memoria
        return 1;
    }
    
    // Adiciona a nova mensagem à pilha de mensagens do destinarário
    strcpy(nova_mensagem->mensagem, mensagem);
    nova_mensagem->prox = destinatario->pilha_de_mensagens->topo;
    destinatario->pilha_de_mensagens->topo = nova_mensagem;
    
    // Deu tudo certo
    return 0;
}

int Ler_Mensagem(Usuario *usuario) 
{
    if(isEmpty_Pilha_de_Mensagens(usuario->pilha_de_mensagens))
    {
        return 1;
    }

    // Mostra a mensagem e popa ela
    printf("%s\n", usuario->pilha_de_mensagens->topo->mensagem);
    Mensagem *aux = usuario->pilha_de_mensagens->topo;
    usuario->pilha_de_mensagens->topo = usuario->pilha_de_mensagens->topo->prox;
    free(aux);

    return 0;
}
