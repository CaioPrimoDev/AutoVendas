#include <stdio.h>
#include <stdlib.h>
#include "carros.h"
#include "clientes.h"
#include "vendas.h"

void liberar_memoria();
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
                liberar_memoria();
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
    // Aloca memória para os clientes
    clientes = malloc(CLIENT_MAX * sizeof(Cliente));
    if (clientes == NULL) {
        printf("Erro ao alocar memória para clientes.\n");
        exit(1);
    }

    // Inicializa os clientes
    for (int i = 0; i < CLIENT_MAX; i++) {
        inicializarCliente(&clientes[i]);
    }

    // Inicializa outros dados (carros, vendas, etc)
    for (int i = 0; i < VENDAS_MAX; i++) {
        inicializarCarro(&carros[i]);
        inicializarVenda(&vendas[i]);
    }
}


void liberar_memoria() {
    if (clientes_ptr != NULL) {
        free(clientes_ptr);
        clientes_ptr = NULL; // Defina o ponteiro como NULL para evitar acessos inválidos.
    }

    if (carros_ptr != NULL) {
        free(carros_ptr);
        carros_ptr = NULL; // Defina o ponteiro como NULL para evitar acessos inválidos.
    }
    if (vendas_ptr != NULL) {
        free(vendas_ptr);
        vendas_ptr = NULL; // Defina o ponteiro como NULL para evitar acessos inválidos.
    }
}








