#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"
#include "paciente.h"



void exibir_menu() { //exibido para o paciente fazer a escolha
    
    printf("\n=== Sistema de Gerenciamento de Pacientes ===\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf("Escolha uma opção: ");
}


int main() {
    BDPaciente bd;
    inicializar_bd(&bd); //inicia o banco de dados
    carregar_bd_csv(&bd, "bd_paciente.csv");

    char opcao; //opções que o paciente vai escolher para determinar a ação

    do {
        exibir_menu();
        char linha[10];
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0) {
            printf("Entrada inválida! Tente novamente.\n");
            continue;
        }

        opcao = linha[0];
        switch (opcao) {
            case '1': // Consultar paciente
                consultar_paciente(&bd); 
                break;
            case '2': // Atualizar paciente
                atualizar_paciente(&bd);
                break;
            case '3': // Remover paciente
                remover_paciente_confirmacao(&bd);
                break;
            case '4': // Inserir paciente
                inserir_paciente_manual(&bd);
                break;
            case '5': // Imprimir lista de pacientes
                printf("\nImprimindo lista de pacientes...\n\n");
                imprimir_lista_pacientes(&bd);
                break;
            case 'Q':
            case 'q':
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 'Q' && opcao != 'q');


    // Salva os dados no arquivo CSV antes de encerrar
    printf("Salvando dados no arquivo 'bd_paciente.csv'...\n");
    salvar_bd_csv(&bd, "bd_paciente.csv");

    // Libera a memória alocada
    printf("Liberando memoria...\n");
    liberar_bd(&bd);

    return 0;
}