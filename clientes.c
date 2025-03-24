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
#define debug 1

void cadastrar_cliente() {
    FILE *file = fopen("cliente_dados.bin", "rb+");
    if (file == NULL) {
        file = fopen("cliente_dados.bin", "wb+");
        if (file == NULL) {
            printf("Erro ao abrir ou criar o arquivo de clientes.\n");
            return;
        }
    }

    if (clientes_ptr == NULL) {
        if(debug)
        printf("DEBUG: Inicializando clientes_ptr...\n");
        clientes_ptr = malloc(10 * sizeof(Cliente)); // NOLINT(*-misleading-indentation)
        if (clientes_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        capacidade_clientes = 10;
        if(debug)
        printf("DEBUG: clientes_ptr inicializado com capacidade: %d\n", capacidade_clientes);
    }

    if (carregar_ultimo_idCL() >= capacidade_clientes) {
        if(debug)
        printf("DEBUG: Re-alocando memória: capacidade atual = %d, total_clientes = %d\n", capacidade_clientes, total_clientes);
        int nova_capacidade = capacidade_clientes * ((carregar_ultimo_idCL() / 10) + 1); // NOLINT(*-misleading-indentation)
        Cliente *novo_array = realloc(clientes_ptr, nova_capacidade * sizeof(Cliente));
        if (novo_array == NULL) {
            printf("\n\nDEBUG: !!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        clientes_ptr = novo_array;
        capacidade_clientes = nova_capacidade;
        if(debug)
        printf("DEBUG: Re-alocação concluída. Nova capacidade: %d\n", capacidade_clientes);
    }

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
    cliente->id_cliente = carregar_ultimo_idCL();

    fseek(file, 0, SEEK_END); // Garante que os dados serão gravados no final
    fwrite(cliente, sizeof(Cliente), 1, file);


    salvar_ultimo_idCL(carregar_ultimo_idCL() + 1);
    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");
    fclose(file);

    if (carregar_ultimo_idCL() == capacidade_clientes) {
        free(clientes_ptr);
        clientes_ptr = NULL;
        if(debug)
        printf("DEBUG: Memória liberada após cadastro.\n");
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
        fclose(file);
        return;
    }

    Cliente cliente;
    printf("\n\n### Lista de Clientes Cadastrados ###\n");

    while (fread(&cliente, sizeof(Cliente), 1, file) == 1) {
        printf("\n\n===========================\n");
        printf("ID - CLIENTE: %d\n", cliente.id_cliente);
        printf("===========================\n");
        printf("Nome: %s\nCPF: %s\nCelular: %s\nEndereco: %s\nData: %s\n",
               cliente.nome, cliente.cpf, cliente.cell,
               cliente.endereco, cliente.data);
    }

    fclose(file);
}
void excluir_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.bin", "rb");
    if (carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    int numCL[20];
    int index = 0;
    printf("Clientes encontrados:\n");
    printf("============================================================================================================\n");
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("ID: %d | Nome: %s | CPF: %s\n",
                cliente.id_cliente,
                cliente.nome,
                cliente.cpf);

            numCL[index] = cliente.id_cliente;
            index++;
            encontrado = 1;
        }
    }
    printf("============================================================================================================\n");

    fclose(arquivo);

    if (!encontrado) {
        printf("Nenhum cliente encontrado com o termo informado.\n");
        return;
    }

    int id_excluir;
    int id_valido = 0;

    while (!id_valido) {
        printf("\nInforme um ID válido do cliente que deseja excluir: ");
        scanf("%d", &id_excluir);

        for (int i = 0; i < index; i++) {
            if (numCL[i] == id_excluir) {
                id_valido = 1;
                break;
            }
        }

        if (!id_valido) {
            printf("\n\nID inválido. Escolha um ID da lista exibida anteriormente.\n\n");
        }
    }

    arquivo = fopen("cliente_dados.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    encontrado = 0;
    int maior_id = -1;

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (cliente.id_cliente == id_excluir) {
            encontrado = 1; // Cliente encontrado e será excluído
            continue;
        }

        fwrite(&cliente, sizeof(Cliente), 1, temp);

        if (cliente.id_cliente > maior_id) {
            maior_id = cliente.id_cliente;
        }
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Erro: Cliente com ID %d não encontrado.\n", id_excluir);
        remove("temp.bin");
        return;
    }

    remove("cliente_dados.bin");
    rename("temp.bin", "cliente_dados.bin");

    salvar_ultimo_idCL(maior_id + 1);

    printf("\n\nCliente com ID: %d excluído com sucesso!\n", id_excluir);
}
void editar_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.bin", "rb+");
    if (carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    int numCL[20];
    int index = 0;
    printf("Clientes encontrados:\n");
    printf("============================================================================================================\n");
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("ID: %d | Nome: %s | CPF: %s\n", cliente.id_cliente, cliente.nome, cliente.cpf);

            numCL[index] = cliente.id_cliente;
            index++;
            encontrado = 1;
            }
    }
    printf("============================================================================================================\n");

    if (!encontrado) {
        printf("Nenhum cliente encontrado com o termo informado.\n");
        fclose(arquivo);
        return;
    }

    int id_editar;
    int id_valido = 0;

    while (!id_valido) {
        printf("Informe o ID do cliente que deseja editar: ");
        scanf("%d", &id_editar);

        for (int i = 0; i < index; i++) {
            if (numCL[i] == id_editar) {
                id_valido = 1;
                break;
            }
        }

        if (!id_valido) {
            printf("\n\nID inválido. Escolha um ID da lista exibida anteriormente.\n\n");
        }
    }

    rewind(arquivo);
    encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (cliente.id_cliente == id_editar) {
            encontrado = 1;

            printf("Digite o novo nome (atual: %s): ", cliente.nome);
            scanf(" %[^\n]", cliente.nome);
            printf("Digite o novo CPF (atual: %s): ", cliente.cpf);
            scanf(" %[^\n]", cliente.cpf);
            printf("Digite o novo celular (atual: %s): ", cliente.cell);
            scanf(" %[^\n]", cliente.cell);
            printf("Digite o novo endereço (atual: %s): ", cliente.endereco);
            scanf(" %[^\n]", cliente.endereco);
            printf("Digite a nova data (atual: %s): ", cliente.data);
            scanf(" %[^\n]", cliente.data);

            fseek(arquivo, -(long int)sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);

            printf("Cliente com ID: %d atualizado com sucesso!\n", id_editar);
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Erro: Cliente com ID %d não encontrado para edição.\n", id_editar);
    }
}
void buscar_cliente(const char *termo, int tipo) {
    FILE *arquivo = fopen("cliente_dados.bin", "rb"); // Modo binário leitura
    if (carregar_ultimo_idCL() == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
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
    strcpy(cliente->nome, "");
    strcpy(cliente->cpf, "");
    strcpy(cliente->cell, "");
    strcpy(cliente->endereco, "");
    strcpy(cliente->data, "");
    cliente->id_cliente = 0;
}