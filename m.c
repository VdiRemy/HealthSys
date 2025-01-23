#include <stdio.h>
#include <stdlib.h>
#include "bd_paciente.h"

void exibir_menu() {
    printf("\n--- HealthSys ---\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    BDPaciente* bd = criar_bd_paciente();
    carregar_bd_paciente(bd, "bd_paciente.csv");
    
    char opcao;
    int rodando = 1;

    while (rodando) {
        exibir_menu();
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                consultar_paciente(bd);
                break;
            case '2':
                atualizar_paciente(bd);
                break;
            case '3':
                remover_paciente(bd);
                break;
            case '4':
                inserir_paciente(bd);
                break;
            case '5':
                imprimir_pacientes(bd);
                break;
            case 'Q':
            case 'q':
                salvar_bd_paciente(bd, "bd_paciente.csv");
                rodando = 0;
                break;
            default:
                printf("Opção inválida!\n");
        }
    }

    liberar_bd_paciente(bd);
    return 0;
}