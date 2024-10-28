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

///////////////////////////////////////////////////////////////////////
/// minha autoria (MAURO) deve estar errado usei gepeto para testar ///
///////////////////////////////////////////////////////////////////////
void Sugerir_Amigos(ListaUsuario *LU) {
    Usuario *remetente = LU->inf;

    // Percorre todos os usuários cadastrados
    while (remetente != NULL) {
        Usuario *destinatario = remetente->prox;

        // Comparar remetente com cada destinatario que está adiante na lista
        while (destinatario != NULL) {
            // Só sugere parceria se não forem amigos
            if (!Sao_Amigos(remetente, destinatario)) {
                // Verifica se possuem um amigo em comum
                Amigo *amigo1 = remetente->lista_amigos->inf;
                while (amigo1 != NULL) {
                    Amigo *amigo2 = destinatario->lista_amigos->inf;
                    while (amigo2 != NULL) {
                        if (strcmp(amigo1->conexao->apelido, amigo2->conexao->apelido) == 0) {
                            printf("Sugestão de nova parceria: %s e %s\n", remetente->apelido, destinatario->apelido);
                            break;
                        }
                        amigo2 = amigo2->prox;
                    }
                    amigo1 = amigo1->prox;
                }
            }
            destinatario = destinatario->prox;
        }
        remetente = remetente->prox;
    }
}

// Função para listar todos os usuários e seus parceiros de trabalho
void Listar_Usuarios(ListaUsuario *LU) {//2
    Usuario *usuario_atual = LU->inf;

    if (usuario_atual == NULL) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    printf("Pessoas e seus parceiros:\n");
    while (usuario_atual != NULL) {
        printf("%s (%s) com os parceiros seguintes:", usuario_atual->nome, usuario_atual->apelido);
        Amigo *parceiro_atual = usuario_atual->lista_amigos->inf;

        if (parceiro_atual == NULL) {
            printf(" Nenhum parceiro\n");
        } else {
            while (parceiro_atual != NULL) {
                printf(" %s", parceiro_atual->conexao->apelido);
                parceiro_atual = parceiro_atual->prox;
                if (parceiro_atual != NULL) printf(",");
            }
            printf("\n");
        }
        usuario_atual = usuario_atual->prox;
    }
    printf("Listagem completa!\n");
}

// Função para reinicializar o sistema, liberando memória de todas as estruturas
void ReinicializarSistema(ListaUsuario *LU) {//8
    Usuario *usuario_atual = LU->inf;

    while (usuario_atual != NULL) {
        // Libera a lista de amigos do usuário atual
        Amigo *parceiro_atual = usuario_atual->lista_amigos->inf;
        while (parceiro_atual != NULL) {
            Amigo *temp_amigo = parceiro_atual;
            parceiro_atual = parceiro_atual->prox;
            free(temp_amigo);
        }
        free(usuario_atual->lista_amigos);

        // Libera a pilha de mensagens do usuário atual
        Mensagem *mensagem_atual = usuario_atual->pilha_de_mensagens->topo;
        while (mensagem_atual != NULL) {
            Mensagem *temp_mensagem = mensagem_atual;
            mensagem_atual = mensagem_atual->prox;
            free(temp_mensagem);
        }
        free(usuario_atual->pilha_de_mensagens);

        // Libera a fila de pedidos do usuário atual
        Pedido *pedido_atual = usuario_atual->fila_de_pedidos->inf;
        while (pedido_atual != NULL) {
            Pedido *temp_pedido = pedido_atual;
            pedido_atual = pedido_atual->prox;
            free(temp_pedido);
        }
        free(usuario_atual->fila_de_pedidos);

        // Libera o usuário atual
        Usuario *temp_usuario = usuario_atual;
        usuario_atual = usuario_atual->prox;
        free(temp_usuario);
    }

    // Reinicia a lista de usuários
    LU->inf = NULL;
    LU->sup = NULL;

    printf("Sistema reinicializado.\n");
}

//3
int Solicitar_Parceria(ListaUsuario *LU, char apelido_solicitante[MAX_caracter_apelido], char apelido_destinatario[MAX_caracter_apelido]) {
    Usuario *solicitante = Encontrar(LU, apelido_solicitante);
    Usuario *destinatario = Encontrar(LU, apelido_destinatario);

    if (solicitante == NULL) {
        printf("Usuário solicitante '%s' não encontrado.\n", apelido_solicitante);
        return 1;
    }

    if (destinatario == NULL) {
        printf("Usuário destinatário '%s' não encontrado.\n", apelido_destinatario);
        return 1;
    }

    Pedido *novo_pedido = (Pedido *) malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        printf("Erro de memória ao criar pedido de parceria.\n");
        return 1;
    }

    novo_pedido->remetente = solicitante;
    novo_pedido->prox = NULL;

    if (isEmpty_Fila_de_Pedidos(destinatario->fila_de_pedidos)) {
        destinatario->fila_de_pedidos->inf = novo_pedido;
        destinatario->fila_de_pedidos->sup = novo_pedido;
    } else {
        destinatario->fila_de_pedidos->sup->prox = novo_pedido;
        destinatario->fila_de_pedidos->sup = novo_pedido;
    }

    printf("Pedido de parceria enviado de '%s' para '%s' com sucesso!\n", apelido_solicitante, apelido_destinatario);
    return 0;
}
