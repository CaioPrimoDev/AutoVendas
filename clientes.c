#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clientes.h"

// Variáveis globais
Cliente *clientes_ptr = NULL;
Cliente *clientes = NULL;
int capacidade_clientes = 0;
int total_clientes = 0;

void cadastrar_cliente() {
    // Inicializa memória apenas se clientes_ptr for NULL
    if (clientes_ptr == NULL) {
        printf("Inicializando clientes_ptr...\n");
        clientes_ptr = malloc(10 * sizeof(Cliente));
        if (clientes_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            return;
        }
        capacidade_clientes = 10;
        printf("clientes_ptr inicializado com capacidade: %d\n", capacidade_clientes);
    }

    // Verifica se é necessário realocar memória
    if (total_clientes >= capacidade_clientes) {
        printf("Re-alocando memória: capacidade atual = %d, total_clientes = %d\n", capacidade_clientes, total_clientes);
        int nova_capacidade = capacidade_clientes * 2;
        Cliente *novo_array = realloc(clientes_ptr, nova_capacidade * sizeof(Cliente));
        if (novo_array == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            return;
        }
        clientes_ptr = novo_array;
        capacidade_clientes = nova_capacidade;
        printf("Re-alocação concluída. Nova capacidade: %d\n", capacidade_clientes);
    }

    // Cadastra o cliente no array
    Cliente *cliente = &clientes_ptr[total_clientes];
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

    // Atribui ID ao cliente
    cliente->id_cliente = total_clientes;
    total_clientes++;

    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");
}
void listar_clientes() {
    if (total_clientes == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }

    for (int i = 0; i < total_clientes; i++) {
        printf("\n\n===========================\n");
        printf("ID - CLIENTE: %d\n", clientes_ptr[i].id_cliente);
        printf("===========================\n");
        printf("Nome: %s\nCPF: %s\nCelular: %s\nEndereco: %s\nData: %s\n",
               clientes_ptr[i].nome, clientes_ptr[i].cpf, clientes_ptr[i].cell,
               clientes_ptr[i].endereco, clientes_ptr[i].data);
    }
}
void excluir_cliente(const char *termo, int tipo) {
    if (clientes_ptr == NULL || total_clientes == 0) {
        printf("Nenhum cliente para excluir.\n");
        return;
    }

    int encontrado = -1;

    // Procurar o cliente pelo nome ou CPF
    for (int i = 0; i < total_clientes; i++) {
        Cliente cliente = clientes_ptr[i];
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

    // Remover o cliente encontrado deslocando os elementos
    for (int i = encontrado; i < total_clientes - 1; i++) {
        clientes_ptr[i] = clientes_ptr[i + 1];
    }
    total_clientes--;  // Decrementa total_clientes

    // Atualizar os IDs de todos os clientes
    for (int i = 0; i < total_clientes; i++) {
        clientes_ptr[i].id_cliente = i;
    }

    // Reajustar a capacidade se necessário
    if (total_clientes < capacidade_clientes / 2 && capacidade_clientes > 10) {
        int nova_capacidade = capacidade_clientes / 2;
        Cliente *novo_array = (Cliente *)realloc(clientes_ptr, nova_capacidade * sizeof(Cliente));
        if (novo_array != NULL) {
            clientes_ptr = novo_array;
            capacidade_clientes = nova_capacidade;
            printf("Capacidade reduzida para %d após exclusão.\n", capacidade_clientes);
        }
    }

    printf("Cliente removido com sucesso!\n");
}
void editar_cliente(const char *termo, int tipo) {
    if (clientes_ptr == NULL || total_clientes == 0) {
        printf("Nenhum cliente para editar.\n");
        return;
    }

    int encontrado = -1;

    // Procurar o cliente com base no termo e no tipo
    for (int i = 0; i < total_clientes; i++) {
        Cliente cliente = clientes_ptr[i];
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

    // Obter referência ao cliente encontrado
    Cliente *cliente = &clientes_ptr[encontrado];

    // Editar as informações do cliente
    printf("Editando cliente (ID: %d)\n", cliente->id_cliente);
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

    printf("\nCliente editado com sucesso!\n");
}
void buscar_cliente(const char *termo, int tipo) {
    if (clientes_ptr == NULL || total_clientes == 0) {
        printf("Nenhum cliente cadastrado para buscar.\n");
        return;
    }

    int encontrado = 0;

    // Itera sobre os clientes para encontrar o termo
    for (int i = 0; i < total_clientes; i++) {
        Cliente cliente = clientes_ptr[i];
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("\n===========================\n");
            printf("ID: %d\nNome: %s\nCPF: %s\nCelular: %s\nEndereço: %s\nData: %s\n",
                   cliente.id_cliente, cliente.nome, cliente.cpf, cliente.cell, cliente.endereco, cliente.data);
            printf("===========================\n");
            encontrado = 1;
            }
    }

    // Exibe mensagem caso nenhum cliente seja encontrado
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
                cadastrar_cliente(&clientes);
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
            editar_cliente(termo, tipo);
            break;
            case 4:
                printf("\nExcluir cliente por: ");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            excluir_cliente(termo, tipo);
            break;
            case 5:
                printf("Buscar cliente por:");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            buscar_cliente(termo, tipo);
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