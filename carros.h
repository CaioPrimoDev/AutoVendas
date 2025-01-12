#ifndef CARROS_H
#define CARROS_H

#define CAR_MAX 50

typedef struct {
    char modelo[20];
    char fabricante[20];
    int ano_fabricacao;
    int id_carro;
    char categoria[20];
    int estoque;
    float preco;
} Carro;

// Ponteiro global para carros (dinâmico)
extern Carro *carros_ptr;

// Controle de capacidade e total de carros
extern int capacidade_carros;
extern int total_carros;
extern Carro carros[CAR_MAX];

void cadastrar_carro();
void listar_carros();
void excluir_carro(const char *modelo);
void editar_carro(const char *modelo);
void buscar_carro(const char *modelo);
void menu_carros(Carro *carros);

int carregar_ultimo_idCA();
void salvar_ultimo_idCA(int ultimo_id);
void inicializarCarro(Carro *carro);




#endif // CARROS_H
