#include "Vm.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t *load_file(const char *path, size_t *out_size) {
  FILE *f = fopen(path, "rb");
  if (!f) { fprintf(stderr, "[lepvm] No se pudo abrir '%s'\n", path); return NULL; }
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
  long size = ftell(f);
  if (size <= 0) { fclose(f); return NULL; }
  rewind(f);
  uint8_t *buf = malloc((size_t)size);
  if (!buf) { fclose(f); return NULL; }
  if (fread(buf, 1, (size_t)size, f) != (size_t)size) { free(buf); fclose(f); return NULL; }
  fclose(f);
  *out_size = (size_t)size;
  return buf;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "LEP-VM v3.14\nUso: %s <archivo.pbc> [modulo.so ...]\n", argv[0]);
    return 1;
  }
  size_t bytecode_size = 0;
  uint8_t *bytecode = load_file(argv[1], &bytecode_size);
  if (!bytecode) return 1;

  LEPVM vm = init_vm();
  for (int i = 2; i < argc; ++i) {
    if (!LEP_ffi_load(&vm.ffi, argv[i])) {
      fprintf(stderr, "[lepvm] No se pudo cargar FFI '%s'\n", argv[i]);
      free(bytecode); LEP_ffi_destroy(&vm.ffi); free(vm.env.tags); free(vm.env.start_ptr); return 2;
    }
  }
  const char *mods = getenv("LEP_FFI_MODULES");
  if (mods && *mods) {
    char *copy = strdup(mods);
    for (char *p = copy; p;) {
      char *next = strchr(p, ':');
      if (next) *next++ = '\0';
      if (*p && !LEP_ffi_load(&vm.ffi, p)) fprintf(stderr, "[lepvm] Aviso: FFI no cargada '%s'\n", p);
      p = next;
    }
    free(copy);
  }

  vm_execute(&vm, bytecode);
  LEP_ffi_destroy(&vm.ffi);
  free(vm.env.tags); free(vm.env.start_ptr); free(bytecode);
  return 0;
}
