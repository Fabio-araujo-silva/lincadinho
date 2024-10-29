/* tad_final_main.c */
#include "tad_final.h"

void lincadinho(ListaUsuarios *lista);
void Admin(ListaUsuarios *lista);
void botoesUsuario(ListaUsuarios *lista, Usuario *usuarioAtual);
void cadastrarUsuario_main(ListaUsuarios *lista);
Usuario* Logar(ListaUsuarios *lista);


int main() {
    ListaUsuarios *lista = (ListaUsuarios *)malloc(sizeof(ListaUsuarios));
    if (lista == NULL) {
        printf("Erro ao inicializar o sistema.\n");
        return 1;
    }
    criarListaUsuarios(lista);

    lincadinho(lista);

    return 0;
}

void lincadinho(ListaUsuarios *lista) {

    int opcao;
    Usuario *usuarioAtual = NULL;

    while(TRUE) {
        printf("\n====== MENU PRINCIPAL ======\n");
        printf("1) Login\n");
        printf("2) Cadastrar\n");
        printf("3) Admin\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                usuarioAtual = Logar(lista);
                if (usuarioAtual == NULL) {
                    printf("Usuário não encontrado.\n");
                } else {
                    botoesUsuario(lista, usuarioAtual);
                }
                break;
            case 2:
                cadastrarUsuario_main(lista);
                break;
            case 3:
                Admin(lista);
                break;
            case 0:
                reinicializarSistema(lista);
                free(lista);
                printf("Sistema encerrado.\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

void cadastrarUsuario_main(ListaUsuarios *lista) {
    int erro = 0;
    char nome[MAX_NOME], apelido[MAX_APELIDO];

    printf("\n===== Cadastro de Usuário =====\n");
    printf("Nome: ");
    scanf(" %[^\n]s", nome);
    printf("Apelido: ");
    scanf(" %s", apelido);

    erro = cadastrarUsuario(lista, nome, apelido);
    
    if (erro == 1) {
        printf("Apelido já em uso. Tente outro.\n");
    } else if (erro == 0) {
        printf("Usuário cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar usuário.\n");
    }
}

Usuario* Logar(ListaUsuarios *lista) {
    char apelido[MAX_APELIDO];
    printf("\n===== Login =====\n");
    printf("Entre com seu apelido: ");
    scanf("%s", apelido);
    Usuario *usuarioAtual = encontrarUsuario(lista, apelido);
    return usuarioAtual;
}

void botoesUsuario(ListaUsuarios *lista, Usuario *usuarioAtual) {
    int opcao, erro = 0;
    char apelido[MAX_APELIDO];
    while (TRUE) {
        printf("\n====== MENU DE USUÁRIO ======\n");
        printf("1) Enviar mensagem\n");
        printf("2) Ler mensagens\n");
        printf("3) Mostrar amigos\n");
        printf("4) Sugerir novas parcerias\n");
        printf("5) Solicitar parceria\n");
        printf("6) Avaliar pedidos de parceria\n");
        printf("7) Remover amigo\n");
        printf("8) Deslogar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                erro = 0;
                printf("Pra quem deseja enviar mensagem?: ");
                scanf(" %[^\n]s", apelido);
                Usuario *amigo = encontrarUsuario(lista, apelido);

                if (amigo == NULL) {
                    printf("Usuário não encontrado.\n");
                    break;
                }

                printf("Mensagem: ");
                char mensagem[MAX_MENSAGEM];
                scanf(" %[^\n]s", mensagem);

                erro = enviarMensagem(usuarioAtual, amigo, mensagem);

                if (erro == 0) {
                    printf("Mensagem enviada com sucesso!\n");
                } else if(erro == 1){
                    printf("Não são amigos!\n");
                } else if (erro == 2) {
                    printf("Erro ao enviar a mensagem.\n");
                } else if (erro == 3) {
                    printf("Destinatário não encontrado.\n");
                }
                break;
            }
            case 2:
                if (usuarioAtual && lerMensagens(usuarioAtual) == 0) {
                    printf("Todas as mensagens lidas.\n");
                } else {
                    printf("Nenhuma mensagem encontrada ou erro.\n");
                }
                break;
            case 3:
                mostrarAmigos(usuarioAtual);
                break;
            case 4:
                sugerirParcerias(lista, usuarioAtual);
                break;
            case 5: {
                printf("Apelido destinatário: ");
                scanf("%s", apelido);
                if(strcmp(apelido, usuarioAtual->apelido)) { // se os nomes são diferentes
                    Usuario *destinatario = encontrarUsuario(lista, apelido);
                    erro = solicitarParceria(usuarioAtual, destinatario);
                    if (erro == 0) {
                        printf("Sucesso!\n");
                    } else if (erro == 1) {
                        printf("Vocês já são amigos.\n");
                    } else if (erro == 2) {
                        printf("Usuário destinatário não encontrado.\n");
                    } else {
                        printf("Erro ao enviar o pedido de parceria.\n");
                    }
                } 
                else {
                    printf("Operação inválida\n");
                }
                break;
            }
            case 6:
                avaliarPedidosParceria(usuarioAtual);
                break;
            case 7:
                printf("Quem você deseja remover? (apelido): ");
                scanf("%s", apelido);

                erro = removerAmigo(lista, usuarioAtual, apelido);

                if (erro == 1)
                    printf("Usuário destinatário não encontrado ou não é seu amigo.\n");
                else
                    printf("Amigo removido com sucesso!\n");
                break;
            case 8:
                usuarioAtual = NULL;
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}

void Admin(ListaUsuarios *lista) {
    int opcao, erro = 0;
    char apelido[MAX_APELIDO];

    while (TRUE) {
        printf("\n====== MENU ADMINISTRATIVO ======\n");
        printf("1) Listar usuários\n");
        printf("2) Remover usuário\n");
        printf("3) Reinicializar sistema\n");
        printf("4) Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                listarUsuarios(lista);
                break;
            case 2:
                printf("Quem você deseja remover? (apelido): ");
                scanf("%s", apelido);

                erro = removerUsuario(lista, apelido);

                if (erro == 1)
                    printf("Usuário não encontrado.\n");
                else
                    printf("Usuário %s removido com sucesso.\n", apelido);
                break;
            case 3:
                reinicializarSistema(lista);
                printf("Sistema reinicializado com sucesso.\n");
                break;
            case 4:
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}
