#pragma once
#include "Calc.c"
#include "Typecast_and_read.c"

// ==========================================
// Librerías vendidas junto a la VM.
// Las de cabecera única (stb_* y miniaudio) se implementan aquí mismo y
// siempre están disponibles en el build normal. Chipmunk2D y pdfio se
// compilan desde third_party/. La ventana gráfica requiere SDL3 instalada
// en el sistema y se activa definiendo LEP_ENABLE_SDL3.
// En lep.h (single-header) los #include "..." se eliminan, por lo que las
// guardas __has_include desactivan los nativos correspondientes solos.
// ==========================================

// --- Imágenes (stb_image / write / resize2) ---
#if __has_include("stb_image.h") && !defined(LEP_NO_STB)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE2_IMPLEMENTATION
#include "stb_image_resize2.h"
#define LEP_HAS_IMG 1
#endif

// --- Fuentes (stb_truetype) ---
#if __has_include("stb_truetype.h") && !defined(LEP_NO_STB)
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_easy_font.h"
#include "stb_truetype.h"
#define LEP_HAS_FONT 1
#endif

#if __has_include("stb_ds.h")
#include "stb_ds.h"
#endif

// --- Audio (miniaudio) ---
#if __has_include("miniaudio.h") && !defined(LEP_NO_MINIAUDIO)
#define MA_IMPLEMENTATION
#include "miniaudio.h"
#define LEP_HAS_AUDIO 1
#endif

// --- Física (Chipmunk2D 7, fuentes en third_party/chipmunk) ---
#if __has_include("third_party/chipmunk/chipmunk/chipmunk.h")
#include "third_party/chipmunk/chipmunk/chipmunk.h"
#define LEP_HAS_PHYS 1
#endif

// --- PDF (pdfio + zlib, fuentes en third_party/pdfio) ---
#if __has_include("third_party/pdfio/pdfio.h")
#include "third_party/pdfio/pdfio-content.h"
#include "third_party/pdfio/pdfio.h"
#define LEP_HAS_PDF 1
#endif

// Gráficos (sokol + NanoVG, opcional: LEP_ENABLE_NVG). Se activa solo si se
// compila con -DLEP_ENABLE_NVG y los headers sokol/nanovg están disponibles.
// Las implementaciones de sokol (app/gfx/time) y del backend GL3 de NanoVG
// se compilan aquí mismo en la TU de la VM; SOKOL_NO_ENTRY evita que sokol
// capture main() (la VM define su propio main en Main.c). Sin la bandera, los
// nativos quedan como fallback inofensivo.
#if (defined(LEP_ENABLE_NVG) && __has_include("sokol_app.h") && \
     __has_include("nanovg.h")) || \
    (defined(LEP_EMBEDDED_LIBS) && defined(LEP_ENABLE_NVG))
#define SOKOL_GLCORE
#define SOKOL_NO_ENTRY
#define SOKOL_APP_IMPL
#define SOKOL_GFX_IMPL
#define SOKOL_TIME_IMPL
#define NANOVG_GL3_IMPLEMENTATION
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_time.h"
#include "gl3_compat.h"
#include "nanovg.h"     // NVGcontext y API de dibujo
#include "nanovg_gl.h"  // backend GL3 de NanoVG
#define LEP_HAS_NVG 1
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
  NATIVE_PRINT,
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
  // Ventana/gráficos. Los IDs DEBEN coincidir con los que emite el
  // compilador (abytec.go): win_*/tex_* = 58..75, pdf_* = 76..87.
  NATIVE_WIN_OPEN = 58,       // -> sokol_init
  NATIVE_WIN_CLOSE = 59,      // -> sokol_shutdown
  NATIVE_WIN_COLOR = 60,      // -> sokol_color
  NATIVE_WIN_CLEAR = 61,      // -> sokol_clear
  NATIVE_WIN_RECT = 62,       // -> nvg_rect
  NATIVE_WIN_LINE = 63,       // -> nvg_line
  NATIVE_WIN_CIRCLE = 64,     // -> nvg_circle
  NATIVE_WIN_TEXT = 65,       // -> nvg_text
  NATIVE_TEX_LOAD = 66,       // -> tex_load (textura desde píxeles)
  NATIVE_TEX_DRAW = 67,       // -> tex_draw
  NATIVE_TEX_FREE = 68,       // -> tex_free
  NATIVE_WIN_SHOW = 69,       // -> sokol_show (bucle de eventos)
  NATIVE_WIN_POLL = 70,       // -> sokol_poll
  NATIVE_WIN_KEY = 71,        // -> sokol_key
  NATIVE_WIN_MOUSE = 72,      // -> sokol_mouse
  NATIVE_WIN_MOUSEDOWN = 73,  // -> sokol_mousedown
  NATIVE_WIN_TIME = 74,       // -> sokol_time
  NATIVE_WIN_DELAY = 75,      // -> sokol_delay
  // PDF (pdfio)
  NATIVE_PDF_OPEN = 76,
  NATIVE_PDF_NEW = 77,
  NATIVE_PDF_PAGES = 78,
  NATIVE_PDF_PAGE_SIZE = 79,
  NATIVE_PDF_TEXT = 80,
  NATIVE_PDF_FONT = 81,
  NATIVE_PDF_PAGE_BEGIN = 82,
  NATIVE_PDF_COLOR = 83,
  NATIVE_PDF_WRITE_RECT = 84,
  NATIVE_PDF_WRITE_LINE = 85,
  NATIVE_PDF_WRITE_TEXT = 86,
  NATIVE_PDF_CLOSE = 87,
  // Nativos adicionales de sokol/NanoVG (no emitidos por el compilador).
  NATIVE_SOKOL_INIT = 88,
  NATIVE_SOKOL_SHUTDOWN = 89,
  NATIVE_SOKOL_CLEAR = 90,
  NATIVE_SOKOL_COLOR = 91,
  NATIVE_SOKOL_SHOW = 92,
  NATIVE_SOKOL_POLL = 93,
  NATIVE_SOKOL_KEY = 94,
  NATIVE_SOKOL_MOUSE = 95,
  NATIVE_SOKOL_MOUSEDOWN = 96,
  NATIVE_SOKOL_TIME = 97,
  NATIVE_SOKOL_DELAY = 98,
  NATIVE_NVG_CREATE = 99,
  NATIVE_NVG_CANCEL_FRAME = 100,
  NATIVE_NVG_BEGIN_FRAME = 101,
  NATIVE_NVG_END_FRAME = 102,
  NATIVE_NVG_RECT = 103,
  NATIVE_NVG_LINE = 104,
  NATIVE_NVG_CIRCLE = 105,
  NATIVE_NVG_TEXT = 106,
  NATIVE_NVG_FILL_COLOR = 107,
  NATIVE_NVG_STROKE_COLOR = 108,
  NATIVE_NVG_STROKE_WIDTH = 109,
  NATIVE_NVG_FILL = 110,
  NATIVE_NVG_STROKE = 111,
  NATIVE_ID_COUNT
} NativeId;

// ==========================================
// Funciones nativas
// ==========================================

static void print_intfp(PaxoFxp f) { printf("%s", (const char *)readint(f)); }

static void print_pkdec(PaxoPdec d) { printf("%s", (const char *)readpdec(d)); }

static void print_var_inline(PaxoVar elem) {
  switch (var_type(elem)) {
  case NUM16:
    printf("%s", (const char *)readnum16(var_num16_get(elem), 1));
    break;
  case NUM64:
    printf("%s", (const char *)readnum64(var_num64_get(elem), 1));
    break;
  case VBOOL:
    printf("%s", var_bool_get(elem) ? "true" : "false");
    break;
  case TRIT:
    printf("%s", (const char *)readtrit(var_trit_get(elem)));
    break;
  case CHAR:
    printf("'%s'", (const char *)readchar32(var_char_get(elem)));
    break;
  case INT_FP:
    print_intfp(var_fxp_get(elem));
    break;
  case PKDEC:
    print_pkdec(var_pkdec_get(elem));
    break;
  case COLOR:
    printf("#%08X", var_color_get(elem));
    break;
  case COMPLEX:
  case COMPLEX16:
    printf("%s", (const char *)readcomplex(var_complex_get(elem)));
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
    return LEP_ZERO;

  for (uint8_t i = 0; i < argc; i++) {
    PaxoVar val = args[i];

    switch (var_type(val)) {
    case NUM16:
      printf("%s", (const char *)readnum16(var_num16_get(val), 1));
      break;
    case NUM64:
      printf("%s", (const char *)readnum64(var_num64_get(val), 1));
      break;
    case VBOOL:
      printf("%s", var_bool_get(val) ? "true" : "false");
      break;
    case TRIT:
      printf("%s", (const char *)readtrit(var_trit_get(val)));
      break;
    case CHAR:
      printf("%s", (const char *)readchar32(var_char_get(val)));
      break;
    case INT_FP:
      print_intfp(var_fxp_get(val));
      break;
    case PKDEC:
      print_pkdec(var_pkdec_get(val));
      break;
    case COLOR:
      printf("#%08X", var_color_get(val));
      break;
    case COMPLEX:
    case COMPLEX16:
      printf("%s", (const char *)readcomplex(var_complex_get(val)));
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

  return LEP_ZERO;
}

static PaxoVar native_println(PaxoVar *args, uint8_t argc) {
  native_print(args, argc);
  putchar('\n');
  return LEP_ZERO;
}

static PaxoVar native_typeof(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return LEP_ZERO;
  const char *type_name = "unknown";
  switch (var_type(args[0])) {
  case NUM16:
    type_name = "num16";
    break;
  case NUM64:
    type_name = "num64";
    break;
  case VBOOL:
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
  case INT_FP:
    type_name = "int";
    break;
  case PKDEC:
    type_name = "pdec";
    break;
  case COLOR:
    type_name = "col";
    break;
  case COMPLEX:
    type_name = "ni";
    break;
  case COMPLEX16:
    type_name = "sni";
    break;
  }

  return var_string(type_name);
}

static PaxoVar native_set_text_color(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) {
    return LEP_ZERO;
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
  return LEP_ZERO;
}

static PaxoVar native_reset_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  reset_colors(stdout);
  return LEP_ZERO;
}

static PaxoVar native_set_bg_color(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) {
    return LEP_ZERO;
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
  return LEP_ZERO;
}

static PaxoVar native_scan(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  static char buf[65536];
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
    return LEP_ZERO;
  size_t len = var_array_get(args[0])->len;
  Num64 result = {0};
  result.exp = BIAS64;
  result.bc = (uint64_t)len;
  return var_num64(result);
}

static PaxoVar native_array_push(PaxoVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != ARRAY)
    return LEP_ZERO;
  PaxoArray *arr = var_array_get(args[0]);
  if (arr->len >= arr->capacity) {
    arr->capacity *= 2;
    arr->items = realloc(arr->items, sizeof(PaxoVar) * arr->capacity);
  }
  arr->items[arr->len++] = args[1];
  return LEP_ZERO;
}

static PaxoVar native_set_text_type(PaxoVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) {
    return LEP_ZERO;
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
  return LEP_ZERO;
}

// ==========================================
// Gráficos básicos (terminal ANSI)
// ==========================================

static long gfx_width = 80;
static long gfx_height = 24;

// Convierte un PaxoVar numérico a entero largo (coordenadas, tamaños)
static inline long native_arg_long(PaxoVar v) {
  enum type t = var_type(v);
  if (t == INT_FP)
    v = var_num64(fxp_to_num64(var_fxp_get(v)));
  else if (t == PKDEC)
    v = var_num64(pdec_to_num64(var_pkdec_get(v)));
  t = var_type(v);
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

// Convierte un PaxoVar numérico a doble (MP16/MP64/int/pdec)
static inline double native_arg_double(PaxoVar v) {
  enum type t = var_type(v);
  if (t == INT_FP)
    v = var_num64(fxp_to_num64(var_fxp_get(v)));
  else if (t == PKDEC)
    v = var_num64(pdec_to_num64(var_pkdec_get(v)));
  t = var_type(v);
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
  return LEP_ZERO;
}

// Dibuja un rectángulo relleno con '█': draw_rect(x, y, ancho, alto)
// Coordenadas 0-based desde la esquina superior izquierda; se recorta
// al lienzo de init_window. Usa el color de texto actual.
static PaxoVar native_draw_rect(PaxoVar *args, uint8_t argc) {
  if (argc < 4)
    return LEP_ZERO;
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
    return LEP_ZERO;

  for (long row = 0; row < h; row++) {
    printf("\033[%ld;%ldH", y + row + 1, x + 1);
    for (long col = 0; col < w; col++)
      fputs("█", stdout);
  }
  fflush(stdout);
  return LEP_ZERO;
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

#ifdef LEP_HAS_IMG

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

#endif // LEP_HAS_IMG

// ==========================================
// Fuentes (stb_truetype)
// ==========================================

#ifdef LEP_HAS_FONT

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
  return LEP_ZERO;
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
  return LEP_ZERO;
}

#endif // LEP_HAS_FONT

// ==========================================
// Audio (miniaudio, motor global + sonidos por handle)
// ==========================================

#ifdef LEP_HAS_AUDIO

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
    return LEP_ZERO;
  for (size_t i = 0; i < snd_reg.len; i++) {
    if (snd_reg.ptr[i])
      snd_freer(snd_reg.ptr[i]);
    snd_reg.ptr[i] = NULL;
  }
  ma_engine_uninit(&audio_engine);
  audio_up = false;
  return LEP_ZERO;
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
  float vol = (float)native_arg_double(argc >= 2 ? args[1] : LEP_ZERO);
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
  return LEP_ZERO;
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

#endif // LEP_HAS_AUDIO

// ==========================================
// Física 2D (Chipmunk2D)
// Espacios, cuerpos y formas referenciados por handles numéricos.
// ==========================================

#ifdef LEP_HAS_PHYS

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
                          native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)));
  return LEP_ZERO;
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
  return LEP_ZERO;
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
                          native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)));
  return LEP_ZERO;
}

// Fija velocidad: phys_set_vel(body, vx, vy)
static PaxoVar native_phys_set_vel(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodySetVelocity(r->body,
                      cpv(native_arg_double(args[1]),
                          native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)));
  return LEP_ZERO;
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
  return LEP_ZERO;
}

// Acumula fuerza este paso: phys_force(body, fx, fy)
static PaxoVar native_phys_force(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodyApplyForceAtLocalPoint(
        r->body,
        cpv(native_arg_double(args[1]),
            native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)),
        cpvzero);
  return LEP_ZERO;
}

// Impulso instantáneo: phys_impulse(body, ix, iy)
static PaxoVar native_phys_impulse(PaxoVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r)
    cpBodyApplyImpulseAtLocalPoint(
        r->body,
        cpv(native_arg_double(args[1]),
            native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)),
        cpvzero);
  return LEP_ZERO;
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
  return LEP_ZERO;
}

// Rozamiento: phys_friction(shape, f)
static PaxoVar native_phys_friction(PaxoVar *args, uint8_t argc) {
  PhysShapeRec *r = argc >= 1 ? shape_from_args(args[0]) : NULL;
  if (r)
    cpShapeSetFriction(r->shape, native_arg_double(args[1]));
  return LEP_ZERO;
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
  return LEP_ZERO;
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
  return LEP_ZERO;
}

// Libera espacio con todo su contenido: phys_free_space(space)
static PaxoVar native_phys_free_space(PaxoVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp)
    return LEP_ZERO;
  int64_t sid = (int64_t)native_arg_long(args[0]);
  reg_free_owned(&shape_reg, sp, ps_freer);
  reg_free_owned(&body_reg, sp, pb_freer);
  cpSpaceFree(sp);
  reg_del(&space_reg, sid, false);
  return LEP_ZERO;
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
  return LEP_ZERO;
}
static PaxoVar native_phys_step(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
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
  return LEP_ZERO;
}
static PaxoVar native_phys_set_vel(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_angle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_set_angle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_force(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_impulse(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
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
  return LEP_ZERO;
}
static PaxoVar native_phys_friction(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_collide(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_phys_free_shape(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_free_body(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_phys_free_space(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

#endif // LEP_HAS_PHYS

// ==========================================
// Ventana y gráficos (sokol + NanoVG, opcional: LEP_ENABLE_NVG)
// Los nativos sokol_* y nvg_* dibujan con NanoVG sobre un contexto GL.
// Sin LEP_ENABLE_NVG se activa el fallback que devuelve valores inofensivos.
// ==========================================

#ifdef LEP_HAS_NVG

// =====================================================================
// Estado de ventana (sokol) y cola de eventos
// =====================================================================
static NVGcontext *g_nvg = NULL;
static int g_nvg_w = 800, g_nvg_h = 600;
static float g_nvg_scale = 1.0f;
static int g_sok_master = 0; // 1 mientras sapp_run esté en curso

#define LEP_EVQ_CAP 256
static char g_evq[LEP_EVQ_CAP][64];
static int g_evq_head = 0, g_evq_tail = 0, g_evq_n = 0;

// Color de limpieza de pantalla (0..255)
static unsigned char g_cc_r = 0, g_cc_g = 0, g_cc_b = 0, g_cc_a = 255;

// Color de pincel NanoVG actual (canal 0..1); usado para relleno/trazo/texto
static float g_fill_r = 1, g_fill_g = 1, g_fill_b = 1, g_fill_a = 1;

// Estado de entrada, completado desde event_cb
static int g_sok_key_state[512];
static float g_sok_mouse_x = 0, g_sok_mouse_y = 0;
static int g_sok_mouse_down = 0;

static void evq_push(const char *s) {
  if (g_evq_n >= LEP_EVQ_CAP)
    return;
  strncpy(g_evq[g_evq_tail], s, 63);
  g_evq[g_evq_tail][63] = '\0';
  g_evq_tail = (g_evq_tail + 1) % LEP_EVQ_CAP;
  g_evq_n++;
}

// =====================================================================
// Cola de comandos de dibujo: se graba SIN contexto GL y se reproduce
// dentro de frame_cb de sokol (donde sí hay contexto GL activo).
// =====================================================================
typedef enum {
  LG_FILLCOLOR, LG_STROKECOLOR, LG_STROKEW,
  LG_RECT, LG_LINE, LG_CIRCLE, LG_TEXT, LG_IMAGE
} lg_cmd_kind;

typedef struct {
  lg_cmd_kind k;
  float a, b, c, d;
  float r, g, bb, aa; // color
  char *text;
  int tex;            // textura (LG_IMAGE)
} lg_cmd;

#define LEP_MAX_TEX 32
typedef struct {
  int used;              // slot ocupado
  int built;             // textura ya subida a GL (img válido)
  int img;               // NVG image handle
  int w, h, ch;
  unsigned char *px;     // copia de los píxeles (RGBA o RGB)
} LEPTex;
static LEPTex g_tex[LEP_MAX_TEX] = {{0}};

static lg_cmd *g_cmds = NULL;
static size_t g_cmd_n = 0, g_cmd_cap = 0;

static void lg_push(lg_cmd_kind k, float a, float b, float c, float d,
                    const char *txt) {
  if (g_cmd_n == g_cmd_cap) {
    g_cmd_cap = g_cmd_cap ? g_cmd_cap * 2 : 64;
    g_cmds = (lg_cmd *)realloc(g_cmds, g_cmd_cap * sizeof(lg_cmd));
    if (!g_cmds)
      return;
  }
  lg_cmd *cmd = &g_cmds[g_cmd_n++];
  cmd->k = k;
  cmd->a = a; cmd->b = b; cmd->c = c; cmd->d = d;
  cmd->r = g_fill_r; cmd->g = g_fill_g; cmd->bb = g_fill_b; cmd->aa = g_fill_a;
  cmd->text = NULL;
  cmd->tex = 0;
  if (txt) {
    size_t len = strlen(txt);
    cmd->text = (char *)malloc(len + 1);
    if (cmd->text)
      memcpy(cmd->text, txt, len + 1);
  }
}
static void lg_reset(void) {
  size_t i;
  for (i = 0; i < g_cmd_n; i++)
    free(g_cmds[i].text);
  g_cmd_n = 0;
}

// Sube a la GPU las texturas pendientes (solo se puede crear la imagen
// NVG con contexto GL activo, es decir dentro del bucle de sokol).
static void lep_tex_build_all(void) {
  int i;
  if (!g_nvg)
    return;
  for (i = 0; i < LEP_MAX_TEX; i++) {
    LEPTex *t = &g_tex[i];
    if (!t->used || t->built)
      continue;
    t->img = nvgCreateImageRGBA(g_nvg, t->w, t->h, 0, t->px);
    t->built = (t->img != 0);
  }
}

// =====================================================================
// Callbacks de sokol (ventana, eventos y frame)
// =====================================================================
static void lep_sapp_init(void) {
  // Crea el contexto de dibujo de NanoVG sobre el contexto GL de sokol.
  // on the rendering (frame) thread.
  if (!g_nvg)
    g_nvg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
  lep_tex_build_all();
}

static void lep_sapp_frame(void) {
  size_t i;
  if (!g_nvg)
    return;
  lep_tex_build_all();
  glViewport(0, 0, g_nvg_w, g_nvg_h);
  glClearColor((float)g_cc_r / 255.f, (float)g_cc_g / 255.f,
               (float)g_cc_b / 255.f, (float)g_cc_a / 255.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  nvgBeginFrame(g_nvg, (float)g_nvg_w, (float)g_nvg_h, g_nvg_scale);
  for (i = 0; i < g_cmd_n; i++) {
    lg_cmd *c = &g_cmds[i];
    switch (c->k) {
    case LG_FILLCOLOR:
      nvgFillColor(g_nvg, nvgRGBAf(c->r, c->g, c->bb, c->aa));
      break;
    case LG_STROKECOLOR:
      nvgStrokeColor(g_nvg, nvgRGBAf(c->r, c->g, c->bb, c->aa));
      break;
    case LG_STROKEW:
      nvgStrokeWidth(g_nvg, c->a);
      break;
    case LG_RECT:
      nvgBeginPath(g_nvg);
      nvgRect(g_nvg, c->a, c->b, c->c, c->d);
      nvgFill(g_nvg);
      break;
    case LG_LINE:
      nvgBeginPath(g_nvg);
      nvgMoveTo(g_nvg, c->a, c->b);
      nvgLineTo(g_nvg, c->c, c->d);
      nvgStroke(g_nvg);
      break;
    case LG_CIRCLE:
      nvgBeginPath(g_nvg);
      nvgCircle(g_nvg, c->a, c->b, c->c);
      nvgFill(g_nvg);
      break;
    case LG_TEXT:
      if (c->text) {
        nvgFillColor(g_nvg, nvgRGBAf(c->r, c->g, c->bb, c->aa));
        nvgFontSize(g_nvg, c->d > 0 ? c->d : 16.0f);
        nvgFontFace(g_nvg, "sans");
        nvgTextAlign(g_nvg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
        nvgText(g_nvg, c->a, c->b, c->text, NULL);
      }
      break;
    case LG_IMAGE: {
      int idx = c->tex - 1;
      if (idx >= 0 && idx < LEP_MAX_TEX && g_tex[idx].used && g_tex[idx].built) {
        NVGpaint img =
            nvgImagePattern(g_nvg, c->a, c->b, c->c, c->d, 0.0f, g_tex[idx].img, 1.0f);
        nvgBeginPath(g_nvg);
        nvgRect(g_nvg, c->a, c->b, c->c, c->d);
        nvgFillPaint(g_nvg, img);
        nvgFill(g_nvg);
      }
      break;
    }
    default:
      break;
    }
  }
  nvgEndFrame(g_nvg);
}

static void lep_sapp_event(const sapp_event *ev) {
  char buf[64];
  switch (ev->type) {
  case SAPP_EVENTTYPE_KEY_DOWN:
    if (ev->key_code >= 0 && ev->key_code < 512)
      g_sok_key_state[ev->key_code] = 1;
    if (!ev->key_repeat) {
      snprintf(buf, sizeof(buf), "keydown:%d", (int)ev->key_code);
      evq_push(buf);
    }
    break;
  case SAPP_EVENTTYPE_KEY_UP:
    if (ev->key_code >= 0 && ev->key_code < 512)
      g_sok_key_state[ev->key_code] = 0;
    snprintf(buf, sizeof(buf), "keyup:%d", (int)ev->key_code);
    evq_push(buf);
    break;
  case SAPP_EVENTTYPE_MOUSE_DOWN:
    g_sok_mouse_down = 1;
    evq_push("mousedown");
    break;
  case SAPP_EVENTTYPE_MOUSE_UP:
    g_sok_mouse_down = 0;
    evq_push("mouseup");
    break;
  case SAPP_EVENTTYPE_MOUSE_MOVE:
    g_sok_mouse_x = ev->mouse_x;
    g_sok_mouse_y = ev->mouse_y;
    break;
  case SAPP_EVENTTYPE_QUIT_REQUESTED:
    evq_push("quit");
    break;
  default:
    break;
  }
}

static void lep_sapp_cleanup(void) {
  int i;
  for (i = 0; i < LEP_MAX_TEX; i++) {
    LEPTex *t = &g_tex[i];
    if (t->used && t->built && g_nvg)
      nvgDeleteImage(g_nvg, t->img);
    free(t->px);
    memset(t, 0, sizeof(*t));
  }
  if (g_nvg) {
    nvgDeleteGL3(g_nvg);
    g_nvg = NULL;
  }
}

// =====================================================================
// Nativos: sokol (ventana / utilidades)
// =====================================================================
// sokol_init(titulo, ancho, alto) -> bool (prepara; la ventana se abre
// al llamar sokol_show, ya que sokol exige su propio bucle de eventos).
static PaxoVar native_sokol_init(PaxoVar *args, uint8_t argc) {
  long w = argc >= 2 ? native_arg_long(args[1]) : 800;
  long h = argc >= 3 ? native_arg_long(args[2]) : 600;
  if (w <= 0)
    w = 800;
  if (h <= 0)
    h = 600;
  g_nvg_w = (int)w;
  g_nvg_h = (int)h;
  g_nvg_scale = 1.0f;
  stm_setup();
  return var_bool(true);
}

// sokol_shutdown() -> bool (fuerza fin del bucle en curso)
static PaxoVar native_sokol_shutdown(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (g_sok_master)
    sapp_request_quit();
  lg_reset();
  return var_bool(true);
}

// sokol_color(r, g, b[, a]) -> LEP_ZERO (color de limpieza, 0..255)
static PaxoVar native_sokol_color(PaxoVar *args, uint8_t argc) {
  if (argc < 3)
    return LEP_ZERO;
  long r = native_arg_long(args[0]), g = native_arg_long(args[1]),
       b = native_arg_long(args[2]);
  long a = argc >= 4 ? native_arg_long(args[3]) : 255;
  g_cc_r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
  g_cc_g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
  g_cc_b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
  g_cc_a = (unsigned char)(a < 0 ? 0 : (a > 255 ? 255 : a));
  return LEP_ZERO;
}

// sokol_clear() -> LEP_ZERO (marca limpieza; se aplica cada frame)
static PaxoVar native_sokol_clear(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

// sokol_show() -> bool (abre la ventana y corre el bucle de eventos hasta
// que se cierra; dibuja la escena grabada con los nativos nvg_*).
static PaxoVar native_sokol_show(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  if (g_sok_master)
    return var_bool(true);
  sapp_desc desc = {0};
  desc.width = g_nvg_w;
  desc.height = g_nvg_h;
  desc.sample_count = 4;
  desc.init_cb = lep_sapp_init;
  desc.frame_cb = lep_sapp_frame;
  desc.event_cb = lep_sapp_event;
  desc.cleanup_cb = lep_sapp_cleanup;
  desc.window_title = "Lepvm";
  desc.user_data = NULL;
  g_sok_master = 1;
  sapp_run(&desc);
  g_sok_master = 0;
  lg_reset();
  return var_bool(true);
}

// sokol_poll() -> array de strings con eventos colgantes
static PaxoVar native_sokol_poll(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  PaxoArray *a = arr_new(4);
  while (g_evq_n > 0) {
    arr_push_var(a, var_string(g_evq[g_evq_head]));
    g_evq_head = (g_evq_head + 1) % LEP_EVQ_CAP;
    g_evq_n--;
  }
  return var_array(a);
}

// sokol_key(codigo) -> bool
static PaxoVar native_sokol_key(PaxoVar *args, uint8_t argc) {
  long k = argc >= 1 ? native_arg_long(args[0]) : 0;
  if (k < 0 || k >= 512)
    return var_bool(false);
  return var_bool(g_sok_key_state[(int)k] != 0);
}

// sokol_mouse() -> [x, y]
static PaxoVar native_sokol_mouse(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return ret_xy(g_sok_mouse_x, g_sok_mouse_y);
}

// sokol_mousedown() -> bool
static PaxoVar native_sokol_mousedown(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(g_sok_mouse_down != 0);
}

// sokol_time() -> num (milisegundos desde sokol_init)
static PaxoVar native_sokol_time(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  uint64_t now = stm_now();
  return num_from_i64((int64_t)stm_ms(now));
}

// sokol_delay(ms) -> LEP_ZERO
static PaxoVar native_sokol_delay(PaxoVar *args, uint8_t argc) {
  long ms = argc >= 1 ? native_arg_long(args[0]) : 0;
  if (ms > 0)
    usleep((useconds_t)(ms * 1000));
  return LEP_ZERO;
}

// =====================================================================
// Nativos: NanoVG (dibujo). Graban comandos reproducidos en cada frame.
// =====================================================================
// nvg_create() -> bool (ameniza la API; sin operación aquí)
static PaxoVar native_nvg_create(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(true);
}

// nvg_fill_color([r,g,b,a] o COLOR 0..255) -> LEP_ZERO
static PaxoVar native_nvg_fill_color(PaxoVar *args, uint8_t argc) {
  float r = 1, g = 1, b = 1, a = 1;
  if (argc >= 1 && var_type(args[0]) == COLOR) {
    uint32_t rgba = var_color_get(args[0]);
    r = (float)((rgba >> 24) & 0xFF) / 255.f;
    g = (float)((rgba >> 16) & 0xFF) / 255.f;
    b = (float)((rgba >> 8) & 0xFF) / 255.f;
    a = (float)(rgba & 0xFF) / 255.f;
  } else if (argc >= 3) {
    r = ((float)native_arg_long(args[0])) / 255.f;
    g = ((float)native_arg_long(args[1])) / 255.f;
    b = ((float)native_arg_long(args[2])) / 255.f;
    a = argc >= 4 ? ((float)native_arg_long(args[3])) / 255.f : 1.f;
  }
  g_fill_r = r; g_fill_g = g; g_fill_b = b; g_fill_a = a;
  if (g_sok_master)
    lg_push(LG_FILLCOLOR, 0, 0, 0, 0, NULL);
  return LEP_ZERO;
}

// nvg_stroke_color([r,g,b,a] o COLOR) -> LEP_ZERO
static PaxoVar native_nvg_stroke_color(PaxoVar *args, uint8_t argc) {
  float r = 1, g = 1, b = 1, a = 1;
  if (argc >= 1 && var_type(args[0]) == COLOR) {
    uint32_t rgba = var_color_get(args[0]);
    r = (float)((rgba >> 24) & 0xFF) / 255.f;
    g = (float)((rgba >> 16) & 0xFF) / 255.f;
    b = (float)((rgba >> 8) & 0xFF) / 255.f;
    a = (float)(rgba & 0xFF) / 255.f;
  } else if (argc >= 3) {
    r = ((float)native_arg_long(args[0])) / 255.f;
    g = ((float)native_arg_long(args[1])) / 255.f;
    b = ((float)native_arg_long(args[2])) / 255.f;
    a = argc >= 4 ? ((float)native_arg_long(args[3])) / 255.f : 1.f;
  }
  g_fill_r = r; g_fill_g = g; g_fill_b = b; g_fill_a = a;
  if (g_sok_master)
    lg_push(LG_STROKECOLOR, 0, 0, 0, 0, NULL);
  return LEP_ZERO;
}

// nvg_stroke_width(w) -> LEP_ZERO
static PaxoVar native_nvg_stroke_width(PaxoVar *args, uint8_t argc) {
  float w = argc >= 1 ? (float)native_arg_double(args[0]) : 1.0f;
  lg_push(LG_STROKEW, w, 0, 0, 0, NULL);
  return LEP_ZERO;
}

// nvg_rect(x, y, w, h) -> LEP_ZERO (rectángulo relleno con el color actual)
static PaxoVar native_nvg_rect(PaxoVar *args, uint8_t argc) {
  if (argc < 4)
    return LEP_ZERO;
  float x = (float)native_arg_double(args[0]);
  float y = (float)native_arg_double(args[1]);
  float w = (float)native_arg_double(args[2]);
  float h = (float)native_arg_double(args[3]);
  lg_push(LG_RECT, x, y, w, h, NULL);
  return LEP_ZERO;
}

// nvg_line(x1, y1, x2, y2) -> LEP_ZERO
static PaxoVar native_nvg_line(PaxoVar *args, uint8_t argc) {
  if (argc < 4)
    return LEP_ZERO;
  float x1 = (float)native_arg_double(args[0]);
  float y1 = (float)native_arg_double(args[1]);
  float x2 = (float)native_arg_double(args[2]);
  float y2 = (float)native_arg_double(args[3]);
  lg_push(LG_LINE, x1, y1, x2, y2, NULL);
  return LEP_ZERO;
}

// nvg_circle(cx, cy, r) -> LEP_ZERO (relleno con el color actual)
static PaxoVar native_nvg_circle(PaxoVar *args, uint8_t argc) {
  if (argc < 3)
    return LEP_ZERO;
  float cx = (float)native_arg_double(args[0]);
  float cy = (float)native_arg_double(args[1]);
  float r = (float)native_arg_double(args[2]);
  lg_push(LG_CIRCLE, cx, cy, r, 0, NULL);
  return LEP_ZERO;
}

// nvg_text(x, y, texto[, tamaño]) -> LEP_ZERO
static PaxoVar native_nvg_text(PaxoVar *args, uint8_t argc) {
  if (argc < 3)
    return LEP_ZERO;
  const char *s = native_arg_str(args[2]);
  if (!s)
    return LEP_ZERO;
  float x = (float)native_arg_double(args[0]);
  float y = (float)native_arg_double(args[1]);
  float sz = argc >= 4 ? (float)native_arg_double(args[3]) : 16.0f;
  lg_push(LG_TEXT, x, y, 0, sz, s);
  return LEP_ZERO;
}

// nvg_begin_frame([w, h]) -> bool (no-op en el modelo grabado)
static PaxoVar native_nvg_begin_frame(PaxoVar *args, uint8_t argc) {
  if (argc >= 2) {
    long w = native_arg_long(args[0]), h = native_arg_long(args[1]);
    if (w > 0)
      g_nvg_w = (int)w;
    if (h > 0)
      g_nvg_h = (int)h;
  }
  return var_bool(true);
}

// nvg_end_frame() -> bool
static PaxoVar native_nvg_end_frame(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(true);
}

// nvg_cancel_frame() -> bool
static PaxoVar native_nvg_cancel_frame(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(true);
}

// nvg_fill() -> LEP_ZERO (consolida la ruta; en el modelo grabado no-op)
static PaxoVar native_nvg_fill(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

// nvg_stroke() -> LEP_ZERO (no-op en el modelo grabado; ver nvg_line)
static PaxoVar native_nvg_stroke(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

// =====================================================================
// Nativos: texturas (tex_load / tex_draw / tex_free)
// =====================================================================
// tex_load(píxeles, w, h, ch) -> num (handle) | 0 si falla.
static PaxoVar native_tex_load(PaxoVar *args, uint8_t argc) {
  if (argc < 4)
    return num_from_double(0);
  if (var_type(args[0]) != ARRAY)
    return num_from_double(0);
  long w = native_arg_long(args[1]);
  long h = native_arg_long(args[2]);
  long ch = native_arg_long(args[3]);
  if (w <= 0 || h <= 0)
    return num_from_double(0);
  if (ch != 3 && ch != 4)
    return num_from_double(0);
  PaxoArray *a = var_array_get(args[0]);
  if (a->len < (size_t)(w * h * ch))
    return num_from_double(0);
  int slot = -1;
  for (int i = 0; i < LEP_MAX_TEX; i++) {
    if (!g_tex[i].used) {
      slot = i;
      break;
    }
  }
  if (slot < 0)
    return num_from_double(0);
  size_t npix = (size_t)(w * h * ch);
  unsigned char *px = (unsigned char *)malloc(npix);
  if (!px)
    return num_from_double(0);
  for (size_t i = 0; i < npix; i++) {
    double v = native_arg_double(a->items[i]);
    long b = (long)v;
    px[i] = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
  }
  LEPTex *t = &g_tex[slot];
  memset(t, 0, sizeof(*t));
  t->used = 1;
  t->w = (int)w;
  t->h = (int)h;
  t->ch = (int)ch;
  t->px = px;
  if (g_nvg) {
    t->img = nvgCreateImageRGBA(g_nvg, t->w, t->h, 0, t->px);
    t->built = (t->img != 0);
  }
  return num_from_double((double)(slot + 1));
}

// tex_draw(tex, x, y[, w, h]) -> LEP_ZERO
static PaxoVar native_tex_draw(PaxoVar *args, uint8_t argc) {
  if (argc < 3)
    return LEP_ZERO;
  long handle = native_arg_long(args[0]);
  int idx = (int)handle - 1;
  if (idx < 0 || idx >= LEP_MAX_TEX || !g_tex[idx].used)
    return LEP_ZERO;
  float x = (float)native_arg_double(args[1]);
  float y = (float)native_arg_double(args[2]);
  float w = (float)(argc >= 4 ? native_arg_double(args[3]) : g_tex[idx].w);
  float h = (float)(argc >= 5 ? native_arg_double(args[4]) : g_tex[idx].h);
  lg_push(LG_IMAGE, x, y, w, h, NULL);
  g_cmds[g_cmd_n - 1].tex = (int)handle;
  return LEP_ZERO;
}

// tex_free(tex) -> LEP_ZERO
static PaxoVar native_tex_free(PaxoVar *args, uint8_t argc) {
  if (argc < 1)
    return LEP_ZERO;
  long handle = native_arg_long(args[0]);
  int idx = (int)handle - 1;
  if (idx < 0 || idx >= LEP_MAX_TEX || !g_tex[idx].used)
    return LEP_ZERO;
  LEPTex *t = &g_tex[idx];
  if (t->built && g_nvg)
    nvgDeleteImage(g_nvg, t->img);
  free(t->px);
  memset(t, 0, sizeof(*t));
  return LEP_ZERO;
}

#else // !LEP_HAS_NVG

static PaxoVar native_sokol_init(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] sokol_init: recompila la VM con -DLEP_ENABLE_NVG para usar "
        "gráficos\n",
        stderr);
  return var_bool(false);
}
static PaxoVar native_sokol_shutdown(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_sokol_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_sokol_clear(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_sokol_show(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_sokol_poll(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_array(arr_new(0));
}
static PaxoVar native_sokol_key(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_sokol_mouse(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return ret_xy(0, 0);
}
static PaxoVar native_sokol_mousedown(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_sokol_time(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return num_from_i64(0);
}
static PaxoVar native_sokol_delay(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_create(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_nvg_begin_frame(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_nvg_end_frame(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_nvg_cancel_frame(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return var_bool(false);
}
static PaxoVar native_nvg_rect(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] nvg_rect: recompila la VM con -DLEP_ENABLE_NVG para usar "
        "gráficos\n",
        stderr);
  return LEP_ZERO;
}
static PaxoVar native_nvg_line(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_circle(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_text(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_fill_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_stroke_color(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_stroke_width(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_fill(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_nvg_stroke(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

// Fallbacks de textura sin gráficos
static PaxoVar native_tex_load(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  fputs("[paxo] tex_load: recompila la VM con -DLEP_ENABLE_NVG para usar "
        "texturas\n",
        stderr);
  return num_from_double(0);
}
static PaxoVar native_tex_draw(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_tex_free(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

#endif // LEP_HAS_NVG

// ==========================================
// PDF (pdfio)
// ==========================================

#ifdef LEP_HAS_PDF

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
    return LEP_ZERO;
  double r = native_arg_double(args[1]) / 255.0;
  double g = native_arg_double(args[2]) / 255.0;
  double b = native_arg_double(args[3]) / 255.0;
  pdfioContentSetFillColorDeviceRGB(d->page, r, g, b);
  pdfioContentSetStrokeColorDeviceRGB(d->page, r, g, b);
  return LEP_ZERO;
}

// Rectángulo relleno: pdf_write_rect(doc, x, y, w, h)
static PaxoVar native_pdf_write_rect(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 5 ? pdf_from_args(args[0]) : NULL;
  if (!d || !d->page)
    return LEP_ZERO;
  pdfioContentPathRect(d->page, native_arg_double(args[1]),
                       native_arg_double(args[2]), native_arg_double(args[3]),
                       native_arg_double(args[4]));
  pdfioContentFill(d->page, false);
  return LEP_ZERO;
}

// Línea: pdf_write_line(doc, x1, y1, x2, y2)
static PaxoVar native_pdf_write_line(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 5 ? pdf_from_args(args[0]) : NULL;
  if (!d || !d->page)
    return LEP_ZERO;
  pdfioContentPathMoveTo(d->page, native_arg_double(args[1]),
                         native_arg_double(args[2]));
  pdfioContentPathLineTo(d->page, native_arg_double(args[3]),
                         native_arg_double(args[4]));
  pdfioContentStroke(d->page);
  return LEP_ZERO;
}

// Escribe texto: pdf_write_text(doc, x, y, tamano, texto)
static PaxoVar native_pdf_write_text(PaxoVar *args, uint8_t argc) {
  PaxoPdf *d = argc >= 5 ? pdf_from_args(args[0]) : NULL;
  const char *s = argc >= 5 ? native_arg_str(args[4]) : NULL;
  if (!d || !d->page || !s)
    return LEP_ZERO;
  pdfioContentSetTextFont(d->page, d->names[d->curfont],
                          native_arg_double(args[3]));
  pdfioContentTextMoveTo(d->page, native_arg_double(args[1]),
                         native_arg_double(args[2]));
  pdfioContentTextShow(d->page, false, s);
  return LEP_ZERO;
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
  return LEP_ZERO;
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
  return LEP_ZERO;
}
static PaxoVar native_pdf_write_rect(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_pdf_write_line(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_pdf_write_text(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}
static PaxoVar native_pdf_close(PaxoVar *args, uint8_t argc) {
  (void)args;
  (void)argc;
  return LEP_ZERO;
}

#endif // LEP_HAS_PDF

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
    // Ventana/gráficos. NATIVE_WIN_*/TEX_* son los IDs que emite el
    // compilador; NATIVE_SOKOL_*/NVG_* los internos de la VM.
  case NATIVE_WIN_OPEN:
  case NATIVE_SOKOL_INIT:
    return native_sokol_init(args, argc);
  case NATIVE_WIN_CLOSE:
  case NATIVE_SOKOL_SHUTDOWN:
    return native_sokol_shutdown(args, argc);
  case NATIVE_WIN_CLEAR:
  case NATIVE_SOKOL_CLEAR:
    return native_sokol_clear(args, argc);
  case NATIVE_WIN_COLOR:
  case NATIVE_SOKOL_COLOR:
    return native_sokol_color(args, argc);
  case NATIVE_WIN_SHOW:
  case NATIVE_SOKOL_SHOW:
    return native_sokol_show(args, argc);
  case NATIVE_WIN_POLL:
  case NATIVE_SOKOL_POLL:
    return native_sokol_poll(args, argc);
  case NATIVE_WIN_KEY:
  case NATIVE_SOKOL_KEY:
    return native_sokol_key(args, argc);
  case NATIVE_WIN_MOUSE:
  case NATIVE_SOKOL_MOUSE:
    return native_sokol_mouse(args, argc);
  case NATIVE_WIN_MOUSEDOWN:
  case NATIVE_SOKOL_MOUSEDOWN:
    return native_sokol_mousedown(args, argc);
  case NATIVE_WIN_TIME:
  case NATIVE_SOKOL_TIME:
    return native_sokol_time(args, argc);
  case NATIVE_WIN_DELAY:
  case NATIVE_SOKOL_DELAY:
    return native_sokol_delay(args, argc);
  case NATIVE_TEX_LOAD:
    return native_tex_load(args, argc);
  case NATIVE_TEX_DRAW:
    return native_tex_draw(args, argc);
  case NATIVE_TEX_FREE:
    return native_tex_free(args, argc);
  case NATIVE_WIN_RECT:
  case NATIVE_NVG_RECT:
    return native_nvg_rect(args, argc);
  case NATIVE_WIN_LINE:
  case NATIVE_NVG_LINE:
    return native_nvg_line(args, argc);
  case NATIVE_WIN_CIRCLE:
  case NATIVE_NVG_CIRCLE:
    return native_nvg_circle(args, argc);
  case NATIVE_WIN_TEXT:
  case NATIVE_NVG_TEXT:
    return native_nvg_text(args, argc);
  case NATIVE_NVG_CREATE:
    return native_nvg_create(args, argc);
  case NATIVE_NVG_CANCEL_FRAME:
    return native_nvg_cancel_frame(args, argc);
  case NATIVE_NVG_BEGIN_FRAME:
    return native_nvg_begin_frame(args, argc);
  case NATIVE_NVG_END_FRAME:
    return native_nvg_end_frame(args, argc);
  case NATIVE_NVG_FILL_COLOR:
    return native_nvg_fill_color(args, argc);
  case NATIVE_NVG_STROKE_COLOR:
    return native_nvg_stroke_color(args, argc);
  case NATIVE_NVG_STROKE_WIDTH:
    return native_nvg_stroke_width(args, argc);
  case NATIVE_NVG_FILL:
    return native_nvg_fill(args, argc);
  case NATIVE_NVG_STROKE:
    return native_nvg_stroke(args, argc);
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
  return LEP_NO_VALUE;
}
