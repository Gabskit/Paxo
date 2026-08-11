# Variables de compilación
CC = clang
CFLAGS = -Wall -Wextra -O3 -std=c23
ZIG = zig

BUILD_DIR = build
TARGET_LIB = $(BUILD_DIR)/libpaxo_vm.a
HEADER_OUT = paxo_vm.h

# Objetos
OBJS = $(BUILD_DIR)/vars.o $(BUILD_DIR)/calc.o $(BUILD_DIR)/deque.o

all: $(BUILD_DIR) $(TARGET_LIB)

# 1. Crear directorio de salida
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 2. Compilar Vars.zig a objeto C C-ABI
$(BUILD_DIR)/vars.o: Vars.zig
	$(ZIG) build-lib -femit-bin=$@ -femit-h=$(BUILD_DIR)/vars_gen.h -target native -O ReleaseFast Vars.zig

# 3. Compilar Calc.c (requiere soporte de _BitInt en Clang)
$(BUILD_DIR)/calc.o: Calc.c
	$(CC) $(CFLAGS) -c $< -o $@

# 4. Compilar Deque.c
$(BUILD_DIR)/deque.o: Deque.c
	$(CC) $(CFLAGS) -c $< -o $@

# 5. Empaquetar todo en una librería estática (.a)
$(TARGET_LIB): $(OBJS)
	ar rcs $@ $(OBJS)
	@echo "=========================================="
	@echo " Paxo VM compilada exitosamente:"
	@echo " Header:    $(HEADER_OUT)"
	@echo " Biblioteca: $(TARGET_LIB)"
	@echo "=========================================="

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean