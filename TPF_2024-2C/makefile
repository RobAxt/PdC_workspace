TARGET = pdcServer

SRC_DIR = ./src
INC_DIR = ./inc
OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj
DOC_DIR = $(OUT_DIR)/doc

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
DEFINES =

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.DEFAULT_GOAL := all

-include $(patsubst %.o,%.d,$(OBJ_FILES))

all: $(OBJ_FILES)
	@echo Enlazando $@
	$(CC) $(OBJ_FILES) -o $(OUT_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compilando $<
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_DIR) -MMD -D$(DEFINES)

clean:
	@rm -r $(OUT_DIR)

run: $(OUT_DIR)/$(TARGET)
	@echo Ejecutando $<
	@./$(OUT_DIR)/$(TARGET)

debug: $(BUILD_DIR)/$(TARGET)
	@echo "Debugging $<..."
	@valgrind --leak-check=full --show-leak-kinds=all -s ./$(BUILD_DIR)/$(TARGET)

doc:
	@mkdir -p $(DOC_DIR)
	@doxygen doxyfile

check:  $(SRC_DIR)/%.c
	@echo Verificando el formato $<
	@clang-format -style=file -dry-run $(SRC_FILES)

format: $(SRC_DIR)/%.c
	@echo Formateando $<
	@clang-format -i $(SRC_FILES)

.PHONY: clean run
