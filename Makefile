# Definindo o compilador e as flags
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Arquivos fonte (use caminhos relativos)
SRC = main.c funcionalidade.c bd_paciente.c menu.c

# Arquivos objeto (substitui a extensão .c por .o)
OBJ = $(SRC:.c=.o)

# Nome do arquivo executável
OUTPUT = sistema

# Regra para compilar o programa
$(OUTPUT): $(OBJ)
    $(CC) -o $(OUTPUT) $(OBJ)    

# Regra para compilar os arquivos .c em .o
%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@    

# Limpeza de arquivos temporários
clean:
    rm -f $(OBJ) $(OUTPUT)    
