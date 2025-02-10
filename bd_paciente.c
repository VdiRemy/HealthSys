#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"
#include "funcionalidade.h"


/* 
Remove paciente do banco de dados com confirmação
A função imprime a lista de pacientes atual, então solicita o ID do paciente a ser removido.
*/
void dados_pacientes_a_remover(BDPaciente *bd) {
    // Imprime toda a lista de pacientes    
    printf("Lista de pacientes:\n");
    imprimir_lista_pacientes(bd);

    printf("Digite o ID do paciente a ser removido: ");
    int id;
    scanf("%d", &id);
    limpar_buffer(); // Limpa o buffer após ler o número

    // Busca o paciente pelo ID
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

/*Atualiza o paciente no banco de dados.
Por meio do Id do paciente, o dado a ser atualizado é modificado diretamente na lista encadeada*/
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

    printf("Idade (ou - para manter): ");
    scanf("%s", entrada_idade_str);
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

/*Reolhe dados do paciente a ser inserido no banco de dados.
A função solicita ao usuário que insira manualmente os dados do paciente a ser inserido no banco de dados.
Então exibe os dados inseridos para confirmação e pede a confirmação do usuário para salvar o registro.
Em seguida, verifica se o CPF já está cadastrado e se o CPF e a data de cadastro são válidos.
Se todas as verificações forem bem-sucedidas, o paciente é inserido no banco de dados através da função inserir_paciente.
*/
void dados_pacientes_a_inserir(BDPaciente *bd) {

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
    novo_paciente.id = id; /* Define o ID com base no tamanho atual do banco de dados, 
    fazendo uma verificação prévia do id para não haver duplicidade
    */
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

/*Consulta o paciente no banco de dados
Fornece ao usuario opcoes onde é possível escolher por qual método vai ser feita a consulta.
O usuário pode escolher entre consultar por ID, CPF ou Nome.
Com base na opção, é executada a função para realizar a busca dentro da lista encadeada de pacientes.
*/
void consultar_paciente(BDPaciente *bd) {
    //opções para consultar o apciente no banco
    printf("Escolha o modo de consulta:\n");
    printf("1 - Por CPF\n");
    printf("2 - Por Nome\n");
    printf("3 - Retornar ao menu principal\n");

    int opcao;
    scanf("%d", &opcao);
    limpar_buffer(); // Limpa o buffer após ler o número

    if (opcao == 1) {
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

    } else if (opcao == 2) {

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

//iniciando o banco de dados para ser usado no sistema
void inicializar_bd(BDPaciente *bd) {
    bd->inicio = NULL;
    bd->tamanho = 0;
}

/**
  Carrega os dados de um arquivo CSV para a lista encadeada do banco de dados.
  bd Ponteiro para o banco de dados onde os dados serão carregados.
  arquivo Nome do arquivo CSV a ser lido.
 */
void carregar_bd_csv(BDPaciente *bd, const char *arquivo) {

    // Tenta abrir o arquivo CSV em modo de leitura ("r").
    FILE *fp = fopen(arquivo, "r");

    // Se o arquivo não for encontrado, exibe uma mensagem e retorna.
    if (!fp) {
        printf("Arquivo nao encontrado. Criando novo banco de dados.\n");
        return;
    }

    // Buffer para armazenar cada linha do arquivo CSV.
    char linha[256];
    
    //ignora cabeçalho
    fgets(linha, sizeof(linha), fp);

    // Lê o arquivo linha por linha usando fgets.
    while (fgets(linha, sizeof(linha), fp)) {
        Paciente p;

        // Usa sscanf para extrair os campos da linha no formato esperado:
        // ID (inteiro), CPF (string), Nome (string), Idade (inteiro), Data de Cadastro (string)
        sscanf(linha, "%d,%[^,],%[^,],%d,%[^,\n]", 
               &p.id, p.cpf, p.nome, &p.idade, p.data_cadastro);
        inserir_paciente(bd, p);
    }
    fclose(fp); //fecha o arquivo
}

/*Salvando o banco, função que é utilizada apos o fechamento do sistema
 Esta função imprime uma tabela formatada contendo os dados de todos os pacientes
 presentes na lista encadeada do banco de dados. A tabela inclui as colunas ID, CPF,
 Nome, Idade e Data de Cadastro.
 */
void salvar_bd_csv(BDPaciente *bd, const char *arquivo) {

    // Tenta abrir o arquivo CSV em modo de escrita ("w").
    FILE *fp = fopen(arquivo, "w");

    if (!fp) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    } 
    //reescreve cabeçalho
    fprintf(fp, "ID,CPF,Nome,Idade,Data_Cadastro\n");

    // Inicializa um ponteiro para percorrer a lista encadeada de pacientes.
    No *atual = bd->inicio;

    while (atual) {

        /*  Escreve os dados do paciente no arquivo no formato:
            ID,CPF,Nome,Idade,Data_Cadastro
            fprintf grava os dados diretamente em um arquivo especificado.
        */

        fprintf(fp, "%d,%s,%s,%d,%s\n", 
                atual->paciente.id, atual->paciente.cpf, 
                atual->paciente.nome, atual->paciente.idade, 
                atual->paciente.data_cadastro);

        //avança
        atual = atual->proximo;
    }

    fclose(fp);
    printf("Dados salvos com sucesso no arquivo '%s'.\n", arquivo);
}

/*
Libera espaço ocupado pela lista encadeada do banco de dados.
*/
void liberar_bd(BDPaciente *bd) {
    No *atual = bd->inicio; // Começa pelo primeiro nó da lista
    while (atual) {
        No *temp = atual;       // Armazena o nó atual temporariamente
        atual = atual->proximo; // Avança para o próximo nó
        free(temp);             // Libera a memória do nó atual
    }
    bd->inicio = NULL;          // Define o início da lista como NULL
    bd->tamanho = 0;            // Reseta o tamanho do banco de dados
}

/*Insere um novo paciente, ja dentro de uma estrutura, no início da lista encadeada do banco de dados.*/
void inserir_paciente(BDPaciente *bd, Paciente paciente) {
    No *novo_no = (No *)malloc(sizeof(No));

    if (!novo_no) { // Verifica se a alocação falhou
        printf("Erro ao alocar memoria para novo paciente.\n");
        return;
    }

    novo_no->paciente = paciente;
    novo_no->proximo = bd->inicio;
    bd->inicio = novo_no;
    bd->tamanho++;
}

/*Remove um paciente da lista encadeada com base no ID fornecido*/
void remover_paciente(BDPaciente *bd, int id) {
    No *anterior = NULL;
    No *atual = bd->inicio;

    // Percorre a lista até encontrar o paciente com o ID especificado.
    while (atual && atual->paciente.id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (!atual) return; // Paciente não encontrado

    if (anterior) {
        anterior->proximo = atual->proximo;
    } else {
        bd->inicio = atual->proximo;
    }

    free(atual);
    bd->tamanho--;
}

//Busca um paciente na lista encadeada com base no ID fornecido.
Paciente* buscar_paciente_por_id(BDPaciente *bd, int id) {
    No *atual = bd->inicio;

    // Percorre a lista até encontrar o paciente com o ID especificado.
    while (atual) {
        if (atual->paciente.id == id) {
            return &atual->paciente;
        }
        atual = atual->proximo;
    }
    return NULL;
}

//Busca um paciente na lista encadeada com base no CPF fornecido.
Paciente* buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf) {
    No *atual = bd->inicio;

    // Percorre a lista até encontrar o paciente com o CPF especificado.
    while (atual) {

        /*Compara o CPF do paciente armazenado no nó atual com o CPF fornecido.
          Se os CPFs forem iguais, strcmp retorna 0, e o paciente é encontrado.
        */
        if (strcmp(atual->paciente.cpf, cpf) == 0) {
            return &atual->paciente;
        }
        atual = atual->proximo;
    }
    return NULL;
}

/*Imprimir a lista completa dos pacientes*/
void imprimir_lista_pacientes(BDPaciente *bd) {

    // Imprime o cabeçalho da tabela
    printf("+----+----------------+---------------------------------------------------+-------+---------------+\n");
    printf("| ID | CPF            | Nome                                              | Idade | Data Cadastro |\n");
    printf("+----+----------------+---------------------------------------------------+-------+---------------+\n");

    // Percorre a lista encadeada e imprime cada paciente
    No *atual = bd->inicio;
    while (atual) {

        // Imprime os dados do paciente
        imprimir_paciente(&atual->paciente);

        // Avança para o próximo nó
        atual = atual->proximo;
    }
    
    // Linha de rodapé da tabela
    printf("+----+----------------+---------------------------------------------------+-------+---------------+\n");
}