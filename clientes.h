#ifndef CLIENTES_H
#define CLIENTES_H
#include "cadastro.h"

typedef struct {
    char nome[20];
    char cpf[20];
    char cell[12];
    char endereco[30];
    char data[11];
    int id_cliente;
} Cliente;

extern Cliente clientes[CLIENT_MAX];


void cadastrar_cliente(Cliente *clientes, Cadastro *cadastro);
void listar_clientes(const Cliente *clientes, const Cadastro *cadastro);
void excluir_cliente(Cliente *clientes, const char *termo, int tipo, Cadastro *cadastro);
void editar_cliente(Cliente *clientes, const char *termo, int tipo, const Cadastro *cadastro);
void buscar_cliente(const Cliente *clientes, const char *termo, int tipo, const Cadastro *cadastro);

void menu_clientes(Cliente *clientes, Cadastro *cadastro);


#endif // CLIENTES_H
