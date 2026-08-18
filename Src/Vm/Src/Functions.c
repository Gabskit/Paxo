#pragma once
#include "Calc.c"
#include "Typecast_and_read.c"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// ==========================================
// IDs de funciones nativas
// ==========================================
typedef enum {
  NATIVE_PRINT = 0,
  NATIVE_PRINTLN,
  NATIVE_TYPEOF,
  NATIVE_LEN,
  NATIVE_ID_COUNT
} NativeId;

// ==========================================
// Funciones nativas
// ==========================================

static PaxoVar native_print(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return (PaxoVar){0};
  PaxoVar val = args[0];

  switch (val.type) {
  case NUM8: {
    const char *s = (const char *)readnum8(val.as.number8, 1);
    printf("%s", s);
    break;
  }
  case NUM16: {
    const char *s = (const char *)readnum16(val.as.number16, 1);
    printf("%s", s);
    break;
  }
  case NUM32: {
    const char *s = (const char *)readnum32(val.as.number32, 1);
    printf("%s", s);
    break;
  }
  case NUM64: {
    const char *s = (const char *)readnum64(val.as.number64, 1);
    printf("%s", s);
    break;
  }
  case BOOL:
    printf("%s", val.as.truebool ? "true" : "false");
    break;
  case TRIT: {
    const char *s = (const char *)readtrit(val.as.bit);
    printf("%s", s);
    break;
  }
  case CHAR:
    printf("%c", val.as.chara);
    break;
  default:
    break;
  }

  return (PaxoVar){0}; // print no retorna valor
}

static PaxoVar native_println(PaxoVar *args, uint8_t argc) {
  native_print(args, argc);
  putchar('\n');
  return (PaxoVar){0};
}

static PaxoVar native_typeof(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return (PaxoVar){0};
  const char *type_name = "unknown";
  switch (args[0].type) {
  case NUM8:
    type_name = "num8";
    break;
  case NUM16:
    type_name = "num16";
    break;
  case NUM32:
    type_name = "num32";
    break;
  case NUM64:
    type_name = "num64";
    break;
  case BOOL:
    type_name = "bool";
    break;
  case TRIT:
    type_name = "trit";
    break;
  case CHAR:
    type_name = "char";
    break;
  case POINT:
    type_name = "pin";
    break;
  case FUNC:
    type_name = "func";
    break;
  }

  PaxoVar result = {0};
  result.type = CHAR;
  result.as.chara = type_name[0];
  return result;
}

// ==========================================
// Dispatcher de llamadas nativas
// ==========================================

PaxoVar native_call(uint16_t id, PaxoVar *args, uint8_t argc) {
  switch (id) {
  case NATIVE_PRINT:
    return native_print(args, argc);
  case NATIVE_PRINTLN:
    return native_println(args, argc);
  case NATIVE_TYPEOF:
    return native_typeof(args, argc);
  default:
    break;
  }
  // Retorno sentinel: type = 0xFF indica sin retorno
  return (PaxoVar){.type = 0xFF};
}
