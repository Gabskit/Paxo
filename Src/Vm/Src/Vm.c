#include "Calc.c"
#include "Typecast_and_read.c"

typedef enum {
  // Carga de Literales a la Pila
  OP_PUSH,

  // Operaciones Aritméticas
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,

  // Conversión de Tipos (Typecast)
  OP_CAST,

  // Variables (Entorno / Stack Frame)
  OP_LOAD_VAR,  // [uint16_t index] -> Push var
  OP_STORE_VAR, // [uint16_t index] -> Pop var

  // Entrada / Salida (I/O)
  OP_PRINT,

  // Control de Flujo y Fin
  OP_JUMP,          // [int16_t offset]
  OP_JUMP_IF_FALSE, // [int16_t offset]
  OP_HALT           // Detener la VM
} PaxoOpcode;