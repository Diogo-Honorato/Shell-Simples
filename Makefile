COMPILADORC = gcc
CFLAGS = -Wall -Wextra -O2 -g
LDFLAGS = -lm -D_POSIX_C_SOURCE=200809L -lreadline
EXECUTABLE = shell

# Diretórios
HEADER_DIR = headers
SRC_DIR = sources
OBJ_DIR = objects

SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))


all: obj_dirs $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	@$(COMPILADORC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | obj_dirs
	@mkdir -p $(@D)
	@$(COMPILADORC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@


obj_dirs:
	@mkdir -p $(OBJ_DIR)


clean:
	@rm -rf $(OBJ_DIR) $(EXECUTABLE)


.PHONY: all clean leak