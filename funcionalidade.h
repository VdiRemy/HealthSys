#ifndef FUNCIONALIDADE_H
#define FUNCIONALIDADE_H

// estrutura do paciente com as informações
typedef struct {
    int id;
    char cpf[15];
    char nome[100];
    int idade;
    char data_cadastro[11];
} Paciente;

// Funções para manipulação de pacientes
void limpar_buffer();
void formatar_cpf(const char *cpf, char *cpf_formatado);
int validar_cpf(const char *cpf);
int validar_data(const char *data);

#endif