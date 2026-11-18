#include <stdio.h>
#include <string.h>

typedef struct { int id; char nome[50]; } Dono;
typedef struct { int id, idade, dono_id, ativo; char nome[50], especie[30]; } Pet;

Dono donos[10] = {{1, "Ana Paula Ribeiro"}, {2, "Carlos Souza"}};
Pet pets[50];
int total_donos = 2, total_pets = 0;

Dono* get_dono(int id) {
    for (int i = 0; i < total_donos; i++) if (donos[i].id == id) return &donos[i];
    return NULL;
}

Pet* get_pet(int id) {
    for (int i = 0; i < total_pets; i++) if (pets[i].id == id && pets[i].ativo) return &pets[i];
    return NULL;
}

void print_pet(Pet* p) {
    Dono* d = get_dono(p->dono_id);
    printf("{\"id\":%d,\"nome\":\"%s\",\"especie\":\"%s\",\"idade\":%d,\"dono_id\":%d,\"dono_nome\":\"%s\"}",
           p->id, p->nome, p->especie, p->idade, p->dono_id, d ? d->nome : "");
}

// 1. GET /pets (filtro_dono = 0 lista todos)
void get_pets(int filtro_dono) {
    printf("200 [");
    int first = 1;
    for (int i = 0; i < total_pets; i++) {
        if (!pets[i].ativo || (filtro_dono && pets[i].dono_id != filtro_dono)) continue;
        if (!first) printf(",");//parei aqui 
        print_pet(&pets[i]); 
        first = 0;
    }
    printf("]\n");
}

// 2. GET /pets/{id}
void get_pet_id(int id) {
    Pet* p = get_pet(id);
    if (!p) { printf("404 {\"erro\":\"Pet nao encontrado\"}\n"); return; }
    printf("200 "); print_pet(p); printf("\n");
}

// 3. POST /pets (+ Desafio dono_id)
void post_pet(const char* nome, const char* especie, int idade, int dono_id) {
    if (!nome[0] || !especie[0] || idade < 0 || dono_id <= 0) {
        printf("400 {\"erro\":\"Informe nome, especie, idade e dono_id\"}\n"); return;
    }
    if (!get_dono(dono_id)) {
        printf("404 {\"erro\":\"Dono nao encontrado\"}\n"); return;
    }
    pets[total_pets] = (Pet){total_pets + 1, idade, dono_id, 1};
    strcpy(pets[total_pets].nome, nome);
    strcpy(pets[total_pets].especie, especie);
    printf("201 "); print_pet(&pets[total_pets++]); printf("\n");
}

// 4. PUT /pets/{id}
void put_pet(int id, const char* nome, const char* especie, int idade, int dono_id) {
    Pet* p = get_pet(id);
    if (!p) { printf("404 {\"erro\":\"Pet nao encontrado\"}\n"); return; }
    if (!get_dono(dono_id)) { printf("404 {\"erro\":\"Dono nao encontrado\"}\n"); return; }
    strcpy(p->nome, nome); strcpy(p->especie, especie);
    p->idade = idade; p->dono_id = dono_id;
    printf("200 "); print_pet(p); printf("\n");
}

// 5. DELETE /pets/{id}
void delete_pet(int id) {
    Pet* p = get_pet(id);
    if (!p) { printf("404 {\"erro\":\"Pet nao encontrado\"}\n"); return; }
    p->ativo = 0;
    printf("200 {\"ok\":true}\n");
}

int main() {
    post_pet("Bidu", "cachorro", 2, 1);       // 201 Criado
    post_pet("Fido", "cao", 3, 999);          // 404 Dono nao encontrado (Desafio)
    get_pets(0);                              // 200 Lista todos
    get_pets(1);                              // 200 Filtra por dono_id=1
    get_pet_id(1);                            // 200 Busca ID 1
    put_pet(1, "Rex", "cachorro", 4, 1);      // 200 Atualiza ID 1
    delete_pet(1);                            // 200 Remove ID 1
    get_pet_id(1);                            // 404 Pet nao encontrado
    return 0;
}