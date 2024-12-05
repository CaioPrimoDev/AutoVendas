#include "cadastro.h"
#include "carros.h"
#include "clientes.h"
#include "vendas.h"

#include <string.h>

// Definindo as variáveis globais

Cadastro cadastro[CADASTRO_MAX] = {0};   // Inicializa a struct Cadastro
Cliente clientes[CLIENT_MAX] = {0};      // Inicializa a struct Cliente
Carro carros[CAR_MAX] = {0};             // Inicializa a struct Carro
Venda vendas[CADASTRO_MAX] = {0};        // Inicializa a struct Venda

void inicializarCliente(Cliente *cliente) {
    // Inicializa os campos do cliente
    strcpy(cliente->nome, "");
    strcpy(cliente->cpf, "");
    strcpy(cliente->cell, "");
    strcpy(cliente->endereco, "");
    strcpy(cliente->data, "");
    cliente->id_cliente = 0;
}
void inicializarCarro(Carro *carro) {
    // Inicializa os campos do carro
    strcpy(carro->modelo, "");
    strcpy(carro->fabricante, "");
    carro->ano_fabricacao = 0;
    carro->id_carro = 0;
    carro->categoria = 0;
    carro->estoque = 0;
    carro->preco = 0.0f;
}
void inicializarVenda(Venda *venda) {
    // Inicializa os campos da venda
    strcpy(venda->cliente_nome, "Desconhecido");
    venda->id_venda = 0;
    venda->quantidade = 0;
    venda->preco_total = 0.0f;
}

// Função para inicializar todos os cadastros
void inicializarCadastro() {
    for (int i = 0; i < CADASTRO_MAX; i++) {
        inicializarCliente(&clientes[i]);
        inicializarCarro(&carros[i]);
        inicializarVenda(&vendas[i]);
    }
}
