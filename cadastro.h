#ifndef CADASTRO_H
#define CADASTRO_H

#define CAR_MAX 50
#define CLIENT_MAX 50
#define CADASTRO_MAX (CAR_MAX + CLIENT_MAX)

typedef struct {
    int total_carros;  // Contador de carros
    int total_clientes;  // Contador de clientes
    int total_vendas;  // Contador de vendas
} Cadastro;

extern Cadastro cadastro[CADASTRO_MAX];

void chamarMenu_carros();
void chamarMenu_clientes();
void chamarMenu_vendas();

void inicializarCadastro();

#endif // CADASTRO_H
