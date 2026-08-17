# Variables de compilación
CC = clang
CFLAGS = -Wall -Wextra -O3 -std=gnu23

BUILD_DIR = build
TARGET_LIB = $(BUILD_DIR)/libpaxo_vm.a
HEADER_OUT = paxo_vm.h

# Fuentes y Objetos en C
SRCS = Calc.c Deque.c
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(BUILD_DIR) $(TARGET_LIB)

# 1. Crear directorio de salida
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 2. Regla genérica para compilar archivos .c a .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 3. Empaquetar en librería estática (.a)
$(TARGET_LIB): $(OBJS)
	ar rcs $@ $(OBJS)
	@echo "=========================================="
	@echo " LEP VM compilada exitosamente (C puro):"
	@echo " Header:    $(HEADER_OUT)"
	@echo " Biblioteca: $(TARGET_LIB)"
	@echo "=========================================="

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
