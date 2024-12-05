#ifndef VENDAS_H
#define VENDAS_H

#include "cadastro.h"
#include "carros.h"
#include "clientes.h"

typedef struct {
    char cliente_nome[20];
    int id_venda;
    int quantidade;
    float preco_total;
} Venda;

extern Venda vendas[CADASTRO_MAX];

void registrar_venda(Venda *vendas, const Cliente *clientes, Carro *carros, Cadastro *cadastro);
void listar_vendas(const Venda *vendas, const Cadastro *cadastro);

void menu_vendas(Venda *vendas, const Cliente *clientes, Carro *carros, Cadastro *cadastro);

#endif // VENDAS_H
