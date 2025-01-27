#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

//cria novo nó
Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade, const char* data_cadastro) {
    Paciente* novo = (Paciente*)malloc(sizeof(Paciente));
    if (novo == NULL){
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    novo->id = id;
    strcpy(novo->cpf, cpf);
    strcpy(novo->nome, nome);
    novo->idade = idade;
    strcpy(novo->data_cadastro, data_cadastro);
    novo->proximo = NULL; //o próximo nó é inicializado com vazio
    return novo;
}
//função para inserir novo paciente no final da lista
void adicionar_paciente(Paciente** lista, Paciente* novo) {
    if (*lista == NULL) {
        *lista = novo; //lista vazia, o novo nó será o primeiro
    }
    else {
        Paciente* atual = *lista;
        while (atual->proximo !=NULL) {  //navega até o último nó
            atual = atual->proximo;
            
        }
        atual->proximo = novo; //liga o novo nó ao fim da lista
    }
}

//função para remover paciente
void remover_paciente(Paciente** lista, const char* chave, int buscar_por_cpf){
    Paciente* atual = lista, *anterior = NULL;

    while (atual != NULL){
        if ((buscar_por_cpf))
    }
}

//função para consultar paciente por nome ou cpf
void consultar_paciente(Paciente* lista, const char* chave, int buscar_por_cpf) {
    Paciente* atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if ((buscar_por_cpf && strcmp(atual->cpf, chave) == 0) ||
        (!buscar_por_cpf && strcmp(atual->nome, chave) == 0)) {
            printf("ID: %d\n", atual->id);
            printf("CPF: %s\n", atual->cpf);
            printf("Nome: %s\n", atual->nome);
            printf("Idade: %d\n", atual->idade);
            printf("Data de Cadastro: %s\n", atual->data_cadastro);
            encontrado = 1;
            break;
        }
        atual = atual->proximo; //passa para o próximo nó
    }
    if (!encontrado) {
        printf("Paciente não encontrado,\nverifique os dados inseridos e tente novamente.");
    }
}

//função para imprimir todos os pacientes
void imprimir_todos_pacientes(Paciente* lista){
    Paciente* atual = lista;
    while (atual != NULL){
        printf("ID: %d, CPF: %s, Nome: %s, Idade: %d, Data: %s\n",
        atual->id, atual->cpf, atual->nome, atual->idade, atual->data_cadastro);
        atual = atual->proximo; //avança para o proximo nó
    }
}



//funcao para liberar memória alocada para lista

void liberar_lista(Paciente* lista) {
    Paciente* atual = lista;
    while (atual != NULL){
        Paciente* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}