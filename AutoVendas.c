
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAR_MAX 50
#define CLIENT_MAX 50
#define CADASTRO_MAX (CAR_MAX + CLIENT_MAX)

typedef struct {
    char modelo[20];
    char fabricante[20];
    int ano_fabricacao;
    int id_carro;
    int categoria;
    int estoque;
    float preco;
} Carro;

typedef struct {
    char nome[20];
    char cpf[20];
    char cell[12];
    char endereco[30];
    char data[11];
    int id_cliente;
} Cliente;

typedef struct {
    char cliente_nome[20];
    int id_venda;
    int quantidade;
    float preco_total;
} Venda;

typedef struct {
    int total_carros;  // Contador de carros
    int total_clientes;  // Contador de clientes
    int total_vendas;  // Contador de vendas
} Cadastro;

// FUNÇÕES CARROS
void cadastrar_carro(Carro *carros, Cadastro *cadastro);
void listar_carros(const Carro *carros, const Cadastro *cadastro);
void excluir_carro(Carro *carros, const char *modelo, Cadastro *cadastro);
void editar_carro(Carro *carros, const char *modelo, const Cadastro *cadastro);
void buscar_carro(const Carro *carros, const char *modelo, const Cadastro *cadastro);

// FUNÇÕES CLIENTES
void cadastrar_cliente(Cliente *clientes, Cadastro *cadastro);
void listar_clientes(const Cliente *clientes, const Cadastro *cadastro);
void excluir_cliente(Cliente *clientes, const char *termo, int tipo, Cadastro *cadastro);
void editar_cliente(Cliente *clientes, const char *termo, int tipo, const Cadastro *cadastro);
void buscar_cliente(const Cliente *clientes, const char *termo, int tipo, const Cadastro *cadastro);

// FUNÇÕES VENDAS
void registrar_venda(Venda *vendas, const Cliente *clientes, Carro *carros, Cadastro *cadastro);
void listar_vendas(const Venda *vendas, const Cadastro *cadastro);


// FUNÇÕES MENU
int menu_principal();

void menu_carros(Carro *carros, Cadastro *cadastro);
void menu_clientes(Cliente *clientes, Cadastro *cadastro);
void menu_vendas(Venda *vendas, const Cliente *clientes, Carro *carros, Cadastro *cadastro);


int main() {
    printf("%d", CAR_MAX);
    Carro carros[CAR_MAX] = {0};
    Cliente clientes[CLIENT_MAX] = {0};
    Venda vendas[CLIENT_MAX] = {0};
    Cadastro cadastro[CADASTRO_MAX] = {0};

    cadastro[0].total_carros = 0;
    cadastro[0].total_clientes = 0;
    cadastro[0].total_vendas = 0;

    int opcao;
    do {
        opcao = menu_principal();
        switch (opcao) {
            case 1:
                menu_carros(carros, cadastro);
            break;
            case 2:
                menu_clientes(clientes, cadastro);
            break;
            case 3:
                menu_vendas(vendas, clientes, carros, cadastro);
            break;
            case 0:
                printf("Finalizando o programa...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}



// Implementação das funções
void cadastrar_carro(Carro *carros,
Cadastro *cadastro) {
    if (cadastro[0].total_carros >= CAR_MAX) {
        printf("\n!!! Limite de carros atingido !!!\n");
        return;
    }
    Carro *carro = &carros[cadastro[0].total_carros];

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

    carro->id_carro = cadastro[0].total_carros;
    cadastro[0].total_carros++;

    printf("\n#### Carro cadastrado com sucesso! ####\n");
}

void listar_carros(const Carro *carros,
const Cadastro *cadastro) {
    if (cadastro[0].total_carros == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }

    for (int i = 0; i < cadastro[0].total_carros; i++) {
        printf("\n\n===========================\n");
        printf("ID - CARRO: %d", carros[i].id_carro);
        printf("\n===========================\n");
        printf("Modelo: %s\nFabricante: %s\nAno: %d\nCategoria: %d\nEstoque: %d\nPreco: %.2f\n",
               carros[i].modelo, carros[i].fabricante, carros[i].ano_fabricacao,
               carros[i].categoria, carros[i].estoque, carros[i].preco);
    }
}

void excluir_carro(Carro *carros, const char *modelo,
Cadastro *cadastro) {
    int encontrado = -1;

    // Procurar o carro pelo modelo
    for (int i = 0; i < cadastro[0].total_carros; i++) {
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
    for (int i = encontrado; i < cadastro[0].total_carros - 1; i++) {
        carros[i] = carros[i + 1];
    }

    // Limpar o último carro
    //memset(&carros[carros[0].total_carros - 1], 0, sizeof(Carro));

    cadastro[0].total_carros--;  // Decrementa total_carros

    // Atualizar os IDs de todos os carros
    for (int i = 0; i < cadastro[0].total_carros; i++) {
        carros[i].id_carro = i;
    }

    printf("Carro com modelo '%s' removido com sucesso!\n", modelo);
}

void editar_carro(Carro *carros, const char *modelo,
const Cadastro *cadastro) {
    int encontrado = -1;
    for (int i = 0; i < cadastro[0].total_carros; i++) {
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

void buscar_carro(const Carro *carros, const char *modelo,
const Cadastro *cadastro) {
    int encontrado = 0;

    for (int i = 0; i < cadastro[0].total_carros; i++) {
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

// ########################################################

void cadastrar_cliente(Cliente *clientes,
    Cadastro *cadastro) {
    if (cadastro[0].total_clientes >= CLIENT_MAX) {
        printf("\n\n!!! Limite de clientes atingido !!!\n\n");
        return;
    }
    Cliente *cliente = &clientes[cadastro[0].total_clientes];

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

    cliente->id_cliente = cadastro[0].total_clientes;
    cadastro[0].total_clientes++;

    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");
}

void listar_clientes(const Cliente *clientes,
const Cadastro *cadastro) {
    if (cadastro[0].total_clientes == 0) {
        printf("\n\n!!! Nenhum cliente cadastrado !!!\n\n");
        return;
    }
    for (int i = 0; i < cadastro[0].total_clientes; i++) {
        printf("\n\n===========================\n");
        printf("ID - CLIENTE: %d\n", clientes[i].id_cliente);
        printf("===========================\n");
        printf("Nome: %s\nCPF: %s\nCelular: %s\nEndereco: %s\nData: %s\n",
               clientes[i].nome, clientes[i].cpf, clientes[i].cell,
               clientes[i].endereco, clientes[i].data);
    }
}

void excluir_cliente(Cliente *clientes, const char *termo, const int tipo,
    Cadastro *cadastro) {
    int encontrado = -1;

    for (int i = 0; i < cadastro[0].total_clientes; i++) {
        Cliente cliente = clientes[i];
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

    // Deslocar os elementos para preencher o espaço vazio
    for (int i = encontrado; i < cadastro[0].total_clientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    cadastro[0].total_clientes--;

    // Atualizar IDs
    for (int i = 0; i < cadastro[0].total_clientes; i++) {
        clientes[i].id_cliente = i;
    }

    printf("Cliente removido com sucesso!\n");
}

void editar_cliente(Cliente *clientes, const char *termo, const int tipo,
const Cadastro *cadastro) {
    int encontrado = -1;

    for (int i = 0; i < cadastro[0].total_clientes; i++) {
        Cliente cliente = clientes[i];
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

    Cliente *cliente = &clientes[encontrado];

    printf("Editando cliente\n");
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

    printf("Cliente editado com sucesso!\n");
}

void buscar_cliente(const Cliente *clientes, const char *termo, const int tipo,
const Cadastro *cadastro) {
    int encontrado = 0;

    for (int i = 0; i < cadastro[0].total_clientes; i++) {
        Cliente cliente = clientes[i];
        if ((tipo == 1 && strcasecmp(cliente.nome, termo) == 0) ||
            (tipo == 2 && strcmp(cliente.cpf, termo) == 0)) {
            printf("\n===========================\n");
            printf("ID: %d\nNome: %s\nCPF: %s\nCelular: %s\nEndereço: %s\nData: %s\n",
                   cliente.id_cliente, cliente.nome, cliente.cpf, cliente.cell, cliente.endereco, cliente.data);
            printf("===========================\n");
            encontrado = 1;
            }
    }

    if (!encontrado) {
        printf("Cliente não encontrado.\n");
    }
}

// ########################################################

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

// ########################################################

// Implementação das funções de menu
int menu_principal() {
    int opcao;
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1. Gerenciar Carros\n");
    printf("2. Gerenciar Clientes\n");
    printf("3. Gerenciar Vendas\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf(" %d", &opcao);
    return opcao;
}

void menu_carros(Carro *carros,
    Cadastro *cadastro) {
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
                cadastrar_carro(carros, cadastro);
            break;
            case 2:
                listar_carros(carros, cadastro);
            break;
            case 3:
                printf("Modelo do carro para editar: ");
            scanf(" %[^\n]", modelo);
            editar_carro(carros, modelo, cadastro);
            break;
            case 4:
                printf("Modelo do carro para excluir: ");
            scanf(" %[^\n]", modelo);
            excluir_carro(carros, modelo, cadastro);
            break;
            case 5:
                printf("Modelo do carro para buscar: ");
            scanf(" %[^\n]", modelo);
            buscar_carro(carros, modelo, cadastro);
            break;
            case 0:
                printf("\nVoltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void menu_clientes(Cliente *clientes,
    Cadastro *cadastro) {
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
                cadastrar_cliente(clientes, cadastro);
            break;
            case 2:
                listar_clientes(clientes, cadastro);
            break;
            case 3:
                printf("\n\nEditar cliente por: ");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            editar_cliente(clientes, termo, tipo, cadastro);
            break;
            case 4:
                printf("\nExcluir cliente por: ");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            excluir_cliente(clientes, termo, tipo, cadastro);
            break;
            case 5:
                printf("Buscar cliente por:");
            printf("\n1 - Nome\n2 - CPF\n> ");
            scanf("%d", &tipo);
            printf("\n\nDigite o termo de busca: ");
            scanf(" %[^\n]", termo);
            buscar_cliente(clientes, termo, tipo, cadastro);
            break;
            case 0:
                printf("\n\nVoltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
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
