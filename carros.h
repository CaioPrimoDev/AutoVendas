#ifndef CARROS_H
#define CARROS_H

#define CAR_MAX 50

typedef struct {
    char modelo[20];
    char fabricante[20];
    int ano_fabricacao;
    int id_carro;
    int categoria;
    int estoque;
    float preco;
} Carro;

extern int total_carros ;  // Contador de carros
extern Carro carros[CAR_MAX];

void cadastrar_carro(Carro *carros);
void listar_carros(const Carro *carros);
void excluir_carro(Carro *carros, const char *modelo);
void editar_carro(Carro *carros, const char *modelo);
void buscar_carro(const Carro *carros, const char *modelo);

void menu_carros(Carro *carros);
void inicializarCarro(Carro *carro);




#endif // CARROS_H
