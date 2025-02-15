# HealthSys
Trabalho de Estrutura de Dados por Alice Lourenço e Remerson Victor com o professor Thaigo Paixão.

## Sistema de Gerenciamento de Pacientes
Este projeto implementa um **Sistema de Gerenciamento de Pacientes**, que permite consultar, atualizar, remover, inserir e imprimir as informações de pacientes em um banco de dados (arquivo CSV). O sistema utiliza uma lista encadeada para manipular os dados na memória durante a execução, garantindo eficiência e flexibilidade.

### Pré-requisitos
- Compilador GCC instalado.
- Um editor de texto ou IDE para visualizar e modificar o código.

### Descrição dos Diretórios e Arquivos
- **main.c**: Código principal do programa. Contém o menu interativo que permite ao usuário realizar operações como cadastrar, consultar, atualizar e remover pacientes. Também chama as funções implementadas em outros arquivos.
- **menu.c**: Implementa principais funcionalidades utilizadas no sistema menu.
- **menu.h**: Declara as funções e estruturas do arquivo menu.c
- **funcionalidade.c**:Implementa as funções relacionadas à manipulação de dados do sistema no geral. Isso inclui operações como validar CPF, formatar dados, limpar buffer e validar a data.
- **funcionalidade.h**: Declara as funções e estruturas de dados usadas no arquivo funcionalidade.c. Define a interface para interagir com os dados de um paciente individual.
- **bd_paciente.c**: Implementa as funções relacionadas ao gerenciamento do banco de dados de pacientes. Inclui operações como carregar dados do arquivo CSV (bd_paciente.csv), salvar dados no arquivo e manipular a lista encadeada.
- **bd_pacientes.h**: Declara as funções e estruturas de dados usadas no arquivo bd_paciente.c. Define a interface para interagir com o banco de dados de pacientes.
- **bd_paciente.csv**: Arquivo CSV que armazena os dados dos pacientes.
- **'README.md'**: Contém a documentação completa do projeto, incluindo instruções de uso, estrutura do repositório, principais decisões de implementação e informações sobre contribuições.
- **Makefile**: automatiza a compilação de projetos em C/C++. Ele define regras para compilar arquivos-fonte (.c) em objetos (.o) e gerar o executável final, facilitando o processo sem precisar digitar comandos manualmente.

### Passos para Executar
**1. Clone este repositório:**  
  git clone https://github.com/VdiRemy/HealthSys.git
   
**3. Compile o código.**    
   use o gcc main.c bd_paciente.c funcionalidade.c menu.c -o sistema
   ou utilize make para executar com o Makefile.
   
**5. Execute o programa.**   
   ./sistema
   
**7. Menu Principal**  
O sistema carregará automaticamente os dados do arquivo bd_paciente.csv (se existir). Caso contrário, criará um novo arquivo ao salvar os dados. E mostrará o menu do sistema.
   - 1 Consultar paciente 
   - 2 Atualizar paciente
   - 3 Remover paciente  
   - 4 Inserir paciente
   - 5 Imprimir lista de todos os pacientes
   - Q Sair
  
Ao selecionar as opções:

**1 -** O usuário poderá consultar algum paciente do sistema e verificar os dados cadastrados. Primeiro será gerado todos os pacientes cadastrados e o usuário poderá procurar o paciente pelo nome ou pelo CPF.

**2 -** O usuário pode atualizar os dados cadastrados de algum paciente, inserindo o dado novo ou usando "-" para deixar a mesma informação. O paciente a ser atualizado é identificado pelo ID selecionado. Dessa forma: CPF (apenas dígitos), nome, idade e data de cadastro (AAAA-MM-DD). E o id será gerado automaticamente de acordo com a ordem do banco de dados.

**3 -** O usuário pode remover algum paciente do banco de dados, identificando o paciente pelo ID.

**4 -** O usuário do sistema poderá cadastrar um novo paciente e seus seguintes dados no banco de dados:  
CPF (apenas dígitos), nome, idade e data de cadastro (AAAA-MM-DD). E o id será gerado automaticamente de acordo com a ordem do banco de dados.

**5 -** Listagem de todos os pacientes cadastrados.

**Q -** Sair do sistema.

### Principais TADs usadas:
**1. Estrutura do Paciente:**   
A estrutura Paciente representa os dados de um paciente no sistema.

**2. A lista encadeada**

   **- A estrutura No:**    
   A estrutura No representa um nó da lista encadeada. Cada nó contém um registro de Paciente e um ponteiro para o próximo nó.

   **- A estrutura BDPaciente:**  
   A estrutura BDPaciente representa o banco de dados de pacientes. Ela contém um ponteiro para o início da lista encadeada e o tamanho total do banco de dados.

### Principais Decisões de Implementação:
**1.** **Dados**  
Os dados são salvos em um arquivo CSV (bd_paciente.csv) para garantir persistência entre execuções do programa.  
O arquivo CSV segue o formato:  
|ID | CPF             | NOME            | IDADE | Data_cadastro |
|---|-----------------|-----------------|-------|---------------|
| 1 | 123.456.789-09  | João Silva      | 20    | 2024-12-01    |
| 2 | 987.654.321-00  | Maria Oliveira  | 25    | 2024-12-02    | 

As funções utilizadas para a manipulação do banco de dados são: inicializar_bd, carregar_bd_csv, salvar_bd_csv.

**2.** **Lista Encadeada**  
A lista encadeada foi escolhida como estrutura de dados principal porque:  
Permite inserções rápidas no início da lista.  
É dinâmica, permitindo que o número de pacientes cresça ou diminua sem limitações fixas.
As funções que manipulam listas são: remover_paciente_confirmacao, atualizar_paciente, inserir_paciente_manual, consultar_paciente, inicializar_bd, carregar_bd_csv, salvar_bd_csv,
inserir_paciente,
remover_paciente,
buscar_paciente_por_id,
buscar_paciente_por_cpf,
imprimir_lista_pacientes,
liberar_bd.

**3.** **Validação de Dados e Formatação de entrada**   
O CPF é validado antes de ser salvo no sistema. Isso garante que apenas CPFs válidos sejam armazenados.  
A função validar_cpf verifica se o CPF tem 11 dígitos e segue regras básicas de validação.  
A função validar_data verifica se a data de cadastro está de acordo com a forma solicitada na entrada.  
A função limpar_buffer ajuda a evitar problemas com caracteres residuais no buffer. Assim, o sistema nao interpreta nenhuma entrada indesejada do scanf.
f_confirmacao é a função para o usuario confirmar ou não, com S ou N, as ações inseridas.

**4.** **Formatação de Saída**  
O CPF é formatado automaticamente no padrão XXX.XXX.XXX-XX para melhor legibilidade.  
Os dados são exibidos em formato tabular usando \t (tabulações) para alinhar os campos.

**5.** **Confirmação de Alterações**  
Antes de salvar qualquer alteração (inserção ou atualização), o sistema exibe os novos valores para confirmação do usuário. Isso reduz o risco de erros acidentais.

**6.** **Liberação de Memória**  
A função liberar_bd faz a liberação de memória quando o programa é finalizado (pela letra Q). Dessa forma, toda memória alocada dinamicamente durante a execução do sistema é esvaziada, evitando vazamento.
