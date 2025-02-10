#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "bd_paciente.h"
#include "funcionalidade.h"

/*Funcao para inicializar Tela de menu
Primeiro as opções são impressas na tela
Há uma verificação do que foi digitado, onde caso as opcões não existam, uma mensagem de erro é impressa e o loop é encerrado
Caso tudo ocorra corretamente, a opção é processada através da funcao processar_opcao*/
void exibir_menu(BDPaciente *bd) {
    char opcao; //opções que o paciente vai escolher para determinar a ação
    do {
        imprimir_opcoes_menu();
        char linha[10];
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = '\0'; // Remove a quebra de linha
        if (strlen(linha) == 0) {
            limpar_buffer();
            printf("Entrada invalida! Tente novamente.\n");
            continue;
        }

        if (strlen(linha) > 1) {
            limpar_buffer();
            printf("Entrada invalida! Digite apenas uma opção.\n");
            continue;
        }
        opcao = linha[0];
        processar_opcao(opcao, bd);

    } while (1); // O loop será encerrado por `exit(0)` em `menu.c`
}

/*Funcao responsável por imprimir opcões na tela*/
void imprimir_opcoes_menu() { //exibido para o paciente fazer a escolha
    
    printf("\n=== Sistema de Gerenciamento de Pacientes ===\n");
    printf("1 - Consultar paciente\n");
    printf("2 - Atualizar paciente\n");
    printf("3 - Remover paciente\n");
    printf("4 - Inserir paciente\n");
    printf("5 - Imprimir lista de pacientes\n");
    printf("Q - Sair\n");
    printf("Escolha uma opcao: ");
}

/*Função responsável por salvar dados da lista encadeada no arquivo csv
É utilizada a função salvar_bd_csv, onde toda parte lógica fica pra ela e essa função apenas imprime*/
void sair_e_salvar(BDPaciente *bd) {
    printf("Salvando dados no arquivo 'bd_paciente.csv'...\n");
    salvar_bd_csv(bd, "bd_paciente.csv");

    printf("Liberando memoria...\n");
    liberar_bd(bd);
    printf("Saindo...\n");
    exit(0);
}

/*Função responsável por processar a opção escolhida pelo paciente
Através do switch case, é possível invocar a função de acordo com a opção escolhida*/
void processar_opcao(char opcao, BDPaciente *bd) {
    switch (opcao) {
        case '1': // Consultar paciente
            consultar_paciente(bd); 
            break;
        case '2': // Atualizar paciente
            atualizar_paciente(bd);
            break;
        case '3': // Remover paciente
            dados_pacientes_a_remover(bd);
            break;
        case '4': // Inserir paciente
            dados_pacientes_a_inserir(bd);
            break;
        case '5': // Imprimir lista de pacientes
            printf("\nImprimindo lista de pacientes...\n\n");
            imprimir_lista_pacientes(bd);
            break;
        case 'Q':
        case 'q':
            sair_e_salvar(bd);
            break;
        default:
            printf("Opcao invalida!\n");
    }
}