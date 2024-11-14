#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAR_MAX 50
#define CLIENT_MAX 50

char carro_modelo[CAR_MAX][20];
int cadastro_carro = 0;
char fabricante[CAR_MAX][20];
int ano_fabricacao[CAR_MAX];
int carro_id[CAR_MAX];
int categoria[CAR_MAX];
int estoque[CAR_MAX];
float preco[CAR_MAX];

int cliente_cadastro = 0;
char cliente_nome[CLIENT_MAX][20];
char cliente_cpf[CLIENT_MAX][20];
int cliente_id[CLIENT_MAX];
char cliente_cell[CLIENT_MAX][12];
char cliente_endereco[CLIENT_MAX][30];
char cliente_data[CLIENT_MAX][11];

char cliente_vendas[CLIENT_MAX][20];
int registro_vendas[CLIENT_MAX];
int registro_preco[CLIENT_MAX];
int cadastro_vendas = 0;

// Colocar a função como tipo int, no futuro, será usado para verificar se a função funcionou corretamente
void cadastrar_anoFab(int cadastro_carro, int ano_fabricacao[]);
void cadastrar_carro(int *cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);
void consultar_carro(int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);
void listar_carro(int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);
void editar_carro(int cadastro_carro, char modelo[][20], char carro_fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);
void excluir_carro(int *cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);

void cadastrar_cliente(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]);
void editar_cliente(int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]);
void listar_cliente(int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]);
void excluir_cliente(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]);
void buscar_cliente(int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]);

void registrar_venda(int *cadastro_vendas, int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[], int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);
void exibir_vendas(int cadastro_vendas, char cliente_vendas[][20], int registro_vendas[], int registro_preco[], char client_cpf[][20], char modelo[][20]);

void menu_carro(int *cadastro_carro, char carro_modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);
void menu_cliente(int *cadastro_cliente, char client_nome[][20],char client_cpf[][20],char client_cell[][12],char client_endereco[][30],char client_data[][11]);
void menu_vendas(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[], int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]);

int menu_principal(void);


int main() {

    menu_principal();

    return 0;
}

void cadastrar_anoFab(int cadastro_carro, int ano_fabricacao[]) {
    printf("Ano de fabricacao: \n> ");
    fflush(stdin); // Limpa o buffer antes de ler
    scanf(" %d", &ano_fabricacao[cadastro_carro]);
}
void cadastrar_carro(int *cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {

    if (*cadastro_carro >= CAR_MAX) { // Verifica se atingiu o limite
        printf("Limite máximo de carros cadastrados atingido.\n");
        return;
    }

    printf("\n\nCadastro de Veiculo\n\n");
    printf("Digie o modelo do carro: \n> ");
    scanf(" %[^\n]", modelo[*cadastro_carro]);

    printf("Digie o fabricante: \n> ");
    scanf(" %[^\n]", fabricante[*cadastro_carro]);

    cadastrar_anoFab(*cadastro_carro, ano_fabricacao);

    id[*cadastro_carro] = (*cadastro_carro);

    printf("Categoria: \n1 - Sedan\n2 - SUV\n3 - Hatch\n4 - Off-Road\n5 - Outros\n>  ");
    scanf(" %d", &categoria[*cadastro_carro]);

    printf("Quantidade disponais: \n> ");
    scanf(" %d", &estoque[*cadastro_carro]);

    printf("Preço: \n> ");
    scanf(" %f", &preco[*cadastro_carro]);
    printf("\n\n### Veiculo cadastrado com sucesso! ###\n\n");

    (*cadastro_carro)++;
}
void consultar_carro(int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {

char modelo_buscando[CAR_MAX];
int posicao = 0;

    printf("Digite o modelo do carro\n> ");
    scanf(" %[^\n]", modelo_buscando);

    for(int i = 0; i < cadastro_carro; i++) {
        if(strcmp(modelo[i], modelo_buscando) == 0)
            posicao = i;
        }

    for(int i = 0; i < cadastro_carro; i++) {
    printf("==========================================\n");
        printf("   ID: %d\n", id[posicao]);
    //printf("\n\nCodigo: %d\n", cadastro_carro);

        printf("   Modelo: %s\n", modelo[posicao]);
        printf("   Fabricante: %s\n", fabricante[posicao]);
        printf("   Ano de fabricação: %d\n", ano_fabricacao[posicao]);
        printf("   Categoria: %d\n", categoria[posicao]);
        printf("   No estoque: %d\n", estoque[posicao]);
        printf("   Preço: %.2f\n", preco[posicao]);
    printf("==========================================\n");
    }
}
void listar_carro(int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {

    for(int i = 0; i < cadastro_carro; i++) {
    printf("==========================================\n");
    printf("   ID: %d\n", id[i]);
    //printf("\n\nCodigo: %d\n", cadastro_carro);

        printf("   Modelo: %s\n", modelo[i]);
        printf("   Fabricante: %s\n", fabricante[i]);
        printf("   Ano de fabricação: %d\n", ano_fabricacao[i]);
        printf("   Categoria: %d\n", categoria[i]);
        printf("   No estoque: %d\n", estoque[i]);
        printf("   Preço: %.2f\n", preco[i]);
        printf("==========================================\n");
    }
}
void editar_carro(int cadastro_carro, char modelo[][20], char carro_fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {
    char modelo_buscado[20];
    int posicao = 0;
    char escolha;

    printf("Digite o modelo do carro buscado:");
    scanf(" %[^\n]", modelo_buscado);

    for(int i = 0; i < cadastro_carro; i++)
        if(strcmp(carro_modelo[i],modelo_buscado)==0)
            posicao = i;


    printf("\n==========================================\n");
    //printf("   Carro %d\n", id[posicao++]);
    printf("   ID(posição): %d\n", id[posicao]);
    //printf("\n\nCodigo: %d\n", cadastro_carro);
    printf("   Modelo: %s\n", modelo[posicao]);
    printf("   Fabricante: %s\n", fabricante[posicao]);
    printf("   Ano de fabricação: %d\n", ano_fabricacao[posicao]);
    printf("   Categoria: %d\n", categoria[posicao]);
    printf("   No estoque: %d\n", estoque[posicao]);
    printf("   Preço: %.2f\n", preco[posicao]);
    printf("==========================================\n");
    printf("Deseja editar os dados deste carro? (s/n) :");
    scanf(" %c", &escolha);

    if(escolha == 's'){
        printf("Digite o modelo do carro: ");
        scanf(" %[^\n]", carro_modelo[posicao]);

        printf("Digite o fabricante do carro: ");
        scanf(" %[^\n]", carro_fabricante[posicao]);

        cadastrar_anoFab(cadastro_carro, ano_fabricacao);

        id[posicao] = (posicao);

        printf("Categoria: \n1 - Sedan\n2 - SUV\n3 - Hatch\n4 - Off-Road\n5 - Outros\n>  ");
        scanf(" %d", &categoria[posicao]);

        printf("Quantidade disponais: \n> ");
        scanf(" %d", &estoque[posicao]);

        printf("Preço: \n> ");
        scanf(" %f", &preco[posicao]);
        printf("\n\n### Veiculo editado com sucesso! ###\n\n");
    }else
        printf("Retornando ao menu principal");
}
void excluir_carro(int *cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {

    int indice;
    char escolha;
    printf("Digite o índice do carro a ser excluído: ");
    scanf("%d", &indice);

    if (indice < 0 || indice >= *cadastro_carro) {
        printf("Índice inválido.\n");
        return;
    }
    printf("\n==========================================\n");
    //printf("   Carro %d\n", id[posicao++]);
    printf("   ID(indice): %d\n", id[indice]);
    //printf("\n\nCodigo: %d\n", cadastro_carro);
    printf("   Modelo: %s\n", modelo[indice]);
    printf("   Fabricante: %s\n", fabricante[indice]);
    printf("   Ano de fabricação: %d\n", ano_fabricacao[indice]);
    printf("   Categoria: %d\n", categoria[indice]);
    printf("   No estoque: %d\n", estoque[indice]);
    printf("   Preço: %.2f\n", preco[indice]);
    printf("==========================================\n");
    printf("Deseja excluir os dados deste carro? (s/n) :");
    scanf(" %c", &escolha);

    if(escolha == 'n')
        return;

    // Se o índice for o último, basta limpar os dados e decrementar *cadastro_carro
    if (indice == *cadastro_carro - 1) {
        strcpy(modelo[indice], "\0");
        strcpy(fabricante[indice], "\0");
        ano_fabricacao[indice] = 0;
        id[indice] = 0;
        categoria[indice] = 0;
        estoque[indice] = 0;
        preco[indice] = 0;

        (*cadastro_carro)--;  // Reduz o contador de carros cadastrados
        printf("\n\n #### Último carro removido com sucesso! ####\n");
    } else {
        // Desloca todos os elementos a partir do índice a ser removido
        for (int i = indice; i < *cadastro_carro - 1; i++) {
            strcpy(modelo[i], modelo[i + 1]);
            strcpy(fabricante[i], fabricante[i + 1]);
            ano_fabricacao[i] = ano_fabricacao[i + 1];
            id[i] = id[i + 1];
            categoria[i] = categoria[i + 1];
            estoque[i] = estoque[i + 1];
            preco[i] = preco[i + 1];
        }

        (*cadastro_carro)--;  // Reduz o contador de carros cadastrados
        printf("Carro removido com sucesso!\n");
    }
}


void cadastrar_cliente(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]) {
    if (*cadastro_client >= CLIENT_MAX) { // Verifica se atingiu o limite
        printf("Limite máximo de clientes cadastrados atingido.\n");
        return;
    }

    int cliente_atual = *cadastro_client;

    printf("\n\nCadastro de Clientes\n\n");
    printf("Digite o nome completo do cliente: \n> ");
    scanf(" %[^\n]", client_nome[cliente_atual]);

    printf("Digite o CPF:\n> ");
    scanf(" %[^\n]", client_cpf[cliente_atual]);

    printf("Digite o telefone:\n> ");
    scanf(" %[^\n]", client_cell[cliente_atual]);

    cliente_id[cliente_atual] = cliente_atual;  // Define o ID como o índice atual

    printf("Digite o endereço:\n> ");
    scanf(" %[^\n]", client_endereco[cliente_atual]);

    printf("Data do cadastro (DD/MM/AAAA):\n> ");
    scanf(" %[^\n]", client_data[cliente_atual]);

    printf("\n\n### Cliente cadastrado com sucesso! ###\n\n");

    (*cadastro_client)++; // Incrementa o contador de clientes
}
void listar_cliente(int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]) {
    if (cadastro_client == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < cadastro_client; i++) {
        printf("\n==========================================\n");
        printf("   ID: %d\n", cliente_id[i]);
        printf("   Nome: %s\n", client_nome[i]);
        printf("   CPF: %s\n", client_cpf[i]);
        printf("   Telefone: %s\n", client_cell[i]);
        printf("   Endereço: %s\n", client_endereco[i]);
        printf("   Data de cadastramento: %s\n", client_data[i]);
        printf("==========================================\n");
    }
}
void editar_cliente(int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]) {
    int id;
    char escolha;

    printf("Digite o ID do cliente que deseja editar: ");
    scanf("%d", &id);

    if (id < 0 || id >= cadastro_client) {
        printf("ID inválido.\n");
        return;
    }

    printf("\n==========================================\n");
    printf("   Nome: %s\n", client_nome[id]);
    printf("   CPF: %s\n", client_cpf[id]);
    printf("   Telefone: %s\n", client_cell[id]);
    printf("   Endereço: %s\n", client_endereco[id]);
    printf("   Data de cadastro: %s\n", client_data[id]);
    printf("==========================================\n");

    printf("Deseja editar os dados deste cliente? (s/n): ");
    scanf(" %c", &escolha);

    if (escolha == 's') {
        printf("Digite o novo nome completo do cliente: ");
        scanf(" %[^\n]", client_nome[id]);

        printf("Digite o novo CPF: ");
        scanf(" %[^\n]", client_cpf[id]);

        printf("Digite o novo telefone: ");
        scanf(" %[^\n]", client_cell[id]);  // Corrigido para aceitar string

        printf("Digite o novo endereço: ");
        scanf(" %[^\n]", client_endereco[id]);

        printf("Digite a nova data de cadastro (dd/mm/aaaa): ");
        scanf(" [^\n]", &client_data[id]);

        printf("\n\n### Cliente editado com sucesso! ###\n\n");
    } else {
        printf("Retornando ao menu principal\n");
    }
}
void excluir_cliente(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]) {
    int id;
    char escolha;

    printf("Digite o ID do cliente que deseja excluir: ");
    scanf("%d", &id);

    if (id < 0 || id >= *cadastro_client) {
        printf("ID inválido.\n");
        return;
    }

    printf("\n==========================================\n");
    printf("   Nome: %s\n", client_nome[id]);
    printf("   CPF: %s\n", client_cpf[id]);
    printf("   Telefone: %s\n", client_cell[id]);  // Corrigido para imprimir string
    printf("   Endereço: %s\n", client_endereco[id]);
    printf("   Data de cadastro: %s\n", client_data[id]);
    printf("==========================================\n");

    printf("Deseja excluir este cliente? (s/n): ");
    scanf(" %c", &escolha);

    if (escolha == 'n') {
        return;
    }

    // Desloca os registros para preencher o espaço vazio
    for (int i = id; i < *cadastro_client - 1; i++) {
        strcpy(client_nome[i], client_nome[i + 1]);
        strcpy(client_cpf[i], client_cpf[i + 1]);
        strcpy(client_cell[i], client_cell[i + 1]);
        strcpy(client_endereco[i], client_endereco[i + 1]);
        for (int j = 0; j < 3; j++) {
            client_data[i][j] = client_data[i + 1][j];
        }
        cliente_id[i] = cliente_id[i + 1];
    }

    (*cadastro_client)--;  // Reduz o contador de clientes cadastrados
    printf("\n\n### Cliente excluído com sucesso! ###\n\n");
}
void buscar_cliente(int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[]) {
    if (cadastro_client == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char nome_buscando[20];
    char cpf_buscando[20];
    int posicao = 0;
    int escolha = 0;

    printf("Buscar por\n1 - NOME\n2 - CPF\n: ");
    scanf(" %d", &escolha);

    if(escolha == 1) {
        printf("Digite o nome do cliente\n> ");
        scanf(" %[^\n]", nome_buscando);
    }else if(escolha == 2) {
        printf("Digite o CPF\n> ");
        scanf(" %[^\n]", cpf_buscando[posicao]);
    }

    for(int i = 0; i < cadastro_client; i++) {

        if(escolha == 1) {
            if(strcmp(client_nome[i], nome_buscando) == 0)
            posicao = i;
        }else if(escolha == 2) {
            if(strcmp(client_cpf[i], cpf_buscando) == 0)
            posicao = i;
        }

    }

        printf("\n==========================================\n");
        printf("   ID: %d\n", cliente_id[posicao]);
        printf("   Nome: %s\n", client_nome[posicao]);
        printf("   CPF: %s\n", client_cpf[posicao]);
        printf("   Telefone: %s\n", client_cell[posicao]);
        printf("   Endereço: %s\n", client_endereco[posicao]);
        printf("   Data de cadastramento: %s\n", client_data[posicao]);
        printf("==========================================\n");

        menu_cliente(&cliente_cadastro, cliente_nome, cliente_cpf, cliente_cell, cliente_endereco, cliente_data);

}

void registrar_venda(int *cadastro_vendas, int cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[], int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {
    if (cadastro_client == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char nome_buscando[20];
    char cpf_buscando[20];
    int posicaoC = -1;
    int escolha = 0;

    printf("Buscar cliente por\n1 - NOME\n2 - CPF\n: ");
    scanf(" %d", &escolha);

    if (escolha == 1) {
        printf("Digite o nome do cliente\n> ");
        scanf(" %[^\n]", nome_buscando);
    } else if (escolha == 2) {
        printf("Digite o CPF\n> ");
        scanf(" %[^\n]", cpf_buscando);
    }

    for (int i = 0; i < cadastro_client; i++) {
        if (escolha == 1 && strcmp(client_nome[i], nome_buscando) == 0) {
            posicaoC = i;
            break;
        } else if (escolha == 2 && strcmp(client_cpf[i], cpf_buscando) == 0) {
            posicaoC = i;
            break;
        }
    }

    if (posicaoC == -1) {
        printf("Cliente não encontrado.\n");
        return;
    }

    printf("\n==========================================\n");
    printf("   ID: %d\n", cliente_id[posicaoC]);
    printf("   Nome: %s\n", client_nome[posicaoC]);
    printf("   CPF: %s\n", client_cpf[posicaoC]);
    printf("   Telefone: %s\n", client_cell[posicaoC]);
    printf("   Endereço: %s\n", client_endereco[posicaoC]);
    printf("   Data de cadastramento: %s\n", client_data[posicaoC]);
    printf("==========================================\n");

    char modelo_buscando[20];
    int posicao = -1;

    printf("Digite o modelo do carro\n> ");
    scanf(" %[^\n]", modelo_buscando);

    for (int i = 0; i < cadastro_carro; i++) {
        if (strcmp(modelo[i], modelo_buscando) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Carro não encontrado.\n");
        return;
    }

    printf("==========================================\n");
    printf("   ID: %d\n", id[posicao]);
    printf("   Modelo: %s\n", modelo[posicao]);
    printf("   Fabricante: %s\n", fabricante[posicao]);
    printf("   Ano de fabricação: %d\n", ano_fabricacao[posicao]);
    printf("   Categoria: %d\n", categoria[posicao]);
    printf("   No estoque: %d\n", estoque[posicao]);
    printf("   Preço: %.2f\n", preco[posicao]);
    printf("==========================================\n");

    int quantidade = 0;
    char escolhaF;

    printf("\n\n## VENDAS ##");
    printf("\nQuantidade desejada: ");
    scanf("%d", &quantidade);

    if (quantidade > estoque[posicao]) {
        printf("Quantidade desejada excede o estoque disponível.\n");
        return;
    }

    float preco_final = (float)quantidade * preco[posicao];

    printf("\n\nPreço final: %.2f\n", preco_final);

    printf("Deseja efetuar a compra? (s/n)\n> ");
    getchar();  // Limpa o buffer do '\n' deixado pelo scanf anterior
    scanf("%c", &escolhaF);

    if (escolhaF == 's') {
        estoque[posicao] -= quantidade;

        // Registrar a venda
        strcpy(cliente_vendas[*cadastro_vendas], client_nome[posicaoC]);
        registro_vendas[*cadastro_vendas] = quantidade;
        registro_preco[*cadastro_vendas] = preco_final;

        (*cadastro_vendas)++;  // Incrementa o contador de vendas

        printf("\n\n #### COMPRA EFETUADA COM SUCESSO! ####\n");
    } else {
        printf("\nCompra cancelada.\n");
    }
}
void exibir_vendas(int cadastro_vendas, char cliente_vendas[][20], int registro_vendas[], int registro_preco[], char client_cpf[][20], char modelo[][20]) {
    if (cadastro_vendas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    printf("\n======== REGISTRO DE VENDAS ========\n");

    for (int i = 0; i < cadastro_vendas; i++) {
        printf("Venda #%d:\n", i + 1);
        printf("   Nome do Cliente: %s\n", cliente_vendas[i]);
        printf("   CPF do Cliente: %s\n", client_cpf[i]);
        printf("   Modelo do Carro: %s\n", modelo[i]);
        printf("   Quantidade Comprada: %d\n", registro_vendas[i]);
        printf("   Preço Final: %.2f\n", (float)registro_preco[i]);
        printf("===================================\n");
    }
}


int menu_principal() {
    int escolha;

    do{

        printf("==========MENU==========\n");
        printf("1 - Gerenciar carros\n");
        printf("2 - Gerenciar Usuario\n");
        printf("3 - Gerenciar venda\n");
        printf("0 - Sair\n");

        printf(">   ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 0:
                return 0;
            case 1:
                menu_carro(&cadastro_carro, carro_modelo, fabricante, ano_fabricacao, carro_id, categoria, estoque, preco);
                break;
            case 2:
                menu_cliente(&cliente_cadastro, cliente_nome, cliente_cpf, cliente_cell, cliente_endereco, cliente_data);
                break;
            case 3:
                menu_vendas(&cliente_cadastro, cliente_nome, cliente_cpf, cliente_cell, cliente_endereco, cliente_data, cliente_id,
                           cadastro_carro, carro_modelo, fabricante, ano_fabricacao, carro_id, categoria, estoque, preco);
                break;
            default: ;
        }
    }while(escolha != 0);
    return 0;
}
void menu_carro(int *cadastro_carro, char carro_modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {

    int escolha;

    do {
        printf("\n========== MENU - CARROS ==========\n");
        printf("1 - Cadastrar carro\n");
        printf("2 - Editar carro\n");
        printf("3 - Listar carros\n");
        printf("4 - Excluir carro\n");
        printf("5 - Consultar carro\n");
        printf("0 - Voltar ao menu principal\n");

        printf("> ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cadastrar_carro(cadastro_carro, carro_modelo, fabricante, ano_fabricacao, id, categoria, estoque, preco);
            break;
            case 2:
                editar_carro(*cadastro_carro, carro_modelo, fabricante, ano_fabricacao, id, categoria, estoque, preco);
            break;
            case 3:
                listar_carro(*cadastro_carro, carro_modelo, fabricante, ano_fabricacao, id, categoria, estoque, preco);
            break;
            case 4:
                excluir_carro(cadastro_carro, carro_modelo, fabricante, ano_fabricacao, id, categoria, estoque, preco);
            break;
            case 5:
                consultar_carro(*cadastro_carro, carro_modelo, fabricante, ano_fabricacao, id, categoria, estoque, preco);
            break;
            case 0:
                printf("Voltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (escolha != 0);
}
void menu_cliente(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11]) {

    int escolha;

    do {
        printf("\n========== MENU - CLIENTES ==========\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Editar cliente\n");
        printf("3 - Listar clientes\n");
        printf("4 - Excluir cliente\n");
        printf("5 - Buscar cliente\n");
        printf("0 - Voltar ao menu principal\n");

        printf("> ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                cadastrar_cliente(cadastro_client, client_nome, client_cpf, client_cell, client_endereco, client_data, cliente_id);
            break;
            case 2:
                editar_cliente(*cadastro_client, client_nome, client_cpf, client_cell, client_endereco, client_data, cliente_id);
            break;
            case 3:
                listar_cliente(*cadastro_client, client_nome, client_cpf, client_cell, client_endereco, client_data, cliente_id);
            break;
            case 4:
                excluir_cliente(cadastro_client, client_nome, client_cpf, client_cell, client_endereco, client_data, cliente_id);
            break;
            case 5:
                buscar_cliente(*cadastro_client, client_nome, client_cpf, client_cell, client_endereco, client_data, cliente_id);
            break;
            case 0:
                printf("Voltando ao menu principal...\n");
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (escolha != 0);
}
void menu_vendas(int *cadastro_client, char client_nome[][20], char client_cpf[][20], char client_cell[][12], char client_endereco[][30], char client_data[][11], int cliente_id[], int cadastro_carro, char modelo[][20], char fabricante[][20], int ano_fabricacao[], int id[], int categoria[], int estoque[], float preco[]) {


    int escolha;

    do {
        printf("\n========== MENU - VENDAS ==========\n");
        printf("1 - Registrar venda\n");
        printf("2 - Relatorio de vendas\n");
        printf("0 - Voltar ao menu principal\n");

        printf("> ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                registrar_venda(&cadastro_vendas,*cadastro_client,client_nome,client_cpf,client_cell,client_endereco,client_data,cliente_id,cadastro_carro,modelo,fabricante,ano_fabricacao,id,categoria,estoque,preco);
            break;
            case 2:
                exibir_vendas(cadastro_vendas,cliente_vendas,registro_vendas,registro_preco,client_cpf, modelo);
            break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (escolha != 0);

}










