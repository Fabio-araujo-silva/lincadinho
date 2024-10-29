#include "tad_final.h"

void criarPilhaMensagens(PilhaMensagens *pilha) {
    pilha->topo = NULL;
}

int pilhaMensagensVazia(PilhaMensagens *pilha) {
    return (pilha->topo == NULL ? TRUE : FALSE);
}

void criarFilaPedidos(FilaPedidos *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int filaPedidosVazia(FilaPedidos *fila) {
    return (fila->inicio == NULL ? TRUE : FALSE);
}

void criarListaUsuarios(ListaUsuarios *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int listaUsuariosVazia(ListaUsuarios *lista) {
    return (lista->inicio == NULL ? TRUE : FALSE);
}

void criarListaAmigos(ListaAmigos *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

int listaAmigosVazia(ListaAmigos *lista) {
    return (lista->inicio == NULL ? TRUE : FALSE);
}

int adicionarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char apelido[MAX_APELIDO]) {
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    if (novo == NULL)
        return 1;

    strcpy(novo->nome, nome);
    strcpy(novo->apelido, apelido);

    novo->amigos = (ListaAmigos*) malloc(sizeof(ListaAmigos));
    criarListaAmigos(novo->amigos);

    novo->mensagens = (PilhaMensagens*) malloc(sizeof(PilhaMensagens));
    criarPilhaMensagens(novo->mensagens);

    novo->pedidos = (FilaPedidos*) malloc(sizeof(FilaPedidos));
    criarFilaPedidos(novo->pedidos);

    novo->proximo = NULL;

    if (listaUsuariosVazia(lista)) {
        lista->inicio = lista->fim = novo;
    } else {
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    return 0;
}

Usuario* encontrarUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]) {
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->apelido, apelido) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

int cadastrarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char apelido[MAX_APELIDO]) {
    if (encontrarUsuario(lista, apelido) != NULL) {
        return 1;
    } else if (adicionarUsuario(lista, nome, apelido) == 0) {
        return 0;
    } else {
        return 2;
    }
}

int saoAmigos(Usuario *remetente, Usuario *destinatario) {
    Amigo *atual = remetente->amigos->inicio;
    while (atual != NULL) {
        if (atual->usuario == destinatario)
            return TRUE;
        atual = atual->proximo;
    }
    return FALSE;
}

int enviarMensagem(Usuario *remetente, Usuario *destinatario, char mensagem[MAX_MENSAGEM]) {
    if (!saoAmigos(remetente, destinatario))
        return 1;

    Mensagem *nova = (Mensagem*) malloc(sizeof(Mensagem));
    if (nova == NULL)
        return 1;

    strcpy(nova->conteudo, mensagem);
    nova->proxima = destinatario->mensagens->topo;
    destinatario->mensagens->topo = nova;
    return 0;
}

int lerMensagens(Usuario *usuario) {
    if (pilhaMensagensVazia(usuario->mensagens))
        return 1;

    Mensagem *atual;
    while (usuario->mensagens->topo != NULL) {
        atual = usuario->mensagens->topo;
        printf("Mensagem: %s\n", atual->conteudo);
        usuario->mensagens->topo = atual->proxima;
        free(atual);
    }
    return 0;
}

void listarUsuarios(ListaUsuarios *lista) {
    if (listaUsuariosVazia(lista)) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Apelido: %s\n", atual->nome, atual->apelido);
        atual = atual->proximo;
    }
}

void reinicializarSistema(ListaUsuarios *lista) {
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        Usuario *prox = atual->proximo;

        while (atual->mensagens->topo != NULL) {
            Mensagem *msg = atual->mensagens->topo;
            atual->mensagens->topo = msg->proxima;
            free(msg);
        }
        free(atual->mensagens);

        while (atual->pedidos->inicio != NULL) {
            Pedido *pedido = atual->pedidos->inicio;
            atual->pedidos->inicio = pedido->proximo;
            free(pedido);
        }
        free(atual->pedidos);

        while (atual->amigos->inicio != NULL) {
            Amigo *amigo = atual->amigos->inicio;
            atual->amigos->inicio = amigo->proximo;
            free(amigo);
        }
        free(atual->amigos);
        
        free(atual);
        atual = prox;
    }
    lista->inicio = lista->fim = NULL;
    printf("Sistema reinicializado.\n");
}

int solicitarParceria(Usuario *solicitante, Usuario *destinatario) {
    if (saoAmigos(solicitante, destinatario))
        return 1;

    Pedido *novoPedido = (Pedido*) malloc(sizeof(Pedido));
    if (novoPedido == NULL)
        return 1;

    novoPedido->solicitante = solicitante;
    novoPedido->proximo = NULL;

    if (filaPedidosVazia(destinatario->pedidos)) {
        destinatario->pedidos->inicio = destinatario->pedidos->fim = novoPedido;
    } else {
        destinatario->pedidos->fim->proximo = novoPedido;
        destinatario->pedidos->fim = novoPedido;
    }
    return 0;
}

void avaliarPedidosParceria(Usuario *usuario) {
    if (filaPedidosVazia(usuario->pedidos)) {
        printf("Nenhum pedido de parceria.\n");
        return;
    }
    Pedido *atual = usuario->pedidos->inicio;
    while (atual != NULL) {
        char resposta;
        printf("Pedido de %s (%s). Aceitar? (S/N): ", atual->solicitante->nome, atual->solicitante->apelido);
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            Amigo *novoAmigo = (Amigo*) malloc(sizeof(Amigo));
            if (novoAmigo == NULL) {
                printf("Erro ao aceitar parceria.\n");
                break;
            }
            novoAmigo->usuario = atual->solicitante;
            novoAmigo->proximo = NULL;

            if (listaAmigosVazia(usuario->amigos)) {
                usuario->amigos->inicio = usuario->amigos->fim = novoAmigo;
            } else {
                usuario->amigos->fim->proximo = novoAmigo;
                usuario->amigos->fim = novoAmigo;
            }

            Amigo *novoAmigoSolicitante = (Amigo*) malloc(sizeof(Amigo));
            if (novoAmigoSolicitante == NULL) {
                printf("Erro ao aceitar parceria.\n");
                break;
            }
            novoAmigoSolicitante->usuario = usuario;
            novoAmigoSolicitante->proximo = NULL;

            if (listaAmigosVazia(atual->solicitante->amigos)) {
                atual->solicitante->amigos->inicio = atual->solicitante->amigos->fim = novoAmigoSolicitante;
            } else {
                atual->solicitante->amigos->fim->proximo = novoAmigoSolicitante;
                atual->solicitante->amigos->fim = novoAmigoSolicitante;
            }
            printf("Parceria aceita com %s.\n", atual->solicitante->nome);
        }
        Pedido *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    usuario->pedidos->inicio = usuario->pedidos->fim = NULL;
}

void sugerirNovasParcerias(ListaUsuarios *lista, Usuario *usuario) {
    if (listaUsuariosVazia(lista)) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }
    int encontrou = 0;
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        if (atual != usuario && !saoAmigos(usuario, atual)) {
            printf("Sugestão de parceria: %s (%s)\n", atual->nome, atual->apelido);
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou)
        printf("Nenhuma sugestão disponível.\n");
}

void mostrarAmigos(Usuario *usuario) {
    if (listaAmigosVazia(usuario->amigos)) {
        printf("%s não tem amigos ainda.\n", usuario->nome);
        return;
    }

    printf("Amigos de %s:\n", usuario->nome);
    Amigo *atual = usuario->amigos->inicio;
    while (atual != NULL) {
        printf(" - %s (apelido: %s)\n", atual->usuario->nome, atual->usuario->apelido);
        atual = atual->proximo;
    }
}
