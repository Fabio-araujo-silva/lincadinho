#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Usuario.h"



// Função para exibir o menu de opções
void mostrarMenu() {
    printf("\nCaro usuário, suas opções são:\n");
    printf("1) Cadastrar um usuário\n");
    printf("2) Listar usuários cadastrados e suas informações\n");
    printf("3) Pedir para ser parceiro de um usuário\n");
    printf("4) Avaliar lista de pedidos de parceria\n");
    printf("5) Enviar mensagem para um parceiro\n");
    printf("6) Ver mensagens recebidas\n");
    printf("7) Sugerir novas parcerias\n");
    printf("8) Reinicializar sistema\n");
    printf("0) Sair\n");
    printf("O que deseja fazer? ");
}

int main() {
    // Declara a lista principal de usuários
    ListaUsuario listaUsuarios;
    int n;    
    do {
        mostrarMenu();
        scanf("%d", &n);
        
        int resultado;
        
        Usuario  *usuario, *remetente, *destinatario; 
        
        switch(n) {
            case 1://feito
                // Cadastrar um novo usuário
                Cadastrar(listaUsuarios);
            case 2://feito
                // Listar usuários e seus parceiros
                Listar_Usuarios(listaUsuarios);
                break;
            //perdir para ser parceiro do usuario
            case 3://feito
                Solicitar_Parceria(listaUsuarios);
                break;

            case 4:
                // Avaliar lista de pedidos de parceria
                printf("Entre com seu apelido: ");
                scanf(" %s", apelido);

                usuario = Encontrar(&listaUsuarios, apelido);
                if (usuario == NULL) {
                    printf("Usuário não encontrado.\n");
                } else {
                    while (!isEmpty_Fila_de_Pedidos(usuario->fila_de_pedidos)) {
                        Usuario *parceiro = Remover_Pedido(usuario);
                        printf("%s deseja ser seu parceiro. Aceita (sim/nao)? ", parceiro->apelido);
                        char resposta[4];
                        scanf("%s", resposta);
                        if (strcmp(resposta, "sim") == 0) {
                            Adicionar_Parceiro(usuario, parceiro);
                            Adicionar_Parceiro(parceiro, usuario);
                            printf("Parceria com %s aceita.\n", parceiro->apelido);
                        } else {
                            printf("Parceria com %s recusada.\n", parceiro->apelido);
                        }
                    }
                    printf("Operação realizada com sucesso.\n");
                }
                break;

            case 5:
                // Enviar mensagem para um parceiro
                printf("Entre com seu apelido: ");
                scanf(" %s", apelido);
                printf("Entre com o apelido de quem quer enviar mensagem: ");
                scanf(" %s", apelidoDest);
                printf("Entre com a mensagem: ");
                scanf(" %s", mensagem);

                remetente = Encontrar(&listaUsuarios, apelido);
                destinatario = Encontrar(&listaUsuarios, apelidoDest);

                if (remetente == NULL || destinatario == NULL) {
                    printf("Erro: um dos usuários não existe.\n");
                } else if (!Sao_Amigos(remetente, destinatario)) {
                    printf("Erro: %s não é amigo de %s.\n", apelido, apelidoDest);
                } else {
                    resultado = Enviar_Mensagem(&listaUsuarios, remetente, apelidoDest, mensagem);
                    if (resultado == 0)
                        printf("Mensagem enviada com sucesso.\n");
                    else
                        printf("Erro ao enviar mensagem.\n");
                }
                break;

            case 6:
                // Ver mensagens recebidas
                printf("Entre com seu apelido: ");
                scanf(" %s", apelido);

                usuario = Encontrar(&listaUsuarios, apelido);
                if (usuario == NULL) {
                    printf("Usuário não encontrado.\n");
                } else {
                    printf("Suas mensagens são:\n");
                    while (!isEmpty_Pilha_de_Mensagens(usuario->pilha_de_mensagens)) {
                        Ler_Mensagem(usuario);
                    }
                    printf("Mensagens exibidas!\n");
                }
                break;

            case 7:
                Sugerir_Amigos(&listaUsuarios);
                printf("Operação de sugestão de amigos realizada.\n");
                break;

            case 8:
                ReinicializarSistema(&listaUsuarios);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (n != 0);

    return 0;
}
