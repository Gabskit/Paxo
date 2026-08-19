#pragma once
#include "Calc.c"
#include "Typecast_and_read.c"
#include "termcolor-c.h"
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
  NATIVE_SET_COLOR_TEXT,
  NATIVE_SET_TYPE_TEXT,
  NATIVE_SET_COLOR_BACK,
  NATIVE_RESET_COLOR,
  NATIVE_SCAN,
  NATIVE_LEN,
  NATIVE_ID_COUNT
} NativeId;

// ==========================================
// Funciones nativas
// ==========================================

static PaxoVar native_print(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return (PaxoVar){0};

  for (uint8_t i = 0; i < argc; i++) {
    PaxoVar val = args[i];

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
    case STRING:
      printf("%s", (const char *)val.as.puntero);
      break;
    default:
      break;
    }
  }

  return (PaxoVar){0};
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

static PaxoVar native_set_text_color(PaxoVar *args, uint8_t argc) {
  if (argc < 1) {
    return (PaxoVar){0};
  }
  const char *color = (const char *)args[0].as.puntero;
  if (strcmp(color, "red") == 0) {
    text_red(stdout);
  } else if (strcmp(color, "yellow") == 0) {
    text_yellow(stdout);
  } else if (strcmp(color, "green") == 0) {
    text_green(stdout);
  } else if (strcmp(color, "cyan") == 0) {
    text_cyan(stdout);
  } else if (strcmp(color, "blue") == 0) {
    text_blue(stdout);
  } else if (strcmp(color, "magenta") == 0) {
    text_magenta(stdout);
  } else if (strcmp(color, "white") == 0) {
    text_white(stdout);
  } else if (strcmp(color, "gray") == 0) {
    text_gray(stdout);
  } else if (strcmp(color, "grey") == 0) {
    text_grey(stdout);
  } else if (strcmp(color, "dark red") == 0) {
    text_dark(stdout);
    text_red(stdout);
  } else if (strcmp(color, "dark green") == 0) {
    text_dark(stdout);
    text_green(stdout);
  } else if (strcmp(color, "dark blue") == 0) {
    text_dark(stdout);
    text_blue(stdout);
  } else if (strcmp(color, "dark yellow") == 0) {
    text_dark(stdout);
    text_yellow(stdout);
  } else if (strcmp(color, "dark cyan") == 0) {
    text_dark(stdout);
    text_cyan(stdout);
  } else if (strcmp(color, "dark magenta") == 0) {
    text_dark(stdout);
    text_magenta(stdout);
  } else if (strcmp(color, "dark white") == 0) {
    text_dark(stdout);
    text_white(stdout);
  } else if (strcmp(color, "dark gray") == 0) {
    text_dark(stdout);
    text_gray(stdout);
  }
  return (PaxoVar){0};
}

static PaxoVar native_reset_color(PaxoVar *args, uint8_t argc) {
  reset_colors(stdout);
  return (PaxoVar){0};
}

static PaxoVar native_set_bg_color(PaxoVar *args, uint8_t argc) {
  if (argc < 1) {
    return (PaxoVar){0};
  }
  const char *color = (const char *)args[0].as.puntero;
  if (strcmp(color, "red") == 0) {
    background_red(stdout);
  } else if (strcmp(color, "green") == 0) {
    background_green(stdout);
  } else if (strcmp(color, "blue") == 0) {
    background_blue(stdout);
  } else if (strcmp(color, "yellow") == 0) {
    background_yellow(stdout);
  } else if (strcmp(color, "cyan") == 0) {
    background_cyan(stdout);
  } else if (strcmp(color, "magenta") == 0) {
    background_magenta(stdout);
  } else if (strcmp(color, "white") == 0) {
    background_white(stdout);
  } else if (strcmp(color, "gray") == 0) {
    background_gray(stdout);
  } else if (strcmp(color, "grey") == 0) {
    background_grey(stdout);
  }
  return (PaxoVar){0};
}

static PaxoVar native_set_text_type(PaxoVar *args, uint8_t argc) {
  if (argc < 1) {
    return (PaxoVar){0};
  }
  const char *type = (const char *)args[0].as.puntero;
  if (strcmp(type, "bold") == 0) {
    text_bold(stdout);
  } else if (strcmp(type, "dark") == 0) {
    text_dark(stdout);
  } else if (strcmp(type, "underline") == 0) {
    text_underline(stdout);
  } else if (strcmp(type, "blink") == 0) {
    text_blink(stdout);
  } else if (strcmp(type, "reverse") == 0) {
    text_reverse(stdout);
  } else if (strcmp(type, "concealed") == 0) {
    text_concealed(stdout);
  }
  return (PaxoVar){0};
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
  case NATIVE_SET_COLOR_TEXT:
    return native_set_text_color(args, argc);
  case NATIVE_SET_COLOR_BACK:
    return native_set_bg_color(args, argc);
  case NATIVE_SET_TYPE_TEXT:
    return native_set_text_type(args, argc);
  case NATIVE_RESET_COLOR:
    return native_reset_color(args, argc);
  default:
    break;
  }
  // Retorno sentinel: type = 0xFF indica sin retorno
  return (PaxoVar){.type = 0xFF};
}
