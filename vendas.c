#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"

Venda *vendas_ptr = NULL;
int total_vendas = 0;
int capacidade_vendas = 0;
Venda vendas[VENDAS_MAX] = {0};  // Inicializa a struct Venda

void registrar_venda() {
    // Inicializa memória apenas se vendas_ptr for NULL
    if (vendas_ptr == NULL) {
        printf("Inicializando vendas_ptr...\n");
        vendas_ptr = malloc(10 * sizeof(Venda));
        if (vendas_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            return;
        }
        capacidade_vendas = 10;
        total_vendas = 0;
        printf("vendas_ptr inicializado com capacidade: %d\n", capacidade_vendas);
    }

    // Verifica se é necessário realocar memória
    if (total_vendas >= capacidade_vendas) {
        printf("Re-alocando memória: capacidade atual = %d, total_vendas = %d\n", capacidade_vendas, total_vendas);
        int nova_capacidade = capacidade_vendas * 2;
        Venda *novo_array = realloc(vendas_ptr, nova_capacidade * sizeof(Venda));
        if (novo_array == NULL) {
            printf("\n\n!!! Erro ao realocar memória !!!\n\n");
            return;
        }
        vendas_ptr = novo_array;
        capacidade_vendas = nova_capacidade;
        printf("Re-alocação concluída. Nova capacidade: %d\n", capacidade_vendas);
    }

    // Verifica se há clientes e carros cadastrados
    if (total_clientes == 0 || total_carros == 0) {
        printf("\n\n< Necessário pelo menos um cliente e um carro cadastrados para registrar uma venda >\n\n");
        return;
    }

    char nome_cliente[20];
    char modelo_carro[20];
    int quantidade;

    // Busca pelo nome do cliente
    printf("\nNome do Cliente: ");
    scanf(" %[^\n]", nome_cliente);

    int cliente_index = -1;
    for (int i = 0; i < total_clientes; i++) {
        if (strcasecmp(clientes_ptr[i].nome, nome_cliente) == 0) {
            cliente_index = i;
            break;
        }
    }

    if (cliente_index == -1) {
        printf("\n\n!!! Cliente '%s' não encontrado !!!\n\n", nome_cliente);
        return;
    }

    // Busca pelo modelo do carro
    printf("\nModelo do Carro: ");
    scanf(" %[^\n]", modelo_carro);

    int carro_index = -1;
    for (int i = 0; i < total_carros; i++) {
        if (strcasecmp(carros_ptr[i].modelo, modelo_carro) == 0) {
            carro_index = i;
            break;
        }
    }

    if (carro_index == -1) {
        printf("\n\n!!! Carro '%s' não encontrado !!!\n\n", modelo_carro);
        return;
    }

    // Verifica estoque antes de continuar
    Carro *carro = &carros_ptr[carro_index];
    printf("\nQuantidade Disponível no Estoque: %d\n", carro->estoque);
    printf("\nQuantidade desejada: ");
    scanf("%d", &quantidade);

    if (quantidade > carro->estoque) {
        printf("\n\n!!! Estoque insuficiente !!!\n\n");
        return;
    }

    // Calcula preço total
    float preco_total = (float) quantidade * carro->preco;
    printf("\nPreço total da venda: R$ %.2f\n", preco_total);

    // Confirmação final
    char confirmar;
    printf("\nDeseja finalizar a compra? (S/N): ");
    scanf(" %c", &confirmar);

    if (confirmar == 'S' || confirmar == 's') {
        // Registro da venda
        Venda *venda = &vendas_ptr[total_vendas];
        strcpy(venda->cliente_nome, clientes_ptr[cliente_index].nome);
        venda->id_venda = carro->id_carro;
        venda->quantidade = quantidade;
        venda->preco_total = preco_total;

        // Atualiza o estoque
        carro->estoque -= quantidade;

        // Incrementa o total de vendas
        total_vendas++;

        printf("\n### Venda registrada com sucesso! ###\n");
    } else {
        printf("\n### Venda cancelada! ###\n");
    }
}
void listar_vendas() {
    // Verifica se o ponteiro de vendas está alocado e se há vendas registradas
    if (vendas_ptr == NULL || total_vendas == 0) {
        printf("\n\n!!! Nenhuma venda registrada !!!\n\n");
        return;
    }

    // Percorre e exibe as vendas cadastradas
    for (int i = 0; i < total_vendas; i++) {
        printf("\n===========================\n");
        printf("Cliente: %s\nID do carro: %d\n", vendas_ptr[i].cliente_nome, vendas_ptr[i].id_venda);
        printf("===========================\n");
        printf("Quantidade: %d\nPreço Total: R$ %.2f\n",
               vendas_ptr[i].quantidade, vendas_ptr[i].preco_total);
    }

    // Exibe o total de vendas registradas
    printf("\n\nTotal de vendas registradas: %d\n", total_vendas);
}
void menu_vendas(Venda *vendas, const Cliente *clientes, Carro *carros) {
    int opcao;
    do {
        printf("\n======== MENU - VENDAS ========\n");
        printf("1. Registrar Venda\n");
        printf("2. Listar Vendas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                registrar_venda(vendas, clientes, carros);
                break;
            case 2:
                listar_vendas(vendas);
                break;
            case 0:
                printf("\n\nVoltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void inicializarVenda(Venda *venda) {
    // Inicializa os campos da venda
    strcpy(venda->cliente_nome, "Desconhecido");
    venda->id_venda = 0;
    venda->quantidade = 0;
    venda->preco_total = 0.0f;
}
