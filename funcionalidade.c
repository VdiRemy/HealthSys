#include <stdio.h>
#include <string.h>
#include "funcionalidade.h"

/*Limpando o buffer para nao dar erro de ficar algum caracter
A variável c é usada para assumir os valores que sobraram da digitação do usuário
O loop continua enquanto não há quebra de linha ou não for o fim do arquivo*/
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

}

/* Formata um CPF para o padrão XXX.XXX.XXX-XX
O CPF de entrada deve conter exatamente 11 dígitos numéricos.
O resultado é armazenado na string cpf_formatado, que deve ter pelo menos 15 caracteres.
Utiliza snprintf para inserir os separadores '.' e '-' corretamente. */
void formatar_cpf(const char *cpf, char *cpf_formatado) {
    snprintf(cpf_formatado, 15, "%.3s.%.3s.%.3s-%.2s",
             cpf, cpf + 3, cpf + 6, cpf + 9);
}

/*
Imprime os dados de um paciente em formato de tabela.
Formata o CPF no padrão XXX.XXX.XXX-XX.
Exibe os dados do paciente alinhados em colunas com espaçamento adequado.
Caso o paciente seja nulo, exibe uma mensagem de erro.
 */
void imprimir_paciente(Paciente *paciente) {
    // Formata o CPF no padrão XXX.XXX.XXX-XX
    char cpf_formatado[15];
    formatar_cpf(paciente->cpf, cpf_formatado);

    if (!paciente) {
        printf("Paciente não encontrado.\n");
        return;
    }
    // printf("Print dentro da impressao %d\n\n\n", paciente->id);
    // Imprime os dados do paciente
    printf("|%5d  | %s | %-49s | %5d | %s | \n", 
        paciente->id, 
        cpf_formatado, 
        paciente->nome, 
        paciente->idade, 
        paciente->data_cadastro);
 
}

/**
Valida um CPF conforme o algoritmo oficial.
Primeiro, verifica se o CPF possui 11 dígitos numéricos.
Em seguida, checa se todos os números são iguais (CPF inválido).
Depois, calcula os dois dígitos verificadores usando multiplicações e somas específicas.
Por fim, compara os dígitos calculados com os fornecidos para validar o CPF.rna 1 se o CPF for válido, 0 caso contrário.
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

/**
 Valida uma data no formato "AAAA-MM-DD".
Primeiro, verifica se a string tem exatamente 10 caracteres.
Em seguida, confere se os caracteres nas posições corretas são hífens.
Por fim, verifica se os demais caracteres são números. 
Retorna 1 se a data estiver no formato correto, 0 caso contrário.
 */

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