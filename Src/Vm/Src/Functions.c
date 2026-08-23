#pragma once
#include "Calc.c"
#include "Typecast_and_read.c"
#include "chipmunk.h"
#include "miniaudio.h"
#include "nanovg_gl3.h"
#include "simple2d.h"
#include "stb_image.h"
#include "stb_image_resize2.h"
#include "stb_image_write.h"
#include "stb_truetype.h"
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
  NATIVE_ARRAY_LEN,
  NATIVE_ARRAY_PUSH,
  NATIVE_ID_COUNT
} NativeId;

// ==========================================
// Funciones nativas
// ==========================================

static void print_var_inline(PaxoVar elem) {
  switch (var_type(elem)) {
  case NUM16:
    printf("%s", (const char *)readnum16(var_num16_get(elem), 1));
    break;
  case NUM64:
    printf("%s", (const char *)readnum64(var_num64_get(elem), 1));
    break;
  case BOOL:
    printf("%s", var_bool_get(elem) ? "true" : "false");
    break;
  case TRIT:
    printf("%s", (const char *)readtrit(var_trit_get(elem)));
    break;
  case CHAR:
    printf("'%s'", (const char *)readchar32(var_char_get(elem)));
    break;
  case STRING:
    printf("\"%s\"", var_string_get(elem));
    break;
  case ARRAY:
    printf("«...»");
    break;
  case PACKAGE:
    printf("{...}");
    break;
  default:
    break;
  }
}

static PaxoVar native_print(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return PAXO_ZERO;

  for (uint8_t i = 0; i < argc; i++) {
    PaxoVar val = args[i];

    switch (var_type(val)) {
    case NUM16:
      printf("%s", (const char *)readnum16(var_num16_get(val), 1));
      break;
    case NUM64:
      printf("%s", (const char *)readnum64(var_num64_get(val), 1));
      break;
    case BOOL:
      printf("%s", var_bool_get(val) ? "true" : "false");
      break;
    case TRIT:
      printf("%s", (const char *)readtrit(var_trit_get(val)));
      break;
    case CHAR:
      printf("%s", (const char *)readchar32(var_char_get(val)));
      break;
    case STRING:
      printf("%s", var_string_get(val));
      break;
    case ARRAY: {
      printf("«");
      PaxoArray *arr = var_array_get(val);
      for (size_t i = 0; i < arr->len; i++) {
        if (i > 0)
          printf(", ");
        print_var_inline(arr->items[i]);
      }
      printf("»");
      break;
    }
    case PACKAGE:
      printf("{package}");
      break;
    default:
      break;
    }
  }

  return PAXO_ZERO;
}

static PaxoVar native_println(PaxoVar *args, uint8_t argc) {
  native_print(args, argc);
  putchar('\n');
  return PAXO_ZERO;
}

static PaxoVar native_typeof(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return PAXO_ZERO;
  const char *type_name = "unknown";
  switch (var_type(args[0])) {
  case NUM16:
    type_name = "num16";
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
  case STRING:
    type_name = "string";
    break;
  case ARRAY:
    type_name = "array";
    break;
  case PACKAGE:
    type_name = "package";
    break;
  }

  return var_string(type_name);
}

static PaxoVar native_set_text_color(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) {
    return PAXO_ZERO;
  }
  const char *color = var_string_get(args[0]);
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
  return PAXO_ZERO;
}

static PaxoVar native_reset_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  reset_colors(stdout);
  return PAXO_ZERO;
}

static PaxoVar native_set_bg_color(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) {
    return PAXO_ZERO;
  }
  const char *color = var_string_get(args[0]);
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
  } else if (strcmp(color, "gray") == 0 || strcmp(color, "grey") == 0) {
    background_gray(stdout);
  } else if (strcmp(color, "dark red") == 0) {
    background_dark_red(stdout);
  } else if (strcmp(color, "dark green") == 0) {
    background_dark_green(stdout);
  } else if (strcmp(color, "dark blue") == 0) {
    background_dark_blue(stdout);
  } else if (strcmp(color, "dark yellow") == 0) {
    background_dark_yellow(stdout);
  } else if (strcmp(color, "dark cyan") == 0) {
    background_dark_cyan(stdout);
  } else if (strcmp(color, "dark magenta") == 0) {
    background_dark_magenta(stdout);
  } else if (strcmp(color, "dark white") == 0) {
    background_dark_white(stdout);
  } else if (strcmp(color, "dark gray") == 0 ||
             strcmp(color, "dark grey") == 0) {
    background_dark_gray(stdout);
  }
  return PAXO_ZERO;
}

static PaxoVar native_scan(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  static char buf[1024];
  if (!fgets(buf, sizeof(buf), stdin)) {
    buf[0] = '\0';
  }
  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n') {
    buf[len - 1] = '\0';
  }
  return var_string(buf);
}

static PaxoVar native_array_len(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != ARRAY)
    return PAXO_ZERO;
  size_t len = var_array_get(args[0])->len;
  Num64 result = {0};
  result.exp = BIAS64;
  result.bc = (uint64_t)len;
  return var_num64(result);
}

static PaxoVar native_array_push(PaxoVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != ARRAY)
    return PAXO_ZERO;
  PaxoArray *arr = var_array_get(args[0]);
  if (arr->len >= arr->capacity) {
    arr->capacity *= 2;
    arr->items = realloc(arr->items, sizeof(PaxoVar) * arr->capacity);
  }
  arr->items[arr->len++] = args[1];
  return PAXO_ZERO;
}

static PaxoVar native_set_text_type(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) {
    return PAXO_ZERO;
  }
  const char *type = var_string_get(args[0]);
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
  return PAXO_ZERO;
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
  case NATIVE_SCAN:
    return native_scan(args, argc);
  case NATIVE_ARRAY_LEN:
    return native_array_len(args, argc);
  case NATIVE_ARRAY_PUSH:
    return native_array_push(args, argc);
  default:
    break;
  }
  return PAXO_NO_VALUE;
}
