#pragma once
#include "Calc.c"
#include "Typecast_and_read.c"
// Librerías externas: se activan solas cuando sus dependencias están
// disponibles (headers vendidos junto a este archivo o instaladas).
#if __has_include("chipmunk_types.h")
#include "chipmunk.h" // Chipmunk2D
#endif
#include "miniaudio.h"
#if __has_include("nanovg.h")
#include "gl3_compat.h"
#include "nanovg_gl3.h" // NanoVG (requiere nanovg.h + headers GL)
#endif
#if __has_include(<SDL3/SDL.h>)
#define SDL_MAIN_HANDLED
#include "simple2d.h" // Simple 2D (requiere SDL3)
#undef main            // evita el rewrite de main de SDL_main.h
#endif
#include "pdfio.h"
#include "stb_image.h"
#include "stb_image_resize2.h"
#include "stb_image_write.h"
#include "stb_truetype.h"
#include "termcolor-c.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
  // Nuevas funciones gráficas
  NATIVE_INIT_WINDOW,
  NATIVE_CLEAR_SCREEN,
  NATIVE_DRAW_RECT,
  // Manejo de archivos
  NATIVE_FILE_READ,
  NATIVE_FILE_WRITE,
  NATIVE_FILE_APPEND,
  NATIVE_FILE_EXISTS,
  NATIVE_FILE_DELETE,
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
// Gráficos básicos (terminal ANSI)
// ==========================================

static long gfx_width = 80;
static long gfx_height = 24;

// Convierte un PaxoVar numérico a entero largo (coordenadas, tamaños)
static inline long native_arg_long(PaxoVar v) {
  enum type t = var_type(v);
  if (t != NUM16 && t != NUM64)
    return 0;
  Num64 n = (t == NUM16) ? num16tonum64(var_num16_get(v)) : var_num64_get(v);
  int e = (int)n.exp - BIAS64 - (int)n.p;
  unsigned _BitInt(128) val = n.bc;
  if (e >= 0) {
    if (e > 18)
      e = 18; // saturación
    for (int i = 0; i < e; i++)
      val *= 10;
  } else {
    int k = -e;
    unsigned _BitInt(128) d = 1;
    for (int i = 0; i < k && d <= val; i++)
      d *= 10;
    val /= d;
  }
  long r = (long)val;
  return n.signo ? -r : r;
}

// Define el tamaño del lienzo: init_window(ancho, alto)
static PaxoVar native_init_window(PaxoVar *args, uint8_t argc) {
  if (argc < 2)
    return var_bool(false);
  long w = native_arg_long(args[0]);
  long h = native_arg_long(args[1]);
  if (w <= 0 || h <= 0 || w > 10000 || h > 10000)
    return var_bool(false);
  gfx_width = w;
  gfx_height = h;
  return var_bool(true);
}

// Limpia la terminal y lleva el cursor al origen
static PaxoVar native_clear_screen(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("\033[2J\033[H", stdout);
  fflush(stdout);
  return PAXO_ZERO;
}

// Dibuja un rectángulo relleno con '█': draw_rect(x, y, ancho, alto)
// Coordenadas 0-based desde la esquina superior izquierda; se recorta
// al lienzo de init_window. Usa el color de texto actual.
static PaxoVar native_draw_rect(PaxoVar *args, uint8_t argc) {
  if (argc < 4)
    return PAXO_ZERO;
  long x = native_arg_long(args[0]);
  long y = native_arg_long(args[1]);
  long w = native_arg_long(args[2]);
  long h = native_arg_long(args[3]);

  if (x < 0) {
    w += x;
    x = 0;
  }
  if (y < 0) {
    h += y;
    y = 0;
  }
  if (x + w > gfx_width)
    w = gfx_width - x;
  if (y + h > gfx_height)
    h = gfx_height - y;
  if (w <= 0 || h <= 0)
    return PAXO_ZERO;

  for (long row = 0; row < h; row++) {
    printf("\033[%ld;%ldH", y + row + 1, x + 1);
    for (long col = 0; col < w; col++)
      fputs("█", stdout);
  }
  fflush(stdout);
  return PAXO_ZERO;
}

// ==========================================
// Manejo de archivos
// ==========================================

// Lee todo el archivo como string: file_read(ruta)
// Retorna "" si el archivo no existe o falla la lectura.
static PaxoVar native_file_read(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING)
    return var_string("");
  const char *path = var_string_get(args[0]);
  FILE *f = fopen(path, "rb");
  if (!f) {
    text_red(stderr);
    fprintf(stderr, "[paxo] file_read: no se pudo abrir '%s'\n", path);
    reset_colors(stderr);
    return var_string("");
  }
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);
  if (size < 0)
    size = 0;
  char *buf = malloc((size_t)size + 1);
  if (!buf) {
    fclose(f);
    return var_string("");
  }
  size_t leidos = fread(buf, 1, (size_t)size, f);
  buf[leidos] = '\0';
  fclose(f);
  return var_string(buf);
}

static PaxoVar file_write_mode(const char *path, const char *data,
                               const char *mode) {
  FILE *f = fopen(path, mode);
  if (!f)
    return var_bool(false);
  size_t len = strlen(data);
  bool ok = fwrite(data, 1, len, f) == len;
  fclose(f);
  return var_bool(ok);
}

// Escribe (sobrescribe): file_write(ruta, contenido) -> bool
static PaxoVar native_file_write(PaxoVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != STRING || var_type(args[1]) != STRING)
    return var_bool(false);
  return file_write_mode(var_string_get(args[0]), var_string_get(args[1]),
                         "wb");
}

// Agrega al final: file_append(ruta, contenido) -> bool
static PaxoVar native_file_append(PaxoVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != STRING || var_type(args[1]) != STRING)
    return var_bool(false);
  return file_write_mode(var_string_get(args[0]), var_string_get(args[1]),
                         "ab");
}

// Verifica existencia: file_exists(ruta) -> bool
static PaxoVar native_file_exists(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING)
    return var_bool(false);
  return var_bool(access(var_string_get(args[0]), F_OK) == 0);
}

// Borra archivo: file_delete(ruta) -> bool
static PaxoVar native_file_delete(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING)
    return var_bool(false);
  return var_bool(remove(var_string_get(args[0])) == 0);
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
  case NATIVE_INIT_WINDOW:
    return native_init_window(args, argc);
  case NATIVE_CLEAR_SCREEN:
    return native_clear_screen(args, argc);
  case NATIVE_DRAW_RECT:
    return native_draw_rect(args, argc);
  case NATIVE_FILE_READ:
    return native_file_read(args, argc);
  case NATIVE_FILE_WRITE:
    return native_file_write(args, argc);
  case NATIVE_FILE_APPEND:
    return native_file_append(args, argc);
  case NATIVE_FILE_EXISTS:
    return native_file_exists(args, argc);
  case NATIVE_FILE_DELETE:
    return native_file_delete(args, argc);
  default:
    break;
  }
  return PAXO_NO_VALUE;
}
