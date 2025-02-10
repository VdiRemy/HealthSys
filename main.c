#include "bd_paciente.h"
#include "funcionalidade.h"
#include "menu.h"

int main() {
    BDPaciente bd;
    inicializar_bd(&bd); //inicia o banco de dados
    carregar_bd_csv(&bd, "bd_paciente.csv");
    exibir_menu(&bd); //exibe o menu
    return 0;
}