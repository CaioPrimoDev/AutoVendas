#include <stdio.h>
#include <stdlib.h>

void cadastrar_carro(int *cadastro_carro, char modelo[][20], char fabricante[][20], int *ano_fabricacao, int *id, int *categoria, int *estoque, float *preco);

int main() {
    char carro_modelo[50][20];
    int cadastro_carro = 0;
    char fabricante[50][20];
    int ano_fabricacao = 0;
    int id = 0;
    int categoria;
    int estoque;
    float preco;
    int escolha;

    do{

       printf("==========MENU==========\n");
       printf("1 - Cadastrar carro\n");
       printf("2 - Listar carros\n");
       printf("3 - Sair\n");

       printf(">   ");
       scanf("%d", &escolha);

       switch (escolha) {
           case 1:
               cadastrar_carro(&cadastro_carro, carro_modelo, fabricante, &ano_fabricacao, &id, &categoria, &estoque, &preco);
               break;
           case 2:

               break;
           case 3:

               break;
       }
    }while(escolha != 3);

    printf("Codigo: %d\n", cadastro_carro);
    for(int i = 0; i < cadastro_carro; i++) {
        printf("Modelo: %s\n", carro_modelo[i]);
        printf("Fabricante: %s\n", fabricante[i]);
        printf("Ano de fabricação: %d\n", ano_fabricacao);
        printf("ID: %d\n", id);
        printf("Categoria: %d\n", categoria);
        printf("No estoque: %d\n", estoque);
        printf("Preço: %.2f\n", preco);
    }
    return 0;
}

void cadastrar_carro(int *cadastro_carro, char modelo[][20], char fabricante[][20], int *ano_fabricacao, int *id, int *categoria, int *estoque, float *preco) {

    printf("\n\nCadastro de Veiculo\n\n");
    printf("Digie o modelo do carro: \n> ");
    scanf(" %[^\n]", modelo[*cadastro_carro]);

    printf("Digie o fabricante: \n> ");
    scanf(" %s", fabricante[*cadastro_carro]);

    printf("Ano de fabricacao: \n> ");
    scanf(" %d", &ano_fabricacao[*cadastro_carro]);

    id[*cadastro_carro] = (*cadastro_carro);

    printf("Categoria: \n1 - Sedan\n2 - SUV\n3 - Hatch\n4 - Off-Road\n5 - Outros\n>  ");
    scanf("%d", &categoria[*cadastro_carro]);

    printf("Quantidade disponais: \n> ");
    scanf(" %d", &estoque[*cadastro_carro]);

    printf("Preço: \n> ");
    scanf(" %f", &preco[*cadastro_carro]);
    printf("\n\n### Veiculo cadastrado com sucesso! ###\n\n");

    (*cadastro_carro)++;
}
















