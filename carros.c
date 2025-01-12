// ReSharper disable CppDFADeletedPointer
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carros.h"

// Definições das variáveis globais
int total_carros = 0;
int capacidade_carros = 0;
Carro *carros_ptr = NULL;
Carro carros[CAR_MAX] = {0};


void cadastrar_carro() {
    // Abre o arquivo de carros para leitura e escrita
    FILE *file = fopen("carro_dados.bin", "rb+");
    if (file == NULL) {
        // Cria o arquivo caso ele não exista
        file = fopen("carro_dados.bin", "wb+");
        if (file == NULL) {
            printf("Erro ao abrir ou criar o arquivo de carros.\n");
            return;
        }
    }

    // Inicializa memória apenas se carros_ptr for NULL
    if (carros_ptr == NULL) {
        printf("DEBUG: Inicializando carros_ptr...\n");
        carros_ptr = malloc(10 * sizeof(Carro));
        if (carros_ptr == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        capacidade_carros = 10;
        printf("DEBUG: carros_ptr inicializado com capacidade: %d\n", capacidade_carros);
    }

    // Verifica se é necessário realocar memória
    if (carregar_ultimo_idCA() >= capacidade_carros) {
        printf("DEBUG: Re-alocando memória: capacidade atual = %d, total_carros = %d\n", capacidade_carros, total_carros);
        int nova_capacidade = capacidade_carros * ((carregar_ultimo_idCA() / 10) + 1);
        Carro *novo_array = realloc(carros_ptr, nova_capacidade * sizeof(Carro));
        if (novo_array == NULL) {
            printf("\n\n!!! Erro ao alocar memória !!!\n\n");
            fclose(file);
            return;
        }
        carros_ptr = novo_array;
        capacidade_carros = nova_capacidade;
        printf("DEBUG: Re-alocação concluída. Nova capacidade: %d\n", capacidade_carros);
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
    carro->id_carro = carregar_ultimo_idCA();

    // Grava os dados no arquivo
    fseek(file, 0, SEEK_END); // Garante que os dados serão gravados no final
    fwrite(carro, sizeof(Carro), 1, file);

    // Incrementa o ID persistente
    salvar_ultimo_idCA(carregar_ultimo_idCA() + 1);

    printf("\n\n### Carro cadastrado com sucesso! ###\n\n");

    // Fecha o arquivo
    fclose(file);

    // Libera a memória alocada (se necessário)
    if (carregar_ultimo_idCA() == capacidade_carros) {
        free(carros_ptr);
        carros_ptr = NULL;
        printf("Memória liberada após cadastro.\n");
    }
}
void listar_carros() {
    FILE *file = fopen("carro_dados.bin", "rb"); // Abre o arquivo no modo binário leitura
    if(carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        return;
    }
    if (file == NULL) {
        printf("\n\n!!! Erro ao abrir o arquivo carro_dados.txt !!!\n\n");
        return;
    }

    if (carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
        fclose(file); // Garante que o arquivo seja fechado mesmo sem carros
        return;
    }

    Carro carro;
    printf("\n\n### Lista de Carros Cadastrados ###");

    // Lê os dados do arquivo registro por registro
    while (fread(&carro, sizeof(Carro), 1, file) == 1) {
        printf("\n\n===========================\n");
        printf("ID - CARRO: %d\n", carro.id_carro);
        printf("===========================\n");
        printf("Modelo: %s\nFabricante: %s\nAno: %d\nCategoria: %s\nEstoque: %d\nPreco: %.2f\n",
               carro.modelo, carro.fabricante, carro.ano_fabricacao,
               carro.categoria, carro.estoque, carro.preco);
    }

    fclose(file); // Fecha o arquivo após a leitura
}
void excluir_carro(const char *modelo) {
    FILE *arquivo = fopen("carro_dados.bin", "rb"); // Abre o arquivo no modo binário leitura
    if(carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
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

    Carro carro;
    int encontrado = 0; // Indica se o carro a ser excluído foi encontrado
    int novo_id = 0;    // ID sequencial a ser atribuído aos carros restantes

    // Lê os carros do arquivo original e os processa
    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        printf("DEBUG: Comparando Modelo: %s com Termo: %s\n", carro.modelo, modelo);

        // Verifica se o carro atual corresponde ao critério de exclusão
        if (strcasecmp(carro.modelo, modelo) == 0) {
            printf("DEBUG: CARRO ENCONTRADO\n");
            encontrado = 1;
            continue; // Pula o carro encontrado (não o escreve no arquivo temporário)
        }

        // Reatribui ID ao carro restante
        carro.id_carro = novo_id++;
        fwrite(&carro, sizeof(Carro), 1, temp); // Escreve no arquivo temporário
    }

    fclose(arquivo); // Fecha o arquivo original
    fclose(temp);    // Fecha o arquivo temporário

    // Se o carro não foi encontrado
    if (!encontrado) {
        printf("Erro: Carro não encontrado.\n");
        remove("temp.bin"); // Remove o arquivo temporário, pois não houve alterações
        return;
    }

    // Atualiza o último ID salvo
    salvar_ultimo_idCA(novo_id - 1);

    // Substitui o arquivo original pelo temporário
    if (remove("carro_dados.bin") != 0 || rename("temp.bin", "carro_dados.bin") != 0) {
        printf("Erro ao atualizar o arquivo de carros.\n");
        return;
    }

    printf("Carro removido com sucesso e IDs atualizados!\n");
}
void editar_carro(const char *modelo) {
    FILE *arquivo = fopen("carro_dados.bin", "rb"); // Abre o arquivo no modo binário leitura
    if(carregar_ultimo_idCA() == 0) {
        printf("\n\n!!! Nenhum carro cadastrado !!!\n\n");
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

    Carro carro;
    int encontrado = 0;

    // Lê os carros do arquivo original
    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        // Verifica se o carro corresponde ao critério de edição
        if (strcasecmp(carro.modelo, modelo) == 0) {
            encontrado = 1;

            // Exibe os dados atuais do carro
            printf("\nEditando carro (ID: %d, Modelo: %s)\n", carro.id_carro, carro.modelo);
            printf("Fabricante atual: %s\n", carro.fabricante);
            printf("Ano de fabricação atual: %d\n", carro.ano_fabricacao);
            printf("Categoria atual: %s\n", carro.categoria);
            printf("Estoque atual: %d\n", carro.estoque);
            printf("Preço atual: %.2f\n", carro.preco);

            // Solicita novos dados
            printf("\nNovo modelo: ");
            scanf(" %[^\n]", carro.modelo);
            printf("Novo fabricante: ");
            scanf(" %[^\n]", carro.fabricante);
            printf("Novo ano de fabricação: ");
            scanf("%d", &carro.ano_fabricacao);
            printf("Nova categoria: ");
            scanf(" %[^\n]", carro.categoria);
            printf("Novo estoque: ");
            scanf("%d", &carro.estoque);
            printf("Novo preço: ");
            scanf("%f", &carro.preco);

            printf("\nCarro editado com sucesso!\n");
        }

        // Escreve o carro (editado ou não) no arquivo temporário
        fwrite(&carro, sizeof(Carro), 1, temp);
    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrado) {
        printf("Carro com modelo '%s' não encontrado.\n", modelo);
        remove("temp.bin"); // Remove o arquivo temporário se nenhuma edição foi feita
        return;
    }

    // Substitui o arquivo original pelo temporário
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

    // Lê os carros do arquivo
    while (fread(&carro, sizeof(Carro), 1, arquivo) == 1) {
        // Verifica se o carro corresponde ao modelo buscado
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

int carregar_ultimo_idCA() {
    FILE *arquivo = fopen("carro_id.bin", "r");
    if (arquivo == NULL) {
        // Se o arquivo não existir, inicializa o ID como 1
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
    // Inicializa os campos do carro
    strcpy(carro->modelo, "");
    strcpy(carro->fabricante, "");
    carro->ano_fabricacao = 0;
    carro->id_carro = 0;
    strcpy(carro->categoria, "");
    carro->estoque = 0;
    carro->preco = 0.0f;
}