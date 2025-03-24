// ReSharper disable CppDFADeletedPointer
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carros.h"

#define debug 1

int total_carros = 0;
int capacidade_carros = 0;
Carro *carros_ptr = NULL;
Carro carros[CAR_MAX] = {0};


void cadastrar_carro() {
    FILE *file = fopen("carro_dados.bin", "rb+");
    if (file == NULL) {
        file = fopen("carro_dados.bin", "wb+");
        if (file == NULL) {
            printf("Erro ao abrir ou criar o arquivo de carros.\n");
            return;
        }
    }

    if (carros_ptr == NULL) {
        if(debug)
        printf("DEBUG: Inicializando carros_ptr...\n");
        carros_ptr = malloc(10 * sizeof(Carro)); // NOLINT(*-misleading-indentation)
        if (carros_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        capacidade_carros = 10;
        if(debug)
        printf("DEBUG: carros_ptr inicializado com capacidade: %d\n", capacidade_carros);
    }

    if (carregar_ultimo_idCA() >= capacidade_carros) {
        if(debug)
        printf("DEBUG: Re-alocando memória: capacidade atual = %d, total_carros = %d\n", capacidade_carros, total_carros);
        int nova_capacidade = capacidade_carros * ((carregar_ultimo_idCA() / 10) + 1); // NOLINT(*-misleading-indentation)
        Carro *novo_array = realloc(carros_ptr, nova_capacidade * sizeof(Carro));
        if (novo_array == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        carros_ptr = novo_array;
        capacidade_carros = nova_capacidade;
        if(debug)
        printf("DEBUG: Re-alocação concluída. Nova capacidade: %d\n", capacidade_carros);
    }

    Carro *carro = &carros_ptr[total_carros];
    printf("\nModelo: ");
    scanf(" %[^\n]", carro->modelo);
    printf("Fabricante: ");
    scanf(" %[^\n]", carro->fabricante);
    printf("Ano de Fabricação: ");
    scanf("%d", &carro->ano_fabricacao);
    printf("Categoria: ");
    scanf(" %[^\n]", carro->categoria);
    printf("Estoque: ");
    scanf("%d", &carro->estoque);
    printf("Preço: ");
    scanf("%f", &carro->preco);
    carro->id_carro = carregar_ultimo_idCA();

    fseek(file, 0, SEEK_END);
    fwrite(carro, sizeof(Carro), 1, file);
    salvar_ultimo_idCA(carregar_ultimo_idCA() + 1);

    printf("\n\n### Carro cadastrado com sucesso! ###\n\n");

    fclose(file);

    if (carregar_ultimo_idCA() == capacidade_carros) {
        free(carros_ptr);
        carros_ptr = NULL;
        if(debug)
        printf("DEBUG: Memória liberada após cadastro.\n");
    }
}
void listar_carros() {
    FILE *arquivo = fopen("carro_dados.bin", "rb");
    if (carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("\n\n!!! Erro ao abrir o arquivo carro_dados.bin !!!\n\n");
        return;
    }

    Carro carro;
    int encontrado = 0;

    printf("\n\n< Lista de Carros Cadastrados >");

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        encontrado = 1;
        printf("\n\n===========================\n");
        printf("ID - CARRO: %d\n", carro.id_carro);
        printf("===========================\n");
        printf("> Modelo: %s\n> Fabricante: %s\n> Ano: %d\n> Categoria: %s\n> Estoque: %d\n> Preço: %.2f\n",
               carro.modelo, carro.fabricante, carro.ano_fabricacao,
               carro.categoria, carro.estoque, carro.preco);
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
    }
}
void excluir_carro(const char *modelo) {
FILE *arquivo = fopen("carro_dados.bin", "rb");
    if (carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Carro carro;
    int encontrado = 0;

    int numCA[20];
    int index = 0;
    printf("\n\n### Carros encontrados com o modelo '%s' ###\n", modelo);
    printf("============================================================================================================");
    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcasecmp(carro.modelo, modelo) == 0) {
            printf("\nID - CARRO: %d || Modelo: %s | Fabricante: %s | Ano: %d | Categoria: %s | Estoque: %d | Preço: %.2f",
            carro.id_carro,
            carro.modelo,
            carro.fabricante,
            carro.ano_fabricacao,
            carro.categoria,
            carro.estoque,
            carro.preco);

            numCA[index] = carro.id_carro;
            index++;
            encontrado = 1;
        }
    }
    printf("\n============================================================================================================\n");

    if (!encontrado) {
        printf("\nNenhum carro encontrado com o modelo '%s'.\n", modelo);
        fclose(arquivo);
        return;
    }

    rewind(arquivo);

    int id_excluir;
    int id_valido = 0;

    while (!id_valido) {
        printf("\nInforme um ID válido do carro que deseja excluir: ");
        scanf("%d", &id_excluir);

        for (int i = 0; i < index; i++) {
            if (numCA[i] == id_excluir) {
                id_valido = 1;
                break;
            }
        }

        if (!id_valido) {
            printf("\n\nID inválido. Escolha um ID da lista exibida anteriormente.\n\n");
        }
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    encontrado = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcasecmp(carro.modelo, modelo) == 0 && carro.id_carro == id_excluir) {
            encontrado = 1;
            printf("\nCarro excluído: Modelo '%s', ID %d.\n", carro.modelo, carro.id_carro);
            continue;
        }
        fwrite(&carro, sizeof(Carro), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("\nErro: Nenhum carro encontrado com o modelo '%s' e ID %d.\n", modelo, id_excluir);
        remove("temp.bin");
        return;
    }

    salvar_ultimo_idCA(carregar_ultimo_idCA() - 1);

    if (remove("carro_dados.bin") != 0 || rename("temp.bin", "carro_dados.bin") != 0) {
        printf("Erro ao atualizar o arquivo de carros.\n");
        return;
    }

    printf("\nCarro removido com sucesso e IDs atualizados!\n");
}
void editar_carro(const char *modelo) {
    FILE *arquivo = fopen("carro_dados.bin", "rb");
    if (carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Carro carro;
    int encontrado = 0;

    int numCA[20];
    int index = 0;
    printf("\n\n</> Carros encontrados com o modelo '%s' </>\n", modelo);
    printf("============================================================================================================");
    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcasecmp(carro.modelo, modelo) == 0) {
            printf("\nID - CARRO: %d || Modelo: %s | Fabricante: %s | Ano: %d | Categoria: %s | Estoque: %d | Preço: %.2f",
            carro.id_carro,
            carro.modelo,
            carro.fabricante,
            carro.ano_fabricacao,
            carro.categoria,
            carro.estoque,
            carro.preco);

            numCA[index] = carro.id_carro;
            index++;
            encontrado = 1;
        }
    }
    printf("\n============================================================================================================\n");

    if (!encontrado) {
        printf("\nNenhum carro encontrado com o modelo '%s'.\n", modelo);
        fclose(arquivo);
        fclose(temp);
        remove("temp.bin");
        return;
    }

    rewind(arquivo);

    int id_editar;
    int id_valido = 0;

    while (!id_valido) {
        printf("\nInforme o ID do cliente que deseja editar: ");
        scanf("%d", &id_editar);

        for (int i = 0; i < index; i++) {
            if (numCA[i] == id_editar) {
                id_valido = 1;
                break;
            }
        }
        if (!id_valido) {
            printf("\n\nID inválido. Escolha um ID da lista exibida anteriormente.\n\n");
        }
    }
    encontrado = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcasecmp(carro.modelo, modelo) == 0 && carro.id_carro == id_editar) {
            encontrado = 1;

            printf("\nNovo modelo (Atual: %s): ", carro.modelo);
                scanf(" %[^\n]", carro.modelo);
            printf("Novo fabricante (Atual: %s): ", carro.fabricante);
                scanf(" %[^\n]", carro.fabricante);
            printf("Novo ano de fabricação (Atual: %d): ", carro.ano_fabricacao);
                scanf("%d", &carro.ano_fabricacao);
            printf("Nova categoria (Atual: %s): ", carro.categoria);
                scanf(" %[^\n]", carro.categoria);
            printf("Novo estoque (Atual: %d): ", carro.estoque);
                scanf("%d", &carro.estoque);
            printf("Novo preço (Atual: %f): ", carro.preco);
                scanf("%f", &carro.preco);

            printf("\nCarro editado com sucesso!\n");
        }

        fwrite(&carro, sizeof(Carro), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("\nErro: Nenhum carro encontrado com o modelo '%s' e ID %d.\n", modelo, id_editar);
        remove("temp.bin");
        return;
    }

    if (remove("carro_dados.bin") != 0 || rename("temp.bin", "carro_dados.bin") != 0) {
        printf("Erro ao atualizar o arquivo de carros.\n");
        return;
    }
}
void buscar_carro(const char *modelo) {
    FILE *arquivo = fopen("carro_dados.bin", "rb"); // Abre o arquivo no modo binário leitura
    if(carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    Carro carro;
    int encontrado = 0;

    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        if (strcasecmp(carro.modelo, modelo) == 0) {
            printf("\n===========================\n");
            printf("ID: %d\nModelo: %s\nFabricante: %s\nAno de fabricação: %d\nCategoria: %s\nEstoque: %d\nPreço: %.2f\n",
                   carro.id_carro,
                   carro.modelo,
                   carro.fabricante,
                   carro.ano_fabricacao,
                   carro.categoria,
                   carro.estoque,
                   carro.preco);
            printf("===========================\n");
            encontrado = 1;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Carro com modelo '%s' não encontrado.\n", modelo);
    }
}
void menu_carros(Carro *carros) {
    int opcao;
    do {
        printf("\n======== MENU - CARROS ========\n");
        printf("1. Cadastrar Carro\n");
        printf("2. Listar Carros\n");
        printf("3. Editar Carro\n");
        printf("4. Excluir Carro\n");
        printf("5. Buscar Carro\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        char modelo[20];

        switch (opcao) {
            case 1:
                cadastrar_carro(carros);
            break;
            case 2:
                listar_carros(carros);
            break;
            case 3:
                printf("Modelo do carro para editar: ");
            scanf(" %[^\n]", modelo);
            editar_carro(modelo);
            break;
            case 4:
                printf("Modelo do carro para excluir: ");
            scanf(" %[^\n]", modelo);
            excluir_carro(modelo);
            break;
            case 5:
                printf("Modelo do carro para buscar: ");
            scanf(" %[^\n]", modelo);
            buscar_carro(modelo);
            break;
            case 0:
                printf("\nVoltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

int carregar_ultimo_idCA() {
    FILE *arquivo = fopen("carro_id.bin", "r");
    if (arquivo == NULL) {
        return 0;
    }
    int ultimo_id;
    fscanf(arquivo, "%d", &ultimo_id);
    fclose(arquivo);
    return ultimo_id;
}
void salvar_ultimo_idCA(int ultimo_id) {
    FILE *arquivo = fopen("carro_id.bin", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o último ID.\n");
        return;
    }
    fprintf(arquivo, "%d", ultimo_id);
    fclose(arquivo);
}
void inicializarCarro(Carro *carro) {
    strcpy(carro->modelo, "");
    strcpy(carro->fabricante, "");
    carro->ano_fabricacao = 0;
    carro->id_carro = 0;
    strcpy(carro->categoria, "");
    carro->estoque = 0;
    carro->preco = 0.0f;
}