// Functions_2.c (Corregido)
#pragma once
#include "vars.c"

#if __has_include("cast.c")
#include "cast.c"
#endif

#if __has_include("stb_image.h") && !defined(LEP_NO_STB)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE2_IMPLEMENTATION
#include "stb_image_resize2.h"
#define LEP_HAS_IMG 1
#endif

#if __has_include("stb_truetype.h") && !defined(LEP_NO_STB)
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_easy_font.h"
#include "stb_truetype.h"
#define LEP_HAS_FONT 1
#endif

#if __has_include("stb_ds.h")
#include "stb_ds.h"
#endif

#if __has_include("miniaudio.h") && !defined(LEP_NO_MINIAUDIO)
#define MA_IMPLEMENTATION
#include "miniaudio.h"
#define LEP_HAS_AUDIO 1
#endif

#if __has_include("third_party/chipmunk/chipmunk/chipmunk.h")
#include "third_party/chipmunk/chipmunk/chipmunk.h"
#define LEP_HAS_PHYS 1
#endif

#if (defined(LEP_ENABLE_NVG) && __has_include("nanovg.h")) || \
    (defined(LEP_EMBEDDED_LIBS) && defined(LEP_ENABLE_NVG))

#if defined(__ANDROID__)
#define SOKOL_GLES3
#define NANOVG_GLES3_IMPLEMENTATION
#else
#define SOKOL_GLCORE
#define SOKOL_NO_ENTRY
#define SOKOL_APP_IMPL
#define NANOVG_GL3_IMPLEMENTATION
#include "sokol_app.h"
#endif

#define SOKOL_GFX_IMPL
#define SOKOL_TIME_IMPL
#include "sokol_gfx.h"
#include "sokol_time.h"
#include "nanovg.h"
#include "nanovg_gl.h"
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
  NATIVE_INIT_WINDOW,
  NATIVE_CLEAR_SCREEN,
  NATIVE_DRAW_RECT,
  NATIVE_FILE_READ,
  NATIVE_FILE_WRITE,
  NATIVE_FILE_APPEND,
  NATIVE_FILE_EXISTS,
  NATIVE_FILE_DELETE,
  NATIVE_IMG_LOAD,
  NATIVE_IMG_INFO,
  NATIVE_IMG_SAVE_PNG,
  NATIVE_IMG_SAVE_JPG,
  NATIVE_IMG_SAVE_BMP,
  NATIVE_IMG_RESIZE,
  NATIVE_FONT_LOAD,
  NATIVE_FONT_GLYPH,
  NATIVE_FONT_METRICS,
  NATIVE_FONT_FREE,
  NATIVE_AUDIO_INIT,
  NATIVE_AUDIO_QUIT,
  NATIVE_AUDIO_PLAY,
  NATIVE_AUDIO_PAUSE,
  NATIVE_AUDIO_RESUME,
  NATIVE_AUDIO_STOP,
  NATIVE_AUDIO_VOLUME,
  NATIVE_AUDIO_PLAYING,
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
  NATIVE_SOKOL_INIT,
  NATIVE_SOKOL_SHUTDOWN,
  NATIVE_SOKOL_CLEAR,
  NATIVE_SOKOL_COLOR,
  NATIVE_SOKOL_SHOW,
  NATIVE_SOKOL_POLL,
  NATIVE_SOKOL_KEY,
  NATIVE_SOKOL_MOUSE,
  NATIVE_SOKOL_MOUSEDOWN,
  NATIVE_SOKOL_TIME,
  NATIVE_SOKOL_DELAY,
  NATIVE_NVG_CREATE,
  NATIVE_NVG_CANCEL_FRAME,
  NATIVE_NVG_BEGIN_FRAME,
  NATIVE_NVG_END_FRAME,
  NATIVE_NVG_RECT,
  NATIVE_NVG_LINE,
  NATIVE_NVG_CIRCLE,
  NATIVE_NVG_TEXT,
  NATIVE_NVG_FILL_COLOR,
  NATIVE_NVG_STROKE_COLOR,
  NATIVE_NVG_STROKE_WIDTH,
  NATIVE_NVG_FILL,
  NATIVE_NVG_STROKE,
  NATIVE_ID_COUNT
} NativeId;

static void print_var_inline(LEPVar elem) {
  switch (var_type(elem)) {
  case INT: {
    int64_t n = var_int_get(elem);
    double val = (double)n;
    printf("%g", val);
    break;
  }
  case BOOL:
    printf("%s", var_bool_get(elem) ? "true" : "false");
    break;
  case TRIT:
    printf("%u", var_trit_get(elem));
    break;
  case CHAR:
    printf("'%c'", (char)var_char_get(elem));
    break;
  case COLOR:
    printf("#%08X", var_color_get(elem));
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

static void print_var_full(LEPVar elem) {
  switch (var_type(elem)) {
  case CHAR:
    printf("%c", (char)var_char_get(elem));
    return;

  case STRING:
    printf("%s", var_string_get(elem));
    return;

  case POINT:
    printf("<point>");
    return;

  case ARRAY: {
    LEPArray *arr = var_array_get(elem);
    printf("«");
    for (size_t i = 0; i < arr->len; i++) {
      if (i > 0) printf(", ");
      print_var_inline(arr->items[i]);
    }
    printf("»");
    return;
  }

  case PACKAGE:
    printf("{package}");
    return;

  default:
    break;
  }

  print_var_inline(elem);
}

static LEPVar native_print(LEPVar *args, uint8_t argc) {
  if (argc < 1)
    return LEP_ZERO;
  for (uint64_t i = 0; i < argc; i++)
    print_var_full(args[i]);
  return LEP_ZERO;
}

static LEPVar native_println(LEPVar *args, uint8_t argc) {
  native_print(args, argc);
  putchar('\n');
  return LEP_ZERO;
}

static LEPVar native_typeof(LEPVar *args, uint8_t argc) {
  if (argc < 1)
    return LEP_ZERO;
  const char *type_name = "unknown";
  switch (var_type(args[0])) {
  case INT: type_name = "integer: int"; break;
  case UINT: type_name = "unsigned integer: uint"; break;
  case SFP: type_name = "float16: sfp"; break;
  case FP: type_name = "float64: fp"; break;
  case DEC: type_name = "decimal64: dec"; break;
  case FRAC: type_name = "fraction: frac"; break;
  case ACCUM: type_name = "accumulator: accum"; break;
  case BOOL: type_name = "boolean: bool"; break;
  case TRIT: type_name = "trit: trit"; break;
  case CHAR: type_name = "character: abc"; break;
  case POINT: type_name = "pointer: pin"; break;
  case FUNC: type_name = "function: fx"; break;
  case STRING: type_name = "string: abc[]"; break;
  case ARRAY: type_name = "array: var[]"; break;
  case PACKAGE: type_name = "package: pkg"; break;
  case COLOR: type_name = "color: col"; break;
  case SCOM: type_name = "complex16: scom"; break;
  case COM: type_name = "complex64: com"; break;
  }
  return var_string(type_name);
}

static LEPVar native_set_text_color(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING)
    return LEP_ZERO;
  const char *color = var_string_get(args[0]);
  if (strcmp(color, "red") == 0) text_red(stdout);
  else if (strcmp(color, "yellow") == 0) text_yellow(stdout);
  else if (strcmp(color, "green") == 0) text_green(stdout);
  else if (strcmp(color, "cyan") == 0) text_cyan(stdout);
  else if (strcmp(color, "blue") == 0) text_blue(stdout);
  else if (strcmp(color, "magenta") == 0) text_magenta(stdout);
  else if (strcmp(color, "white") == 0) text_white(stdout);
  else if (strcmp(color, "gray") == 0 || strcmp(color, "grey") == 0) text_gray(stdout);
  return LEP_ZERO;
}

static LEPVar native_reset_color(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  reset_colors(stdout);
  return LEP_ZERO;
}

static LEPVar native_set_bg_color(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING)
    return LEP_ZERO;
  const char *color = var_string_get(args[0]);
  if (strcmp(color, "red") == 0) background_red(stdout);
  else if (strcmp(color, "green") == 0) background_green(stdout);
  else if (strcmp(color, "blue") == 0) background_blue(stdout);
  else if (strcmp(color, "yellow") == 0) background_yellow(stdout);
  else if (strcmp(color, "cyan") == 0) background_cyan(stdout);
  else if (strcmp(color, "magenta") == 0) background_magenta(stdout);
  else if (strcmp(color, "white") == 0) background_white(stdout);
  return LEP_ZERO;
}

static LEPVar native_scan(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  static char buf[65536];
  if (!fgets(buf, sizeof(buf), stdin))
    buf[0] = '\0';
  size_t len = strlen(buf);
  if (len > 0 && buf[len - 1] == '\n')
    buf[len - 1] = '\0';
  return var_string(buf);
}

static LEPVar num_from_i64(int64_t v) {
  return var_int(v);
}

static LEPVar num_from_double(double d) {
  return var_fp64(d);
}

static LEPVar native_array_len(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != ARRAY)
    return LEP_ZERO;
  size_t len = var_array_get(args[0])->len;
  return num_from_i64((int64_t)len);
}

static LEPVar native_array_push(LEPVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != ARRAY)
    return LEP_ZERO;
  LEPArray *arr = var_array_get(args[0]);
  if (arr->len >= arr->capacity) {
    arr->capacity = arr->capacity ? arr->capacity * 2 : 4;
    arr->items = realloc(arr->items, sizeof(LEPVar) * arr->capacity);
  }
  arr->items[arr->len++] = args[1];
  return LEP_ZERO;
}

static LEPVar native_set_text_type(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING)
    return LEP_ZERO;
  const char *type = var_string_get(args[0]);
  if (strcmp(type, "bold") == 0) text_bold(stdout);
  else if (strcmp(type, "underline") == 0) text_underline(stdout);
  return LEP_ZERO;
}

static long gfx_width = 80;
static long gfx_height = 24;

static inline long native_arg_long(LEPVar v) {
  switch (var_type(v)) {
    case INT: return (long)var_int_get(v);
    case UINT: return (long)var_uint_get(v);
    case SFP: return (long)var_fp16_get(v);
    case FP: return (long)var_fp64_get(v);
    default: return 0;
  }
}

static inline double native_arg_double(LEPVar v) {
  switch (var_type(v)) {
    case INT: return (double)var_int_get(v);
    case UINT: return (double)var_uint_get(v);
    case SFP: return (double)var_fp16_get(v);
    case FP: return var_fp64_get(v);
    case DEC: return (double)var_dec_get(v);
    default: return 0.0;
  }
}

static inline const char *native_arg_str(LEPVar v) {
  return var_type(v) == STRING ? var_string_get(v) : NULL;
}

static LEPArray *arr_new(size_t cap) {
  LEPArray *a = malloc(sizeof(LEPArray));
  a->len = 0;
  a->capacity = cap ? cap : 4;
  a->items = malloc(sizeof(LEPVar) * a->capacity);
  return a;
}

static void arr_push_var(LEPArray *a, LEPVar v) {
  if (a->len >= a->capacity) {
    a->capacity *= 2;
    a->items = realloc(a->items, sizeof(LEPVar) * a->capacity);
  }
  a->items[a->len++] = v;
}

static inline void arr_push_num(LEPArray *a, double v) {
  arr_push_var(a, num_from_double(v));
}

static LEPVar ret_xy(double x, double y) {
  LEPArray *a = arr_new(2);
  arr_push_num(a, x);
  arr_push_num(a, y);
  return var_array(a);
}

static uint8_t *arg_arr_bytes(LEPVar v, size_t *out_len) {
  *out_len = 0;
  if (var_type(v) != ARRAY) return NULL;
  LEPArray *a = var_array_get(v);
  uint8_t *buf = malloc(a->len ? a->len : 1);
  for (size_t i = 0; i < a->len; i++) {
    long x = native_arg_long(a->items[i]);
    buf[i] = (uint8_t)(x < 0 ? 0 : (x > 255 ? 255 : x));
  }
  *out_len = a->len;
  return buf;
}

static LEPVar ret_bytes_array(const uint8_t *b, size_t len) {
  LEPArray *a = arr_new(len ? len : 1);
  for (size_t i = 0; i < len; i++)
    arr_push_var(a, num_from_i64(b[i]));
  return var_array(a);
}

typedef struct {
  void **ptr;
  void **owner;
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
  if (id < 1 || (size_t)id > r->len) return NULL;
  return r->ptr[id - 1];
}

static bool reg_del(NativeReg *r, int64_t id, bool free_ptr) {
  void *p = reg_get(r, id);
  if (!p) return false;
  if (free_ptr) free(p);
  r->ptr[id - 1] = NULL;
  r->owner[id - 1] = NULL;
  return true;
}

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

static LEPVar native_init_window(LEPVar *args, uint8_t argc) {
  if (argc < 2) return var_bool(false);
  long w = native_arg_long(args[0]);
  long h = native_arg_long(args[1]);
  if (w <= 0 || h <= 0 || w > 10000 || h > 10000) return var_bool(false);
  gfx_width = w;
  gfx_height = h;
  return var_bool(true);
}

static LEPVar native_clear_screen(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  fputs("\033[2J\033[H", stdout);
  fflush(stdout);
  return LEP_ZERO;
}

static LEPVar native_draw_rect(LEPVar *args, uint8_t argc) {
  if (argc < 4) return LEP_ZERO;
  long x = native_arg_long(args[0]);
  long y = native_arg_long(args[1]);
  long w = native_arg_long(args[2]);
  long h = native_arg_long(args[3]);
  if (x < 0) { w += x; x = 0; }
  if (y < 0) { h += y; y = 0; }
  if (x + w > gfx_width) w = gfx_width - x;
  if (y + h > gfx_height) h = gfx_height - y;
  if (w <= 0 || h <= 0) return LEP_ZERO;
  for (long row = 0; row < h; row++) {
    printf("\033[%ld;%ldH", y + row + 1, x + 1);
    for (long col = 0; col < w; col++) fputs("█", stdout);
  }
  fflush(stdout);
  return LEP_ZERO;
}

static LEPVar native_file_read(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) return var_string("");
  const char *path = var_string_get(args[0]);
  FILE *f = fopen(path, "rb");
  if (!f) return var_string("");
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);
  if (size < 0) size = 0;
  char *buf = malloc((size_t)size + 1);
  if (!buf) { fclose(f); return var_string(""); }
  size_t leidos = fread(buf, 1, (size_t)size, f);
  buf[leidos] = '\0';
  fclose(f);
  return var_string(buf);
}

static LEPVar file_write_mode(const char *path, const char *data, const char *mode) {
  FILE *f = fopen(path, mode);
  if (!f) return var_bool(false);
  size_t len = strlen(data);
  bool ok = fwrite(data, 1, len, f) == len;
  fclose(f);
  return var_bool(ok);
}

static LEPVar native_file_write(LEPVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != STRING || var_type(args[1]) != STRING) return var_bool(false);
  return file_write_mode(var_string_get(args[0]), var_string_get(args[1]), "wb");
}

static LEPVar native_file_append(LEPVar *args, uint8_t argc) {
  if (argc < 2 || var_type(args[0]) != STRING || var_type(args[1]) != STRING) return var_bool(false);
  return file_write_mode(var_string_get(args[0]), var_string_get(args[1]), "ab");
}

static LEPVar native_file_exists(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) return var_bool(false);
  return var_bool(access(var_string_get(args[0]), F_OK) == 0);
}

static LEPVar native_file_delete(LEPVar *args, uint8_t argc) {
  if (argc < 1 || var_type(args[0]) != STRING) return var_bool(false);
  return var_bool(remove(var_string_get(args[0])) == 0);
}

#define STUB_LEP(n) static LEPVar n(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return LEP_ZERO; }
#define STUB_0(n) static LEPVar n(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return num_from_i64(0); }
#define STUB_FALSE(n) static LEPVar n(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_bool(false); }

#ifdef LEP_HAS_IMG
static LEPVar native_img_load(LEPVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path) return var_array(arr_new(0));
  int w, h, ch;
  unsigned char *data = stbi_load(path, &w, &h, &ch, 0);
  if (!data) return var_array(arr_new(0));
  size_t n = (size_t)w * h * ch;
  LEPArray *a = arr_new(n + 3);
  arr_push_num(a, w); arr_push_num(a, h); arr_push_num(a, ch);
  for (size_t i = 0; i < n; i++) arr_push_var(a, num_from_i64(data[i]));
  stbi_image_free(data);
  return var_array(a);
}
static LEPVar native_img_info(LEPVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  int w, h, ch;
  if (!path || !stbi_info(path, &w, &h, &ch)) return var_array(arr_new(0));
  LEPArray *a = arr_new(3);
  arr_push_num(a, w); arr_push_num(a, h); arr_push_num(a, ch);
  return var_array(a);
}
static LEPVar img_save_generic(LEPVar *args, int fmt) {
  const char *path = native_arg_str(args[0]);
  if (!path) return var_bool(false);
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]), ch = native_arg_long(args[3]);
  if (w <= 0 || h <= 0 || ch < 1 || ch > 4) return var_bool(false);
  size_t len = 0;
  uint8_t *data = arg_arr_bytes(args[4], &len);
  if (!data || len < (size_t)(w * h * ch)) { free(data); return var_bool(false); }
  bool ok = false;
  if (fmt == 0) ok = stbi_write_png(path, (int)w, (int)h, (int)ch, data, (int)w * (int)ch);
  else if (fmt == 1) ok = stbi_write_jpg(path, (int)w, (int)h, (int)ch, data, 90);
  else ok = stbi_write_bmp(path, (int)w, (int)h, (int)ch, data);
  free(data);
  return var_bool(ok);
}
static LEPVar native_img_save_png(LEPVar *args, uint8_t argc) { (void)argc; return img_save_generic(args, 0); }
static LEPVar native_img_save_jpg(LEPVar *args, uint8_t argc) { (void)argc; return img_save_generic(args, 1); }
static LEPVar native_img_save_bmp(LEPVar *args, uint8_t argc) { (void)argc; return img_save_generic(args, 2); }
static LEPVar native_img_resize(LEPVar *args, uint8_t argc) {
  if (argc < 6) return var_array(arr_new(0));
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]);
  long nw = native_arg_long(args[3]), nh = native_arg_long(args[4]);
  long ch = native_arg_long(args[5]);
  if (w <= 0 || h <= 0 || nw <= 0 || nh <= 0 || ch < 1 || ch > 4) return var_array(arr_new(0));
  size_t len = 0;
  uint8_t *src = arg_arr_bytes(args[0], &len);
  if (!src || len < (size_t)(w * h * ch)) { free(src); return var_array(arr_new(0)); }
  uint8_t *dst = malloc((size_t)nw * nh * ch);
  bool ok = dst && stbir_resize_uint8_linear(src, (int)w, (int)h, 0, dst, (int)nw, (int)nh, 0, (stbir_pixel_layout)ch);
  free(src);
  LEPVar res = ok ? ret_bytes_array(dst, (size_t)nw * nh * ch) : var_array(arr_new(0));
  free(dst);
  return res;
}
#else
static LEPVar native_img_load(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_array(arr_new(0)); }
STUB_0(native_img_info)
STUB_FALSE(native_img_save_png)
STUB_FALSE(native_img_save_jpg)
STUB_FALSE(native_img_save_bmp)
static LEPVar native_img_resize(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_array(arr_new(0)); }
#endif

#ifdef LEP_HAS_FONT
typedef struct { unsigned char *buf; stbtt_fontinfo info; } LEPFont;
static NativeReg font_reg = {0};
static LEPVar native_font_load(LEPVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path) return num_from_i64(0);
  FILE *f = fopen(path, "rb");
  if (!f) return num_from_i64(0);
  fseek(f, 0, SEEK_END); long size = ftell(f); rewind(f);
  if (size <= 0) { fclose(f); return num_from_i64(0); }
  LEPFont *pf = malloc(sizeof(LEPFont));
  pf->buf = malloc((size_t)size);
  size_t rd = fread(pf->buf, 1, (size_t)size, f);
  fclose(f);
  if (rd == 0 || !stbtt_InitFont(&pf->info, pf->buf, 0)) {
    free(pf->buf); free(pf); return num_from_i64(0);
  }
  if (font_reg.cap == 0) reg_init(&font_reg);
  return num_from_i64(reg_add(&font_reg, pf, NULL));
}
static LEPFont *font_from_args(LEPVar v) {
  if (font_reg.cap == 0) return NULL;
  return (LEPFont *)reg_get(&font_reg, (int64_t)native_arg_long(v));
}
static LEPVar native_font_glyph(LEPVar *args, uint8_t argc) {
  LEPFont *pf = argc >= 1 ? font_from_args(args[0]) : NULL;
  if (!pf) return var_array(arr_new(0));
  long cp = native_arg_long(args[1]);
  float size = (float)native_arg_double(args[2]);
  if (size <= 0) size = 16;
  float scale = stbtt_ScaleForPixelHeight(&pf->info, size);
  int adv = 0, lsb = 0;
  stbtt_GetCodepointHMetrics(&pf->info, (int)cp, &adv, &lsb);
  int w, h, ox, oy;
  unsigned char *bmp = stbtt_GetCodepointBitmap(&pf->info, scale, scale, (int)cp, &w, &h, &ox, &oy);
  LEPArray *a = arr_new((size_t)(w > 0 ? w : 1) * (h > 0 ? h : 1) + 5);
  arr_push_num(a, w); arr_push_num(a, h); arr_push_num(a, ox); arr_push_num(a, oy);
  arr_push_num(a, (double)adv * scale);
  if (bmp) {
    for (int i = 0; i < w * h; i++) arr_push_var(a, num_from_i64(bmp[i]));
    stbtt_FreeBitmap(bmp, NULL);
  }
  return var_array(a);
}
static LEPVar native_font_metrics(LEPVar *args, uint8_t argc) {
  LEPFont *pf = argc >= 1 ? font_from_args(args[0]) : NULL;
  if (!pf) return var_array(arr_new(0));
  float size = (float)native_arg_double(args[1]);
  if (size <= 0) size = 16;
  float scale = stbtt_ScaleForPixelHeight(&pf->info, size);
  int asc = 0, desc = 0, gap = 0;
  stbtt_GetFontVMetrics(&pf->info, &asc, &desc, &gap);
  LEPArray *a = arr_new(3);
  arr_push_num(a, (double)asc * scale);
  arr_push_num(a, (double)desc * scale);
  arr_push_num(a, (double)gap * scale);
  return var_array(a);
}
static LEPVar native_font_free(LEPVar *args, uint8_t argc) {
  if (argc >= 1 && font_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    LEPFont *pf = (LEPFont *)reg_get(&font_reg, id);
    if (pf) { free(pf->buf); reg_del(&font_reg, id, true); }
  }
  return LEP_ZERO;
}
#else
STUB_0(native_font_load)
static LEPVar native_font_glyph(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_array(arr_new(0)); }
static LEPVar native_font_metrics(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_array(arr_new(0)); }
STUB_LEP(native_font_free)
#endif

#ifdef LEP_HAS_AUDIO
static ma_engine audio_engine;
static bool audio_up = false;
static NativeReg snd_reg = {0};
static void snd_freer(void *p) { ma_sound *s = (ma_sound *)p; ma_sound_uninit(s); free(s); }
static LEPVar native_audio_init(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (audio_up) return var_bool(true);
  if (ma_engine_init(NULL, &audio_engine) != MA_SUCCESS) return var_bool(false);
  audio_up = true;
  return var_bool(true);
}
static LEPVar native_audio_quit(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (!audio_up) return LEP_ZERO;
  for (size_t i = 0; i < snd_reg.len; i++) {
    if (snd_reg.ptr[i]) snd_freer(snd_reg.ptr[i]);
    snd_reg.ptr[i] = NULL;
  }
  ma_engine_uninit(&audio_engine);
  audio_up = false;
  return LEP_ZERO;
}
static LEPVar native_audio_play(LEPVar *args, uint8_t argc) {
  const char *path = argc >= 1 ? native_arg_str(args[0]) : NULL;
  if (!path) return num_from_i64(0);
  if (!audio_up && !var_bool_get(native_audio_init(NULL, 0))) return num_from_i64(0);
  ma_sound *s = malloc(sizeof(ma_sound));
  if (ma_sound_init_from_file(&audio_engine, path, 0, NULL, NULL, s) != MA_SUCCESS) {
    free(s); return num_from_i64(0);
  }
  ma_sound_set_looping(s, argc >= 2 && var_bool_get(args[1]));
  ma_sound_start(s);
  if (snd_reg.cap == 0) reg_init(&snd_reg);
  return num_from_i64(reg_add(&snd_reg, s, NULL));
}
static ma_sound *snd_from_args(LEPVar v) {
  if (snd_reg.cap == 0) return NULL;
  return (ma_sound *)reg_get(&snd_reg, (int64_t)native_arg_long(v));
}
static LEPVar native_audio_pause(LEPVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  if (!s) return var_bool(false);
  ma_sound_stop(s);
  return var_bool(true);
}
static LEPVar native_audio_resume(LEPVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  if (!s) return var_bool(false);
  ma_sound_start(s);
  return var_bool(true);
}
static LEPVar native_audio_stop(LEPVar *args, uint8_t argc) {
  if (argc < 1 || snd_reg.cap == 0) return var_bool(false);
  int64_t id = (int64_t)native_arg_long(args[0]);
  ma_sound *s = (ma_sound *)reg_get(&snd_reg, id);
  if (!s) return var_bool(false);
  snd_freer(s);
  reg_del(&snd_reg, id, false);
  return var_bool(true);
}
static LEPVar native_audio_volume(LEPVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  if (!s) return var_bool(false);
  float vol = (float)native_arg_double(argc >= 2 ? args[1] : LEP_ZERO);
  if (vol < 0) vol = 0;
  ma_sound_set_volume(s, vol);
  return var_bool(true);
}
static LEPVar native_audio_playing(LEPVar *args, uint8_t argc) {
  ma_sound *s = argc >= 1 ? snd_from_args(args[0]) : NULL;
  return var_bool(s && ma_sound_is_playing(s));
}
#else
static LEPVar native_audio_init(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_bool(false); }
STUB_LEP(native_audio_quit)
STUB_0(native_audio_play)
STUB_FALSE(native_audio_pause)
STUB_FALSE(native_audio_resume)
STUB_FALSE(native_audio_stop)
STUB_FALSE(native_audio_volume)
STUB_FALSE(native_audio_playing)
#endif

#ifdef LEP_HAS_PHYS
typedef struct { cpBody *body; cpSpace *space; } PhysBodyRec;
typedef struct { cpShape *shape; cpSpace *space; } PhysShapeRec;
static NativeReg space_reg = {0}, body_reg = {0}, shape_reg = {0};
static void pb_freer(void *p) {
  PhysBodyRec *r = (PhysBodyRec *)p;
  if (r->space && cpSpaceGetStaticBody(r->space) != r->body) cpSpaceRemoveBody(r->space, r->body);
  cpBodyFree(r->body);
  free(r);
}
static void ps_freer(void *p) {
  PhysShapeRec *r = (PhysShapeRec *)p;
  if (r->space) cpSpaceRemoveShape(r->space, r->shape);
  cpShapeFree(r->shape);
  free(r);
}
static LEPVar native_phys_space(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (space_reg.cap == 0) { reg_init(&space_reg); reg_init(&body_reg); reg_init(&shape_reg); }
  return num_from_i64(reg_add(&space_reg, cpSpaceNew(), NULL));
}
static cpSpace *space_from_args(LEPVar v) {
  if (space_reg.cap == 0) return NULL;
  return (cpSpace *)reg_get(&space_reg, (int64_t)native_arg_long(v));
}
static PhysBodyRec *body_from_args(LEPVar v) {
  if (body_reg.cap == 0) return NULL;
  return (PhysBodyRec *)reg_get(&body_reg, (int64_t)native_arg_long(v));
}
static PhysShapeRec *shape_from_args(LEPVar v) {
  if (shape_reg.cap == 0) return NULL;
  return (PhysShapeRec *)reg_get(&shape_reg, (int64_t)native_arg_long(v));
}
static LEPVar native_phys_gravity(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (sp) cpSpaceSetGravity(sp, cpv(native_arg_double(args[1]), native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)));
  return LEP_ZERO;
}
static LEPVar native_phys_step(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (sp) {
    double dt = native_arg_double(args[1]);
    if (dt <= 0 || dt > 1) dt = 1.0 / 60.0;
    cpSpaceStep(sp, dt);
  }
  return LEP_ZERO;
}
static LEPVar native_phys_body(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp) return num_from_i64(0);
  double mass = native_arg_double(args[1]), inertia = native_arg_double(args[2]);
  if (mass <= 0) mass = 1;
  if (inertia <= 0) inertia = 1;
  PhysBodyRec *rec = malloc(sizeof(PhysBodyRec));
  rec->body = cpSpaceAddBody(sp, cpBodyNew(mass, inertia));
  rec->space = sp;
  return num_from_i64(reg_add(&body_reg, rec, sp));
}
static LEPVar native_phys_body_static(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp) return num_from_i64(0);
  PhysBodyRec *rec = malloc(sizeof(PhysBodyRec));
  rec->body = cpSpaceGetStaticBody(sp);
  rec->space = sp;
  return num_from_i64(reg_add(&body_reg, rec, NULL));
}
static LEPVar native_phys_pos(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (!r) return ret_xy(0, 0);
  cpVect p = cpBodyGetPosition(r->body);
  return ret_xy(p.x, p.y);
}
static LEPVar native_phys_vel(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (!r) return ret_xy(0, 0);
  cpVect v = cpBodyGetVelocity(r->body);
  return ret_xy(v.x, v.y);
}
static LEPVar native_phys_set_pos(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r) cpBodySetPosition(r->body, cpv(native_arg_double(args[1]), native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)));
  return LEP_ZERO;
}
static LEPVar native_phys_set_vel(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r) cpBodySetVelocity(r->body, cpv(native_arg_double(args[1]), native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)));
  return LEP_ZERO;
}
static LEPVar native_phys_angle(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  return num_from_double(r ? cpBodyGetAngle(r->body) : 0);
}
static LEPVar native_phys_set_angle(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r) cpBodySetAngle(r->body, native_arg_double(args[1]));
  return LEP_ZERO;
}
static LEPVar native_phys_force(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r) cpBodyApplyForceAtLocalPoint(r->body, cpv(native_arg_double(args[1]), native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)), cpvzero);
  return LEP_ZERO;
}
static LEPVar native_phys_impulse(LEPVar *args, uint8_t argc) {
  PhysBodyRec *r = argc >= 1 ? body_from_args(args[0]) : NULL;
  if (r) cpBodyApplyImpulseAtLocalPoint(r->body, cpv(native_arg_double(args[1]), native_arg_double(argc >= 3 ? args[2] : LEP_ZERO)), cpvzero);
  return LEP_ZERO;
}
static LEPVar shape_add(cpSpace *sp, cpShape *s) {
  PhysShapeRec *rec = malloc(sizeof(PhysShapeRec));
  rec->shape = cpSpaceAddShape(sp, s);
  rec->space = sp;
  return num_from_i64(reg_add(&shape_reg, rec, sp));
}
static LEPVar native_phys_circle(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  PhysBodyRec *b = argc >= 2 ? body_from_args(args[1]) : NULL;
  if (!sp || !b) return num_from_i64(0);
  return shape_add(sp, cpCircleShapeNew(b->body, native_arg_double(args[4]), cpv(native_arg_double(args[2]), native_arg_double(args[3]))));
}
static LEPVar native_phys_box(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  PhysBodyRec *b = argc >= 2 ? body_from_args(args[1]) : NULL;
  if (!sp || !b) return num_from_i64(0);
  return shape_add(sp, cpBoxShapeNew(b->body, native_arg_double(args[2]), native_arg_double(args[3]), 0));
}
static LEPVar native_phys_segment(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  PhysBodyRec *b = argc >= 2 ? body_from_args(args[1]) : NULL;
  if (!sp || !b) return num_from_i64(0);
  return shape_add(sp, cpSegmentShapeNew(b->body, cpv(native_arg_double(args[2]), native_arg_double(args[3])), cpv(native_arg_double(args[4]), native_arg_double(args[5])), native_arg_double(args[6])));
}
static LEPVar native_phys_elasticity(LEPVar *args, uint8_t argc) {
  PhysShapeRec *r = argc >= 1 ? shape_from_args(args[0]) : NULL;
  if (r) cpShapeSetElasticity(r->shape, native_arg_double(args[1]));
  return LEP_ZERO;
}
static LEPVar native_phys_friction(LEPVar *args, uint8_t argc) {
  PhysShapeRec *r = argc >= 1 ? shape_from_args(args[0]) : NULL;
  if (r) cpShapeSetFriction(r->shape, native_arg_double(args[1]));
  return LEP_ZERO;
}
static LEPVar native_phys_collide(LEPVar *args, uint8_t argc) {
  PhysShapeRec *a = argc >= 1 ? shape_from_args(args[0]) : NULL;
  PhysShapeRec *b = argc >= 2 ? shape_from_args(args[1]) : NULL;
  if (!a || !b) return var_bool(false);
  return var_bool(cpShapesCollide(a->shape, b->shape).count > 0);
}
static LEPVar native_phys_free_shape(LEPVar *args, uint8_t argc) {
  if (argc >= 1 && shape_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    if (reg_get(&shape_reg, id)) { ps_freer(reg_get(&shape_reg, id)); reg_del(&shape_reg, id, false); }
  }
  return LEP_ZERO;
}
static LEPVar native_phys_free_body(LEPVar *args, uint8_t argc) {
  if (argc >= 1 && body_reg.cap != 0) {
    int64_t id = (int64_t)native_arg_long(args[0]);
    PhysBodyRec *r = (PhysBodyRec *)reg_get(&body_reg, id);
    if (r) { pb_freer(r); reg_del(&body_reg, id, false); }
  }
  return LEP_ZERO;
}
static LEPVar native_phys_free_space(LEPVar *args, uint8_t argc) {
  cpSpace *sp = argc >= 1 ? space_from_args(args[0]) : NULL;
  if (!sp) return LEP_ZERO;
  int64_t sid = (int64_t)native_arg_long(args[0]);
  reg_free_owned(&shape_reg, sp, ps_freer);
  reg_free_owned(&body_reg, sp, pb_freer);
  cpSpaceFree(sp);
  reg_del(&space_reg, sid, false);
  return LEP_ZERO;
}
#else
static LEPVar native_phys_space(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return num_from_i64(0); }
STUB_LEP(native_phys_gravity)
STUB_LEP(native_phys_step)
STUB_0(native_phys_body)
STUB_0(native_phys_body_static)
static LEPVar native_phys_pos(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return ret_xy(0, 0); }
static LEPVar native_phys_vel(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return ret_xy(0, 0); }
STUB_LEP(native_phys_set_pos)
STUB_LEP(native_phys_set_vel)
STUB_LEP(native_phys_angle)
STUB_LEP(native_phys_set_angle)
STUB_LEP(native_phys_force)
STUB_LEP(native_phys_impulse)
STUB_0(native_phys_circle)
STUB_0(native_phys_box)
STUB_0(native_phys_segment)
STUB_LEP(native_phys_elasticity)
STUB_LEP(native_phys_friction)
STUB_FALSE(native_phys_collide)
STUB_LEP(native_phys_free_shape)
STUB_LEP(native_phys_free_body)
STUB_LEP(native_phys_free_space)
#endif

#ifdef LEP_HAS_NVG
static NVGcontext *g_nvg = NULL;
static int g_nvg_w = 800, g_nvg_h = 600;
static float g_nvg_scale = 1.0f;
static int g_sok_master = 0;

#define LEP_EVQ_CAP 256
static char g_evq[LEP_EVQ_CAP][64];
static int g_evq_head = 0, g_evq_tail = 0, g_evq_n = 0;

static unsigned char g_cc_r = 0, g_cc_g = 0, g_cc_b = 0, g_cc_a = 255;
static float g_fill_r = 1, g_fill_g = 1, g_fill_b = 1, g_fill_a = 1;

static int g_sok_key_state[512];
static float g_sok_mouse_x = 0, g_sok_mouse_y = 0;
static int g_sok_mouse_down = 0;

static void evq_push(const char *s) {
  if (g_evq_n >= LEP_EVQ_CAP) return;
  strncpy(g_evq[g_evq_tail], s, 63);
  g_evq[g_evq_tail][63] = '\0';
  g_evq_tail = (g_evq_tail + 1) % LEP_EVQ_CAP;
  g_evq_n++;
}

typedef enum {
  LG_FILLCOLOR, LG_STROKECOLOR, LG_STROKEW,
  LG_RECT, LG_LINE, LG_CIRCLE, LG_TEXT, LG_IMAGE
} lg_cmd_kind;

typedef struct {
  lg_cmd_kind k;
  float a, b, c, d;
  float r, g, bb, aa;
  char *text;
  int tex;
} lg_cmd;

#define LEP_MAX_TEX 32
typedef struct {
  int used;
  int built;
  int img;
  int w, h, ch;
  unsigned char *px;
} LEPTex;
static LEPTex g_tex[LEP_MAX_TEX] = {{0}};

static lg_cmd *g_cmds = NULL;
static size_t g_cmd_n = 0, g_cmd_cap = 0;

static void lg_push(lg_cmd_kind k, float a, float b, float c, float d, const char *txt) {
  if (g_cmd_n == g_cmd_cap) {
    g_cmd_cap = g_cmd_cap ? g_cmd_cap * 2 : 64;
    g_cmds = (lg_cmd *)realloc(g_cmds, g_cmd_cap * sizeof(lg_cmd));
    if (!g_cmds) return;
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
    if (cmd->text) memcpy(cmd->text, txt, len + 1);
  }
}

static void lg_reset(void) {
  for (size_t i = 0; i < g_cmd_n; i++) free(g_cmds[i].text);
  g_cmd_n = 0;
}

static void lep_tex_build_all(void) {
  if (!g_nvg) return;
  for (int i = 0; i < LEP_MAX_TEX; i++) {
    LEPTex *t = &g_tex[i];
    if (!t->used || t->built) continue;
    t->img = nvgCreateImageRGBA(g_nvg, t->w, t->h, 0, t->px);
    t->built = (t->img != 0);
  }
}

static void lep_sapp_init(void) {
  if (!g_nvg) g_nvg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
  lep_tex_build_all();
}

static void lep_sapp_frame(void) {
  if (!g_nvg) return;
  lep_tex_build_all();
  glViewport(0, 0, g_nvg_w, g_nvg_h);
  glClearColor((float)g_cc_r / 255.f, (float)g_cc_g / 255.f, (float)g_cc_b / 255.f, (float)g_cc_a / 255.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  nvgBeginFrame(g_nvg, (float)g_nvg_w, (float)g_nvg_h, g_nvg_scale);
  for (size_t i = 0; i < g_cmd_n; i++) {
    lg_cmd *c = &g_cmds[i];
    switch (c->k) {
    case LG_FILLCOLOR: nvgFillColor(g_nvg, nvgRGBAf(c->r, c->g, c->bb, c->aa)); break;
    case LG_STROKECOLOR: nvgStrokeColor(g_nvg, nvgRGBAf(c->r, c->g, c->bb, c->aa)); break;
    case LG_STROKEW: nvgStrokeWidth(g_nvg, c->a); break;
    case LG_RECT:
      nvgBeginPath(g_nvg); nvgRect(g_nvg, c->a, c->b, c->c, c->d); nvgFill(g_nvg);
      break;
    case LG_LINE:
      nvgBeginPath(g_nvg); nvgMoveTo(g_nvg, c->a, c->b); nvgLineTo(g_nvg, c->c, c->d); nvgStroke(g_nvg);
      break;
    case LG_CIRCLE:
      nvgBeginPath(g_nvg); nvgCircle(g_nvg, c->a, c->b, c->c); nvgFill(g_nvg);
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
        NVGpaint img = nvgImagePattern(g_nvg, c->a, c->b, c->c, c->d, 0.0f, g_tex[idx].img, 1.0f);
        nvgBeginPath(g_nvg); nvgRect(g_nvg, c->a, c->b, c->c, c->d); nvgFillPaint(g_nvg, img); nvgFill(g_nvg);
      }
      break;
    }
    default: break;
    }
  }
  nvgEndFrame(g_nvg);
}

static void lep_sapp_event(const sapp_event *ev) {
  char buf[64];
  switch (ev->type) {
  case SAPP_EVENTTYPE_KEY_DOWN:
    if (ev->key_code >= 0 && ev->key_code < 512) g_sok_key_state[ev->key_code] = 1;
    if (!ev->key_repeat) { snprintf(buf, sizeof(buf), "keydown:%d", (int)ev->key_code); evq_push(buf); }
    break;
  case SAPP_EVENTTYPE_KEY_UP:
    if (ev->key_code >= 0 && ev->key_code < 512) g_sok_key_state[ev->key_code] = 0;
    snprintf(buf, sizeof(buf), "keyup:%d", (int)ev->key_code); evq_push(buf);
    break;
  case SAPP_EVENTTYPE_MOUSE_DOWN: g_sok_mouse_down = 1; evq_push("mousedown"); break;
  case SAPP_EVENTTYPE_MOUSE_UP: g_sok_mouse_down = 0; evq_push("mouseup"); break;
  case SAPP_EVENTTYPE_MOUSE_MOVE: g_sok_mouse_x = ev->mouse_x; g_sok_mouse_y = ev->mouse_y; break;
  case SAPP_EVENTTYPE_QUIT_REQUESTED: evq_push("quit"); break;
  default: break;
  }
}

static void lep_sapp_cleanup(void) {
  for (int i = 0; i < LEP_MAX_TEX; i++) {
    LEPTex *t = &g_tex[i];
    if (t->used && t->built && g_nvg) nvgDeleteImage(g_nvg, t->img);
    free(t->px);
    memset(t, 0, sizeof(*t));
  }
  if (g_nvg) { nvgDeleteGL3(g_nvg); g_nvg = NULL; }
}

static LEPVar native_sokol_init(LEPVar *args, uint8_t argc) {
  long w = argc >= 2 ? native_arg_long(args[1]) : 800;
  long h = argc >= 3 ? native_arg_long(args[2]) : 600;
  if (w <= 0) w = 800;
  if (h <= 0) h = 600;
  g_nvg_w = (int)w; g_nvg_h = (int)h; g_nvg_scale = 1.0f;
  stm_setup();
  return var_bool(true);
}

static LEPVar native_sokol_shutdown(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (g_sok_master) sapp_request_quit();
  lg_reset();
  return var_bool(true);
}

static LEPVar native_sokol_color(LEPVar *args, uint8_t argc) {
  if (argc < 3) return LEP_ZERO;
  long r = native_arg_long(args[0]), g = native_arg_long(args[1]), b = native_arg_long(args[2]);
  long a = argc >= 4 ? native_arg_long(args[3]) : 255;
  g_cc_r = (unsigned char)(r < 0 ? 0 : (r > 255 ? 255 : r));
  g_cc_g = (unsigned char)(g < 0 ? 0 : (g > 255 ? 255 : g));
  g_cc_b = (unsigned char)(b < 0 ? 0 : (b > 255 ? 255 : b));
  g_cc_a = (unsigned char)(a < 0 ? 0 : (a > 255 ? 255 : a));
  return LEP_ZERO;
}

static LEPVar native_sokol_clear(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  return LEP_ZERO;
}

static LEPVar native_sokol_show(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  const char *title = argc >= 1 && var_type(args[0]) == STRING ? var_string_get(args[0]) : "LEP Window";
  g_sok_master = 1;
  sapp_run(&(sapp_desc){
      .init_cb = lep_sapp_init,
      .frame_cb = lep_sapp_frame,
      .event_cb = lep_sapp_event,
      .cleanup_cb = lep_sapp_cleanup,
      .width = g_nvg_w,
      .height = g_nvg_h,
      .window_title = title,
      .icon.sokol_default = true,
  });
  g_sok_master = 0;
  return var_bool(true);
}

static LEPVar native_sokol_poll(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (g_evq_n == 0) return var_string("");
  char s[64];
  strcpy(s, g_evq[g_evq_head]);
  g_evq_head = (g_evq_head + 1) % LEP_EVQ_CAP;
  g_evq_n--;
  return var_string(s);
}

static LEPVar native_sokol_key(LEPVar *args, uint8_t argc) {
  if (argc < 1) return var_bool(false);
  long kc = native_arg_long(args[0]);
  if (kc < 0 || kc >= 512) return var_bool(false);
  return var_bool(g_sok_key_state[kc]);
}

static LEPVar native_sokol_mouse(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  return ret_xy(g_sok_mouse_x, g_sok_mouse_y);
}

static LEPVar native_sokol_mousedown(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  return var_bool(g_sok_mouse_down);
}

static LEPVar native_sokol_time(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  return num_from_double(stm_sec(stm_now()));
}

static LEPVar native_sokol_delay(LEPVar *args, uint8_t argc) {
  if (argc < 1) return LEP_ZERO;
  long ms = native_arg_long(args[0]);
  if (ms > 0) usleep((useconds_t)(ms * 1000));
  return LEP_ZERO;
}

static LEPVar native_tex_load(LEPVar *args, uint8_t argc) {
  if (argc < 4) return num_from_i64(0);
  long w = native_arg_long(args[1]), h = native_arg_long(args[2]), ch = native_arg_long(args[3]);
  if (w <= 0 || h <= 0 || ch < 1 || ch > 4) return num_from_i64(0);
  size_t len = 0;
  uint8_t *px = arg_arr_bytes(args[0], &len);
  if (!px || len < (size_t)(w * h * ch)) { free(px); return num_from_i64(0); }
  uint8_t *rgba = malloc((size_t)w * h * 4);
  for (int i = 0; i < w * h; i++) {
    if (ch == 4) {
      rgba[i*4 + 0] = px[i*4 + 0]; rgba[i*4 + 1] = px[i*4 + 1]; rgba[i*4 + 2] = px[i*4 + 2]; rgba[i*4 + 3] = px[i*4 + 3];
    } else if (ch == 3) {
      rgba[i*4 + 0] = px[i*3 + 0]; rgba[i*4 + 1] = px[i*3 + 1]; rgba[i*4 + 2] = px[i*3 + 2]; rgba[i*4 + 3] = 255;
    } else if (ch == 1) {
      rgba[i*4 + 0] = px[i]; rgba[i*4 + 1] = px[i]; rgba[i*4 + 2] = px[i]; rgba[i*4 + 3] = 255;
    } else {
      rgba[i*4 + 0] = 0; rgba[i*4 + 1] = 0; rgba[i*4 + 2] = 0; rgba[i*4 + 3] = 255;
    }
  }
  free(px);
  int slot = -1;
  for (int i = 0; i < LEP_MAX_TEX; i++) {
    if (!g_tex[i].used) { slot = i; break; }
  }
  if (slot == -1) { free(rgba); return num_from_i64(0); }
  LEPTex *t = &g_tex[slot];
  t->used = 1; t->built = 0; t->w = (int)w; t->h = (int)h; t->ch = 4; t->px = rgba; t->img = 0;
  if (g_nvg) {
    t->img = nvgCreateImageRGBA(g_nvg, t->w, t->h, 0, t->px);
    t->built = (t->img != 0);
  }
  return num_from_i64(slot + 1);
}

static LEPVar native_tex_draw(LEPVar *args, uint8_t argc) {
  if (argc < 5) return LEP_ZERO;
  long tex_id = native_arg_long(args[0]);
  float x = (float)native_arg_double(args[1]), y = (float)native_arg_double(args[2]);
  float w = (float)native_arg_double(args[3]), h = (float)native_arg_double(args[4]);
  lg_push(LG_IMAGE, x, y, w, h, NULL);
  g_cmds[g_cmd_n - 1].tex = (int)tex_id;
  return LEP_ZERO;
}

static LEPVar native_tex_free(LEPVar *args, uint8_t argc) {
  if (argc < 1) return LEP_ZERO;
  long tex_id = native_arg_long(args[0]) - 1;
  if (tex_id >= 0 && tex_id < LEP_MAX_TEX) {
    LEPTex *t = &g_tex[tex_id];
    if (t->used) {
      if (t->built && g_nvg) nvgDeleteImage(g_nvg, t->img);
      free(t->px);
      memset(t, 0, sizeof(*t));
    }
  }
  return LEP_ZERO;
}

static LEPVar native_win_open(LEPVar *args, uint8_t argc) { return native_sokol_init(args, argc); }
static LEPVar native_win_close(LEPVar *args, uint8_t argc) { return native_sokol_shutdown(args, argc); }
static LEPVar native_win_color(LEPVar *args, uint8_t argc) { return native_sokol_color(args, argc); }
static LEPVar native_win_clear(LEPVar *args, uint8_t argc) { return native_sokol_clear(args, argc); }
static LEPVar native_win_rect(LEPVar *args, uint8_t argc) {
  if (argc < 4) return LEP_ZERO;
  lg_push(LG_RECT, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), (float)native_arg_double(args[2]), (float)native_arg_double(args[3]), NULL);
  return LEP_ZERO;
}
static LEPVar native_win_line(LEPVar *args, uint8_t argc) {
  if (argc < 4) return LEP_ZERO;
  lg_push(LG_LINE, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), (float)native_arg_double(args[2]), (float)native_arg_double(args[3]), NULL);
  return LEP_ZERO;
}
static LEPVar native_win_circle(LEPVar *args, uint8_t argc) {
  if (argc < 3) return LEP_ZERO;
  lg_push(LG_CIRCLE, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), (float)native_arg_double(args[2]), 0, NULL);
  return LEP_ZERO;
}
static LEPVar native_win_text(LEPVar *args, uint8_t argc) {
  if (argc < 3) return LEP_ZERO;
  const char *txt = native_arg_str(args[2]);
  float size = argc >= 4 ? (float)native_arg_double(args[3]) : 16.0f;
  lg_push(LG_TEXT, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), 0, size, txt);
  return LEP_ZERO;
}
static LEPVar native_win_show(LEPVar *args, uint8_t argc) { return native_sokol_show(args, argc); }
static LEPVar native_win_poll(LEPVar *args, uint8_t argc) { return native_sokol_poll(args, argc); }
static LEPVar native_win_key(LEPVar *args, uint8_t argc) { return native_sokol_key(args, argc); }
static LEPVar native_win_mouse(LEPVar *args, uint8_t argc) { return native_sokol_mouse(args, argc); }
static LEPVar native_win_mousedown(LEPVar *args, uint8_t argc) { return native_sokol_mousedown(args, argc); }
static LEPVar native_win_time(LEPVar *args, uint8_t argc) { return native_sokol_time(args, argc); }
static LEPVar native_win_delay(LEPVar *args, uint8_t argc) { return native_sokol_delay(args, argc); }

static LEPVar native_nvg_create(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (!g_nvg) g_nvg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
  return var_bool(g_nvg != NULL);
}
static LEPVar native_nvg_cancel_frame(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (g_nvg) nvgCancelFrame(g_nvg);
  return LEP_ZERO;
}
static LEPVar native_nvg_begin_frame(LEPVar *args, uint8_t argc) {
  if (argc < 2) return LEP_ZERO;
  if (g_nvg) nvgBeginFrame(g_nvg, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), 1.0f);
  return LEP_ZERO;
}
static LEPVar native_nvg_end_frame(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (g_nvg) nvgEndFrame(g_nvg);
  return LEP_ZERO;
}
static LEPVar native_nvg_rect(LEPVar *args, uint8_t argc) {
  if (argc < 4 || !g_nvg) return LEP_ZERO;
  nvgBeginPath(g_nvg);
  nvgRect(g_nvg, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), (float)native_arg_double(args[2]), (float)native_arg_double(args[3]));
  nvgFill(g_nvg);
  return LEP_ZERO;
}
static LEPVar native_nvg_line(LEPVar *args, uint8_t argc) {
  if (argc < 4 || !g_nvg) return LEP_ZERO;
  nvgBeginPath(g_nvg);
  nvgMoveTo(g_nvg, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]));
  nvgLineTo(g_nvg, (float)native_arg_double(args[2]), (float)native_arg_double(args[3]));
  nvgStroke(g_nvg);
  return LEP_ZERO;
}
static LEPVar native_nvg_circle(LEPVar *args, uint8_t argc) {
  if (argc < 3 || !g_nvg) return LEP_ZERO;
  nvgBeginPath(g_nvg);
  nvgCircle(g_nvg, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), (float)native_arg_double(args[2]));
  nvgFill(g_nvg);
  return LEP_ZERO;
}
static LEPVar native_nvg_text(LEPVar *args, uint8_t argc) {
  if (argc < 3 || !g_nvg) return LEP_ZERO;
  const char *txt = native_arg_str(args[2]);
  if (txt) {
    nvgFontSize(g_nvg, argc >= 4 ? (float)native_arg_double(args[3]) : 16.0f);
    nvgFontFace(g_nvg, "sans");
    nvgTextAlign(g_nvg, NVG_ALIGN_LEFT | NVG_ALIGN_TOP);
    nvgText(g_nvg, (float)native_arg_double(args[0]), (float)native_arg_double(args[1]), txt, NULL);
  }
  return LEP_ZERO;
}
static LEPVar native_nvg_fill_color(LEPVar *args, uint8_t argc) {
  if (argc < 3) return LEP_ZERO;
  g_fill_r = (float)native_arg_double(args[0]);
  g_fill_g = (float)native_arg_double(args[1]);
  g_fill_b = (float)native_arg_double(args[2]);
  g_fill_a = argc >= 4 ? (float)native_arg_double(args[3]) : 1.0f;
  lg_push(LG_FILLCOLOR, 0, 0, 0, 0, NULL);
  if (g_nvg) nvgFillColor(g_nvg, nvgRGBAf(g_fill_r, g_fill_g, g_fill_b, g_fill_a));
  return LEP_ZERO;
}
static LEPVar native_nvg_stroke_color(LEPVar *args, uint8_t argc) {
  if (argc < 3) return LEP_ZERO;
  g_fill_r = (float)native_arg_double(args[0]);
  g_fill_g = (float)native_arg_double(args[1]);
  g_fill_b = (float)native_arg_double(args[2]);
  g_fill_a = argc >= 4 ? (float)native_arg_double(args[3]) : 1.0f;
  lg_push(LG_STROKECOLOR, 0, 0, 0, 0, NULL);
  if (g_nvg) nvgStrokeColor(g_nvg, nvgRGBAf(g_fill_r, g_fill_g, g_fill_b, g_fill_a));
  return LEP_ZERO;
}
static LEPVar native_nvg_stroke_width(LEPVar *args, uint8_t argc) {
  if (argc < 1) return LEP_ZERO;
  float w = (float)native_arg_double(args[0]);
  lg_push(LG_STROKEW, w, 0, 0, 0, NULL);
  if (g_nvg) nvgStrokeWidth(g_nvg, w);
  return LEP_ZERO;
}
static LEPVar native_nvg_fill(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (g_nvg) nvgFill(g_nvg);
  return LEP_ZERO;
}
static LEPVar native_nvg_stroke(LEPVar *args, uint8_t argc) {
  (void)args; (void)argc;
  if (g_nvg) nvgStroke(g_nvg);
  return LEP_ZERO;
}
#else
STUB_FALSE(native_sokol_init)
STUB_FALSE(native_sokol_shutdown)
STUB_LEP(native_sokol_color)
STUB_LEP(native_sokol_clear)
STUB_FALSE(native_sokol_show)
static LEPVar native_sokol_poll(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_string(""); }
STUB_FALSE(native_sokol_key)
static LEPVar native_sokol_mouse(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return ret_xy(0,0); }
STUB_FALSE(native_sokol_mousedown)
static LEPVar native_sokol_time(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return num_from_double(0); }
STUB_LEP(native_sokol_delay)
STUB_0(native_tex_load)
STUB_LEP(native_tex_draw)
STUB_LEP(native_tex_free)
STUB_FALSE(native_win_open)
STUB_FALSE(native_win_close)
STUB_LEP(native_win_color)
STUB_LEP(native_win_clear)
STUB_LEP(native_win_rect)
STUB_LEP(native_win_line)
STUB_LEP(native_win_circle)
STUB_LEP(native_win_text)
STUB_FALSE(native_win_show)
static LEPVar native_win_poll(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return var_string(""); }
STUB_FALSE(native_win_key)
static LEPVar native_win_mouse(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return ret_xy(0,0); }
STUB_FALSE(native_win_mousedown)
static LEPVar native_win_time(LEPVar *args, uint8_t argc) { (void)args; (void)argc; return num_from_double(0); }
STUB_LEP(native_win_delay)
STUB_FALSE(native_nvg_create)
STUB_LEP(native_nvg_cancel_frame)
STUB_LEP(native_nvg_begin_frame)
STUB_LEP(native_nvg_end_frame)
STUB_LEP(native_nvg_rect)
STUB_LEP(native_nvg_line)
STUB_LEP(native_nvg_circle)
STUB_LEP(native_nvg_text)
STUB_LEP(native_nvg_fill_color)
STUB_LEP(native_nvg_stroke_color)
STUB_LEP(native_nvg_stroke_width)
STUB_LEP(native_nvg_fill)
STUB_LEP(native_nvg_stroke)
#endif
