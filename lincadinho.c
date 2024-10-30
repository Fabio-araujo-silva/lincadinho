#include "lincadinho.h"

// Inicializam as estruturas dinâmicas
void criarPilhaMensagens(PilhaMensagens *pilha) {
    pilha->topo = NULL;
}

void criarFilaPedidos(FilaPedidos *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void criarListaUsuarios(ListaUsuarios *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void criarListaAmigos(ListaAmigos *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Verificam se as estruturas estão vazias
int pilhaMensagensVazia(PilhaMensagens *pilha) {
    return (pilha->topo == NULL ? TRUE : FALSE);
}

int filaPedidosVazia(FilaPedidos *fila) {
    return (fila->inicio == NULL ? TRUE : FALSE);
}

int listaUsuariosVazia(ListaUsuarios *lista) {
    return (lista->inicio == NULL ? TRUE : FALSE);
}

int listaAmigosVazia(ListaAmigos *lista) {
    return (lista->inicio == NULL ? TRUE : FALSE);
}

// Funções auxiliares para lidar com os nós (usuários) da lista principal

int adicionarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char apelido[MAX_APELIDO]) {
    // Aloca memória para um novo usuário
    Usuario *novo = (Usuario*) malloc(sizeof(Usuario));
    if (novo == NULL) 
        return 2; // Retorna 2 em caso de falha na alocação de memória

    // Copia o nome e apelido fornecidos para o novo usuário
    strcpy(novo->nome, nome);
    strcpy(novo->apelido, apelido);

    // Aloca memória para a lista de amigos do novo usuário
    novo->amigos = (ListaAmigos*) malloc(sizeof(ListaAmigos));
    if (novo->amigos == NULL) {
        // Libera o espaço do novo usuário na memória em caso de falha
        free(novo);
        return 2; // Retorna 2 em caso de falha na alocação de memória
    }
    criarListaAmigos(novo->amigos); // Inicializa a lista de amigos

    // Aloca memória para a pilha de mensagens do novo usuário
    novo->mensagens = (PilhaMensagens*) malloc(sizeof(PilhaMensagens));
    if (novo->mensagens == NULL) {
        // Libera o espaço do novo usuário na memória em caso de falha
        free(novo->amigos);
        free(novo);
        return 2; // Retorna 2 em caso de falha na alocação de memória
    }
    criarPilhaMensagens(novo->mensagens); // Inicializa a pilha de mensagens

    // Aloca memória para a fila de pedidos do novo usuário
    novo->pedidos = (FilaPedidos*) malloc(sizeof(FilaPedidos));
    if (novo->pedidos == NULL) {
        // Libera o espaço do novo usuário na memória em caso de falha
        free(novo->mensagens);
        free(novo->amigos);
        free(novo);
        return 2; // Retorna 2 em caso de falha na alocação de memória
    }
    criarFilaPedidos(novo->pedidos); // Inicializa a fila de pedidos

    // Inicializa o ponteiro para o próximo usuário como NULL
    novo->proximo = NULL;

    // Verifica se a lista de usuários está vazia
    if (listaUsuariosVazia(lista)) {
        // Caso esteja vazia, inicio e fim apontam para o novo
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        // Caso contrário, adiciona o novo usuário no fim da lista e atualiza o ponteiro de fim
        lista->fim->proximo = novo;
        lista->fim = novo;
    }

    return 0;
}

// Caso encontrado, retorna o ponteiro para o usuário, caso contrário, retorna nulo
Usuario* encontrarUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]) {
    // Itera sobre toda a lista de usuários até encontrar
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        // Compara o apelido do atual com o apelido procurado
        if (strcmp(atual->apelido, apelido) == 0)
            return atual;
        atual = atual->proximo;
    }
    // Retorna NULL caso o usuário procurado não esteja na lista
    return NULL;
}

// Parâmetros: lista de usuários, nome e apelido do novo usuário
int cadastrarUsuario(ListaUsuarios *lista, char nome[MAX_NOME], char apelido[MAX_APELIDO]) {
    // Verifica se há um usuário na lista com o mesmo apelido, garantindo a unicidade do apelido
    if (encontrarUsuario(lista, apelido) != NULL)
        return 1;
    else
        // Caso o apelido seja inédito, adiciona o novo usuário à lista pincipal
        return adicionarUsuario(lista, nome, apelido);
}

// Função auxiliar que verifica se um usuário é amigo de outro
int saoAmigos(Usuario *remetente, Usuario *destinatario) {
    // Itera sobre a lista de amigos de remetente
    Amigo *atual = remetente->amigos->inicio;
    while (atual != NULL) {
        // Verifica se o apelido do ponteiro atual coincide com o apelido do destinatário
        if (atual->usuario == destinatario)
            return TRUE;
        atual = atual->proximo;
    }

    return FALSE;
}

// Funções de usuário

int enviarMensagem(Usuario *remetente, Usuario *destinatario, char mensagem[MAX_MENSAGEM]) {
    if (destinatario == NULL)
        return 3; // Destinatário não encontrado
    if (!saoAmigos(remetente, destinatario))
        return 1; // Remetente não é amigo de destinatário

    // Aloca a memória para uma nova mensagem
    Mensagem *nova = (Mensagem*) malloc(sizeof(Mensagem));
    if (nova == NULL)
        return 2; // Retorna 2 em caso de falha na alocação de memória

    // Copia o conteúdo da mensagem passada por parâmetro para a nova mensagem
    strcpy(nova->conteudo, mensagem);

    // Atualiza a pilha de mensagens do destinatário
    nova->proxima = destinatario->mensagens->topo;
    destinatario->mensagens->topo = nova;

    return 0;
}

// Lê todas as mensagens, popando uma a uma
int lerMensagens(Usuario *usuario) {
    if (pilhaMensagensVazia(usuario->mensagens))
        return 1; // Retorna 1 caso a pilha de mensagens esteja vazia

    Mensagem *atual;
    while (usuario->mensagens->topo != NULL) {
        atual = usuario->mensagens->topo;
        // Exibe a mensagem seguida de quem a enviou
        printf("De: %s - Mensagem: %s\n", atual->remetente, atual->conteudo);
        usuario->mensagens->topo = atual->proxima;
        free(atual); // Libera o espaço de memória da mensagem lida
    }

    return 0;
}

// Solicitante envia um "pedido de amizade" para destinatário
int solicitarParceria(Usuario *solicitante, Usuario *destinatario) {
    if (destinatario == NULL)
        return 2; // Destinatário não encontrado

    // Verificar se já são amigos
    if (saoAmigos(solicitante, destinatario))
        return 1; // Retorna 1 caso afirmativo

    // Verificar se o destinatário já tem um pedido do solicitante
    Pedido *anterior = NULL;
    Pedido *atual = solicitante->pedidos->inicio;
    
    while (atual != NULL) {
        // Compara os apelidos
        if (strcmp(atual->solicitante->apelido, destinatario->apelido) == 0) {
            // Conexão automática se já houver um pedido pendente
            
            Amigo *novoAmigoDestinatario = (Amigo*) malloc(sizeof(Amigo));
            Amigo *novoAmigoSolicitante = (Amigo*) malloc(sizeof(Amigo));

            if (novoAmigoDestinatario == NULL || novoAmigoSolicitante == NULL) {
                free(novoAmigoDestinatario);
                free(novoAmigoSolicitante);
                return 3; // Retorna 3 em caso de falha na alocação de memória
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

            // Libera o espaço de memória do pedido
            free(atual);

            return 0;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    // Caso não haja um pedido pendente e não sejam amigos, adiciona um novo pedido
    Pedido *novoPedido = (Pedido*) malloc(sizeof(Pedido));
    if (novoPedido == NULL)
        return 3; // Retorna 3 em caso de falha na alocação de memória

    novoPedido->solicitante = solicitante;
    novoPedido->proximo = NULL;

    // Atualiza a fila de pedidos do destinatário
    if (filaPedidosVazia(destinatario->pedidos)) {
        destinatario->pedidos->inicio = destinatario->pedidos->fim = novoPedido;
    } else {
        destinatario->pedidos->fim->proximo = novoPedido;
        destinatario->pedidos->fim = novoPedido;
    }

    return 0;
}

void avaliarPedidosParceria(Usuario *usuario) {
    // Verifica se a fila de pedidos está vazia
    if (filaPedidosVazia(usuario->pedidos)) {
        printf("Nenhum pedido de parceria.\n");
        return;
    }
    // Itera sobre cada pedido na fila de pedidos do usuário
    Pedido *atual = usuario->pedidos->inicio;
    while (atual != NULL) {
        char resposta;
        printf("Pedido de %s (%s). Aceitar? (S/N): ", atual->solicitante->nome, atual->solicitante->apelido);
        scanf(" %c", &resposta);

        if (resposta == 'S' || resposta == 's') {
            // Verifica se já são amigos
            if (!saoAmigos(usuario, atual->solicitante)) {
                // Aloca memória para a nova amizade
                Amigo *novoAmigo = (Amigo*) malloc(sizeof(Amigo));
                if (novoAmigo == NULL) { // Verifica se foi possível alocar a memória
                    printf("Erro ao aceitar parceria!\n");
                    break;
                }
                // Configura os dados do novo amigo e o adiciona à lista do usuário
                novoAmigo->usuario = atual->solicitante;
                novoAmigo->proximo = NULL;

                if (listaAmigosVazia(usuario->amigos)) {
                    // Se a lista de amigos estiver vazia, inicio e fim apontam para o novo amigo
                    usuario->amigos->inicio = usuario->amigos->fim = novoAmigo;
                } else {
                    // Caso contrário, adiciona o amigo ao final da lista
                    usuario->amigos->fim->proximo = novoAmigo;
                    usuario->amigos->fim = novoAmigo;
                }

                // Cria uma nova entrada de amizade no solicitante para o usuário
                Amigo *novoAmigoSolicitante = (Amigo*) malloc(sizeof(Amigo));
                if (novoAmigoSolicitante == NULL) { // Verifica se foi possível alocar a memória
                    printf("Erro ao aceitar parceria!\n");
                    break;
                }
                novoAmigoSolicitante->usuario = usuario;
                novoAmigoSolicitante->proximo = NULL;

                // Adiciona o usuário como amigo do solicitante na lista de amigos dele
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
            
            // Remove o pedido da fila, atualizando o ponteiro para o próximo pedido
            Pedido *temp = atual;
            atual = atual->proximo;
            free(temp);
        } else if(resposta == 'N' || resposta == 'n') {
            printf("Parceria recusada.\n");
            Pedido *temp = atual;
            atual = atual->proximo;
            free(temp);
        } else {
            printf("Comando inválido\n");
        }
    }
    
    // Limpa a fila de pedidos, pois todos foram processados
    usuario->pedidos->inicio = usuario->pedidos->fim = NULL;
}

void sugerirParcerias(ListaUsuarios *lista, Usuario *usuario) {
    int encontrou = 0;  // Flag para verificar se alguma sugestão foi encontrada
    Amigo *amigoAtual = usuario->amigos->inicio;  // Aponta para o primeiro amigo do usuário

    // Itera sobre todos os amigos diretos do usuário
    while (amigoAtual != NULL) {
        Usuario *amigo = amigoAtual->usuario;

        // Itera sobre todos os amigos do amigo atual (amigos de segundo grau)
        Amigo *amigoDeAmigo = amigo->amigos->inicio;
        while (amigoDeAmigo != NULL) {
            Usuario *sugestao = amigoDeAmigo->usuario;  // Obtém o amigo do amigo como sugestão

            // Verifica se a sugestão não é o próprio usuário e se ainda não são amigos
            if (sugestao != usuario && !saoAmigos(usuario, sugestao)) {
                // Imprime a sugestão de nova parceria
                printf("Sugestao de nova parceria: %s (%s)\n", sugestao->nome, sugestao->apelido);
                encontrou = 1;  // Pelo menos uma sugestão feita
            }

            amigoDeAmigo = amigoDeAmigo->proximo;  // Passa para o próximo amigo do amigo
        }

        amigoAtual = amigoAtual->proximo;  // Passa para o próximo amigo direto do usuário
    }

    if (!encontrou) {
        printf("Nenhuma parceria sugerida no momento.\n");
    }
}

// Imprime todos os amigos de um usuário
void mostrarAmigos(Usuario *usuario) {
    // Caso o usuário não possua parceiros
    if (listaAmigosVazia(usuario->amigos)) {
        printf("%s nao tem amigos ainda.\n", usuario->nome);
        return;
    }

    // Itera sobre os amigos do usuário e imprime os dados da cada um a um
    printf("Amigos de %s:\n", usuario->nome);
    Amigo *atual = usuario->amigos->inicio;
    while (atual != NULL) {
        printf(" - %s (apelido: %s)\n", atual->usuario->nome, atual->usuario->apelido);
        atual = atual->proximo;
    }
}

int removerAmigo(ListaUsuarios *lista, Usuario *usuario, char apelido[MAX_APELIDO]) {
    // Verifica se o usuário ou a lista de amigos é nula
    if (usuario == NULL || usuario->amigos == NULL) return 1;

    // Variáveis para manter referência ao nó atual e ao nó anterior
    Amigo *anterior = NULL;
    Amigo *atual = usuario->amigos->inicio;

    // Percorre a lista de amigos procurando pelo amigo com o apelido especificado
    while (atual != NULL && strcmp(atual->usuario->apelido, apelido) != 0) {
        anterior = atual;           // Guarda o nó atual como o nó anterior
        atual = atual->proximo;     // Move para o próximo nó
    }

    // Verifica se o amigo não foi encontrado
    if (atual == NULL) 
        return 1;

    // Caso o amigo a ser removido seja o primeiro da lista
    if (anterior == NULL) {
        usuario->amigos->inicio = atual->proximo;  // Ajusta o início para o próximo nó
    } else {
        // Caso o amigo esteja no meio ou final da lista
        anterior->proximo = atual->proximo;        // Ajusta o ponteiro prox do nó anterior
    }

    // Verifica se o nó removido era o último da lista e atualiza o ponteiro fim
    if (atual == usuario->amigos->fim) {
        usuario->amigos->fim = anterior;
    }

    // Libera a memória alocada para o nó do amigo removido
    free(atual);

    return 0;
}

// Funções de administrador

void listarUsuarios(ListaUsuarios *lista) {
    if (listaUsuariosVazia(lista)) {
        printf("Nenhum usuario cadastrado!\n");
        return;
    }
    Usuario *atual = lista->inicio;
    while (atual != NULL) {
        printf("Nome: %s, Apelido: %s\n", atual->nome, atual->apelido);
        mostrarAmigos(atual);
        atual = atual->proximo;
    }
}


int removerUsuario(ListaUsuarios *lista, char apelido[MAX_APELIDO]) {
    Usuario *anterior = NULL; // Ponteiro para o usuário anterior
    Usuario *atual = lista->inicio; // Ponteiro para o usuário atual

    // Procura o usuário com o apelido especificado
    while (atual != NULL && strcmp(atual->apelido, apelido) != 0) {
        anterior = atual; // Atualiza o anterior
        atual = atual->proximo; // Avança para o próximo usuário
    }

    // Caso o usuário não foi encontrado
    if (atual == NULL) {
        return 1;
    }

    // Remove o usuário da lista de amigos de outros usuários
    Usuario *usuario_aux = lista->inicio;
    while (usuario_aux != NULL) {
        removerAmigo(lista, usuario_aux, atual->apelido); // Remove o amigo pelo apelido
        usuario_aux = usuario_aux->proximo; // Avança para o próximo usuário
    }

    // Remove o usuário da lista de usuários principal
    if (anterior == NULL) {
        lista->inicio = atual->proximo; // Atualiza o início da lista se for o primeiro
    } else {
        anterior->proximo = atual->proximo; // Remove o usuário do meio ou fim
    }

    // Atualiza o ponteiro fim da lista se necessário
    if (atual == lista->fim) {
        lista->fim = anterior; // Atualiza fim se o usuário removido for o último
    }

    // Libera a memória associada ao usuário
    // Libera as mensagens do usuário
    while (atual->mensagens->topo != NULL) {
        Mensagem *msg = atual->mensagens->topo;
        atual->mensagens->topo = msg->proxima; // Move para o próximo
        free(msg); // Libera a memória da mensagem
    }
    free(atual->mensagens); // Libera a lista de mensagens

    // Libera os pedidos do usuário
    while (atual->pedidos->inicio != NULL) {
        Pedido *pedido = atual->pedidos->inicio;
        atual->pedidos->inicio = pedido->proximo; // Move para o próximo
        free(pedido); // Libera a memória do pedido
    }
    free(atual->pedidos); // Libera a lista de pedidos

    // Libera a lista de amigos do usuário
    while (atual->amigos->inicio != NULL) {
        Amigo *amigo = atual->amigos->inicio;
        atual->amigos->inicio = amigo->proximo; // Move para o próximo
        free(amigo); // Libera a memória do amigo
    }
    free(atual->amigos); // Libera a lista de amigos

    free(atual); // Libera a memória do usuário

    return 0;
}

void reinicializarSistema(ListaUsuarios *lista) {
    Usuario *atual = lista->inicio; // Inicia a partir do primeiro usuário
    while (atual != NULL) {
        Usuario *prox = atual->proximo; // Guarda o próximo usuário

        // Libera mensagens do usuário atual
        while (atual->mensagens->topo != NULL) {
            Mensagem *msg = atual->mensagens->topo;
            atual->mensagens->topo = msg->proxima; // Move para o próximo
            free(msg); // Libera a memória da mensagem
        }
        free(atual->mensagens); // Libera a lista de mensagens

        // Libera pedidos do usuário atual
        while (atual->pedidos->inicio != NULL) {
            Pedido *pedido = atual->pedidos->inicio;
            atual->pedidos->inicio = pedido->proximo; // Move para o próximo
            free(pedido); // Libera a memória do pedido
        }
        free(atual->pedidos); // Libera a lista de pedidos

        // Libera amigos do usuário atual
        while (atual->amigos->inicio != NULL) {
            Amigo *amigo = atual->amigos->inicio;
            atual->amigos->inicio = amigo->proximo; // Move para o próximo
            free(amigo); // Libera a memória do amigo
        }
        free(atual->amigos); // Libera a lista de amigos
        
        free(atual); // Libera a memória do usuário
        atual = prox; // Avança para o próximo usuário
    }
    lista->inicio = lista->fim = NULL; // Reseta a lista de usuários
}
