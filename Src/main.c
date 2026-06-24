#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "axolang.h"

extern int BACKEND_TARGET;

int main(int argc, char** argv) {
  BACKEND_TARGET = 0;

  if (argc > 1 && strcmp(argv[1], "--c") == 0) {
    BACKEND_TARGET = 1;
  }

  // 1. Creamos las variables que pide la nueva API de PackCC
  axolang_context_t *ctx = axolang_create(NULL); // Inicializa el contexto
  char *resultado_parser = NULL;

  // 2. Pasamos el contexto y la dirección de memoria del retorno
  //    FIX: el éxito/fracaso lo indica el valor de RETORNO de axolang_parse,
  //    no el puntero de salida. resultado_parser siempre queda como strdup("")
  //    (un puntero válido, no NULL) cuando la regla Programa hace match, así
  //    que "resultado_parser != 0" era casi siempre verdadero incluso con
  //    una entrada válida -> siempre reportaba error.
  int ok = axolang_parse(ctx, &resultado_parser);

  free(resultado_parser); // era un strdup("") de la acción de Programa; toca liberarlo

  // 3. Verificamos si el análisis fue exitoso
  if (!ok) {
    fprintf(stderr, "Error: El análisis sintáctico de Axolang falló.\n");
    axolang_destroy(ctx); // Limpieza de memoria
    return 1;
  }

  // Limpieza antes de salir
  axolang_destroy(ctx);
  return 0;
}
