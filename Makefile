COMPILADORC = gcc

CFLAGS = -Wall -Wextra -O2 -g

LDFLAGS = -lm

# Nome do executável
EXECUTABLE = shell

# Diretórios
HEADER_DIR = headers
SRC_DIR = sources
OBJ_DIR = objects

SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gerar nomes de arquivos .o a partir dos arquivos .c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))


all: obj_dirs $(EXECUTABLE)


$(EXECUTABLE): $(OBJS)
	@$(COMPILADORC) $(CFLAGS) $^ -o $@ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | obj_dirs
	@$(COMPILADORC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@


obj_dirs:
	@mkdir -p $(OBJ_DIR)
	

# Limpar arquivos objeto e o executável
clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE) $(RESULT_DIR)


.PHONY: all clean