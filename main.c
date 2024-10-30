#include "lincadinho.h"

//função principal do sistema, inicializa a lista de usuários e chama a função de controle lincadinho
void lincadinho(ListaUsuarios *lista);

//função administrativa para operações de gerenciamento de usuários, como listar, remover e reiniciar o sistema
void Admin(ListaUsuarios *lista);

//função para gerenciar as opções do usuário logado, incluindo mensagens e parcerias
void botoesUsuario(ListaUsuarios *lista, Usuario *usuarioAtual);

//função para cadastrar um novo usuário no sistema
void cadastrarUsuario_main(ListaUsuarios *lista);

//função para realizar o login de um usuário a partir de um apelido fornecido
Usuario* Logar(ListaUsuarios *lista);

int main() {
    ListaUsuarios *lista = (ListaUsuarios*) malloc(sizeof(ListaUsuarios));
    if (lista == NULL) {
        printf("Erro ao inicializar o sistema.\n");
        return 1;
    }
    criarListaUsuarios(lista);

    lincadinho(lista);

    return 0;
}

//função principal do sistema, responsável pelo controle do menu inicial, como login, cadastro e acesso ao menu de administrador
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
                    printf("Usuario nao encontrado!\n");
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
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    }
}

//função para realizar o processo de cadastro de um novo usuário no sistema
void cadastrarUsuario_main(ListaUsuarios *lista) {
    int erro = 0;
    char nome[MAX_NOME], apelido[MAX_APELIDO];

    printf("\n===== Cadastro de Usuario =====\n");
    printf("Nome: ");
    scanf(" %[^\n]s", nome);
    printf("Apelido: ");
    scanf(" %s", apelido);

    erro = cadastrarUsuario(lista, nome, apelido);
    
    if (erro == 1) {
        printf("Apelido ja em uso, tente outro!\n");
    } else if (erro == 0) {
        printf("Usuario cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar usuario.\n");
    }
}

//função para autenticar um usuário com base em seu apelido
Usuario* Logar(ListaUsuarios *lista) {
    char apelido[MAX_APELIDO];

    printf("\n===== Login =====\n");
    printf("Entre com seu apelido: ");
    scanf("%s", apelido);

    Usuario *usuarioAtual = encontrarUsuario(lista, apelido);
    return usuarioAtual;
}

//função que apresenta o menu de ações para o usuário logado, como enviar mensagens e gerenciar parcerias
void botoesUsuario(ListaUsuarios *lista, Usuario *usuarioAtual) {
    int opcao, erro = 0;
    char apelido[MAX_APELIDO];

    while (TRUE) {
        printf("\n====== MENU DE USUARIO ======\n");
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
                    printf("Usuario não encontrado!\n");
                    break;
                }

                printf("Mensagem: ");
                char mensagem[MAX_MENSAGEM];
                scanf(" %[^\n]s", mensagem);

                erro = enviarMensagem(usuarioAtual, amigo, mensagem);

                if (erro == 0) {
                    printf("Mensagem enviada com sucesso!\n");
                } else if(erro == 1){
                    printf("Nao sao amigos!\n");
                } else if (erro == 2) {
                    printf("Erro ao enviar a mensagem.\n");
                } else if (erro == 3) {
                    printf("Destinatario nao encontrado.\n");
                }
                break;
            }
            case 2:
                if (usuarioAtual && lerMensagens(usuarioAtual) == 0) {
                    printf("Todas as mensagens lidas.\n");
                } else {
                    printf("Nenhuma mensagem encontrada!\n");
                }
                break;
            case 3:
                mostrarAmigos(usuarioAtual);
                break;
            case 4:
                sugerirParcerias(lista, usuarioAtual);
                break;
            case 5: {
                printf("Apelido destinatario: ");
                scanf("%s", apelido);
                if(strcmp(apelido, usuarioAtual->apelido)) { // se os nomes são diferentes
                    Usuario *destinatario = encontrarUsuario(lista, apelido);
                    erro = solicitarParceria(usuarioAtual, destinatario);
                    if (erro == 0) {
                        printf("Sucesso!\n");
                    } else if (erro == 1) {
                        printf("Voces ja sao amigos!\n");
                    } else if (erro == 2) {
                        printf("Usuario destinatario nao encontrado!\n");
                    } else {
                        printf("Erro ao enviar o pedido de parceria!\n");
                    }
                } 
                else {
                    printf("Operacao invalida\n");
                }
                break;
            }
            case 6:
                avaliarPedidosParceria(usuarioAtual);
                break;
            case 7:
                printf("Quem voce deseja remover? (apelido): ");
                scanf("%s", apelido);

                erro = removerAmigo(lista, usuarioAtual, apelido);

                if (erro == 1)
                    printf("Usuario destinatario nao encontrado ou nao e seu amigo.\n");
                else
                    printf("Amigo removido com sucesso!\n");
                break;
            case 8:
                usuarioAtual = NULL;
                return;
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    }
}

//função para administrar o sistema com funcionalidades como listar, remover usuários e reiniciar o sistema
void Admin(ListaUsuarios *lista) {
    int opcao, erro = 0;
    char apelido[MAX_APELIDO];

    while (TRUE) {
        printf("\n====== MENU ADMINISTRATIVO ======\n");
        printf("1) Listar usuarios\n");
        printf("2) Remover usuario\n");
        printf("3) Reinicializar sistema\n");
        printf("4) Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarUsuarios(lista);
                break;
            case 2:
                printf("Quem voce deseja remover? (apelido): ");
                scanf("%s", apelido);

                erro = removerUsuario(lista, apelido);

                if (erro == 1)
                    printf("Usuario nao encontrado!\n");
                else
                    printf("Usuario %s removido com sucesso.\n", apelido);
                break;
            case 3:
                reinicializarSistema(lista);
                printf("Sistema reinicializado com sucesso.\n");
                break;
            case 4:
                return;
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    }
}
