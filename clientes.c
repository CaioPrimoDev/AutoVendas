#include <stdio.h>
#include <string.h>
#include "clientes.h"

int total_clientes = 0;
Cliente clientes[CLIENT_MAX] = {0};      // Inicializa a struct Cliente

void cadastrar_cliente(Cliente *clientes) {
    if (total_clientes >= CLIENT_MAX) {
        printf("\n\n!!! Limite de clientes atingido !!!\n\n");
        return;
    }
    Cliente *cliente = &clientes[total_clientes];

    printf("\nNome: ");
    scanf(" %[^\n]", cliente->nome);
    printf("CPF: ");
    scanf(" %[^\n]", cliente->cpf);
    printf("Celular: ");
    scanf(" %[^\n]", cliente->cell);
    printf("Endereco: ");
    scanf(" %[^\n]", cliente->endereco);
    printf("Data de Cadastro: ");
    scanf(" %[^\n]", cliente->data);

    cliente->id_cliente = total_clientes;
    total_clientes++;

    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");
}
void listar_clientes(const Cliente *clientes) {
    if (total_clientes == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    for (int i = 0; i < total_clientes; i++) {
        printf("\n\n===========================\n");
        printf("ID - CLIENTE: %d\n", clientes[i].id_cliente);
        printf("===========================\n");
        printf("Nome: %s\nCPF: %s\nCelular: %s\nEndereco: %s\nData: %s\n",
               clientes[i].nome, clientes[i].cpf, clientes[i].cell,
               clientes[i].endereco, clientes[i].data);
    }
}
void excluir_cliente(Cliente *clientes, const char *termo, const int tipo) {
    int encontrado = -1;

    for (int i = 0; i < total_clientes; i++) {
        Cliente cliente = clientes[i];
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            encontrado = i;
            break;
            }
    }

    if (encontrado == -1) {
        printf("Cliente não encontrado.\n");
        return;
    }

    // Deslocar os elementos para preencher o espaço vazio
    for (int i = encontrado; i < total_clientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    total_clientes--;

    // Atualizar IDs
    for (int i = 0; i < total_clientes; i++) {
        clientes[i].id_cliente = i;
    }

    printf("Cliente removido com sucesso!\n");
}
void editar_cliente(Cliente *clientes, const char *termo, const int tipo) {
    int encontrado = -1;

    for (int i = 0; i < total_clientes; i++) {
        Cliente cliente = clientes[i];
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            encontrado = i;
            break;
            }
    }

    if (encontrado == -1) {
        printf("Cliente não encontrado.\n");
        return;
    }

    Cliente *cliente = &clientes[encontrado];

    printf("Editando cliente\n");
    printf("Novo nome: ");
    scanf(" %[^\n]", cliente->nome);
    printf("Novo CPF: ");
    scanf(" %[^\n]", cliente->cpf);
    printf("Novo celular: ");
    scanf(" %[^\n]", cliente->cell);
    printf("Novo endereço: ");
    scanf(" %[^\n]", cliente->endereco);
    printf("Nova data de cadastro: ");
    scanf(" %[^\n]", cliente->data);

    printf("Cliente editado com sucesso!\n");
}
void buscar_cliente(const Cliente *clientes, const char *termo, const int tipo) {
    int encontrado = 0;

    for (int i = 0; i < total_clientes; i++) {
        Cliente cliente = clientes[i];
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("\n===========================\n");
            printf("ID: %d\nNome: %s\nCPF: %s\nCelular: %s\nEndereço: %s\nData: %s\n",
                   cliente.id_cliente, cliente.nome, cliente.cpf, cliente.cell, cliente.endereco, cliente.data);
            printf("===========================\n");
            encontrado = 1;
            }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
    }
}
void menu_clientes(Cliente *clientes) {
    int opcao;
    do {
        printf("\n======== MENU - CLIENTES ========\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Excluir Cliente\n");
        printf("5. Buscar Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        char termo[20];
        int tipo;

        switch (opcao) {
            case 1:
                cadastrar_cliente(clientes);
            break;
            case 2:
                listar_clientes(clientes);
            break;
            case 3:
                printf("\n\nEditar cliente por: ");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            editar_cliente(clientes, termo, tipo);
            break;
            case 4:
                printf("\nExcluir cliente por: ");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            excluir_cliente(clientes, termo, tipo);
            break;
            case 5:
                printf("Buscar cliente por:");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            buscar_cliente(clientes, termo, tipo);
            break;
            case 0:
                printf("\n\nVoltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void inicializarCliente(Cliente *cliente) {
    // Inicializa os campos do cliente
    strcpy(cliente->nome, "");
    strcpy(cliente->cpf, "");
    strcpy(cliente->cell, "");
    strcpy(cliente->endereco, "");
    strcpy(cliente->data, "");
    cliente->id_cliente = 0;
}