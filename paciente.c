#include <stdio.h>
#include <string.h>
#include "paciente.h"

/**
 * Imprime os dados de um paciente.
 */
void imprimir_paciente(Paciente *paciente) {
    printf("ID: %d\n", paciente->id);
    printf("CPF: %s\n", paciente->cpf);
    printf("Nome: %s\n", paciente->nome);
    printf("Idade: %d\n", paciente->idade);
    printf("Data de Cadastro: %s\n", paciente->data_cadastro);
    printf("-----------------------------\n");
}

/**
 Valida um CPF de acordo com o algoritmo oficial.
 Retorna 1 se o CPF for válido, 0 caso contrário.
 */

int validar_cpf(const char *cpf) {
    // Verifica se o CPF tem 11 dígitos numéricos

    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }

    // Verifica se todos os dígitos são iguais (CPF inválido)
    int todos_iguais = 1;
    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais) return 0;

    // Calcula o primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int resto = soma % 11;
    int digito1 = (resto < 2) ? 0 : 11 - resto;

    // Calcula o segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpf[i] - '0') * (11 - i);
    }
    resto = soma % 11;
    int digito2 = (resto < 2) ? 0 : 11 - resto;

    // Verifica os dígitos verificadores
    if ((cpf[9] - '0') != digito1 || (cpf[10] - '0') != digito2) {
        return 0;
    }

    return 1; // CPF válido
}

int validar_data(const char *data){
    if (strlen(data) != 10) return 0;
    if (data[4] != '-' || data[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        //pular hífen
        if (i == 4 || i == 7) continue;
        //verificar se é número
        if (data[i] < '0' || data[i] > '9') return 0;
    }
    return 1;
}