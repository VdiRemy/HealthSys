#ifndef PACIENTE_H
#define PACIENTE_H

//estrutura de um paciente
typedef struct Paciente{
    int id;
    char cpf[14];                   //limitado ao número esperado de caracteres de um cpf (incluindo pontos)
    char nome[50];                  
    int idade;
    char data_cadastro[10];         //AAAA-MM-DD (limitado a 10 characteres)
    struct Paciente *proximo;       //ponteiro para o próximo nó
} Paciente;

Paciente* criar_paciente(int id, const char* cpf, const char* nome, int idade, const char* data_cadastro);
void adicionar_paciente(Paciente** lista, Paciente* novo);
void consultar_paciente(Paciente* lista, const char* chave, int buscar_por_cpf);
void imprimir_todos_pacientes(Paciente* lista);
void liberar_lista(Paciente* lista);
void salvar_em_csv(Paciente* lista, const char* nome_arquivo);
void carregar_de_csv(Paciente** lista, const char* nome_arquivo);
void remover_paciente(Paciente** lista, const char* chave, int buscar_por_cpf);
void atualizar_paciente(Paciente* lista, const char* chave, int buscar_por_cpf);

#endif
