#include <stdio.h>
#include "carros.h"
#include "clientes.h"
#include "vendas.h"

int menu_principal();

void inicializarCadastro();

int main() {

    inicializarCadastro();

    int opcao;
    do {
        opcao = menu_principal();
        switch (opcao) {
            case 1:
                //chamarMenu_carros();
                menu_carros(carros);
            break;
            case 2:
                //chamarMenu_clientes();
                menu_clientes(clientes);
            break;
            case 3:
                //chamarMenu_vendas();
                menu_vendas(vendas, clientes, carros);
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

void inicializarCadastro() {
    for (int i = 0; i < VENDAS_MAX; i++) {
        inicializarCliente(&clientes[i]);
        inicializarCarro(&carros[i]);
        inicializarVenda(&vendas[i]);
    }
}








