#ifndef BD_PACIENTE_H
#define BD_PACIENTE_H
#include "funcionalidade.h"

//estrutura da lista encadeada
typedef struct No {
    Paciente paciente;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} BDPaciente;

//funções 

void dados_pacientes_a_remover(BDPaciente *bd);
void atualizar_paciente(BDPaciente *bd);
void dados_pacientes_a_inserir(BDPaciente *bd);
void consultar_paciente(BDPaciente *bd);
void inicializar_bd(BDPaciente *bd);
void carregar_bd_csv(BDPaciente *bd, const char *arquivo);
void salvar_bd_csv(BDPaciente *bd, const char *arquivo);
void inserir_paciente(BDPaciente *bd, Paciente paciente);
void remover_paciente(BDPaciente *bd, int id);
Paciente* buscar_paciente_por_id(BDPaciente *bd, int id);
Paciente* buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf);
void imprimir_paciente(Paciente *paciente);
void imprimir_lista_pacientes(BDPaciente *bd);
void liberar_bd(BDPaciente *bd); 

#endif