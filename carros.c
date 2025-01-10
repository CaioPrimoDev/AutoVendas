#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carros.h"



// Definições das variáveis globais
int total_carros = 0;
int capacidade_carros = 0;
Carro *carros_ptr = NULL;
Carro carros[CAR_MAX] = {0};             // Inicializa a struct Carro

// Função para cadastrar um carro
void cadastrar_carro() {
    // Inicializa memória apenas se carros_ptr for NULL
    if (carros_ptr == NULL) {
        printf("Inicializando carros_ptr...\n");
        carros_ptr = malloc(10 * sizeof(Carro));
        if (carros_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            return;
        }
        capacidade_carros = 10;
        printf("carros_ptr inicializado com capacidade: %d\n", capacidade_carros);
    }

    // Verifica se é necessário realocar memória
    if (total_carros >= capacidade_carros) {
        printf("Re-alocando memória: capacidade atual = %d, total_carros = %d\n", capacidade_carros, total_carros);
        int nova_capacidade = capacidade_carros * 2;
        Carro *novo_array = realloc(carros_ptr, nova_capacidade * sizeof(Carro));
        if (novo_array == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            return;
        }
        carros_ptr = novo_array;
        capacidade_carros = nova_capacidade;
        printf("Re-alocação concluída. Nova capacidade: %d\n", capacidade_carros);
    }

    // Cadastra o carro no array
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

    // Atribui ID ao carro
    carro->id_carro = total_carros;
    total_carros++;

    printf("\n\n### Carro cadastrado com sucesso! ###\n\n");
}
void listar_carros() {
    // Verifica se há carros cadastrados
    if (carros_ptr == NULL || total_carros == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }

    // Percorre e exibe os carros cadastrados
    for (int i = 0; i < total_carros; i++) {
        printf("\n\n===========================\n");
        printf("ID - CARRO: %d\n", carros_ptr[i].id_carro);
        printf("===========================\n");
        printf("Modelo: %s\nFabricante: %s\nAno: %d\nCategoria: %s\nEstoque: %d\nPreco: %.2f\n",
               carros_ptr[i].modelo,
               carros_ptr[i].fabricante,
               carros_ptr[i].ano_fabricacao,
               carros_ptr[i].categoria,
               carros_ptr[i].estoque,
               carros_ptr[i].preco);
    }
}
void excluir_carro(const char *modelo) {
    if (carros_ptr == NULL || total_carros == 0) {
        printf("Nenhum carro para excluir.\n");
        return;
    }

    int encontrado = -1;

    // Procurar o carro pelo modelo
    for (int i = 0; i < total_carros; i++) {
        if (strcasecmp(carros_ptr[i].modelo, modelo) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Carro com modelo '%s' não encontrado.\n", modelo);
        return;
    }

    // Remover o carro encontrado deslocando os elementos
    for (int i = encontrado; i < total_carros - 1; i++) {
        carros_ptr[i] = carros_ptr[i + 1];
    }
    total_carros--;  // Decrementa total_carros

    // Atualizar os IDs de todos os carros
    for (int i = 0; i < total_carros; i++) {
        carros_ptr[i].id_carro = i;
    }

    // Reajustar a capacidade se necessário
    if (total_carros < capacidade_carros / 2 && capacidade_carros > 10) {
        int nova_capacidade = capacidade_carros / 2;
        Carro *novo_array = (Carro *)realloc(carros_ptr, nova_capacidade * sizeof(Carro));
        if (novo_array != NULL) {
            carros_ptr = novo_array;
            capacidade_carros = nova_capacidade;
            printf("Capacidade reduzida para %d após exclusão.\n", capacidade_carros);
        }
    }

    printf("Carro com modelo '%s' removido com sucesso!\n", modelo);
}
void editar_carro(const char *modelo) {
    if (carros_ptr == NULL || total_carros == 0) {
        printf("Nenhum carro para editar.\n");
        return;
    }

    int encontrado = -1;

    // Procurar o carro pelo modelo
    for (int i = 0; i < total_carros; i++) {
        if (strcasecmp(carros_ptr[i].modelo, modelo) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Carro com modelo '%s' não encontrado.\n", modelo);
        return;
    }

    // Obter referência ao carro encontrado
    Carro *carro = &carros_ptr[encontrado];

    // Editar as informações do carro
    printf("Editando carro (ID: %d, Modelo: %s)\n", carro->id_carro, carro->modelo);
    printf("Novo modelo: ");
    scanf(" %[^\n]", carro->modelo);
    printf("Novo fabricante: ");
    scanf(" %[^\n]", carro->fabricante);
    printf("Novo ano de fabricação: ");
    scanf("%d", &carro->ano_fabricacao);
    printf("Nova categoria: ");
    scanf(" %[^\n]", carro->categoria);
    printf("Novo estoque: ");
    scanf("%d", &carro->estoque);
    printf("Novo preço: ");
    scanf("%f", &carro->preco);

    printf("\nCarro editado com sucesso!\n");
}
void buscar_carro(const char *modelo) {
    if (carros_ptr == NULL || total_carros == 0) {
        printf("Nenhum carro cadastrado para buscar.\n");
        return;
    }

    int encontrado = 0;

    // Itera sobre os carros para encontrar o modelo
    for (int i = 0; i < total_carros; i++) {
        Carro carro = carros_ptr[i];
        if (strcasecmp(carro.modelo, modelo) == 0) {
            printf("\n===========================\n");
            printf("ID: %d\nModelo: %s\nFabricante: %s\nAno: %d\nCategoria: %s\nEstoque: %d\nPreço: %.2f\n",
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

    // Exibe mensagem caso nenhum carro seja encontrado
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
void inicializarCarro(Carro *carro) {
    // Inicializa os campos do carro
    strcpy(carro->modelo, "");
    strcpy(carro->fabricante, "");
    carro->ano_fabricacao = 0;
    carro->id_carro = 0;
    strcpy(carro->categoria, "");
    carro->estoque = 0;
    carro->preco = 0.0f;
}