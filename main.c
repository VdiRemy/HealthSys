#include <stdio.h>
#include <stdlib.h>
#include "bd_paciente.h"
#include "bd_paciente.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "paciente.c"

int main() {
    Paciente* lista = NULL;  // Lista começa vazia

    // Carrega os pacientes do arquivo CSV
    carregar_bd_csv("pacientes.csv", &lista);

    // Imprime a lista para verificar se os pacientes foram carregados
    Paciente* atual = lista;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, CPF: %s, Idade: %d, Data Cadastro: %s\n", atual->id, atual->nome, atual->cpf, atual->idade, atual->data_cadastro);
        atual = atual->proximo;
    }

    return 0;
}