#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura de um paciente

typedef struct Paciente{
    int id;
    char cpf[14];
    char nome[50];
    int idade;
    char data_cadastro[10];         //AAAA-MM-DD (limitado a 10 characteres)
    struct Paciente *proximo;       //ponteiro para o próximo nó
} Paciente;

int bd_exist(const char *arch_name){
    FILE *archive = fopen(arch_name, "r");
    if (archive) {
        fclose(archive);
        return 1;
    }
    return 0;
}

int create_bd(const char *arch_name) {
    FILE *archive = fopen(arch_name, "w");
    if (!archive) {
        perror("Erro ao criar arquivo");
        return 0;
    }

    fprintf(archive, "ID,CPF,Nome,Idade,Data_Cadastro\n");

    fclose(archive);

    printf("Banco de dados criado com sucesso!\n",arch_name);
    return 1;
}

#define MAX_LINE 256

void consult_patient(const char *filename, const char *search_term){
    FILE *file = fopen(filename, "r");
    if (!file){
    printf("Erro: não foi possível abrir o arquivo '%s'.\n", filename);
    return;
    }

    char line[MAX_LINE];
    int found = 0;

    // lê cabeçalho e ignora
    fgets(line, sizeof(line), file);

    //lê cada linha do arquivo (exceto o cabeçalho obviamente)
    while (fgets(line, sizeof(line), file)){
        char id[20], cpf[14], nome[50], idade[3], data_cadastro[10];

        //divide a linha em colunas usando a virgula como delimitador
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^\n]", id, cpf, nome, idade, data_cadastro);

        //precisa terminar essa bosta em
    }
}