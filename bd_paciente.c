#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// verifica se existe arquivo
int bd_exist(const char *arch_name){
    FILE *archive = fopen(arch_name, "r");
    if (archive) {
        fclose(archive);
        return 1;
    }
    return 0;
}

//cria banco de dados em csv caso não exista
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