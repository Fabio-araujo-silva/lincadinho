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
        return 2;

    strcpy(novo->nome, nome);
    strcpy(novo->apelido, apelido);

    novo->amigos = (ListaAmigos*) malloc(sizeof(ListaAmigos));
    if (novo->amigos == NULL) {
        free(novo);
        return 2;
    }
    criarListaAmigos(novo->amigos);

    novo->mensagens = (PilhaMensagens*) malloc(sizeof(PilhaMensagens));
    if (novo->mensagens == NULL) {
        free(novo->amigos);
        free(novo);
        return 2;
    }
    criarPilhaMensagens(novo->mensagens);

    novo->pedidos = (FilaPedidos*) malloc(sizeof(FilaPedidos));
    if (novo->pedidos == NULL) {
        free(novo->mensagens);
        free(novo->amigos);
        free(novo);
        return 2;
    }
    criarFilaPedidos(novo->pedidos);

    novo->proximo = NULL;

    if (listaUsuariosVazia(lista)) {
        lista->inicio = novo;
        lista->fim = novo;
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
    if (encontrarUsuario(lista, apelido) != NULL)
        return 1;
    else
        return adicionarUsuario(lista, nome, apelido);
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
    if (destinatario == NULL)
        return 3; // Destinatário não encontrado
    if (!saoAmigos(remetente, destinatario))
        return 1;

    Mensagem *nova = (Mensagem*) malloc(sizeof(Mensagem));
    if (nova == NULL)
        return 2;

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
    if (destinatario == NULL)
        return 2; // Destinatário não encontrado

    // Primeira coisa: verificar se já são amigos
    if (saoAmigos(solicitante, destinatario))
        return 1; // Já são amigos - retorna imediatamente

    // Verificar se o destinatário já tem um pedido do solicitante
    Pedido *anterior = NULL;
    Pedido *atual = solicitante->pedidos->inicio;
    
    while (atual != NULL) {
        // Comparação correta usando strcmp para comparar os apelidos
        if (strcmp(atual->solicitante->apelido, destinatario->apelido) == 0) {
            // Conexão automática se já houver um pedido pendente
            
            Amigo *novoAmigoDestinatario = (Amigo*) malloc(sizeof(Amigo));
            Amigo *novoAmigoSolicitante = (Amigo*) malloc(sizeof(Amigo));

            if (novoAmigoDestinatario == NULL || novoAmigoSolicitante == NULL) {
                free(novoAmigoDestinatario);
                free(novoAmigoSolicitante);
                return 3; // Erro de alocação
            }

            // Configura a conexão de amizade
            novoAmigoDestinatario->usuario = solicitante;
            novoAmigoDestinatario->proximo = NULL;

            novoAmigoSolicitante->usuario = destinatario;
            novoAmigoSolicitante->proximo = NULL;

            // Atualiza a lista de amigos do destinatário
            if (listaAmigosVazia(destinatario->amigos)) {
                destinatario->amigos->inicio = destinatario->amigos->fim = novoAmigoDestinatario;
            } else {
                destinatario->amigos->fim->proximo = novoAmigoDestinatario;
                destinatario->amigos->fim = novoAmigoDestinatario;
            }

            // Atualiza a lista de amigos do solicitante
            if (listaAmigosVazia(solicitante->amigos)) {
                solicitante->amigos->inicio = solicitante->amigos->fim = novoAmigoSolicitante;
            } else {
                solicitante->amigos->fim->proximo = novoAmigoSolicitante;
                solicitante->amigos->fim = novoAmigoSolicitante;
            }

            // Remove o pedido da fila de pedidos
            if (anterior == NULL) {
                destinatario->pedidos->inicio = atual->proximo;
                if (destinatario->pedidos->inicio == NULL) {
                    destinatario->pedidos->fim = NULL;  // Atualiza o fim se a fila ficou vazia
                }
            } else {
                anterior->proximo = atual->proximo;
                if (atual == destinatario->pedidos->fim) {
                    destinatario->pedidos->fim = anterior;
                }
            }

            free(atual);
            return 0;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    // Caso não haja um pedido pendente e não sejam amigos, adicionar um novo pedido
    Pedido *novoPedido = (Pedido*) malloc(sizeof(Pedido));
    if (novoPedido == NULL)
        return 3; // Erro de alocação

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
            // Verifica se já são amigos
            if (!saoAmigos(usuario, atual->solicitante)) {
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
            } else {
                printf("Vocês já são amigos.\n");
            }
        Pedido *temp = atual;
        atual = atual->proximo;
        free(temp);
        } else if(resposta == 'N' || resposta == 'n') {
            printf("Parceria recusada.\n");
            Pedido *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        else{
            printf("Comando invalido\n");
        }

        
    }
    usuario->pedidos->inicio = usuario->pedidos->fim = NULL;
}

void sugerirParcerias(ListaUsuarios *lista, Usuario *usuario) {
    int encontrou = 0;
    Amigo *amigoAtual = usuario->amigos->inicio;
    while (amigoAtual != NULL) {
        Usuario *amigo = amigoAtual->usuario;

        Amigo *amigoDeAmigo = amigo->amigos->inicio;
        while (amigoDeAmigo != NULL) {
            Usuario *sugestao = amigoDeAmigo->usuario;

            if (sugestao != usuario && !saoAmigos(usuario, sugestao)) {
                printf("Sugestão de nova parceria: %s (%s)\n", sugestao->nome, sugestao->apelido);
                encontrou = 1;
            }

            amigoDeAmigo = amigoDeAmigo->proximo;
        }

        amigoAtual = amigoAtual->proximo;
    }
    if (!encontrou) {
        printf("Nenhuma parceria sugerida no momento.\n");
    }
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

int removerUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]) {
    Usuario *anterior = NULL;
    Usuario *atual = lista->inicio;

    while (atual != NULL && strcmp(atual->apelido, apelido) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return 1; // Usuário não encontrado
    }

    // Remove o usuário da lista de amigos de outros usuários
    Usuario *usuario_aux = lista->inicio;
    while (usuario_aux != NULL) {
        removerAmigo(lista, usuario_aux, atual->apelido);
        usuario_aux = usuario_aux->proximo;
    }

    // Remove o usuário da lista de usuários
    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    if (atual == lista->fim) {
        lista->fim = anterior;
    }

    // Libera a memória associada ao usuário
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
    return 0;
}

int removerAmigo(ListaUsuarios *lista, Usuario *usuario, char apelido[MAX_APELIDO]) {
    if (usuario == NULL || usuario->amigos == NULL) return 1;

    Amigo *anterior = NULL;
    Amigo *atual = usuario->amigos->inicio;

    while (atual != NULL && strcmp(atual->usuario->apelido, apelido) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return 1;

    if (anterior == NULL) {
        usuario->amigos->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    if (atual == usuario->amigos->fim) {
        usuario->amigos->fim = anterior;
    }

    free(atual);
    return 0;
}
