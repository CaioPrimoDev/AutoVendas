#ifndef VENDAS_H
#define VENDAS_H

#include "carros.h"
#include "clientes.h"

#define VENDAS_MAX 100

typedef struct {
    char cliente_nome[20];
    char modelo_carro[20];
    int id_venda;
    int quantidade;
    float preco_total;
} Venda;

// Ponteiro global para vendas (dinâmico)
extern Venda *vendas_ptr;

// Controle de capacidade e total de vendas
extern int capacidade_vendas;
extern int total_vendas;
extern Venda vendas[VENDAS_MAX];

// Funções declaradas, mas não definidas aqui
void registrar_venda();
void listar_vendas();
void menu_vendas(Venda *vendas, const Cliente *clientes, Carro *carros);

int carregar_ultimo_idVE();
void salvar_ultimo_idVE(int ultimo_id);
void inicializarVenda(Venda *venda);

#endif // VENDAS_H
