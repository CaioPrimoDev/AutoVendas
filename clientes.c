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
    FILE *file = fopen("cliente_dados.txt", "a+");  // Abre/cria o arquivo no modo de gravação
    if (file == NULL) {
        printf("Erro ao abrir/criar o arquivo.\n");
        return;
    }

    // Inicializa memória apenas se clientes_ptr for NULL
    if (clientes_ptr == NULL) {
        printf("Inicializando clientes_ptr...\n");
        clientes_ptr = malloc(10 * sizeof(Cliente));
        if (clientes_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        capacidade_clientes = 10;
        printf("clientes_ptr inicializado com capacidade: %d\n", capacidade_clientes);
    }

    // Verifica se é necessário realocar memória
    if (total_clientes >= capacidade_clientes) {
        printf("Re-alocando memória: capacidade atual = %d, total_clientes = %d\n", capacidade_clientes, total_clientes);
        int nova_capacidade = capacidade_clientes * ((total_clientes / 10) + 1);
        Cliente *novo_array = realloc(clientes_ptr, nova_capacidade * sizeof(Cliente));
        if (novo_array == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
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

    // Grava os dados do cliente no arquivo
    fprintf(file, "%d,%s,%s,%s,%s,%s\n",
            cliente->id_cliente,
            cliente->nome,
            cliente->cpf,
            cliente->cell,
            cliente->endereco,
            cliente->data);

    total_clientes++;
    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");

    // Fecha o arquivo
    fclose(file);

    // Libera a memória alocada (se necessário)
    if (total_clientes == capacidade_clientes) {
        free(clientes_ptr);
        clientes_ptr = NULL;
        printf("Memória liberada após cadastro.\n");
    }
}
void listar_clientes() {
    FILE *file = fopen("cliente_dados.txt", "r"); // Abre o arquivo no modo leitura
    if (file == NULL) {
        printf("\n\n!!! Erro ao abrir o arquivo !!!\n\n");
        return;
    }
    if (total_clientes == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }

    Cliente cliente;
    printf("\n\n### Lista de Clientes Cadastrados ###\n");

    // Lê os dados do arquivo linha por linha
    while (fscanf(file, "%d,%19[^,],%19[^,],%11[^,],%29[^,],%10[^\n]",
                  &cliente.id_cliente, cliente.nome, cliente.cpf,
                  cliente.cell, cliente.endereco, cliente.data) == 6) {
        printf("\n\n===========================\n");
        printf("ID - CLIENTE: %d\n", cliente.id_cliente);
        printf("===========================\n");
        printf("Nome: %s\nCPF: %s\nCelular: %s\nEndereco: %s\nData: %s\n",
               cliente.nome, cliente.cpf, cliente.cell,
               cliente.endereco, cliente.data);
                  }

    fclose(file); // Fecha o arquivo após a leitura
}
void excluir_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Cliente cliente;
    int encontrado = 0;
    int novo_id = 0; // ID sequencial a ser atribuído

    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        printf("DEBUG: Comparando Nome: %s com Termo: %s\n", cliente.nome, termo);
        printf("DEBUG: Comparando CPF: %s com Termo: %s\n", cliente.cpf, termo);
        // Verifica se o cliente atual corresponde ao critério de exclusão
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("\n\nDEBUG: CLIENTE ENCONTRADO\n");
            encontrado = 1;
            continue; // Pula o cliente encontrado (não escreve no arquivo temporário)
            }

        // Reatribui ID ao cliente restante
        cliente.id_cliente = novo_id++;
        fwrite(&cliente, sizeof(Cliente), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
        remove("temp.txt"); // Remove o arquivo temporário se nenhum cliente foi encontrado
        return;
    }

    // Substitui o arquivo original pelo temporário
    if (remove("cliente_dados.txt") != 0 || rename("temp.txt", "cliente_dados.txt") != 0) {
        printf("Erro ao atualizar o arquivo de clientes.\n");
        return;
    }

    printf("Cliente removido com sucesso e IDs atualizados!\n");
}
void editar_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        // Verifica se o cliente atual corresponde ao critério de edição
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            encontrado = 1;

            // Exibir os dados atuais do cliente
            printf("\nEditando cliente (ID: %d)\n", cliente.id_cliente);
            printf("Nome atual: %s\n", cliente.nome);
            printf("CPF atual: %s\n", cliente.cpf);
            printf("Celular atual: %s\n", cliente.cell);
            printf("Endereço atual: %s\n", cliente.endereco);
            printf("Data atual: %s\n", cliente.data);

            // Solicitar novos dados do cliente
            printf("\nNovo nome: ");
            scanf(" %[^\n]", cliente.nome);
            printf("Novo CPF: ");
            scanf(" %[^\n]", cliente.cpf);
            printf("Novo celular: ");
            scanf(" %[^\n]", cliente.cell);
            printf("Novo endereço: ");
            scanf(" %[^\n]", cliente.endereco);
            printf("Nova data de cadastro: ");
            scanf(" %[^\n]", cliente.data);

            printf("\nCliente editado com sucesso!\n");
        }

        // Escrever o cliente (editado ou não) no arquivo temporário
        fwrite(&cliente, sizeof(Cliente), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
        remove("temp.txt"); // Remove o arquivo temporário se nenhum cliente foi editado
        return;
    }

    // Substitui o arquivo original pelo temporário
    if (remove("cliente_dados.txt") != 0 || rename("temp.txt", "cliente_dados.txt") != 0) {
        printf("Erro ao atualizar o arquivo de clientes.\n");
        return;
    }
}
void buscar_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    // Itera sobre os registros do arquivo
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        // Verifica se o cliente atual corresponde ao critério de busca
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("\n===========================\n");
            printf("ID: %d\nNome: %s\nCPF: %s\nCelular: %s\nEndereço: %s\nData: %s\n",
                   cliente.id_cliente, cliente.nome, cliente.cpf, cliente.cell, cliente.endereco, cliente.data);
            printf("===========================\n");
            encontrado = 1;
            }
    }

    fclose(arquivo);

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