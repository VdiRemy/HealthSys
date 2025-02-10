#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"
#include "paciente.h"

//limpando o buffer para nao dar erro de ficar algum caracter
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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

void consultar_paciente(BDPaciente *bd) {
    //opções para consultar o apciente no banco
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por ID\n");
    printf("2 - Por CPF\n");
    printf("2 - Por Nome\n");
    printf("3 - Retornar ao menu principal\n");

    int opcao;
    scanf("%d", &opcao);
    limpar_buffer(); // Limpa o buffer após ler o número

    if (opcao == 1) {
        //recebe o id do paciente
        int id;
        printf("Digite o ID: ");
        scanf("%d", &id);
        limpar_buffer(); // Limpa o buffer após ler o número

        // Busca o paciente pelo ID
        Paciente *paciente = buscar_paciente_por_id(bd, id);
        if (paciente) {
            imprimir_paciente(paciente);
        } else {
            printf("Paciente nao encontrado.\n");
        }
    } else if (opcao == 2) {
        //recebe o cpf do paciente 
        char cpf[15];
        printf("Digite o CPF: ");
        scanf(" %[^\n]", cpf);
        limpar_buffer(); // Limpa o buffer após ler o número

    
        // percorre a lista encadeada ate encontrar o paciente com o cpf correspondente
        No *atual = bd->inicio;
        while (atual) {
            if (strcmp(atual->paciente.cpf, cpf) == 0) {
                imprimir_paciente(&atual->paciente);
                return;
            }
            atual = atual->proximo;
        }
        printf("Paciente nao encontrado.\n");

    } else if (opcao == 3) {

        //recebe o nome
        char nome[100];
        printf("Digite o nome: ");
        scanf(" %[^\n]", nome);
        limpar_buffer(); // Limpa o buffer após ler

        // percorre a lista encadeada de pacientes ate achar o nome digitado
        No *atual = bd->inicio;
        while (atual) {
            if (strcmp(atual->paciente.nome, nome)==0) {
                imprimir_paciente(&atual->paciente);
            }
            atual = atual->proximo;
        }
    }
}

void inserir_paciente_manual(BDPaciente *bd) {
    // Passo 1: Solicita as informações do paciente
    printf("Para inserir um novo registro, digite os valores para os campos CPF (apenas digitos), Nome, Idade e Data_Cadastro:\n");
    int id;
    Paciente novo_paciente;
    Paciente *paciente = buscar_paciente_por_id(bd, bd->tamanho + 1);
    if (paciente != NULL) {
        id = bd->tamanho + 2;
    } else {
        id = bd->tamanho + 1;
    }
    novo_paciente.id = id; // Define o ID com base no tamanho atual do banco de dados, fazendo uma verificação prévia do id para não haver duplicidade

    printf("CPF (apenas digitos): ");
    scanf(" %[^\n]", novo_paciente.cpf);
    limpar_buffer();

    printf("Nome: ");
    scanf(" %[^\n]", novo_paciente.nome);
    limpar_buffer();

    printf("Idade: ");
    scanf("%d", &novo_paciente.idade);
    limpar_buffer();

    printf("Data_Cadastro (AAAA-MM-DD): ");
    scanf(" %[^\n]", novo_paciente.data_cadastro);
    limpar_buffer();

    // Passo 2: Exibe os dados inseridos para confirmação
    printf("\nConfirma a inserção do registro abaixo? (S/N)\n");
    printf("ID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");
    printf("%d\t%.3s.%.3s.%.3s-%.2s\t%-15s\t%d\t%s\n",
        novo_paciente.id,
        novo_paciente.cpf, novo_paciente.cpf + 3, novo_paciente.cpf + 6, novo_paciente.cpf + 9,
        novo_paciente.nome,
        novo_paciente.idade,
        novo_paciente.data_cadastro);

    // Passo 3: Pede confirmação para salvar o registro
    char confirmacao;
    printf("Digite S para confirmar ou N para cancelar: ");
    scanf(" %c", &confirmacao);
    limpar_buffer();

    if (confirmacao == 'S' || confirmacao == 's') {
        // Passo 3: Verifica se o CPF já está cadastrado
        Paciente *paciente = buscar_paciente_por_cpf(bd, novo_paciente.cpf);
        if (paciente != NULL) {
                
            if (strcmp(novo_paciente.cpf, paciente->cpf) == 0) {
                printf("CPF ja cadastrado! O registro nao foi inserido.\n");
                return;
            }
        }
        // Passo 4: Valida o CPF antes de inserir
        if (!validar_cpf(novo_paciente.cpf)) {
            printf("CPF invalido! O registro nao foi inserido.\n");
            return;
        }
        if (!validar_data(novo_paciente.data_cadastro)) {
            printf("Data invalida! O registro nao foi inserido.\n");
            return;
        }

        // Insere o paciente no banco de dados
        inserir_paciente(bd, novo_paciente);
        printf("O registro foi inserido com sucesso.\n");
    } else {
        printf("Insercao cancelada. O registro não foi salvo.\n");
    }
}

void atualizar_paciente(BDPaciente *bd) {
    // Passo 1: Imprime toda a lista de pacientes
    printf("Lista de pacientes:\n");
    imprimir_lista_pacientes(bd);

    // Passo 2: Solicita o ID do paciente a ser atualizado
    printf("\nDigite o ID do registro a ser atualizado:\n");
    int id;
    scanf("%d", &id);
    limpar_buffer(); // Limpa o buffer após ler o número

    // Busca o paciente pelo ID
    Paciente *paciente = buscar_paciente_por_id(bd, id);
    if (!paciente) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    // Passo 3: Cria uma cópia temporária para armazenar as alterações
    Paciente temp = *paciente; // Cópia temporária do paciente

    // Solicita os novos valores para os campos
    printf("\nDigite o novo valor para os campos CPF (apenas digitos), Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite '-'): \n");

    char entrada_cpf[15], entrada_nome[100], entrada_idade_str[10], entrada_data_cadastro[11];

    printf("CPF (apenas digitos, ou '-' para manter): ");
    scanf(" %[^\n]", entrada_cpf);
    limpar_buffer();

    printf("Nome (ou '-' para manter): ");
    scanf(" %[^\n]", entrada_nome);
    limpar_buffer();

    printf("Idade (ou -1 para manter): ");
    scanf("%s", entrada_idade_str); // Lê como string para aceitar '-'
    limpar_buffer();

    printf("Data_Cadastro (AAAA-MM-DD, ou '-' para manter): ");
    scanf(" %[^\n]", entrada_data_cadastro);
    limpar_buffer();

    // Aplica as alterações na cópia temporária
    if (strcmp(entrada_cpf, "-") != 0) { // Se o CPF foi alterado
        if (validar_cpf(entrada_cpf)) {
            strcpy(temp.cpf, entrada_cpf); // Atualiza o CPF
        } else {
            printf("CPF invalido!\n");
            return; // Sai da função se o CPF for inválido
        }
    }

    if (strcmp(entrada_nome, "-") != 0) { // Se o nome foi alterado
        strcpy(temp.nome, entrada_nome); // Atualiza o nome
    }

    if (strcmp(entrada_idade_str, "-") != 0) { // Se a idade foi alterada
        int nova_idade = atoi(entrada_idade_str); // Converte a string para inteiro
        temp.idade = nova_idade; // Atualiza a idade
    }

    if (strcmp(entrada_data_cadastro, "-") != 0) { // Se a data de cadastro foi alterada
        strcpy(temp.data_cadastro, entrada_data_cadastro); // Atualiza a data de cadastro
    }

    // Passo 4: Exibe os novos valores para confirmação
    printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
    printf("ID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");
    printf("%d\t%.3s.%.3s.%.3s-%.2s\t%-15s\t%d\t%s\n",
           temp.id,
           temp.cpf, temp.cpf + 3, temp.cpf + 6, temp.cpf + 9,
           temp.nome,
           temp.idade,
           temp.data_cadastro);

    // Passo 5: Pede confirmação para salvar as alterações
    char confirmacao;
    printf("Digite S para confirmar ou N para cancelar: ");
    scanf(" %c", &confirmacao);
    limpar_buffer();

    if (confirmacao == 'S' || confirmacao == 's') {
        // Copia os dados da cópia temporária para o registro original
        *paciente = temp;
        printf("Registro atualizado com sucesso.\n");
    } else {
        printf("Atualizacao cancelada. Os dados nao foram salvos.\n");
    }
}
    
void remover_paciente_confirmacao(BDPaciente *bd) {

    // Imprime toda a lista de pacientes
    printf("Lista de pacientes:\n");
    imprimir_lista_pacientes(bd);

    printf("Digite o ID do paciente a ser removido: ");
    int id;
    scanf("%d", &id);
    limpar_buffer(); // Limpa o buffer após ler o número

    Paciente *paciente = buscar_paciente_por_id(bd, id);
    if (!paciente) {
        printf("Paciente nao encontrado.\n");
        return;
    }


    printf("Tem certeza de que deseja excluir este registro? (S/N): ");
    char confirmacao;
    scanf(" %c", &confirmacao);
    limpar_buffer(); // Limpa o buffer após ler o número

    if (confirmacao == 'S' || confirmacao == 's') {
        remover_paciente(bd, id);
        printf("Registro removido com sucesso!\n");
    } else {
        printf("Exclusao cancelada.\n");
    }
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