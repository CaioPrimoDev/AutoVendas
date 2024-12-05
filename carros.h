#ifndef CARROS_H
#define CARROS_H
#include "cadastro.h"

typedef struct {
    char modelo[20];
    char fabricante[20];
    int ano_fabricacao;
    int id_carro;
    int categoria;
    int estoque;
    float preco;
} Carro;

extern Carro carros[CAR_MAX];

void cadastrar_carro(Carro *carros, Cadastro *cadastro);
void listar_carros(const Carro *carros, const Cadastro *cadastro);
void excluir_carro(Carro *carros, const char *modelo, Cadastro *cadastro);
void editar_carro(Carro *carros, const char *modelo, const Cadastro *cadastro);
void buscar_carro(const Carro *carros, const char *modelo, const Cadastro *cadastro);

void menu_carros(Carro *carros, Cadastro *cadastro);



#endif // CARROS_H
