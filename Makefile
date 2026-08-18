# Variables de compilación
CC = clang
CFLAGS = -Wall -Wextra -O3 -std=gnu23

BUILD_DIR = build
TARGET_VM = $(BUILD_DIR)/lep
TARGET_LIB = $(BUILD_DIR)/libpaxo_vm.a

VM_SRC = Src/Vm/Src/Main.c

all: $(BUILD_DIR) $(TARGET_VM) $(TARGET_LIB)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilar la VM como ejecutable
$(TARGET_VM): $(VM_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ -lm
	@echo "=========================================="
	@echo " LEP VM compilada exitosamente"
	@echo " Ejecutable: $(TARGET_VM)"
	@echo " Uso: $(TARGET_VM) <archivo.pbc>"
	@echo "=========================================="

# Empaquetar componentes como librería estática
$(TARGET_LIB): | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c Src/Vm/Src/Calc.c -o $(BUILD_DIR)/Calc.o
	$(CC) $(CFLAGS) -c Src/Vm/Src/Deque.c -o $(BUILD_DIR)/Deque.o
	ar rcs $@ $(BUILD_DIR)/Calc.o $(BUILD_DIR)/Deque.o
	@echo " Librería: $(TARGET_LIB)"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
