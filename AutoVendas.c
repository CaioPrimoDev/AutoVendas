#include <stdio.h>
#include "cadastro.h"

int menu_principal();

int main() {

    inicializarCadastro();

    int opcao;
    do {
        opcao = menu_principal();
        switch (opcao) {
            case 1:
                chamarMenu_carros();
                //menu_carros(carros, cadastro);
            break;
            case 2:
                chamarMenu_clientes();
                //menu_clientes(clientes, cadastro);
            break;
            case 3:
                chamarMenu_vendas();
                //menu_vendas(vendas, clientes, carros, cadastro);
            break;
            case 0:
                printf("Finalizando o programa...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

int menu_principal() {
    char vazio[] = {"  "};
    int opcao;
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1. Gerenciar Carros\n");
    printf("2. Gerenciar Clientes\n");
    printf("3. Gerenciar Vendas\n");
    printf("0. Sair\n");
    printf(">");
    scanf(" %d", &opcao);
    return opcao;
}








