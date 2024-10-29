#include "tad_final.h"

int main() {

    ListaUsuarios *lista = (ListaUsuarios *)malloc(sizeof(ListaUsuarios));
    if (lista == NULL) {
        printf("Erro ao inicializar o sistema.\n");
        return 1;
    }
    criarListaUsuarios(lista);

    int opcao;
    char apelido[MAX_APELIDO];
    Usuario *usuarioAtual = NULL;

    while (TRUE) {
        printf("Opcoes:\n");
        printf("1) Cadastrar usuario\n");
        printf("2) Listar usuarios\n");
        printf("3) Solicitar parceria\n");
        printf("4) Avaliar pedidos de parceria\n");
        printf("5) Enviar mensagem\n");
        printf("6) Ler mensagens\n");
        printf("7) Sugerir novas parcerias\n");
        printf("8) Mostrar amigos\n");
        printf("9) Reinicializar sistema\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario(lista);
                break;
            case 2:
                listarUsuarios(lista);
                break;
            case 3:
                printf("Entre com seu apelido: ");
                scanf("%s", apelido);
                usuarioAtual = encontrarUsuario(lista, apelido);
                if (!usuarioAtual) {
                    printf("Usuário não encontrado.\n");
                    break;
                }
                printf("Apelido do usuário que deseja solicitar parceria: ");
                scanf("%s", apelido);
                Usuario *destinatario = encontrarUsuario(lista, apelido);
                if (!destinatario) {
                    printf("Usuário destinatário não encontrado.\n");
                } else if (solicitarParceria(usuarioAtual, destinatario) == 0) {
                    printf("Pedido de parceria enviado com sucesso!\n");
                }
                break;
            case 4:
                printf("Entre com seu apelido: ");
                scanf("%s", apelido);
                usuarioAtual = encontrarUsuario(lista, apelido);
                if (usuarioAtual) {
                    avaliarPedidosParceria(usuarioAtual);
                } else {
                    printf("Usuário não encontrado.\n");
                }
                break;
            case 5:
                printf("Entre com seu apelido: ");
                scanf("%s", apelido);
                usuarioAtual = encontrarUsuario(lista, apelido);
                if (!usuarioAtual) {
                    printf("Usuário não encontrado.\n");
                    break;
                }
                printf("Apelido do destinatário: ");
                scanf("%s", apelido);
                Usuario *amigo = encontrarUsuario(lista, apelido);
                if (!amigo || !saoAmigos(usuarioAtual, amigo)) {
                    printf("Usuário não é parceiro.\n");
                    break;
                }
                printf("Mensagem: ");
                char mensagem[MAX_MENSAGEM];
                scanf(" %[^\n]s", mensagem);
                if (enviarMensagem(usuarioAtual, amigo, mensagem) == 0) {
                    printf("Mensagem enviada com sucesso!\n");
                }
                break;
            case 6:
                printf("Entre com seu apelido: ");
                scanf("%s", apelido);
                usuarioAtual = encontrarUsuario(lista, apelido);
                if (usuarioAtual && lerMensagens(usuarioAtual) == 0) {
                    printf("Todas as mensagens lidas.\n");
                } else {
                    printf("Nenhuma mensagem encontrada ou erro.\n");
                }
                break;
            case 7:
                printf("Entre com seu apelido: ");
                scanf("%s", apelido);
                usuarioAtual = encontrarUsuario(lista, apelido);
                if (usuarioAtual) {
                    sugerirNovasParcerias(lista, usuarioAtual);
                } else {
                    printf("Usuário não encontrado.\n");
                }
                break;
            case 8:
                // Mostrar amigos do usuário
                printf("Entre com seu apelido: ");
                scanf("%s", apelido);
                usuarioAtual = encontrarUsuario(lista, apelido);
                if (usuarioAtual) {
                    mostrarAmigos(usuarioAtual);
                } else {
                    printf("Usuário não encontrado.\n");
                }
                break;
            case 9:
                reinicializarSistema(lista);
                break;
            case 0:
                reinicializarSistema(lista);
                free(lista);
                printf("Sistema encerrado.\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
    return 0;
}
