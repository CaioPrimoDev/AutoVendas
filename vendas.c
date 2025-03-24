#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vendas.h"

Venda *vendas_ptr = NULL;
int total_vendas = 0;
int capacidade_vendas = 0;
Venda vendas[VENDAS_MAX] = {0};

void registrar_venda() {
    FILE *arquivo_clientes = fopen("cliente_dados.bin", "rb");
    FILE *arquivo_carros = fopen("carro_dados.bin", "rb+");
    FILE *arquivo_vendas = fopen("vendas_dados.bin", "ab");
    if (!arquivo_clientes || !arquivo_carros || !arquivo_vendas) {
        printf("\nErro ao abrir os arquivos necessários para registrar a venda.\n");
        if (arquivo_clientes) fclose(arquivo_clientes);
        if (arquivo_carros) fclose(arquivo_carros);
        if (arquivo_vendas) fclose(arquivo_vendas);
        return;
    }

    char nome_cliente[20], modelo_carro[20];
    int quantidade, cliente_encontrado = 0, carro_encontrado = 0;
    Cliente cliente;
    Carro carro;

    printf("\nNome do Cliente: ");
    scanf(" %[^\n]", nome_cliente);
    while (fread(&cliente, sizeof(Cliente), 1, arquivo_clientes) == 1) {
        if (strcasecmp(cliente.nome, nome_cliente) == 0) {
            cliente_encontrado = 1;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("\n\n!!! Cliente '%s' não encontrado !!!\n\n", nome_cliente);
        fclose(arquivo_clientes);
        fclose(arquivo_carros);
        fclose(arquivo_vendas);
        return;
    }

    printf("\nModelo do Carro: ");
    scanf(" %[^\n]", modelo_carro);
    long posicao_carro = 0;
    while (fread(&carro, sizeof(Carro), 1, arquivo_carros) == 1) {
        if (strcasecmp(carro.modelo, modelo_carro) == 0) {
            carro_encontrado = 1;
            posicao_carro = ftell(arquivo_carros) - sizeof(Carro); // NOLINT(*-narrowing-conversions)
            break;
        }
    }

    if (!carro_encontrado) {
        printf("\n\n!!! Carro '%s' não encontrado !!!\n\n", modelo_carro);
        fclose(arquivo_clientes);
        fclose(arquivo_carros);
        fclose(arquivo_vendas);
        return;
    }

    printf("\nQuantidade Disponível no Estoque: %d\n", carro.estoque);
    printf("\nQuantidade desejada: ");
    scanf("%d", &quantidade);

    if (quantidade > carro.estoque) {
        printf("\n\n!!! Estoque insuficiente !!!\n\n");
        fclose(arquivo_clientes);
        fclose(arquivo_carros);
        fclose(arquivo_vendas);
        return;
    }

    float preco_total = (float) quantidade * carro.preco;
    printf("\nPreço total da venda: R$ %.2f\n", preco_total);

    char confirmar;
    printf("\nDeseja finalizar a compra? (S/N): ");
    scanf(" %c", &confirmar);

    if (confirmar == 'S' || confirmar == 's') {
        Venda venda;
        venda.id_venda = carregar_ultimo_idVE();
        strcpy(venda.cliente_nome, cliente.nome);
        strcpy(venda.modelo_carro, carro.modelo);
        venda.quantidade = quantidade;
        venda.preco_total = preco_total;

        fwrite(&venda, sizeof(Venda), 1, arquivo_vendas);
        salvar_ultimo_idVE(venda.id_venda + 1);

        carro.estoque -= quantidade;
        fseek(arquivo_carros, posicao_carro, SEEK_SET);
        fwrite(&carro, sizeof(Carro), 1, arquivo_carros);

        printf("\n### Venda registrada com sucesso! ###\n");
    } else {
        printf("\n### Venda cancelada! ###\n");
    }

    fclose(arquivo_clientes);
    fclose(arquivo_carros);
    fclose(arquivo_vendas);
}
void listar_vendas() {
    FILE *arquivo_vendas = fopen("vendas_dados.bin", "rb");
    if(carregar_ultimo_idVE() == 0) {
        printf("\n\n!!! Nenhuma venda registrada !!!\n\n");
    }
    if (arquivo_vendas == NULL) {
        printf("\n\n!!! Erro ao abrir o arquivo !!!\n\n");
        return;
    }
    if(carregar_ultimo_idVE() == 0) {
        printf("\n\n!!! Nenhuma venda registrada !!!\n\n");
    }

    Venda venda;
    int total_vendas_lidas = 0;

    while (fread(&venda, sizeof(Venda), 1, arquivo_vendas) == 1) {
        printf("\n===========================\n");
        printf("Cliente: %s\nID do carro: %d\nQuantidade: %d\nPreço Total: R$ %.2f\n",
            venda.cliente_nome,
            venda.id_venda,
            venda.quantidade,
            venda.preco_total);
        printf("===========================\n");
        total_vendas_lidas++;
    }

    fclose(arquivo_vendas);

    if (total_vendas_lidas > 0) {
        printf("\n\nTotal de vendas registradas: %d\n", total_vendas_lidas);
    } else {
        printf("\n\n!!! Nenhuma venda registrada !!!\n\n");
    }
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

int carregar_ultimo_idVE() {
    FILE *arquivo = fopen("vendas_id.bin", "r");
    if (arquivo == NULL) {
        return 0;
    }
    int ultimo_id;
    fscanf(arquivo, "%d", &ultimo_id);
    fclose(arquivo);
    return ultimo_id;
}
void salvar_ultimo_idVE(int ultimo_id) {
    FILE *arquivo = fopen("vendas_id.bin", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o último ID.\n");
        return;
    }
    fprintf(arquivo, "%d", ultimo_id);
    fclose(arquivo);
}
void inicializarVenda(Venda *venda) {
    strcpy(venda->cliente_nome, "");
    strcpy(venda->modelo_carro, "");
    venda->id_venda = 0;
    venda->quantidade = 0;
    venda->preco_total = 0.0f;
}
