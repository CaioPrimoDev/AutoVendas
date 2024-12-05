#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carros.h"

int total_carros = 0;
Carro carros[CAR_MAX] = {0};             // Inicializa a struct Carro

void cadastrar_carro(Carro *carros) {
    if (total_carros >= CAR_MAX) {
        printf("\n!!! Limite de carros atingido !!!\n");
        return;
    }
    Carro *carro = &carros[total_carros];

    printf("\nModelo: ");
    scanf(" %[^\n]", carro->modelo);
    printf("\nFabricante: ");
    scanf(" %[^\n]", carro->fabricante);
    printf("\nAno de Fabricacao: ");
    scanf("%d", &carro->ano_fabricacao);
    printf("\nCategoria (1-5): ");
    scanf("%d", &carro->categoria);
    printf("\nEstoque: ");
    scanf("%d", &carro->estoque);
    printf("\nPreco: ");
    scanf("%f", &carro->preco);

    carro->id_carro = total_carros;
    total_carros++;

    printf("\n#### Carro cadastrado com sucesso! ####\n");
}
void listar_carros(const Carro *carros) {
    if (total_carros == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }

    for (int i = 0; i < total_carros; i++) {
        printf("\n\n===========================\n");
        printf("ID - CARRO: %d", carros[i].id_carro);
        printf("\n===========================\n");
        printf("Modelo: %s\nFabricante: %s\nAno: %d\nCategoria: %d\nEstoque: %d\nPreco: %.2f\n",
               carros[i].modelo, carros[i].fabricante, carros[i].ano_fabricacao,
               carros[i].categoria, carros[i].estoque, carros[i].preco);
    }
}
void excluir_carro(Carro *carros, const char *modelo) {
    int encontrado = -1;

    // Procurar o carro pelo modelo
    for (int i = 0; i < total_carros; i++) {
        if (strcasecmp(carros[i].modelo, modelo) == 0) {
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
        carros[i] = carros[i + 1];
    }

    // Limpar o último carro
    //memset(&carros[carros[0].total_carros - 1], 0, sizeof(Carro));

    total_carros--;  // Decrementa total_carros

    // Atualizar os IDs de todos os carros
    for (int i = 0; i < total_carros; i++) {
        carros[i].id_carro = i;
    }

    printf("Carro com modelo '%s' removido com sucesso!\n", modelo);
}
void editar_carro(Carro *carros, const char *modelo) {
    int encontrado = -1;
    for (int i = 0; i < total_carros; i++) {
        if (strcasecmp(carros[i].modelo, modelo) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Carro com modelo '%s' não encontrado.\n", modelo);
        return;
    }

    Carro *carro = &carros[encontrado];

    printf("Editando carro com modelo '%s'\n", modelo);
    printf("Novo modelo: ");
    scanf(" %[^\n]", carro->modelo);
    printf("Novo fabricante: ");
    scanf(" %[^\n]", carro->fabricante);
    printf("Novo ano de fabricação: ");
    scanf("%d", &carro->ano_fabricacao);
    printf("Nova categoria: ");
    scanf("%d", &carro->categoria);
    printf("Novo estoque: ");
    scanf("%d", &carro->estoque);
    printf("Novo preço: ");
    scanf("%f", &carro->preco);

    printf("Carro editado com sucesso!\n");
}
void buscar_carro(const Carro *carros, const char *modelo) {
    int encontrado = 0;

    for (int i = 0; i < total_carros; i++) {
        if (strcasecmp(carros[i].modelo, modelo) == 0) {
            printf("\n===========================\n");
            printf("ID: %d", carros[i].id_carro);
            printf("\n===========================\n");
            printf("\nModelo: %s\nFabricante: %s\nAno: %d\nCategoria: %d\nEstoque: %d\nPreço: %.2f\n",
                    carros[i].modelo, carros[i].fabricante,
                   carros[i].ano_fabricacao, carros[i].categoria,
                   carros[i].estoque, carros[i].preco);
            encontrado = 1;
        }
    }

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
            editar_carro(carros, modelo);
            break;
            case 4:
                printf("Modelo do carro para excluir: ");
            scanf(" %[^\n]", modelo);
            excluir_carro(carros, modelo);
            break;
            case 5:
                printf("Modelo do carro para buscar: ");
            scanf(" %[^\n]", modelo);
            buscar_carro(carros, modelo);
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
    carro->categoria = 0;
    carro->estoque = 0;
    carro->preco = 0.0f;
}