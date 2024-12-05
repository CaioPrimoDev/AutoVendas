#ifndef VENDAS_H
#define VENDAS_H

#include "carros.h"
#include "clientes.h"

#define VENDAS_MAX 100

typedef struct {
    char cliente_nome[20];
    int id_venda;
    int quantidade;
    float preco_total;
} Venda;

extern int total_vendas;
extern Venda vendas[VENDAS_MAX];

// Funções declaradas, mas não definidas aqui
void registrar_venda(Venda *vendas, const Cliente *clientes, Carro *carros);
void listar_vendas(const Venda *vendas);
void menu_vendas(Venda *vendas, const Cliente *clientes, Carro *carros);
void inicializarVenda(Venda *venda);

#endif // VENDAS_H
