#ifndef CLIENTES_H
#define CLIENTES_H

#define CLIENT_MAX 50

typedef struct {
    char nome[20];
    char cpf[20];
    char cell[12];
    char endereco[30];
    char data[11];
    int id_cliente;
} Cliente;

extern int total_clientes;
extern Cliente clientes[CLIENT_MAX];


void cadastrar_cliente(Cliente *clientes);
void listar_clientes(const Cliente *clientes);
void excluir_cliente(Cliente *clientes, const char *termo, int tipo);
void editar_cliente(Cliente *clientes, const char *termo, int tipo);
void buscar_cliente(const Cliente *clientes, const char *termo, int tipo);

void menu_clientes(Cliente *clientes);
void inicializarCliente(Cliente *cliente);

#endif // CLIENTES_H
