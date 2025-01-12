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
}Cliente;

extern Cliente *clientes_ptr;
extern int capacidade_clientes;
extern int total_clientes;
extern Cliente *clientes;


void cadastrar_cliente();
void listar_clientes();
void excluir_cliente(const char *termo, int tipo);
void editar_cliente(const char *termo, int tipo);
void buscar_cliente(const char *termo, int tipo);
void menu_clientes(Cliente *clientes);

int carregar_ultimo_idCL();
void salvar_ultimo_idCL(int ultimo_id);
void inicializarCliente(Cliente *cliente);

#endif // CLIENTES_H
