#include "Vm.c"
#include <stdio.h>
#include <stdlib.h>

static uint8_t *load_file(const char *path, size_t *out_size) {
  FILE *f = fopen(path, "rb");
  if (!f) {
    text_red(stderr);
    fprintf(stderr, "[lepvm]");
    reset_colors(stderr);
    fprintf(stderr, " No se pudo abrir '%s'\n", path);
    return NULL;
  }
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  if (size <= 0) {
    fclose(f);
    return NULL;
  }
  rewind(f);
  uint8_t *buf = malloc((size_t)size);
  if (!buf) {
    fclose(f);
    return NULL;
  }
  fread(buf, 1, (size_t)size, f);
  fclose(f);
  *out_size = (size_t)size;
  return buf;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    text_yellow(stderr);
    fprintf(stderr, "LEP-VM v3.14\n");
    reset_colors(stderr);
    fprintf(stderr, "Uso: %s <archivo.pbc>\n", argv[0]);
    return 1;
  }

  size_t bytecode_size = 0;
  uint8_t *bytecode = load_file(argv[1], &bytecode_size);
  if (!bytecode)
    return 1;

  VM vm = {0};
  vm_init(&vm, bytecode, bytecode_size);

  Deque *stack = deque_create();
  PaxoVar globals[256] = {0};

  text_green(stderr);
  fprintf(stderr, "[lepvm]");
  reset_colors(stderr);
  fprintf(stderr, " Ejecutando %s (%zu bytes)\n", argv[1], bytecode_size);

  vm_run(&vm, stack, globals);

  text_green(stderr);
  fprintf(stderr, "[lepvm]");
  reset_colors(stderr);
  fprintf(stderr, " Terminado OK\n");

  deque_free(stack);
  free(bytecode);
  return 0;
}
