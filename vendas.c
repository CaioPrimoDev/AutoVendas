#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vendas.h"
#include "carros.h"
#include "clientes.h"


void registrar_venda(Venda *vendas, const Cliente *clientes, Carro *carros,
Cadastro *cadastro) {
    if (cadastro[0].total_clientes == 0 || cadastro[0].total_carros == 0) {
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
    for (int i = 0; i < cadastro[0].total_clientes; i++) {
        if (strcasecmp(clientes[i].nome, nome_cliente) == 0) {
            cliente_index = i;
            break;
        }
    }

    if (cliente_index == -1) {
        printf("\n\n!!! Cliente '%s' não encontrado !!!\n\n", nome_cliente);
        return;
    }

    // Exibe informações do cliente
    Cliente cliente = clientes[cliente_index];
    printf("\n===== Informações do Cliente =====\n");
    printf("- Nome: %s\n- CPF: %s\n- Celular: %s\n- Endereço: %s\n",
           cliente.nome, cliente.cpf, cliente.cell, cliente.endereco);
    printf("\n==================================\n");

    // Busca pelo modelo do carro
    printf("\nModelo do Carro: ");
    scanf(" %[^\n]", modelo_carro);

    int carro_index = -1;
    for (int i = 0; i < cadastro[0].total_carros; i++) {
        if (strcasecmp(carros[i].modelo, modelo_carro) == 0) {
            carro_index = i;
            break;
        }
    }

    if (carro_index == -1) {
        printf("\n\n!!! Carro '%s' não encontrado !!!\n\n", modelo_carro);
        return;
    }

    // Exibe informações do carro
    Carro carro = carros[carro_index];
    printf("\n===== Informações do Carro =====\n");
    printf("Modelo: %s\nFabricante: %s\nAno: %d\nCategoria: %d\nEstoque Disponível: %d\nPreço Unitário: %.2f\n",
           carro.modelo, carro.fabricante, carro.ano_fabricacao, carro.categoria, carro.estoque, carro.preco);
    printf("\n=================================\n");

    // Verifica estoque antes de continuar
    printf("\nQuantidade Disponível no Estoque: %d\n", carro.estoque);
    printf("\nQuantidade desejada: ");
    scanf("%d", &quantidade);

    if (quantidade > carro.estoque) {
        printf("\n\n!!! Estoque insuficiente !!!\n\n");
        return;
    }

    // Calcula preço total
    float preco_total = quantidade * carro.preco; // NOLINT(*-narrowing-conversions)
    printf("\nPreço total da venda: R$ %.2f\n", preco_total);

    // Confirmação final
    char confirmar;
    printf("\nDeseja finalizar a compra? (S/N): ");
    scanf(" %c", &confirmar);

    if (confirmar == 'S' || confirmar == 's') {
        // Registro da venda
        Venda *venda = &vendas[cadastro[0].total_vendas];
        strcpy(venda->cliente_nome, cliente.nome);
        venda->id_venda = carro_index;
        venda->quantidade = quantidade;
        venda->preco_total = preco_total;

        // Atualiza o estoque
        carros[carro_index].estoque -= quantidade;

        // Incrementa o total de vendas
        cadastro[0].total_vendas++;

        printf("\n### Venda registrada com sucesso! ###\n");
    } else {
        printf("\n### Venda cancelada! ###\n");
    }
}

void listar_vendas(const Venda *vendas,
const Cadastro *cadastro) {
    if (cadastro[0].total_vendas == 0) {
        printf("\n\n< Nenhuma venda registrada >\n\n");
        return;
    }

    for (int i = 0; i < cadastro[0].total_vendas; i++) {
        printf("\n===========================\n");
        printf("Cliente: %s\nID do carro: %d",vendas[i].cliente_nome, vendas[i].id_venda);
        printf("\n===========================");
        printf("\nQuantidade: %d\nPreço Total: R$ %.2f\n",
               vendas[i].quantidade, vendas[i].preco_total);

    }
}

void menu_vendas(Venda *vendas, const Cliente *clientes, Carro *carros,
    Cadastro *cadastro) {
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
                registrar_venda(vendas, clientes, carros, cadastro);
            break;
            case 2:
                listar_vendas(vendas, cadastro);
            break;
            case 0:
                printf("\n\nVoltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void chamarMenu_vendas() {
    menu_vendas(vendas, clientes, carros, cadastro);
}