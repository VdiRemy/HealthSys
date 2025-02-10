#ifndef MENU_H
#define MENU_H

#include "bd_paciente.h"

void imprimir_opcoes_menu();
void exibir_menu(BDPaciente *bd);
void processar_opcao(char opcao, BDPaciente *bd);
void sair_e_salvar(BDPaciente *bd);

#endif
