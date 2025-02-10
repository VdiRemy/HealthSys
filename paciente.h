#ifndef PACIENTE_H
#define PACIENTE_H

// estrutura do paciente com as informações
typedef struct {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;

// Funções para manipulação de pacientes
void imprimir_paciente(Paciente *paciente);
int validar_cpf(const char *cpf);
int validar_data(const char *data);

#endif