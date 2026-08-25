#pragma once
#include "Calc.c"
#include "Typecast_and_read.c"

// ==========================================
// Librerías vendidas junto a la VM.
// Las de cabecera única (stb_* y miniaudio) se implementan aquí mismo y
// siempre están disponibles en el build normal. Chipmunk2D y pdfio se
// compilan desde third_party/. La ventana gráfica requiere SDL3 instalada
// en el sistema y se activa definiendo PAXO_ENABLE_SDL3.
// En lep.h (single-header) los #include "..." se eliminan, por lo que las
// guardas __has_include desactivan los nativos correspondientes solos.
// ==========================================

// --- Imágenes (stb_image / write / resize2) ---
#if __has_include("stb_image.h") && !defined(PAXO_NO_STB)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE2_IMPLEMENTATION
#include "stb_image_resize2.h"
#define PAXO_HAS_IMG 1
#endif

// --- Fuentes (stb_truetype) ---
#if __has_include("stb_truetype.h") && !defined(PAXO_NO_STB)
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define PAXO_HAS_FONT 1
#endif

// --- Audio (miniaudio) ---
#if __has_include("miniaudio.h") && !defined(PAXO_NO_MINIAUDIO)
#define MA_IMPLEMENTATION
#include "miniaudio.h"
#define PAXO_HAS_AUDIO 1
#endif

// --- Física (Chipmunk2D 7, fuentes en third_party/chipmunk) ---
#if __has_include("third_party/chipmunk/chipmunk/chipmunk.h")
#include "third_party/chipmunk/chipmunk/chipmunk.h"
#define PAXO_HAS_PHYS 1
#endif

// --- PDF (pdfio + zlib, fuentes en third_party/pdfio) ---
#if __has_include("third_party/pdfio/pdfio.h")
#include "third_party/pdfio/pdfio-content.h"
#include "third_party/pdfio/pdfio.h"
#define PAXO_HAS_PDF 1
#endif

// --- Ventana/gráficos (SDL3 del sistema, opcional) ---
#if defined(PAXO_ENABLE_SDL3) && __has_include("SDL3/SDL.h")
#include "SDL3/SDL.h"
#define PAXO_HAS_WIN 1
#endif

#if __has_include("nanovg.h")
#include "gl3_compat.h"
#include "nanovg_gl3.h" // NanoVG (requiere nanovg.h + headers GL)
#endif
#if __has_include("SDL3/SDL.h") && !defined(PAXO_HAS_WIN)
#define SDL_MAIN_HANDLED
#include "simple2d.h" // Simple 2D (requiere SDL3)
#undef main           // evita el rewrite de main de SDL_main.h
#endif
#include "termcolor-c.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
  // Imágenes (stb)
  NATIVE_IMG_LOAD,
  NATIVE_IMG_INFO,
  NATIVE_IMG_SAVE_PNG,
  NATIVE_IMG_SAVE_JPG,
  NATIVE_IMG_SAVE_BMP,
  NATIVE_IMG_RESIZE,
  // Fuentes (stb_truetype)
  NATIVE_FONT_LOAD,
  NATIVE_FONT_GLYPH,
  NATIVE_FONT_METRICS,
  NATIVE_FONT_FREE,
  // Audio (miniaudio)
  NATIVE_AUDIO_INIT,
  NATIVE_AUDIO_QUIT,
  NATIVE_AUDIO_PLAY,
  NATIVE_AUDIO_PAUSE,
  NATIVE_AUDIO_RESUME,
  NATIVE_AUDIO_STOP,
  NATIVE_AUDIO_VOLUME,
  NATIVE_AUDIO_PLAYING,
  // Física (Chipmunk2D)
  NATIVE_PHYS_SPACE,
  NATIVE_PHYS_GRAVITY,
  NATIVE_PHYS_STEP,
  NATIVE_PHYS_BODY,
  NATIVE_PHYS_BODY_STATIC,
  NATIVE_PHYS_POS,
  NATIVE_PHYS_VEL,
  NATIVE_PHYS_SET_POS,
  NATIVE_PHYS_SET_VEL,
  NATIVE_PHYS_ANGLE,
  NATIVE_PHYS_SET_ANGLE,
  NATIVE_PHYS_FORCE,
  NATIVE_PHYS_IMPULSE,
  NATIVE_PHYS_CIRCLE,
  NATIVE_PHYS_BOX,
  NATIVE_PHYS_SEGMENT,
  NATIVE_PHYS_ELASTICITY,
  NATIVE_PHYS_FRICTION,
  NATIVE_PHYS_COLLIDE,
  NATIVE_PHYS_FREE_SHAPE,
  NATIVE_PHYS_FREE_BODY,
  NATIVE_PHYS_FREE_SPACE,
  // Ventana/gráficos (SDL3, opcional)
  NATIVE_WIN_OPEN,
  NATIVE_WIN_CLOSE,
  NATIVE_WIN_COLOR,
  NATIVE_WIN_CLEAR,
  NATIVE_WIN_RECT,
  NATIVE_WIN_LINE,
  NATIVE_WIN_CIRCLE,
  NATIVE_WIN_TEXT,
  NATIVE_TEX_LOAD,
  NATIVE_TEX_DRAW,
  NATIVE_TEX_FREE,
  NATIVE_WIN_SHOW,
  NATIVE_WIN_POLL,
  NATIVE_WIN_KEY,
  NATIVE_WIN_MOUSE,
  NATIVE_WIN_MOUSEDOWN,
  NATIVE_WIN_TIME,
  NATIVE_WIN_DELAY,
  // PDF (pdfio)
  NATIVE_PDF_OPEN,
  NATIVE_PDF_NEW,
  NATIVE_PDF_PAGES,
  NATIVE_PDF_PAGE_SIZE,
  NATIVE_PDF_TEXT,
  NATIVE_PDF_FONT,
  NATIVE_PDF_PAGE_BEGIN,
  NATIVE_PDF_COLOR,
  NATIVE_PDF_WRITE_RECT,
  NATIVE_PDF_WRITE_LINE,
  NATIVE_PDF_WRITE_TEXT,
  NATIVE_PDF_CLOSE,
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
  unsigned __int128 val = n.bc;
  if (e >= 0) {
    if (e > 18)
      e = 18; // saturación
    for (int i = 0; i < e; i++)
      val *= 10;
  } else {
    int k = -e;
    unsigned __int128 d = 1;
    for (int i = 0; i < k && d <= val; i++)
      d *= 10;
    val /= d;
  }
  long r = (long)val;
  return n.signo ? -r : r;
}

// Convierte un PaxoVar numérico a doble
static inline double native_arg_double(PaxoVar v) {
  enum type t = var_type(v);
  if (t != NUM16 && t != NUM64)
    return 0;
  Num64 n = (t == NUM16) ? num16tonum64(var_num16_get(v)) : var_num64_get(v);
  double d = (double)n.bc * pow(10.0, (int)n.exp - (int)BIAS64 - (int)n.p);
  return n.signo ? -d : d;
}

// String del argumento i o NULL si no es string
static inline const char *native_arg_str(PaxoVar v) {
  return var_type(v) == STRING ? var_string_get(v) : NULL;
}

// Construye un MP64 exacto desde un entero (hasta 15 dígitos)
static PaxoVar num_from_i64(int64_t v) {
  Num64 n = {0};
  if (v < 0) {
    n.signo = 1;
    v = -v;
  }
  if (v > 999999999999999LL)
    v = 999999999999999LL;
  n.bc = (uint64_t)v;
  n.exp = BIAS64;
  return var_num64(n);
}

// Construye un MP64 con ~15 dígitos significativos desde un doble
static PaxoVar num_from_double(double d) {
  Num64 n = {0};
  if (isnan(d))
    d = 0;
  if (d < 0) {
    n.signo = 1;
    d = -d;
  }
  if (d == 0 || isinf(d)) {
    n.exp = BIAS64;
    return var_num64(n);
  }
  int e = 0;
  while (d >= 1e15 && e < 256) {
    d /= 10;
    e++;
  }
  while (d < 1e14 && d > 0 && e > -256) {
    d *= 10;
    e--;
  }
  uint64_t bc = (uint64_t)(d + 0.5);
  if (bc >= (uint64_t)1e15) { // redondeo subió de década
    bc /= 10;
    e++;
  }
  n.bc = bc;
  n.exp = (uint64_t)(BIAS64 + e);
  return var_num64(n);
}

// ==========================================
// Arrays utilitarios para valores de retorno
// ==========================================

static PaxoArray *arr_new(size_t cap) {
  PaxoArray *a = malloc(sizeof(PaxoArray));
  a->len = 0;
  a->capacity = cap ? cap : 4;
  a->items = malloc(sizeof(PaxoVar) * a->capacity);
  return a;
}

static void arr_push_var(PaxoArray *a, PaxoVar v) {
  if (a->len >= a->capacity) {
    a->capacity *= 2;
    a->items = realloc(a->items, sizeof(PaxoVar) * a->capacity);
  }
  a->items[a->len++] = v;
}

static inline void arr_push_num(PaxoArray *a, double v) {
  arr_push_var(a, num_from_double(v));
}

// Retorna [x, y]
static PaxoVar ret_xy(double x, double y) {
  PaxoArray *a = arr_new(2);
  arr_push_num(a, x);
  arr_push_num(a, y);
  return var_array(a);
}

static size_t arg_arr_len(PaxoVar v) {
  return var_type(v) == ARRAY ? var_array_get(v)->len : 0;
}

static double arg_arr_num(PaxoVar v, size_t i) {
  if (var_type(v) != ARRAY || i >= var_array_get(v)->len)
    return 0;
  return native_arg_double(var_array_get(v)->items[i]);
}

// Convierte un array Paxo de números a bytes (0..255); retorna malloc
static uint8_t *arg_arr_bytes(PaxoVar v, size_t *out_len) {
  *out_len = 0;
  if (var_type(v) != ARRAY)
    return NULL;
  PaxoArray *a = var_array_get(v);
  uint8_t *buf = malloc(a->len ? a->len : 1);
  for (size_t i = 0; i < a->len; i++) {
    long x = native_arg_long(a->items[i]);
    buf[i] = (uint8_t)(x < 0 ? 0 : (x > 255 ? 255 : x));
  }
  *out_len = a->len;
  return buf;
}

// Convierte bytes a array Paxo de números
static PaxoVar ret_bytes_array(const uint8_t *b, size_t len) {
  PaxoArray *a = arr_new(len ? len : 1);
  for (size_t i = 0; i < len; i++)
    arr_push_var(a, num_from_i64(b[i]));
  return var_array(a);
}

// ==========================================
// Registro de handles (ids estables 1..n con reuse de slots)
// ==========================================

typedef struct {
  void **ptr;
  void **owner; // dueño (para liberar en cascada)
  size_t len, cap;
} NativeReg;

static void reg_init(NativeReg *r) {
  r->cap = 16;
  r->len = 0;
  r->ptr = calloc(r->cap, sizeof(void *));
  r->owner = calloc(r->cap, sizeof(void *));
}

static int64_t reg_add(NativeReg *r, void *p, void *owner) {
  for (size_t i = 0; i < r->len; i++) {
    if (!r->ptr[i]) {
      r->ptr[i] = p;
      r->owner[i] = owner;
      return (int64_t)i + 1;
    }
  }
  if (r->len == r->cap) {
    r->cap *= 2;
    r->ptr = realloc(r->ptr, sizeof(void *) * r->cap);
    r->owner = realloc(r->owner, sizeof(void *) * r->cap);
  }
  r->ptr[r->len] = p;
  r->owner[r->len] = owner;
  return (int64_t)(r->len++) + 1;
}

static void *reg_get(NativeReg *r, int64_t id) {
  if (id < 1 || (size_t)id > r->len)
    return NULL;
  return r->ptr[id - 1];
}

static bool reg_del(NativeReg *r, int64_t id, bool free_ptr) {
  void *p = reg_get(r, id);
  if (!p)
    return false;
  if (free_ptr)
    free(p);
  r->ptr[id - 1] = NULL;
  r->owner[id - 1] = NULL;
  return true;
}

// Libera todos los recursos cuyo dueño sea `owner`; retorna ids liberados
static size_t reg_free_owned(NativeReg *r, void *owner, void (*freer)(void *)) {
  size_t n = 0;
  for (size_t i = 0; i < r->len; i++) {
    if (r->ptr[i] && r->owner[i] == owner) {
      freer(r->ptr[i]);
      r->ptr[i] = NULL;
      r->owner[i] = NULL;
      n++;
    }
  }
  return n;
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
// Imágenes (stb_image / stb_image_write / stb_image_resize2)
// ==========================================

#ifdef PAXO_HAS_IMG

// Carga una imagen: img_load(ruta) -> [w, h, canales, byte0, byte1, ...]
// Retorna un array vacío si falla.
static PaxoVar native_img_load(PaxoVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path)
    return var_array(arr_new(0));
  int w, h, ch;
  unsigned char *data = stbi_load(path, &w, &h, &ch, 0);
  if (!data)
    return var_array(arr_new(0));
  size_t n = (size_t)w * h * ch;
  PaxoArray *a = arr_new(n + 3);
  arr_push_num(a, w);
  arr_push_num(a, h);
  arr_push_num(a, ch);
  for (size_t i = 0; i < n; i++)
    arr_push_var(a, num_from_i64(data[i]));
  stbi_image_free(data);
  return var_array(a);
}

// Info sin decodificar: img_info(ruta) -> [w, h, canales] o []
static PaxoVar native_img_info(PaxoVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  int w, h, ch;
  if (!path || !stbi_info(path, &w, &h, &ch))
    return var_array(arr_new(0));
  PaxoArray *a = arr_new(3);
  arr_push_num(a, w);
  arr_push_num(a, h);
  arr_push_num(a, ch);
  return var_array(a);
}

static PaxoVar img_save_generic(PaxoVar *args, int fmt) {
  const char *path = native_arg_str(args[0]);
  if (!path)
    return var_bool(false);
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]),
       ch = native_arg_long(args[3]);
  if (w <= 0 || h <= 0 || ch < 1 || ch > 4)
    return var_bool(false);
  size_t len = 0;
  uint8_t *data = arg_arr_bytes(args[4], &len);
  if (!data || len < (size_t)(w * h * ch)) {
    free(data);
    return var_bool(false);
  }
  bool ok = false;
  if (fmt == 0)
    ok = stbi_write_png(path, (int)w, (int)h, (int)ch, data, (int)w * (int)ch);
  else if (fmt == 1)
    ok = stbi_write_jpg(path, (int)w, (int)h, (int)ch, data, 90);
  else
    ok = stbi_write_bmp(path, (int)w, (int)h, (int)ch, data);
  free(data);
  return var_bool(ok);
}

// Guarda PNG: img_save_png(ruta, w, h, canales, datos) -> bool
static PaxoVar native_img_save_png(PaxoVar *args, uint8_t argc) {
  (void)argc;
  return img_save_generic(args, 0);
}

// Guarda JPEG: img_save_jpg(ruta, w, h, canales, datos) -> bool
static PaxoVar native_img_save_jpg(PaxoVar *args, uint8_t argc) {
  (void)argc;
  return img_save_generic(args, 1);
}

// Guarda BMP: img_save_bmp(ruta, w, h, canales, datos) -> bool
static PaxoVar native_img_save_bmp(PaxoVar *args, uint8_t argc) {
  (void)argc;
  return img_save_generic(args, 2);
}

// Escala píxeles: img_resize(datos, w, h, nuevo_w, nuevo_h, canales)
// -> array de bytes reescalado
static PaxoVar native_img_resize(PaxoVar *args, uint8_t argc) {
  if (argc < 6)
    return var_array(arr_new(0));
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]);
  long nw = native_arg_long(args[3]), nh = native_arg_long(args[4]);
  long ch = native_arg_long(args[5]);
  if (w <= 0 || h <= 0 || nw <= 0 || nh <= 0 || ch < 1 || ch > 4)
    return var_array(arr_new(0));
  size_t len = 0;
  uint8_t *src = arg_arr_bytes(args[0], &len);
  if (!src || len < (size_t)(w * h * ch)) {
    free(src);
    return var_array(arr_new(0));
  }
  uint8_t *dst = malloc((size_t)nw * nh * ch);
  bool ok =
      dst && stbir_resize_uint8_linear(src, (int)w, (int)h, 0, dst, (int)nw,
                                       (int)nh, 0, (stbir_pixel_layout)ch);
  free(src);
  PaxoVar res =
      ok ? ret_bytes_array(dst, (size_t)nw * nh * ch) : var_array(arr_new(0));
  free(dst);
  return res;
}

#else

static PaxoVar native_img_load(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] img_load: soporte de imagenes no compilado\n", stderr);
  return var_bool(false);
}
static PaxoVar native_img_info(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_array(arr_new(0));
}
static PaxoVar native_img_save_png(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_img_save_jpg(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_img_save_bmp(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_img_resize(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_array(arr_new(0));
}

#endif // PAXO_HAS_IMG

// ==========================================
// Fuentes (stb_truetype)
// ==========================================

#ifdef PAXO_HAS_FONT

typedef struct {
  unsigned char *buf;
  stbtt_fontinfo info;
} PaxoFont;

static NativeReg font_reg = {0};

// Carga un .ttf: font_load(ruta) -> handle (>0) o 0
static PaxoVar native_font_load(PaxoVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path)
    return num_from_i64(0);
  FILE *f = fopen(path, "rb");
  if (!f)
    return num_from_i64(0);
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);
  if (size <= 0) {
    fclose(f);
    return num_from_i64(0);
  }
  PaxoFont *pf = malloc(sizeof(PaxoFont));
  pf->buf = malloc((size_t)size);
  size_t rd = fread(pf->buf, 1, (size_t)size, f);
  fclose(f);
  if (rd == 0 || !stbtt_InitFont(&pf->info, pf->buf, 0)) {
    free(pf->buf);
    free(pf);
    return num_from_i64(0);
  }
  if (font_reg.cap == 0)
    reg_init(&font_reg);
  return num_from_i64(reg_add(&font_reg, pf, NULL));
}

static PaxoFont *font_from_args(PaxoVar v) {
  if (font_reg.cap == 0)
    return NULL;
  return (PaxoFont *)reg_get(&font_reg, (int64_t)native_arg_long(v));
}

// Rasteriza un glifo: font_glyph(font, codigo, tamano_px)
// -> [w, h, offset_x, offset_y, avance, byte0, ...]
static PaxoVar native_font_glyph(PaxoVar *args, uint8_t argc) {
  PaxoFont *pf = argc >= 1 ? font_from_args(args[0]) : NULL;
  if (!pf)
    return var_array(arr_new(0));
  long cp = native_arg_long(args[1]);
  float size = (float)native_arg_double(args[2]);
  if (size <= 0)
    size = 16;
  float scale = stbtt_ScaleForPixelHeight(&pf->info, size);
  int adv = 0, lsb = 0;
  stbtt_GetCodepointHMetrics(&pf->info, (int)cp, &adv, &lsb);
  int w, h, ox, oy;
  unsigned char *bmp = stbtt_GetCodepointBitmap(&pf->info, scale, scale,
                                                (int)cp, &w, &h, &ox, &oy);
  PaxoArray *a = arr_new((size_t)(w > 0 ? w : 1) * (h > 0 ? h : 1) + 5);
  arr_push_num(a, w);
  arr_push_num(a, h);
  arr_push_num(a, ox);
  arr_push_num(a, oy);
  arr_push_num(a, (double)adv * scale);
  if (bmp) {
    for (int i = 0; i < w * h; i++)
      arr_push_var(a, num_from_i64(bmp[i]));
    stbtt_FreeBitmap(bmp, NULL);
  }
  return var_array(a);
}

// Métricas verticales escaladas: font_metrics(font, tamano_px)
// -> [ascendente, descendente, linegap]
static PaxoVar native_font_metrics(PaxoVar *args, uint8_t argc) {
  PaxoFont *pf = argc >= 1 ? font_from_args(args[0]) : NULL;
  if (!pf)
    return var_array(arr_new(0));
  float size = (float)native_arg_double(args[1]);
  if (size <= 0)
    size = 16;
  float scale = stbtt_ScaleForPixelHeight(&pf->info, size);
  int asc = 0, desc = 0, gap = 0;
  stbtt_GetFontVMetrics(&pf->info, &asc, &desc, &gap);
  PaxoArray *a = arr_new(3);
  arr_push_num(a, (double)asc * scale);
  arr_push_num(a, (double)desc * scale);
  arr_push_num(a, (double)gap * scale);
  return var_array(a);
}

// Libera una fuente: font_free(font)
static PaxoVar native_font_free(PaxoVar *args, uint8_t argc) {
  if (argc >= 1 && font_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    PaxoFont *pf = (PaxoFont *)reg_get(&font_reg, id);
    if (pf) {
      free(pf->buf);
      reg_del(&font_reg, id, true);
    }
  }
  return PAXO_ZERO;
}

#else

static PaxoVar native_font_load(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_font_glyph(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_array(arr_new(0));
}
static PaxoVar native_font_metrics(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_array(arr_new(0));
}
static PaxoVar native_font_free(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}

#endif // PAXO_HAS_FONT

// ==========================================
// Audio (miniaudio, motor global + sonidos por handle)
// ==========================================

#ifdef PAXO_HAS_AUDIO

static ma_engine audio_engine;
static bool audio_up = false;
static NativeReg snd_reg = {0};

static void snd_freer(void *p) {
  ma_sound *s = (ma_sound *)p;
  ma_sound_uninit(s);
  free(s);
}

// Inicializa el motor de audio: audio_init() -> bool
static PaxoVar native_audio_init(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (audio_up)
    return var_bool(true);
  if (ma_engine_init(NULL, &audio_engine) != MA_SUCCESS)
    return var_bool(false);
  audio_up = true;
  return var_bool(true);
}

// Detiene todo y libera el motor: audio_quit()
static PaxoVar native_audio_quit(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (!audio_up)
    return PAXO_ZERO;
  for (size_t i = 0; i < snd_reg.len; i++) {
    if (snd_reg.ptr[i])
      snd_freer(snd_reg.ptr[i]);
    snd_reg.ptr[i] = NULL;
  }
  ma_engine_uninit(&audio_engine);
  audio_up = false;
  return PAXO_ZERO;
}

// Reproduce un archivo: audio_play(ruta, en_loop) -> handle o 0
static PaxoVar native_audio_play(PaxoVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path)
    return num_from_i64(0);
  if (!audio_up && !var_bool_get(native_audio_init(NULL, 0)))
    return num_from_i64(0);
  ma_sound *s = malloc(sizeof(ma_sound));
  if (ma_sound_init_from_file(&audio_engine, path, 0, NULL, NULL, s) !=
      MA_SUCCESS) {
    free(s);
    return num_from_i64(0);
  }
  ma_sound_set_looping(s, argc >= 2 && var_bool_get(args[1]));
  ma_sound_start(s);
  if (snd_reg.cap == 0)
    reg_init(&snd_reg);
  return num_from_i64(reg_add(&snd_reg, s, NULL));
}

static ma_sound *snd_from_args(PaxoVar v) {
  if (snd_reg.cap == 0)
    return NULL;
  return (ma_sound *)reg_get(&snd_reg, (int64_t)native_arg_long(v));
}

// Pausa: audio_pause(handle) -> bool
static PaxoVar native_audio_pause(PaxoVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  if (!s)
    return var_bool(false);
  ma_sound_stop(s);
  return var_bool(true);
}

// Reanuda: audio_resume(handle) -> bool
static PaxoVar native_audio_resume(PaxoVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  if (!s)
    return var_bool(false);
  ma_sound_start(s);
  return var_bool(true);
}

// Detiene y libera: audio_stop(handle) -> bool
static PaxoVar native_audio_stop(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || snd_reg.cap == 0)
    return var_bool(false);
  int64_t id = (int64_t)native_arg_long(args[0]);
  ma_sound *s = (ma_sound *)reg_get(&snd_reg, id);
  if (!s)
    return var_bool(false);
  snd_freer(s);
  reg_del(&snd_reg, id, false);
  return var_bool(true);
}

// Volumen (0..1+): audio_volume(handle, volumen) -> bool
static PaxoVar native_audio_volume(PaxoVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  if (!s)
    return var_bool(false);
  float vol = (float)native_arg_double(argc >= 2 ? args[1] : PAXO_ZERO);
  if (vol < 0)
    vol = 0;
  ma_sound_set_volume(s, vol);
  return var_bool(true);
}

// ¿Sigue sonando?: audio_playing(handle) -> bool
static PaxoVar native_audio_playing(PaxoVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  return var_bool(s && ma_sound_is_playing(s));
}

#else

static PaxoVar native_audio_init(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] audio: soporte no compilado\n", stderr);
  return var_bool(false);
}
static PaxoVar native_audio_quit(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_audio_play(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_audio_pause(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_audio_resume(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_audio_stop(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_audio_volume(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_audio_playing(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}

#endif // PAXO_HAS_AUDIO

// ==========================================
// Física 2D (Chipmunk2D)
// Espacios, cuerpos y formas referenciados por handles numéricos.
// ==========================================

#ifdef PAXO_HAS_PHYS

typedef struct {
  cpBody *body;
  cpSpace *space;
} PhysBodyRec;

typedef struct {
  cpShape *shape;
  cpSpace *space;
} PhysShapeRec;

static NativeReg space_reg = {0};
static NativeReg body_reg = {0};
static NativeReg shape_reg = {0};

static void pb_freer(void *p) {
  PhysBodyRec *r = (PhysBodyRec *)p;
  if (r->space && cpSpaceGetStaticBody(r->space) != r->body)
    cpSpaceRemoveBody(r->space, r->body);
  cpBodyFree(r->body);
  free(r);
}

static void ps_freer(void *p) {
  PhysShapeRec *r = (PhysShapeRec *)p;
  if (r->space)
    cpSpaceRemoveShape(r->space, r->shape);
  cpShapeFree(r->shape);
  free(r);
}

// Nuevo espacio: phys_space() -> handle
static PaxoVar native_phys_space(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (space_reg.cap == 0) {
    reg_init(&space_reg);
    reg_init(&body_reg);
    reg_init(&shape_reg);
  }
  cpSpace *sp = cpSpaceNew();
  return num_from_i64(reg_add(&space_reg, sp, NULL));
}

static cpSpace *space_from_args(PaxoVar v) {
  if (space_reg.cap == 0)
    return NULL;
  return (cpSpace *)reg_get(&space_reg, (int64_t)native_arg_long(v));
}

static PhysBodyRec *body_from_args(PaxoVar v) {
  if (body_reg.cap == 0)
    return NULL;
  return (PhysBodyRec *)reg_get(&body_reg, (int64_t)native_arg_long(v));
}

static PhysShapeRec *shape_from_args(PaxoVar v) {
  if (shape_reg.cap == 0)
    return NULL;
  return (PhysShapeRec *)reg_get(&shape_reg, (int64_t)native_arg_long(v));
}

// Gravedad: phys_gravity(space, gx, gy)
static PaxoVar native_phys_gravity(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (sp)
    cpSpaceSetGravity(sp,
                      cpv(native_arg_double(args[1]),
                          native_arg_double(argc >= 3 ? args[2] : PAXO_ZERO)));
  return PAXO_ZERO;
}

// Avanza la simulación: phys_step(space, dt)
static PaxoVar native_phys_step(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (sp) {
    double dt = native_arg_double(args[1]);
    if (dt <= 0 || dt > 1)
      dt = 1.0 / 60.0;
    cpSpaceStep(sp, dt);
  }
  return PAXO_ZERO;
}

// Cuerpo dinámico: phys_body(space, masa, inercia) -> handle
static PaxoVar native_phys_body(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp)
    return num_from_i64(0);
  double mass = native_arg_double(args[1]);
  double inertia = native_arg_double(args[2]);
  if (mass <= 0)
    mass = 1;
  if (inertia <= 0)
    inertia = 1;
  PhysBodyRec *rec = malloc(sizeof(PhysBodyRec));
  rec->body = cpSpaceAddBody(sp, cpBodyNew(mass, inertia));
  rec->space = sp;
  return num_from_i64(reg_add(&body_reg, rec, sp));
}

// Cuerpo estático del espacio: phys_body_static(space) -> handle
static PaxoVar native_phys_body_static(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp)
    return num_from_i64(0);
  PhysBodyRec *rec = malloc(sizeof(PhysBodyRec));
  rec->body = cpSpaceGetStaticBody(sp);
  rec->space = sp;
  return num_from_i64(reg_add(&body_reg, rec, NULL));
}

// Posición: phys_pos(body) -> [x, y]
static PaxoVar native_phys_pos(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (!r)
    return ret_xy(0, 0);
  cpVect p = cpBodyGetPosition(r->body);
  return ret_xy(p.x, p.y);
}

// Velocidad: phys_vel(body) -> [x, y]
static PaxoVar native_phys_vel(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (!r)
    return ret_xy(0, 0);
  cpVect v = cpBodyGetVelocity(r->body);
  return ret_xy(v.x, v.y);
}

// Teletransporta: phys_set_pos(body, x, y)
static PaxoVar native_phys_set_pos(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodySetPosition(r->body,
                      cpv(native_arg_double(args[1]),
                          native_arg_double(argc >= 3 ? args[2] : PAXO_ZERO)));
  return PAXO_ZERO;
}

// Fija velocidad: phys_set_vel(body, vx, vy)
static PaxoVar native_phys_set_vel(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodySetVelocity(r->body,
                      cpv(native_arg_double(args[1]),
                          native_arg_double(argc >= 3 ? args[2] : PAXO_ZERO)));
  return PAXO_ZERO;
}

// Ángulo en radianes: phys_angle(body) -> num
static PaxoVar native_phys_angle(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  return num_from_double(r ? cpBodyGetAngle(r->body) : 0);
}

// Fija ángulo: phys_set_angle(body, radianes)
static PaxoVar native_phys_set_angle(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodySetAngle(r->body, native_arg_double(args[1]));
  return PAXO_ZERO;
}

// Acumula fuerza este paso: phys_force(body, fx, fy)
static PaxoVar native_phys_force(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodyApplyForceAtLocalPoint(
        r->body,
        cpv(native_arg_double(args[1]),
            native_arg_double(argc >= 3 ? args[2] : PAXO_ZERO)),
        cpvzero);
  return PAXO_ZERO;
}

// Impulso instantáneo: phys_impulse(body, ix, iy)
static PaxoVar native_phys_impulse(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodyApplyImpulseAtLocalPoint(
        r->body,
        cpv(native_arg_double(args[1]),
            native_arg_double(argc >= 3 ? args[2] : PAXO_ZERO)),
        cpvzero);
  return PAXO_ZERO;
}

static PaxoVar shape_add(cpSpace *sp, cpShape *s) {
  PhysShapeRec *rec = malloc(sizeof(PhysShapeRec));
  rec->shape = cpSpaceAddShape(sp, s);
  rec->space = sp;
  return num_from_i64(reg_add(&shape_reg, rec, sp));
}

// Círculo: phys_circle(space, body, offset_x, offset_y, radio) -> shape
static PaxoVar native_phys_circle(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  PhysBodyRec *b = argc >= 2 ? body_from_args(args[1]) : NULL;
  if (!sp || !b)
    return num_from_i64(0);
  return shape_add(sp, cpCircleShapeNew(b->body, native_arg_double(args[4]),
                                        cpv(native_arg_double(args[2]),
                                            native_arg_double(args[3]))));
}

// Caja centrada en el cuerpo: phys_box(space, body, w, h) -> shape
static PaxoVar native_phys_box(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  PhysBodyRec *b = argc >= 2 ? body_from_args(args[1]) : NULL;
  if (!sp || !b)
    return num_from_i64(0);
  return shape_add(sp, cpBoxShapeNew(b->body, native_arg_double(args[2]),
                                     native_arg_double(args[3]), 0));
}

// Segmento: phys_segment(space, body, ax, ay, bx, by, radio) -> shape
static PaxoVar native_phys_segment(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  PhysBodyRec *b = argc >= 2 ? body_from_args(args[1]) : NULL;
  if (!sp || !b)
    return num_from_i64(0);
  return shape_add(
      sp,
      cpSegmentShapeNew(
          b->body, cpv(native_arg_double(args[2]), native_arg_double(args[3])),
          cpv(native_arg_double(args[4]), native_arg_double(args[5])),
          native_arg_double(args[6])));
}

// Rebote: phys_elasticity(shape, e)
static PaxoVar native_phys_elasticity(PaxoVar *args, uint8_t argc) {
  PhysShapeRec *r = argc >= 1 ? shape_from_args(args[0]) : NULL;
  if (r)
    cpShapeSetElasticity(r->shape, native_arg_double(args[1]));
  return PAXO_ZERO;
}

// Rozamiento: phys_friction(shape, f)
static PaxoVar native_phys_friction(PaxoVar *args, uint8_t argc) {
  PhysShapeRec *r = argc >= 1 ? shape_from_args(args[0]) : NULL;
  if (r)
    cpShapeSetFriction(r->shape, native_arg_double(args[1]));
  return PAXO_ZERO;
}

// ¿Colisionan?: phys_collide(shape_a, shape_b) -> bool
static PaxoVar native_phys_collide(PaxoVar *args, uint8_t argc) {
  PhysShapeRec *a = argc >= 1 ? shape_from_args(args[0]) : NULL;
  PhysShapeRec *b = argc >= 2 ? shape_from_args(args[1]) : NULL;
  if (!a || !b)
    return var_bool(false);
  return var_bool(cpShapesCollide(a->shape, b->shape).count > 0);
}

// Libera forma: phys_free_shape(shape)
static PaxoVar native_phys_free_shape(PaxoVar *args, uint8_t argc) {
  if (argc >= 1 && shape_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    if (reg_get(&shape_reg, id))
      ps_freer(reg_get(&shape_reg, id)), reg_del(&shape_reg, id, false);
  }
  return PAXO_ZERO;
}

// Libera cuerpo: phys_free_body(body)
static PaxoVar native_phys_free_body(PaxoVar *args, uint8_t argc) {
  if (argc >= 1 && body_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    PhysBodyRec *r = (PhysBodyRec *)reg_get(&body_reg, id);
    if (r) {
      pb_freer(r);
      reg_del(&body_reg, id, false);
    }
  }
  return PAXO_ZERO;
}

// Libera espacio con todo su contenido: phys_free_space(space)
static PaxoVar native_phys_free_space(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp)
    return PAXO_ZERO;
  int64_t sid = (int64_t)native_arg_long(args[0]);
  reg_free_owned(&shape_reg, sp, ps_freer);
  reg_free_owned(&body_reg, sp, pb_freer);
  cpSpaceFree(sp);
  reg_del(&space_reg, sid, false);
  return PAXO_ZERO;
}

#else

static PaxoVar native_phys_space(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] fisica: soporte no compilado\n", stderr);
  return num_from_i64(0);
}
static PaxoVar native_phys_gravity(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_step(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_body(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_phys_body_static(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_phys_pos(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return ret_xy(0, 0);
}
static PaxoVar native_phys_vel(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return ret_xy(0, 0);
}
static PaxoVar native_phys_set_pos(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_set_vel(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_angle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_set_angle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_force(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_impulse(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_circle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_phys_box(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_phys_segment(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_phys_elasticity(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_friction(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_collide(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_phys_free_shape(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_free_body(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_phys_free_space(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}

#endif // PAXO_HAS_PHYS

// ==========================================
// Ventana y gráficos 2D (SDL3, opcional: PAXO_ENABLE_SDL3)
// ==========================================

#ifdef PAXO_HAS_WIN

static SDL_Window *g_win = NULL;
static SDL_Renderer *g_ren = NULL;
static int g_r = 255, g_g = 255, g_b = 255;
static NativeReg tex_reg = {0};

static void tex_freer(void *p) { SDL_DestroyTexture((SDL_Texture *)p); }

// Abre ventana: win_open(titulo, ancho, alto) -> bool
static PaxoVar native_win_open(PaxoVar *args, uint8_t argc) {
  if (argc < 3)
    return var_bool(false);
  if (g_win)
    return var_bool(true);
  const char *title = native_arg_str(args[0]);
  if (!title)
    title = "paxo";
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]);
  if (w <= 0 || h <= 0)
    return var_bool(false);
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    fputs("[paxo] win_open: no se pudo iniciar SDL\n", stderr);
    return var_bool(false);
  }
  if (!SDL_CreateWindowAndRenderer(title, (int)w, (int)h, 0, &g_win, &g_ren)) {
    SDL_Quit();
    return var_bool(false);
  }
  if (tex_reg.cap == 0)
    reg_init(&tex_reg);
  return var_bool(true);
}

// Cierra la ventana: win_close()
static PaxoVar native_win_close(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (!g_win)
    return PAXO_ZERO;
  if (tex_reg.cap != 0)
    reg_free_owned(&tex_reg, g_ren, tex_freer);
  SDL_DestroyRenderer(g_ren);
  SDL_DestroyWindow(g_win);
  g_ren = NULL;
  g_win = NULL;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
  return PAXO_ZERO;
}

// Color de dibujo 0..255: win_color(r, g, b)
static PaxoVar native_win_color(PaxoVar *args, uint8_t argc) {
  if (argc < 3)
    return PAXO_ZERO;
  long r = native_arg_long(args[0]), g = native_arg_long(args[1]),
       b = native_arg_long(args[2]);
  g_r = (int)(r < 0 ? 0 : (r > 255 ? 255 : r));
  g_g = (int)(g < 0 ? 0 : (g > 255 ? 255 : g));
  g_b = (int)(b < 0 ? 0 : (b > 255 ? 255 : b));
  return PAXO_ZERO;
}

// Limpia con el color actual: win_clear()
static PaxoVar native_win_clear(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (!g_ren)
    return PAXO_ZERO;
  SDL_SetRenderDrawColor(g_ren, g_r, g_g, g_b, 255);
  SDL_RenderClear(g_ren);
  return PAXO_ZERO;
}

// Rectángulo relleno: win_rect(x, y, w, h)
static PaxoVar native_win_rect(PaxoVar *args, uint8_t argc) {
  if (!g_ren || argc < 4)
    return PAXO_ZERO;
  SDL_FRect rc = {
      (float)native_arg_double(args[0]), (float)native_arg_double(args[1]),
      (float)native_arg_double(args[2]), (float)native_arg_double(args[3])};
  SDL_SetRenderDrawColor(g_ren, g_r, g_g, g_b, 255);
  SDL_RenderFillRect(g_ren, &rc);
  return PAXO_ZERO;
}

// Línea: win_line(x1, y1, x2, y2)
static PaxoVar native_win_line(PaxoVar *args, uint8_t argc) {
  if (!g_ren || argc < 4)
    return PAXO_ZERO;
  SDL_FPoint a = {(float)native_arg_double(args[0]),
                  (float)native_arg_double(args[1])};
  SDL_FPoint b = {(float)native_arg_double(args[2]),
                  (float)native_arg_double(args[3])};
  SDL_SetRenderDrawColor(g_ren, g_r, g_g, g_b, 255);
  SDL_RenderLine(g_ren, a.x, a.y, b.x, b.y);
  return PAXO_ZERO;
}

// Círculo relleno: win_circle(cx, cy, radio)
static PaxoVar native_win_circle(PaxoVar *args, uint8_t argc) {
  if (!g_ren || argc < 3)
    return PAXO_ZERO;
  double cx = native_arg_double(args[0]), cy = native_arg_double(args[1]);
  double r = native_arg_double(args[2]);
  if (r <= 0)
    return PAXO_ZERO;
  enum { SEG = 40 };
  static SDL_Vertex v[SEG + 2];
  SDL_FColor col = {(float)g_r / 255.0f, (float)g_g / 255.0f,
                    (float)g_b / 255.0f, 1.0f};
  v[0].position.x = (float)cx;
  v[0].position.y = (float)cy;
  v[0].color = col;
  for (int i = 0; i <= SEG; i++) {
    double t = 2.0 * 3.14159265358979 * i / SEG;
    v[i + 1].position.x = (float)(cx + r * cos(t));
    v[i + 1].position.y = (float)(cy + r * sin(t));
    v[i + 1].color = col;
  }
  SDL_SetRenderDrawColor(g_ren, g_r, g_g, g_b, 255);
  SDL_RenderGeometry(g_ren, NULL, v, SEG + 2, NULL, 0);
  return PAXO_ZERO;
}

// Texto rápido: win_text(x, y, texto)
static PaxoVar native_win_text(PaxoVar *args, uint8_t argc) {
  if (!g_ren || argc < 3)
    return PAXO_ZERO;
  const char *s = native_arg_str(args[2]);
  if (!s)
    return PAXO_ZERO;
  SDL_SetRenderDrawColor(g_ren, g_r, g_g, g_b, 255);
  SDL_RenderDebugText(g_ren, (float)native_arg_double(args[0]),
                      (float)native_arg_double(args[1]), s);
  return PAXO_ZERO;
}

// Crea textura desde píxeles RGBA/RGB:
// tex_load(datos, w, h, canales) -> handle
static PaxoVar native_tex_load(PaxoVar *args, uint8_t argc) {
  if (!g_ren || argc < 4)
    return num_from_i64(0);
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]),
       ch = native_arg_long(args[3]);
  if (w <= 0 || h <= 0 || (ch != 3 && ch != 4))
    return num_from_i64(0);
  size_t len = 0;
  uint8_t *data = arg_arr_bytes(args[0], &len);
  if (!data || len < (size_t)(w * h * ch)) {
    free(data);
    return num_from_i64(0);
  }
  SDL_Surface *sf = SDL_CreateSurface((int)w, (int)h, SDL_PIXELFORMAT_RGBA32);
  if (!sf) {
    free(data);
    return num_from_i64(0);
  }
  uint8_t *px = (uint8_t *)sf->pixels;
  for (long i = 0; i < w * h; i++) {
    px[i * 4 + 0] = data[i * ch];
    px[i * 4 + 1] = data[i * ch + 1 % ch];
    px[i * 4 + 2] = data[i * ch + 2 % ch];
    px[i * 4 + 3] = ch == 4 ? data[i * ch + 3] : 255;
  }
  free(data);
  SDL_Texture *t = SDL_CreateTextureFromSurface(g_ren, sf);
  SDL_DestroySurface(sf);
  if (!t)
    return num_from_i64(0);
  return num_from_i64(reg_add(&tex_reg, t, g_ren));
}

static SDL_Texture *tex_from_args(PaxoVar v) {
  if (tex_reg.cap == 0)
    return NULL;
  return (SDL_Texture *)reg_get(&tex_reg, (int64_t)native_arg_long(v));
}

// Dibuja textura: tex_draw(tex, x, y [, w, h])
static PaxoVar native_tex_draw(PaxoVar *args, uint8_t argc) {
  SDL_Texture *t = argc >= 1 ? tex_from_args(args[0]) : NULL;
  if (!t || !g_ren)
    return PAXO_ZERO;
  float x = (float)native_arg_double(args[1]);
  float y = (float)native_arg_double(args[2]);
  float w, h;
  if (argc >= 5) {
    w = (float)native_arg_double(args[3]);
    h = (float)native_arg_double(args[4]);
  } else {
    SDL_GetTextureSize(t, &w, &h);
  }
  SDL_FRect dst = {x, y, w, h};
  SDL_RenderTexture(g_ren, t, NULL, &dst);
  return PAXO_ZERO;
}

// Libera textura: tex_free(tex)
static PaxoVar native_tex_free(PaxoVar *args, uint8_t argc) {
  if (argc >= 1 && tex_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    SDL_Texture *t = (SDL_Texture *)reg_get(&tex_reg, id);
    if (t) {
      tex_freer(t);
      reg_del(&tex_reg, id, false);
    }
  }
  return PAXO_ZERO;
}

// Presenta el frame: win_show()
static PaxoVar native_win_show(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (g_ren)
    SDL_RenderPresent(g_ren);
  return PAXO_ZERO;
}

// Procesa eventos: win_poll() -> ["quit", "keydown:32", "mousedown", ...]
static PaxoVar native_win_poll(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  PaxoArray *a = arr_new(4);
  if (!g_win)
    return var_array(a);
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_EVENT_QUIT) {
      arr_push_var(a, var_string("quit"));
    } else if (ev.type == SDL_EVENT_KEY_DOWN || ev.type == SDL_EVENT_KEY_UP) {
      char buf[32];
      snprintf(buf, sizeof(buf), "%s:%lu",
               ev.type == SDL_EVENT_KEY_DOWN ? "keydown" : "keyup",
               (unsigned long)ev.key.key);
      arr_push_var(a, var_string(buf));
    } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      arr_push_var(a, var_string("mousedown"));
    } else if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP) {
      arr_push_var(a, var_string("mouseup"));
    }
  }
  return var_array(a);
}

// ¿Tecla presionada?: win_key("W" | "Space" | ...) -> bool
static PaxoVar native_win_key(PaxoVar *args, uint8_t argc) {
  const char *name = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!name)
    return var_bool(false);
  SDL_Scancode sc = SDL_GetScancodeFromName(name);
  if (sc == SDL_SCANCODE_UNKNOWN)
    return var_bool(false);
  return var_bool(SDL_GetKeyboardState(NULL)[sc]);
}

// Posición del mouse: win_mouse() -> [x, y]
static PaxoVar native_win_mouse(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  float mx = 0, my = 0;
  SDL_GetMouseState(&mx, &my);
  return ret_xy(mx, my);
}

// ¿Botón izquierdo presionado?: win_mousedown() -> bool
static PaxoVar native_win_mousedown(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK);
}

// Milisegundos desde el inicio: win_time() -> num
static PaxoVar native_win_time(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64((int64_t)SDL_GetTicks());
}

// Espera: win_delay(ms)
static PaxoVar native_win_delay(PaxoVar *args, uint8_t argc) {
  long ms = argc >= 1 ? native_arg_long(args[0]) : 0;
  if (ms > 0)
    SDL_Delay((Uint32)ms);
  return PAXO_ZERO;
}

#else

static PaxoVar native_win_open(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] win_open: recompila la VM con SDL3 "
        "(PAXO_ENABLE_SDL3) para usar ventanas\n",
        stderr);
  return var_bool(false);
}
static PaxoVar native_win_close(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_clear(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_rect(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_line(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_circle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_text(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_tex_load(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_tex_draw(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_tex_free(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_show(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_win_poll(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_array(arr_new(0));
}
static PaxoVar native_win_key(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_win_mouse(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return ret_xy(0, 0);
}
static PaxoVar native_win_mousedown(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_win_time(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_win_delay(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}

#endif // PAXO_HAS_WIN

// ==========================================
// PDF (pdfio)
// ==========================================

#ifdef PAXO_HAS_PDF

typedef struct {
  pdfio_file_t *file;
  bool writing;
  pdfio_stream_t *page;
  pdfio_obj_t *fonts[8];
  char names[8][16];
  int nfonts;
  int curfont;
} PaxoPdf;

static NativeReg pdf_reg = {0};

static PaxoPdf *pdf_from_args(PaxoVar v) {
  if (pdf_reg.cap == 0)
    return NULL;
  return (PaxoPdf *)reg_get(&pdf_reg, (int64_t)native_arg_long(v));
}

// Abre para lectura: pdf_open(ruta) -> handle o 0
static PaxoVar native_pdf_open(PaxoVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path)
    return num_from_i64(0);
  pdfio_file_t *f = pdfioFileOpen(path, NULL, NULL, NULL, NULL);
  if (!f)
    return num_from_i64(0);
  PaxoPdf *d = calloc(1, sizeof(PaxoPdf));
  d->file = f;
  d->writing = false;
  if (pdf_reg.cap == 0)
    reg_init(&pdf_reg);
  return num_from_i64(reg_add(&pdf_reg, d, NULL));
}

// Crea para escritura: pdf_new(ruta [, ancho, alto]) -> handle o 0
// El tamaño de página se define al crear el documento (en puntos).
static PaxoVar native_pdf_new(PaxoVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path)
    return num_from_i64(0);
  pdfio_rect_t box = {0, 0, 612, 792};
  pdfio_rect_t *pbox = NULL;
  if (argc >= 3) {
    double w = native_arg_double(args[1]);
    double h = native_arg_double(args[2]);
    if (w > 0 && h > 0) {
      box.x2 = w;
      box.y2 = h;
      pbox = &box;
    }
  }
  pdfio_file_t *f = pdfioFileCreate(path, "1.7", pbox, pbox, NULL, NULL);
  if (!f)
    return num_from_i64(0);
  PaxoPdf *d = calloc(1, sizeof(PaxoPdf));
  d->file = f;
  d->writing = true;
  if (pdf_reg.cap == 0)
    reg_init(&pdf_reg);
  return num_from_i64(reg_add(&pdf_reg, d, NULL));
}

// Cantidad de páginas: pdf_pages(doc) -> num
static PaxoVar native_pdf_pages(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 1 ? pdf_from_args(args[0]) : NULL;
  return num_from_i64(d && !d->writing ? (int64_t)pdfioFileGetNumPages(d->file)
                                       : 0);
}

// Tamaño de página en puntos: pdf_page_size(doc, pagina) -> [w, h]
static PaxoVar native_pdf_page_size(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 2 ? pdf_from_args(args[0]) : NULL;
  if (!d || d->writing)
    return ret_xy(0, 0);
  pdfio_obj_t *page =
      pdfioFileGetPage(d->file, (size_t)native_arg_long(args[1]) - 1);
  if (!page)
    return ret_xy(0, 0);
  pdfio_rect_t r = {0, 0, 612, 792};
  pdfio_dict_t *dict = pdfioObjGetDict(page);
  if (!pdfioDictGetRect(dict, "MediaBox", &r) &&
      !pdfioDictGetRect(dict, "CropBox", &r)) {
    r.x1 = r.y1 = 0;
    r.x2 = 612;
    r.y2 = 792;
  }
  return ret_xy(r.x2 - r.x1, r.y2 - r.y1);
}

// Extrae texto plano: pdf_text(doc, pagina) -> string
static PaxoVar native_pdf_text(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 2 ? pdf_from_args(args[0]) : NULL;
  if (!d || d->writing)
    return var_string("");
  pdfio_obj_t *page =
      pdfioFileGetPage(d->file, (size_t)native_arg_long(args[1]) - 1);
  if (!page || pdfioPageGetNumStreams(page) < 1)
    return var_string("");
  pdfio_stream_t *st = pdfioPageOpenStream(page, 0, true);
  if (!st)
    return var_string("");
  size_t cap = 1024, len = 0;
  char *out = malloc(cap);
  out[0] = '\0';
  char tok[2048];
  while (pdfioStreamGetToken(st, tok, sizeof(tok))) {
    size_t tl;
    if (tok[0] == '(') { // literal string ya desescapada
      const char *txt = tok + 1;
      tl = strlen(txt);
      if (len + tl + 2 > cap) {
        while (len + tl + 2 > cap)
          cap *= 2;
        out = realloc(out, cap);
      }
      memcpy(out + len, txt, tl);
      len += tl;
      out[len++] = ' ';
      out[len] = '\0';
    }
  }
  pdfioStreamClose(st);
  if (len > 0 && out[len - 1] == ' ')
    out[len - 1] = '\0';
  PaxoVar res = var_string(out);
  free(out);
  return res;
}

// Registra fuente base14 ("Helvetica", "Courier", ...):
// pdf_font(doc, nombre) -> índice o 0
static PaxoVar native_pdf_font(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 2 ? pdf_from_args(args[0]) : NULL;
  const char *name = native_arg_str(args[1]);
  if (!d || !d->writing || !name || d->nfonts >= 8)
    return num_from_i64(0);
  pdfio_obj_t *fo = pdfioFileCreateFontObjFromBase(d->file, name);
  if (!fo)
    return num_from_i64(0);
  snprintf(d->names[d->nfonts], sizeof(d->names[0]), "F%d", d->nfonts + 1);
  d->fonts[d->nfonts] = fo;
  d->curfont = d->nfonts++;
  return num_from_i64(d->curfont + 1);
}

// Comienza una página: pdf_page_begin(doc, ancho, alto) -> bool
static PaxoVar native_pdf_page_begin(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 1 ? pdf_from_args(args[0]) : NULL;
  if (!d || !d->writing || d->page)
    return var_bool(false);
  pdfio_rect_t box = {0, 0, 612, 792};
  if (argc >= 3) {
    box.x2 = native_arg_double(args[1]);
    box.y2 = native_arg_double(args[2]);
    if (box.x2 <= 0)
      box.x2 = 612;
    if (box.y2 <= 0)
      box.y2 = 792;
  }
  pdfio_dict_t *dict = pdfioDictCreate(d->file);
  if (!dict)
    return var_bool(false);
  for (int i = 0; i < d->nfonts; i++)
    pdfioPageDictAddFont(dict, d->names[i], d->fonts[i]);
  d->page = pdfioFileCreatePage(d->file, dict);
  if (!d->page)
    return var_bool(false);
  pdfioContentTextBegin(d->page);
  return var_bool(true);
}

// Color de relleno/trazo 0..255: pdf_color(doc, r, g, b)
static PaxoVar native_pdf_color(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 4 ? pdf_from_args(args[0]) : NULL;
  if (!d || !d->page)
    return PAXO_ZERO;
  double r = native_arg_double(args[1]) / 255.0;
  double g = native_arg_double(args[2]) / 255.0;
  double b = native_arg_double(args[3]) / 255.0;
  pdfioContentSetFillColorDeviceRGB(d->page, r, g, b);
  pdfioContentSetStrokeColorDeviceRGB(d->page, r, g, b);
  return PAXO_ZERO;
}

// Rectángulo relleno: pdf_write_rect(doc, x, y, w, h)
static PaxoVar native_pdf_write_rect(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 5 ? pdf_from_args(args[0]) : NULL;
  if (!d || !d->page)
    return PAXO_ZERO;
  pdfioContentPathRect(d->page, native_arg_double(args[1]),
                       native_arg_double(args[2]), native_arg_double(args[3]),
                       native_arg_double(args[4]));
  pdfioContentFill(d->page, false);
  return PAXO_ZERO;
}

// Línea: pdf_write_line(doc, x1, y1, x2, y2)
static PaxoVar native_pdf_write_line(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 5 ? pdf_from_args(args[0]) : NULL;
  if (!d || !d->page)
    return PAXO_ZERO;
  pdfioContentPathMoveTo(d->page, native_arg_double(args[1]),
                         native_arg_double(args[2]));
  pdfioContentPathLineTo(d->page, native_arg_double(args[3]),
                         native_arg_double(args[4]));
  pdfioContentStroke(d->page);
  return PAXO_ZERO;
}

// Escribe texto: pdf_write_text(doc, x, y, tamano, texto)
static PaxoVar native_pdf_write_text(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 5 ? pdf_from_args(args[0]) : NULL;
  const char *s = argc >= 5 ? native_arg_str(args[4]) : NULL;
  if (!d || !d->page || !s)
    return PAXO_ZERO;
  pdfioContentSetTextFont(d->page, d->names[d->curfont],
                          native_arg_double(args[3]));
  pdfioContentTextMoveTo(d->page, native_arg_double(args[1]),
                         native_arg_double(args[2]));
  pdfioContentTextShow(d->page, false, s);
  return PAXO_ZERO;
}

// Cierra y guarda/libera: pdf_close(doc)
static PaxoVar native_pdf_close(PaxoVar *args, uint8_t argc) {
  if (argc >= 1 && pdf_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    PaxoPdf *d = (PaxoPdf *)reg_get(&pdf_reg, id);
    if (d) {
      if (d->page) {
        pdfioContentTextEnd(d->page);
        pdfioStreamClose(d->page);
      }
      pdfioFileClose(d->file);
      free(d);
      reg_del(&pdf_reg, id, false);
    }
  }
  return PAXO_ZERO;
}

#else

static PaxoVar native_pdf_open(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] pdf: soporte no compilado\n", stderr);
  return num_from_i64(0);
}
static PaxoVar native_pdf_new(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_pdf_pages(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_pdf_page_size(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return ret_xy(0, 0);
}
static PaxoVar native_pdf_text(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_string("");
}
static PaxoVar native_pdf_font(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_pdf_page_begin(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_pdf_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_pdf_write_rect(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_pdf_write_line(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_pdf_write_text(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}
static PaxoVar native_pdf_close(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return PAXO_ZERO;
}

#endif // PAXO_HAS_PDF

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
  // Imágenes
  case NATIVE_IMG_LOAD:
    return native_img_load(args, argc);
  case NATIVE_IMG_INFO:
    return native_img_info(args, argc);
  case NATIVE_IMG_SAVE_PNG:
    return native_img_save_png(args, argc);
  case NATIVE_IMG_SAVE_JPG:
    return native_img_save_jpg(args, argc);
  case NATIVE_IMG_SAVE_BMP:
    return native_img_save_bmp(args, argc);
  case NATIVE_IMG_RESIZE:
    return native_img_resize(args, argc);
  // Fuentes
  case NATIVE_FONT_LOAD:
    return native_font_load(args, argc);
  case NATIVE_FONT_GLYPH:
    return native_font_glyph(args, argc);
  case NATIVE_FONT_METRICS:
    return native_font_metrics(args, argc);
  case NATIVE_FONT_FREE:
    return native_font_free(args, argc);
  // Audio
  case NATIVE_AUDIO_INIT:
    return native_audio_init(args, argc);
  case NATIVE_AUDIO_QUIT:
    return native_audio_quit(args, argc);
  case NATIVE_AUDIO_PLAY:
    return native_audio_play(args, argc);
  case NATIVE_AUDIO_PAUSE:
    return native_audio_pause(args, argc);
  case NATIVE_AUDIO_RESUME:
    return native_audio_resume(args, argc);
  case NATIVE_AUDIO_STOP:
    return native_audio_stop(args, argc);
  case NATIVE_AUDIO_VOLUME:
    return native_audio_volume(args, argc);
  case NATIVE_AUDIO_PLAYING:
    return native_audio_playing(args, argc);
  // Física
  case NATIVE_PHYS_SPACE:
    return native_phys_space(args, argc);
  case NATIVE_PHYS_GRAVITY:
    return native_phys_gravity(args, argc);
  case NATIVE_PHYS_STEP:
    return native_phys_step(args, argc);
  case NATIVE_PHYS_BODY:
    return native_phys_body(args, argc);
  case NATIVE_PHYS_BODY_STATIC:
    return native_phys_body_static(args, argc);
  case NATIVE_PHYS_POS:
    return native_phys_pos(args, argc);
  case NATIVE_PHYS_VEL:
    return native_phys_vel(args, argc);
  case NATIVE_PHYS_SET_POS:
    return native_phys_set_pos(args, argc);
  case NATIVE_PHYS_SET_VEL:
    return native_phys_set_vel(args, argc);
  case NATIVE_PHYS_ANGLE:
    return native_phys_angle(args, argc);
  case NATIVE_PHYS_SET_ANGLE:
    return native_phys_set_angle(args, argc);
  case NATIVE_PHYS_FORCE:
    return native_phys_force(args, argc);
  case NATIVE_PHYS_IMPULSE:
    return native_phys_impulse(args, argc);
  case NATIVE_PHYS_CIRCLE:
    return native_phys_circle(args, argc);
  case NATIVE_PHYS_BOX:
    return native_phys_box(args, argc);
  case NATIVE_PHYS_SEGMENT:
    return native_phys_segment(args, argc);
  case NATIVE_PHYS_ELASTICITY:
    return native_phys_elasticity(args, argc);
  case NATIVE_PHYS_FRICTION:
    return native_phys_friction(args, argc);
  case NATIVE_PHYS_COLLIDE:
    return native_phys_collide(args, argc);
  case NATIVE_PHYS_FREE_SHAPE:
    return native_phys_free_shape(args, argc);
  case NATIVE_PHYS_FREE_BODY:
    return native_phys_free_body(args, argc);
  case NATIVE_PHYS_FREE_SPACE:
    return native_phys_free_space(args, argc);
  // Ventana/gráficos
  case NATIVE_WIN_OPEN:
    return native_win_open(args, argc);
  case NATIVE_WIN_CLOSE:
    return native_win_close(args, argc);
  case NATIVE_WIN_COLOR:
    return native_win_color(args, argc);
  case NATIVE_WIN_CLEAR:
    return native_win_clear(args, argc);
  case NATIVE_WIN_RECT:
    return native_win_rect(args, argc);
  case NATIVE_WIN_LINE:
    return native_win_line(args, argc);
  case NATIVE_WIN_CIRCLE:
    return native_win_circle(args, argc);
  case NATIVE_WIN_TEXT:
    return native_win_text(args, argc);
  case NATIVE_TEX_LOAD:
    return native_tex_load(args, argc);
  case NATIVE_TEX_DRAW:
    return native_tex_draw(args, argc);
  case NATIVE_TEX_FREE:
    return native_tex_free(args, argc);
  case NATIVE_WIN_SHOW:
    return native_win_show(args, argc);
  case NATIVE_WIN_POLL:
    return native_win_poll(args, argc);
  case NATIVE_WIN_KEY:
    return native_win_key(args, argc);
  case NATIVE_WIN_MOUSE:
    return native_win_mouse(args, argc);
  case NATIVE_WIN_MOUSEDOWN:
    return native_win_mousedown(args, argc);
  case NATIVE_WIN_TIME:
    return native_win_time(args, argc);
  case NATIVE_WIN_DELAY:
    return native_win_delay(args, argc);
  // PDF
  case NATIVE_PDF_OPEN:
    return native_pdf_open(args, argc);
  case NATIVE_PDF_NEW:
    return native_pdf_new(args, argc);
  case NATIVE_PDF_PAGES:
    return native_pdf_pages(args, argc);
  case NATIVE_PDF_PAGE_SIZE:
    return native_pdf_page_size(args, argc);
  case NATIVE_PDF_TEXT:
    return native_pdf_text(args, argc);
  case NATIVE_PDF_FONT:
    return native_pdf_font(args, argc);
  case NATIVE_PDF_PAGE_BEGIN:
    return native_pdf_page_begin(args, argc);
  case NATIVE_PDF_COLOR:
    return native_pdf_color(args, argc);
  case NATIVE_PDF_WRITE_RECT:
    return native_pdf_write_rect(args, argc);
  case NATIVE_PDF_WRITE_LINE:
    return native_pdf_write_line(args, argc);
  case NATIVE_PDF_WRITE_TEXT:
    return native_pdf_write_text(args, argc);
  case NATIVE_PDF_CLOSE:
    return native_pdf_close(args, argc);
  default:
    break;
  }
  return PAXO_NO_VALUE;
}
