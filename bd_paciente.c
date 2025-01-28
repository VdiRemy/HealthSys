#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"
#include "paciente.c"

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

void adicionar_paciente_bd(Paciente** lista, Paciente* novo) {
    if (*lista == NULL) {
        *lista = novo;
    } else {
        Paciente* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void carregar_bd_csv(const char* nome_arquivo, Paciente** lista){
    FILE* arquivo = fopen(nome_arquivo,"r");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo./n");
        return;
    }

    // Ignorar a primeira linha (cabeçalho)
    char cabecalho[256];
    if (fgets(cabecalho, sizeof(cabecalho), arquivo) == NULL) {
        printf("Erro ao ler o cabeçalho do arquivo.\n");
        fclose(arquivo);
        return;
    }

    int id;
    char cpf[14];                   //limitado ao número esperado de caracteres de um cpf (incluindo pontos)
    char nome[50];                  
    int idade;
    char data_cadastro[10];         //AAAA-MM-DD (limitado a 10 characteres)

    //lê o arquivo linha por linha
    while (fscanf(arquivo, "%d,%13[^,],%49[^,],%d,%10s\n", &id, cpf, nome, &idade, data_cadastro) == 5){
        Paciente* novo_paciente = criar_paciente(id, cpf, nome, idade, data_cadastro);
        adicionar_paciente_bd(lista, novo_paciente);
    }
    fclose(arquivo);
}
