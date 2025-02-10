#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_paciente.h"


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

//salvando o banco, função que é utilizada apos o fechamento do sistema
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

//Insere um novo paciente no início da lista encadeada do banco de dados.
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

//Remove um paciente da lista encadeada com base no ID fornecido
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

Paciente* buscar_paciente_por_cpf(BDPaciente *bd, const char *cpf) {
    No *atual = bd->inicio;
    // Percorre a lista até encontrar o paciente com o CPF especificado.
    while (atual) {
        if (strcmp(atual->paciente.cpf, cpf) == 0) {
            return &atual->paciente;
        }
        atual = atual->proximo;
    }
    return NULL;
}

//imprimir a lista dos pacientes
void imprimir_lista_pacientes(BDPaciente *bd) {
    // Imprime o cabeçalho
    printf("ID\tCPF\t\tNome\t\tIdade\tData_Cadastro\n");

    // Percorre a lista encadeada e imprime cada paciente
    No *atual = bd->inicio;
    while (atual) {
        // Formata o CPF no padrão XXX.XXX.XXX-XX
        char cpf_formatado[15];
        snprintf(cpf_formatado, sizeof(cpf_formatado), "%.3s.%.3s.%.3s-%.2s",
                 atual->paciente.cpf, atual->paciente.cpf + 3,
                 atual->paciente.cpf + 6, atual->paciente.cpf + 9);

        // Imprime os dados do paciente
        printf("%d\t%s\t%-15s\t%d\t%s\n",
               atual->paciente.id,
               cpf_formatado,
               atual->paciente.nome,
               atual->paciente.idade,
               atual->paciente.data_cadastro);

        // Avança para o próximo nó
        atual = atual->proximo;
    }
}