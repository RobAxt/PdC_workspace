TARGET = pdcServer

SRC_DIR = ./src
INC_DIR = ./inc
OUT_DIR = ./bin
OBJ_DIR = $(OUT_DIR)/obj
DOC_DIR = $(OUT_DIR)/doc

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -O3
DEFINES = -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.DEFAULT_GOAL := all

-include $(patsubst %.o,%.d,$(OBJ_FILES))

all: $(OBJ_FILES)
	@echo Enlazando $@
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(OUT_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compilando $<
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEFINES) -o $@ -c $< -I$(INC_DIR) -MMD

clean:
	@rm -r $(OBJ_DIR)
	@rm  $(OUT_DIR)/$(TARGET)

run: $(OUT_DIR)/$(TARGET)
	@echo Ejecutando $<
	@cd $(OUT_DIR) && ./$(TARGET)

debug: $(OUT_DIR)/$(TARGET)
	@echo Debugging $<
	cd $(OUT_DIR) && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(TARGET)

doc:
	@mkdir -p $(DOC_DIR)
	@doxygen doxyfile
	@open $(DOC_DIR)/html/index.html

check:
	@echo Verificando el formato $<
	@clang-format -style=file -dry-run $(SRC_FILES)

format: $(SRC_FILES)
	@echo Formateando $<
	@clang-format -i $(SRC_FILES)

.PHONY: clean run
