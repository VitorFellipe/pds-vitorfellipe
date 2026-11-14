#include <stdio.h>
#include <string.h>

// Definição da estrutura Dono (Tabela "pai")
typedef struct {
    int id;
    char nome[100];
    char telefone[20];
} Dono;

// Definição da estrutura Pet (Tabela "filho" com chave estrangeira dono_id)
typedef struct {
    int id;
    char nome[50];
    char especie[30];
    int idade;
    int dono_id; // Chave estrangeira ligando ao Dono
} Pet;

// "Banco de dados" simulado em memória
Dono donos[] = {
    {1, "Ana Silva", "11999998888"},
    {2, "Carlos Souza", "11888887777"}
};
int total_donos = 2;

Pet pets[] = {
    {1, "Rex", "Cachorro", 3, 1},
    {2, "Mimi", "Gato", 2, 1},
    {3, "Bolt", "Cachorro", 5, 2}
};
int total_pets = 3;

// Função equivalente a 'pet.dono': Busca o Dono a partir do dono_id do pet
Dono* buscar_dono_do_pet(int dono_id) {
    for (int i = 0; i < total_donos; i++) {
        if (donos[i].id == dono_id) {
            return &donos[i];
        }
    }
    return NULL;
}

// Função equivalente a 'dono.pets': Lista todos os pets que pertencem a um determinado dono
void listar_pets_do_dono(int dono_id) {
    printf("--- Pets do Dono ID %d ---\n", dono_id);
    int encontrados = 0;
    for (int i = 0; i < total_pets; i++) {
        if (pets[i].dono_id == dono_id) {
            printf("ID: %d | Nome: %s | Especie: %s | Idade: %d anos\n", 
                   pets[i].id, pets[i].nome, pets[i].especie, pets[i].idade);
            encontrados = 1;
        }
    }
    if (!encontrados) {
        printf("Nenhum pet encontrado para este dono.\n");
    }
    printf("\n");
}

int main() {
    // 1. Testando a navegação Pet -> Dono (Equivalente a pet.dono.nome)
    int pet_id_procurado = 1;
    Pet *p = NULL;
    
    for (int i = 0; i < total_pets; i++) {
        if (pets[i].id == pet_id_procurado) {
            p = &pets[i];
            break;
        }
    }

    if (p != NULL) {
        Dono *d = buscar_dono_do_pet(p->dono_id);
        if (d != NULL) {
            printf("--> Navegacao Pet -> Dono:\n");
            printf("O pet '%s' pertence a '%s' (Contato: %s)\n\n", p->nome, d->nome, d->telefone);
        }
    }

    // 2. Testando a navegação Dono -> Pets (Equivalente a dono.pets)
    listar_pets_do_dono(1);
    listar_pets_do_dono(2);

    return 0;
} 