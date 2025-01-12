// ReSharper disable CppDFADeletedPointer
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
    FILE *file = fopen("cliente_dados.bin", "rb+");
    if (file == NULL) {
        // Tenta criar o arquivo se ele não existir
        file = fopen("cliente_dados.bin", "wb+");
        if (file == NULL) {
            printf("Erro ao abrir ou criar o arquivo de clientes.\n");
            return;
        }
    }

    // Inicializa memória apenas se clientes_ptr for NULL
    if (clientes_ptr == NULL) {
        printf("DEBUG: Inicializando clientes_ptr...\n");
        clientes_ptr = malloc(10 * sizeof(Cliente));
        if (clientes_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        capacidade_clientes = 10;
        printf("DEBUG: clientes_ptr inicializado com capacidade: %d\n", capacidade_clientes);
    }

    // Verifica se é necessário realocar memória
    if (carregar_ultimo_idCL() >= capacidade_clientes) {
        printf("DEBUG: Re-alocando memória: capacidade atual = %d, total_clientes = %d\n", capacidade_clientes, total_clientes);
        int nova_capacidade = capacidade_clientes * ((carregar_ultimo_idCL() / 10) + 1);
        Cliente *novo_array = realloc(clientes_ptr, nova_capacidade * sizeof(Cliente));
        if (novo_array == NULL) {
            printf("\n\nDEBUG: !!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        clientes_ptr = novo_array;
        capacidade_clientes = nova_capacidade;
        printf("DEBUG: Re-alocação concluída. Nova capacidade: %d\n", capacidade_clientes);
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
    cliente->id_cliente = carregar_ultimo_idCL();

    // Grava os dados no arquivo
    fseek(file, 0, SEEK_END); // Garante que os dados serão gravados no final
    fwrite(cliente, sizeof(Cliente), 1, file);


    salvar_ultimo_idCL(carregar_ultimo_idCL() + 1);
    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");

    // Fecha o arquivo
    fclose(file);

    // Libera a memória alocada (se necessário)
    if (carregar_ultimo_idCL() == capacidade_clientes) {
        free(clientes_ptr);
        clientes_ptr = NULL;
        printf("Memória liberada após cadastro.\n");
    }
}
void listar_clientes() {
    FILE *file = fopen("cliente_dados.bin", "rb"); // Abre o arquivo no modo binário leitura
    if(carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (file == NULL) {
        printf("\n\n!!! Erro ao abrir o arquivo cliente_dados.txt !!!\n\n");
        return;
    }

    if (carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        fclose(file); // Garante que o arquivo seja fechado mesmo sem clientes
        return;
    }

    Cliente cliente;
    printf("\n\n### Lista de Clientes Cadastrados ###\n");

    // Lê os dados do arquivo registro por registro
    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
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
    FILE *arquivo = fopen("cliente_dados.bin", "rb"); // Abre o arquivo no modo binário leitura
    if(carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb"); // Cria um arquivo temporário no modo binário escrita
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Cliente cliente;
    int encontrado = 0; // Indica se o cliente a ser excluído foi encontrado
    int novo_id = 0;     // ID sequencial a ser atribuído aos clientes restantes

    // Lê os clientes do arquivo original e os processa
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        printf("DEBUG: Comparando Nome: %s com Termo: %s\n", cliente.nome, termo);
        printf("DEBUG: Comparando CPF: %s com Termo: %s\n", cliente.cpf, termo);

        // Verifica se o cliente atual corresponde ao critério de exclusão
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("\n\nDEBUG: CLIENTE ENCONTRADO\n");
            encontrado = 1;
            continue; // Pula o cliente encontrado (não o escreve no arquivo temporário)
        }

        // Reatribui ID ao cliente restante
        cliente.id_cliente = novo_id++;
        fwrite(&cliente, sizeof(Cliente), 1, temp); // Escreve no arquivo temporário
    }

    fclose(arquivo); // Fecha o arquivo original
    fclose(temp);    // Fecha o arquivo temporário

    // Se o cliente não foi encontrado
    if (!encontrado) {
        printf("Erro: Cliente não encontrado.\n");
        remove("temp.bin"); // Remove o arquivo temporário, pois não houve alterações
        return;
    }

    // Atualiza o último ID salvo
    salvar_ultimo_idCL(novo_id - 1);

    // Substitui o arquivo original pelo temporário
    if (remove("cliente_dados.bin") != 0 || rename("temp.bin", "cliente_dados.bin") != 0) {
        printf("Erro ao atualizar o arquivo de clientes.\n");
        return;
    }

    printf("Cliente removido com sucesso e IDs atualizados!\n");
}
void editar_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.bin", "rb"); // Modo binário leitura
    if(carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb"); // Modo binário escrita
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    // Lê os clientes do arquivo original
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        // Verifica se o cliente corresponde ao critério de edição
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            encontrado = 1;

            // Exibe os dados atuais do cliente
            printf("\nEditando cliente (ID: %d)\n", cliente.id_cliente);
            printf("Nome atual: %s\n", cliente.nome);
            printf("CPF atual: %s\n", cliente.cpf);
            printf("Celular atual: %s\n", cliente.cell);
            printf("Endereço atual: %s\n", cliente.endereco);
            printf("Data atual: %s\n", cliente.data);

            // Solicita novos dados
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

        // Escreve o cliente (editado ou não) no arquivo temporário
        fwrite(&cliente, sizeof(Cliente), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
        remove("temp.bin"); // Remove o arquivo temporário se nenhuma edição foi feita
        return;
    }

    // Substitui o arquivo original pelo temporário
    if (remove("cliente_dados.bin") != 0 || rename("temp.bin", "cliente_dados.bin") != 0) {
        printf("Erro ao atualizar o arquivo de clientes.\n");
        return;
    }
}
void buscar_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.bin", "rb"); // Modo binário leitura
    if(carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    // Lê os registros do arquivo
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        // Verifica se o cliente corresponde ao critério de busca
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

int carregar_ultimo_idCL() {
    FILE *arquivo = fopen("cliente_id.bin", "r");
    if (arquivo == NULL) {
        // Se o arquivo não existir, inicializa o ID como 1
        return 0;
    }
    int ultimo_id;
    fscanf(arquivo, "%d", &ultimo_id);
    fclose(arquivo);
    return ultimo_id;
}
void salvar_ultimo_idCL(int ultimo_id) {
    FILE *arquivo = fopen("cliente_id.bin", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o último ID.\n");
        return;
    }
    fprintf(arquivo, "%d", ultimo_id);
    fclose(arquivo);
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