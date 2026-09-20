/* Light Environment Processing VM (LEP-VM) */
/* Funcionamiento smart_heap: Arreglo dinamico indexado, no una pila */
#pragma once
#include "Calc.c"
#include "Smart_heap.c"
#include "Functions.c"
#include "Typecast_and_read.c"
#include "termcolor-c.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_FRAMES 128
#define MAX_TRY_FRAMES 64

typedef struct {
  size_t return_ip;
  LEPVar locals[256];
} CallFrame;

typedef struct {
  size_t catch_ip;
  size_t stack_size;
  size_t frame_count;
} TryFrame;

typedef struct {
  const uint8_t *bytecode;
  size_t bytecode_size;
  size_t ip;
  CallFrame frames[MAX_FRAMES];
  size_t frame_count;
  TryFrame try_frames[MAX_TRY_FRAMES];
  size_t try_frame_count;
} VM;

typedef enum {
  OP_WRITE,
  OP_READ,
  OP_EXPAND,
  OP_COLAPSE,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_CAST,
  OP_LOAD_VAR,  // [uint16_t index]
  OP_STORE_VAR, // [uint16_t index]
  OP_PRINT,
  OP_JUMP,          // [int16_t offset]
  OP_JUMP_IF_FALSE, // [int16_t offset]
  OP_JUMP_IF_TRUE,  // [int16_t offset]
  OP_HALT,
  OP_CALL,
  OP_CALL_NATIVE,
  // --- Comparacion (writeBOOL) ---
  OP_EQ,
  OP_NEQ,
  OP_LT,
  OP_GT,
  OP_LTE,
  OP_GTE,
  // --- Logicos ---
  OP_AND,
  OP_OR,
  OP_NOT,
  // --- Bitwise ---
  OP_BIT_AND,
  OP_BIT_OR,
  OP_BIT_NOT,
  OP_BIT_XOR,
  OP_BIT_SHL, 
  OP_BIT_SHR,
  // --- Incremento/Decremento ---
  OP_INC,
  OP_DEC,
  OP_RETURN,
  OP_CALL_VAR,
  // --- Arrays ---
  OP_ARRAY_NEW,  // [uint16_t count]
  OP_ARRAY_GET,  
  OP_ARRAY_SET,  
  // --- Packages ---
  OP_PKG_NEW,    // [uint16_t field_count]
  OP_PKG_GET,    // [uint16_t name_len] [chars...]
  OP_PKG_SET,    // [uint16_t name_len] [chars...]
  // --- Try/Catch ---
  OP_TRY_SETUP,  // [int16_t catch_offset]
  OP_TRY_END,    
  OP_THROW,      
  OP_STORE_LOCAL, // [uint16_t index]
  OP_LOAD_LOCAL,  // [uint16_t index]
  OP_CALL_METHOD, // [uint8_t argc]
  OP_THIS_GET,    // [uint16_t name_len] [chars...]
  OP_THIS_SET,    // [uint16_t name_len] [chars...]
} PaxoOpcode;

void vm_init(VM *vm, const uint8_t *bytecode, size_t bytecode_size) {
  vm->bytecode = bytecode;
  vm->bytecode_size = bytecode_size;
  vm->ip = 0;
  vm->frame_count = 1; // Frame 0 es el entorno global inicial
  vm->try_frame_count = 0;
  memset(vm->frames, 0, sizeof(vm->frames));
  memset(vm->try_frames, 0, sizeof(vm->try_frames));
}

void vm_error(VM *vm, const char *msg) {
  text_red(stderr);
  fprintf(stderr, "[LEP-VM Error en IP %zu]: %s \n", vm->ip, msg);
  reset_colors(stderr);
}

static inline uint8_t read_u8(VM *vm) {
    return vm->bytecode[vm->ip++];
}

// Helpers seguros para lectura sin problemas de alineacion
static inline uint16_t read_u16(VM *vm) {
  uint16_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(uint16_t));
  vm->ip += sizeof(uint16_t);
  return val;
}

static inline int16_t read_i16(VM *vm) {
    // Si ya tienes un helper para leer 1 byte y avanzar vm->ip:
    uint16_t low = (uint16_t)read_u8(vm);
    uint16_t high = (uint16_t)read_u8(vm);
    
    return (int16_t)(low | (high << 8));
}

static inline uint32_t read_u32(VM *vm) {
  uint32_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(uint32_t));
  vm->ip += sizeof(uint32_t);
  return val;
}

static inline uint64_t read_u64(VM *vm) {
  uint64_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(uint64_t));
  vm->ip += sizeof(uint64_t);
  return val;
}

/* Despachador de funciones nativas */
static LEPVar lep_call_native(uint16_t id, LEPVar *args, uint8_t argc) {
  typedef LEPVar (*NativeFn)(LEPVar *, uint8_t);
  static const NativeFn table[NATIVE_ID_COUNT] = {
    [NATIVE_PRINT]            = native_print,
    [NATIVE_PRINTLN]          = native_println,
    [NATIVE_TYPEOF]           = native_typeof,
    [NATIVE_SET_COLOR_TEXT]   = native_set_text_color,
    [NATIVE_SET_TYPE_TEXT]    = native_set_text_type,
    [NATIVE_SET_COLOR_BACK]   = native_set_bg_color,
    [NATIVE_RESET_COLOR]      = native_reset_color,
    [NATIVE_SCAN]             = native_scan,
    [NATIVE_ARRAY_LEN]        = native_array_len,
    [NATIVE_ARRAY_PUSH]       = native_array_push,
    [NATIVE_INIT_WINDOW]      = native_init_window,
    [NATIVE_CLEAR_SCREEN]     = native_clear_screen,
    [NATIVE_DRAW_RECT]        = native_draw_rect,
    [NATIVE_FILE_READ]        = native_file_read,
    [NATIVE_FILE_WRITE]       = native_file_write,
    [NATIVE_FILE_APPEND]      = native_file_append,
    [NATIVE_FILE_EXISTS]      = native_file_exists,
    [NATIVE_FILE_DELETE]      = native_file_delete,
    [NATIVE_IMG_LOAD]         = native_img_load,
    [NATIVE_IMG_INFO]         = native_img_info,
    [NATIVE_IMG_SAVE_PNG]     = native_img_save_png,
    [NATIVE_IMG_SAVE_JPG]     = native_img_save_jpg,
    [NATIVE_IMG_SAVE_BMP]     = native_img_save_bmp,
    [NATIVE_IMG_RESIZE]       = native_img_resize,
    [NATIVE_FONT_LOAD]        = native_font_load,
    [NATIVE_FONT_GLYPH]       = native_font_glyph,
    [NATIVE_FONT_METRICS]     = native_font_metrics,
    [NATIVE_FONT_FREE]        = native_font_free,
    [NATIVE_AUDIO_INIT]       = native_audio_init,
    [NATIVE_AUDIO_QUIT]       = native_audio_quit,
    [NATIVE_AUDIO_PLAY]       = native_audio_play,
    [NATIVE_AUDIO_PAUSE]      = native_audio_pause,
    [NATIVE_AUDIO_RESUME]     = native_audio_resume,
    [NATIVE_AUDIO_STOP]       = native_audio_stop,
    [NATIVE_AUDIO_VOLUME]     = native_audio_volume,
    [NATIVE_AUDIO_PLAYING]    = native_audio_playing,
    [NATIVE_PHYS_SPACE]       = native_phys_space,
    [NATIVE_PHYS_GRAVITY]     = native_phys_gravity,
    [NATIVE_PHYS_STEP]        = native_phys_step,
    [NATIVE_PHYS_BODY]        = native_phys_body,
    [NATIVE_PHYS_BODY_STATIC] = native_phys_body_static,
    [NATIVE_PHYS_POS]         = native_phys_pos,
    [NATIVE_PHYS_VEL]         = native_phys_vel,
    [NATIVE_PHYS_SET_POS]     = native_phys_set_pos,
    [NATIVE_PHYS_SET_VEL]     = native_phys_set_vel,
    [NATIVE_PHYS_ANGLE]       = native_phys_angle,
    [NATIVE_PHYS_SET_ANGLE]   = native_phys_set_angle,
    [NATIVE_PHYS_FORCE]       = native_phys_force,
    [NATIVE_PHYS_IMPULSE]     = native_phys_impulse,
    [NATIVE_PHYS_CIRCLE]      = native_phys_circle,
    [NATIVE_PHYS_BOX]         = native_phys_box,
    [NATIVE_PHYS_SEGMENT]     = native_phys_segment,
    [NATIVE_PHYS_ELASTICITY]  = native_phys_elasticity,
    [NATIVE_PHYS_FRICTION]    = native_phys_friction,
    [NATIVE_PHYS_COLLIDE]     = native_phys_collide,
    [NATIVE_PHYS_FREE_SHAPE]  = native_phys_free_shape,
    [NATIVE_PHYS_FREE_BODY]   = native_phys_free_body,
    [NATIVE_PHYS_FREE_SPACE]  = native_phys_free_space,
    [NATIVE_WIN_OPEN]         = native_win_open,
    [NATIVE_WIN_CLOSE]        = native_win_close,
    [NATIVE_WIN_COLOR]        = native_win_color,
    [NATIVE_WIN_CLEAR]        = native_win_clear,
    [NATIVE_WIN_RECT]         = native_win_rect,
    [NATIVE_WIN_LINE]         = native_win_line,
    [NATIVE_WIN_CIRCLE]       = native_win_circle,
    [NATIVE_WIN_TEXT]         = native_win_text,
    [NATIVE_TEX_LOAD]         = native_tex_load,
    [NATIVE_TEX_DRAW]         = native_tex_draw,
    [NATIVE_TEX_FREE]         = native_tex_free,
    [NATIVE_WIN_SHOW]         = native_win_show,
    [NATIVE_WIN_POLL]         = native_win_poll,
    [NATIVE_WIN_KEY]          = native_win_key,
    [NATIVE_WIN_MOUSE]        = native_win_mouse,
    [NATIVE_WIN_MOUSEDOWN]    = native_win_mousedown,
    [NATIVE_WIN_TIME]         = native_win_time,
    [NATIVE_WIN_DELAY]        = native_win_delay,
    [NATIVE_SOKOL_INIT]       = native_sokol_init,
    [NATIVE_SOKOL_SHUTDOWN]   = native_sokol_shutdown,
    [NATIVE_SOKOL_CLEAR]      = native_sokol_clear,
    [NATIVE_SOKOL_COLOR]      = native_sokol_color,
    [NATIVE_SOKOL_SHOW]       = native_sokol_show,
    [NATIVE_SOKOL_POLL]       = native_sokol_poll,
    [NATIVE_SOKOL_KEY]        = native_sokol_key,
    [NATIVE_SOKOL_MOUSE]      = native_sokol_mouse,
    [NATIVE_SOKOL_MOUSEDOWN]  = native_sokol_mousedown,
    [NATIVE_SOKOL_TIME]       = native_sokol_time,
    [NATIVE_SOKOL_DELAY]      = native_sokol_delay,
    [NATIVE_NVG_CREATE]       = native_nvg_create,
    [NATIVE_NVG_CANCEL_FRAME] = native_nvg_cancel_frame,
    [NATIVE_NVG_BEGIN_FRAME]  = native_nvg_begin_frame,
    [NATIVE_NVG_END_FRAME]    = native_nvg_end_frame,
    [NATIVE_NVG_RECT]         = native_nvg_rect,
    [NATIVE_NVG_LINE]         = native_nvg_line,
    [NATIVE_NVG_CIRCLE]       = native_nvg_circle,
    [NATIVE_NVG_TEXT]         = native_nvg_text,
    [NATIVE_NVG_FILL_COLOR]   = native_nvg_fill_color,
    [NATIVE_NVG_STROKE_COLOR] = native_nvg_stroke_color,
    [NATIVE_NVG_STROKE_WIDTH] = native_nvg_stroke_width,
    [NATIVE_NVG_FILL]         = native_nvg_fill,
    [NATIVE_NVG_STROKE]       = native_nvg_stroke,
  };
  if (id >= NATIVE_ID_COUNT || !table[id]) return LEP_ZERO;
  return table[id](args, argc);
}

#define FRAME (vm->frames[vm->frame_count - 1])

#define AS_BOOL(v) lep_truthy(v)

/* Helpers rapidos para leer/escribir registros en el smart_heap */
static inline LEPVar heap_get(Smart_heap *heap, size_t idx) {
  LEPVar *v = heap_read(heap, idx);
  return v ? *v : LEP_ZERO;
}

static inline void heap_set(Smart_heap *heap, size_t idx, LEPVar val) {
  heap_reserve(heap, idx + 1);
  heap_write(heap, idx, val);
}


static inline LEPVar lep_add(LEPVar a, LEPVar b) {
  if (a.type==STRING && b.type==STRING) {
    const char *sa=(const char*)var_string_get(a), *sb=(const char*)var_string_get(b);
    size_t na=sa?strlen(sa):0, nb=sb?strlen(sb):0; char *s=malloc(na+nb+1); if(!s)return LEP_ZERO;
    if(na)memcpy(s,sa,na); if(nb)memcpy(s+na,sb,nb); s[na+nb]='\0'; return var_string((const char8_t*)s);
  }
  if (a.type==INT && b.type==INT) return var_int(a.payload.integer+b.payload.integer);
  if (a.type==UINT && b.type==UINT) return var_uint(a.payload.uinteger+b.payload.uinteger);
  if (var_is_number(a) && var_is_number(b)) return var_fp64((double)(var_to_ld(a)+var_to_ld(b)));
  if (a.type==COM && b.type==COM) return var_com64(a.payload.com64+b.payload.com64);
  if (a.type==SCOM && b.type==SCOM) return var_com16(a.payload.com16+b.payload.com16);
  if (a.type==STRING && b.type==STRING) return var_string(strcat(a.payload.utf8, b.payload.utf8));
  if (a.type==STRING && b.type==CHAR) return var_string(strcat(a.payload.utf8, readchar(b.payload.chara)));
  return LEP_ZERO;
}
static inline LEPVar lep_sub(LEPVar a, LEPVar b) {
  if(a.type==INT&&b.type==INT)return var_int(a.payload.integer-b.payload.integer);
  if(a.type==UINT&&b.type==UINT)return var_uint(a.payload.uinteger-b.payload.uinteger);
  if(var_is_number(a)&&var_is_number(b))return var_fp64((double)(var_to_ld(a)-var_to_ld(b)));
  if(a.type==COM&&b.type==COM)return var_com64(a.payload.com64-b.payload.com64);
  if(a.type==SCOM&&b.type==SCOM)return var_com16(a.payload.com16-b.payload.com16);
  return LEP_ZERO;
}
static inline LEPVar lep_mul(LEPVar a, LEPVar b) {
  if(a.type==INT&&b.type==INT)return var_int(a.payload.integer*b.payload.integer);
  if(a.type==UINT&&b.type==UINT)return var_uint(a.payload.uinteger*b.payload.uinteger);
  if(var_is_number(a)&&var_is_number(b))return var_fp64((double)(var_to_ld(a)*var_to_ld(b)));
  if(a.type==COM&&b.type==COM)return var_com64(a.payload.com64*b.payload.com64);
  if(a.type==SCOM&&b.type==SCOM)return var_com16(a.payload.com16*b.payload.com16);
  return LEP_ZERO;
}
static inline LEPVar lep_div(LEPVar a, LEPVar b) {
  long double d=var_to_ld(b); if(var_is_number(a)&&var_is_number(b)){if(d==0)return LEP_ZERO; return var_fp64((double)(var_to_ld(a)/d));}
  if(a.type==COM&&b.type==COM)return var_com64(a.payload.com64/b.payload.com64);
  if(a.type==SCOM&&b.type==SCOM)return var_com16(a.payload.com16/b.payload.com16);
  return LEP_ZERO;
}
static inline bool lep_equal(LEPVar a, LEPVar b){
  if(a.type!=b.type){ if(var_is_number(a)&&var_is_number(b))return var_to_ld(a)==var_to_ld(b); return false; }
  switch(a.type){case INT:return a.payload.integer==b.payload.integer;case UINT:return a.payload.uinteger==b.payload.uinteger;case CHAR:return a.payload.chara==b.payload.chara;case BOOL:return a.payload.boolean==b.payload.boolean;case TRIT:return a.payload.trit==b.payload.trit;case SFP:return a.payload.fp16==b.payload.fp16;case FP:return a.payload.fp64==b.payload.fp64;case DEC:return a.payload.dec64==b.payload.dec64;case STRING:return strcmp((const char*)a.payload.utf8,(const char*)b.payload.utf8)==0;case POINT:return a.payload.point.ptr==b.payload.point.ptr;case FUNC:return a.payload.function.ip==b.payload.function.ip&&a.payload.function.param_count==b.payload.function.param_count;default:return a.payload.ptr==b.payload.ptr;}
}

void vm_run(VM *vm, Smart_heap *stack) {
  bool running = true;

  while (running) {
    if (vm->ip >= vm->bytecode_size) {
      vm_error(vm, "IP fuera de los limites del bytecode");
      break;
    }
    uint8_t op = vm->bytecode[vm->ip++];

    switch ((PaxoOpcode)op) {

    case OP_WRITE: {
      uint8_t t = vm->bytecode[vm->ip++];
      uint16_t target_reg = read_u16(vm);
      LEPVar v = LEP_ZERO;
      switch ((LEPType)t) {
        case INT: { int64_t x=(int64_t)read_u64(vm); memcpy(&x, vm->bytecode+vm->ip-8, 8); v=var_int(x); break; }
        case UINT: v=var_uint(read_u64(vm)); break;
        case BOOL: v=var_bool(vm->bytecode[vm->ip++]!=0); break;
        case TRIT: v=var_trit(vm->bytecode[vm->ip++]&3u); break;
        case CHAR: v=var_char(read_u32(vm)); break;
        case COLOR: { uint32_t c=read_u32(vm); v=var_color(0,c); break; }
        case SFP: { uint16_t raw=read_u16(vm); _Float16 x; memcpy(&x,&raw,2); v=var_fp16(x); break; }
        case FP: { uint64_t raw=read_u64(vm); double x; memcpy(&x,&raw,8); v=var_fp64(x); break; }
        case STRING: { uint16_t len=read_u16(vm); char *s=malloc((size_t)len+1); memcpy(s,vm->bytecode+vm->ip,len); s[len]='\0'; vm->ip+=len; v=var_string((const char8_t*)s); break; }
        case POINT: { uint32_t p=read_u32(vm); v=var_point((void*)(uintptr_t)p); break; }
        case FUNC: { uint32_t ip=read_u32(vm); uint8_t pc=read_u8(vm); v=var_func(ip,pc); break; }
        default: vm_error(vm,"OP_WRITE: tipo desconocido"); running=false; break;
      }
      heap_set(stack,target_reg,v);
      break;
    }

    case OP_READ: {
      uint16_t src_reg = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      heap_set(stack, dest_reg, heap_get(stack, src_reg));
      break;
    }

    case OP_EXPAND: {
      uint16_t src_reg = read_u16(vm);
      uint16_t base_dest_reg = read_u16(vm);
      LEPVar arr = heap_get(stack, src_reg);
      if (arr.type == ARRAY) {
        LEPArray *a = var_array_get(arr);
        if (a) {
          for (size_t i = 0; i < a->len; i++) {
            heap_set(stack, base_dest_reg + i, a->items[i]);
          }
        }
      }
      break;
    }

    case OP_COLAPSE: {
      uint16_t count = read_u16(vm);
      uint16_t src_base_reg = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      LEPArray *arr = malloc(sizeof(LEPArray));
      arr->capacity = count ? count : 1;
      arr->len = count;
      arr->items = malloc(sizeof(LEPVar) * arr->capacity);
      for (uint16_t i = 0; i < count; i++) {
        arr->items[i] = heap_get(stack, src_base_reg + i);
      }
      heap_set(stack, dest_reg, var_array(arr));
      break;
    }

    case OP_ADD: {
      uint16_t r_a=read_u16(vm), r_b=read_u16(vm), r_dst=read_u16(vm);
      LEPVar result=lep_add(heap_get(stack,r_a),heap_get(stack,r_b));
      if(result.type==INT && result.payload.integer==0 && !(heap_get(stack,r_a).type==INT && heap_get(stack,r_b).type==INT && True)) {}
      heap_set(stack,r_dst,result);
      break;
    }

    case OP_SUB: {
      uint16_t r_a=read_u16(vm), r_b=read_u16(vm), r_dst=read_u16(vm);
      LEPVar result=lep_sub(heap_get(stack,r_a),heap_get(stack,r_b));
      if(result.type==INT && result.payload.integer==0 && !(heap_get(stack,r_a).type==INT && heap_get(stack,r_b).type==INT && False)) {}
      heap_set(stack,r_dst,result);
      break;
    }

    case OP_MUL: {
      uint16_t r_a=read_u16(vm), r_b=read_u16(vm), r_dst=read_u16(vm);
      LEPVar result=lep_mul(heap_get(stack,r_a),heap_get(stack,r_b));
      if(result.type==INT && result.payload.integer==0 && !(heap_get(stack,r_a).type==INT && heap_get(stack,r_b).type==INT && False)) {}
      heap_set(stack,r_dst,result);
      break;
    }

    case OP_DIV: {
      uint16_t r_a=read_u16(vm), r_b=read_u16(vm), r_dst=read_u16(vm);
      LEPVar result=lep_div(heap_get(stack,r_a),heap_get(stack,r_b));
      if(result.type==INT && result.payload.integer==0 && !(heap_get(stack,r_a).type==INT && heap_get(stack,r_b).type==INT && False)) {}
      heap_set(stack,r_dst,result);
      break;
    }

    case OP_CAST: {
      uint8_t target=read_u8(vm); uint16_t r_src=read_u16(vm), r_dst=read_u16(vm); LEPVar v=heap_get(stack,r_src), result=v;
      switch((LEPType)target){
        case INT: result=var_int((int64_t)var_to_ld(v)); break;
        case UINT: result=var_uint((uint64_t)var_to_ld(v)); break;
        case CHAR: result=var_char((char32_t)var_to_ld(v)); break;
        case BOOL: result=var_bool(lep_truthy(v)); break;
        case TRIT: result=var_trit(lep_truthy(v)?2:0); break;
        case FP: result=var_fp64((double)var_to_ld(v)); break;
        case SFP: result=var_fp16((_Float16)var_to_ld(v)); break;
        default: break;
      }
      heap_set(stack,r_dst,result); break;
    }

    case OP_LOAD_VAR: {
      uint16_t global_idx = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      heap_set(stack, dest_reg, vm->frames[0].locals[global_idx]);
      break;
    }

    case OP_STORE_VAR: {
    uint16_t src_reg = read_u16(vm);
    uint16_t global_idx = read_u16(vm);

    LEPVar v = heap_get(stack, src_reg);

    /*fprintf(stderr,
            "STORE_VAR global=%u src=%u type=%u",
            global_idx, src_reg, v.type);

    if (v.type == POINT) {
        fprintf(stderr,
                " sub=%u id=%u",
                v.type,
                var_func_id(v));
    }*/

    //fprintf(stderr, "\n");

    vm->frames[0].locals[global_idx] = v;
    break;
}

    case OP_PRINT: {
      uint16_t src_reg = read_u16(vm);
      print_var_full(heap_get(stack, src_reg));
      putchar('\n');
      break;
    }

    case OP_JUMP: {
    int16_t off = read_i16(vm);
    ssize_t target_ip = (ssize_t)vm->ip + off;
    if (target_ip >= 0 && target_ip < (ssize_t)vm->bytecode_size) {
        vm->ip = (size_t)target_ip;
    } else {
        vm_error(vm, "OP_JUMP target out of bounds");
        running = false;
    }
    break;
}

case OP_JUMP_IF_FALSE: {
    uint16_t cond_reg = read_u16(vm);
    int16_t off = read_i16(vm);
    if (!AS_BOOL(heap_get(stack, cond_reg))) {
        ssize_t target_ip = (ssize_t)vm->ip + off;
        if (target_ip >= 0 && target_ip < (ssize_t)vm->bytecode_size) {
            vm->ip = (size_t)target_ip;
        } else {
            vm_error(vm, "OP_JUMP_IF_FALSE target out of bounds");
            running = false;
        }
    }
    break;
}

case OP_JUMP_IF_TRUE: {
    uint16_t cond_reg = read_u16(vm);
    int16_t off = read_i16(vm);
    if (AS_BOOL(heap_get(stack, cond_reg))) {
        ssize_t target_ip = (ssize_t)vm->ip + off;
        if (target_ip >= 0 && target_ip < (ssize_t)vm->bytecode_size) {
            vm->ip = (size_t)target_ip;
        } else {
            vm_error(vm, "OP_JUMP_IF_TRUE target out of bounds");
            running = false;
        }
    }
    break;
}

    case OP_HALT:
      running = false;
      break;

    case OP_CALL: {
      uint16_t func_reg = read_u16(vm);
      uint8_t argc = vm->bytecode[vm->ip++];
      uint16_t args_base_reg = read_u16(vm);
      LEPVar func = heap_get(stack, func_reg);
     /* old reference debug removed */
      if (func.type != FUNC) {
        vm_error(vm, "OP_CALL: El registro no contiene una funcion valida");
        running = false;
        break;
      }
      CallFrame *frame = &vm->frames[vm->frame_count++];
      frame->return_ip = vm->ip;
      for (uint8_t i = 0; i < argc; i++) {
        frame->locals[i] = heap_get(stack, args_base_reg + i);
      }
      vm->ip = (size_t)var_func_id(func);
      break;
    }

    case OP_CALL_NATIVE: {
      uint16_t func_id = read_u16(vm);
      uint8_t argc = vm->bytecode[vm->ip++];
      uint16_t args_base_reg = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      LEPVar native_args[256];
      for (uint8_t i = 0; i < argc; i++) {
        native_args[i] = heap_get(stack, args_base_reg + i);
      }
      heap_set(stack, dest_reg, lep_call_native(func_id, native_args, argc));
      break;
    }

    case OP_EQ: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      LEPVar a = heap_get(stack, r_a);
      LEPVar b = heap_get(stack, r_b);
      bool eq;
      if (var_is_number(a) && var_is_number(b)) eq = var_to_ld(a) == var_to_ld(b);
      else if (a.type == BOOL && b.type == BOOL) eq = var_bool_get(a) == var_bool_get(b);
      else if (a.type == CHAR && b.type == CHAR) eq = var_char_get(a) == var_char_get(b);
      else if (a.type == TRIT && b.type == TRIT) eq = var_trit_get(a) == var_trit_get(b);
      else if (a.type == STRING && b.type == STRING)
        eq = strcmp(var_string_get(a), var_string_get(b)) == 0;
      else eq = lep_equal(a,b);
      heap_set(stack, r_dst, var_bool(eq));
      break;
    }

    case OP_NEQ: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      LEPVar a = heap_get(stack, r_a);
      LEPVar b = heap_get(stack, r_b);
      bool eq;
      if (var_is_number(a) && var_is_number(b)) eq = var_to_ld(a) == var_to_ld(b);
      else if (a.type == BOOL && b.type == BOOL) eq = var_bool_get(a) == var_bool_get(b);
      else if (a.type == CHAR && b.type == CHAR) eq = var_char_get(a) == var_char_get(b);
      else if (a.type == TRIT && b.type == TRIT) eq = var_trit_get(a) == var_trit_get(b);
      else if (a.type == STRING && b.type == STRING)
        eq = strcmp(var_string_get(a), var_string_get(b)) == 0;
      else eq = lep_equal(a,b);
      heap_set(stack, r_dst, var_bool(!eq));
      break;
    }

    case OP_LT: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(lep_cmp(heap_get(stack,r_a),heap_get(stack,r_b)) < 0));
      break;
    }

    case OP_GT: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(lep_cmp(heap_get(stack,r_a),heap_get(stack,r_b)) > 0));
      break;
    }

    case OP_LTE: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(lep_cmp(heap_get(stack,r_a),heap_get(stack,r_b)) <= 0));
      break;
    }

    case OP_GTE: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(lep_cmp(heap_get(stack,r_a),heap_get(stack,r_b)) >= 0));
      break;
    }

    case OP_AND: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(AS_BOOL(heap_get(stack, r_a)) && AS_BOOL(heap_get(stack, r_b))));
      break;
    }

    case OP_OR: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(AS_BOOL(heap_get(stack, r_a)) || AS_BOOL(heap_get(stack, r_b))));
      break;
    }

    case OP_NOT: {
      uint16_t r_src = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack, r_dst, var_bool(!AS_BOOL(heap_get(stack, r_src))));
      break;
    }

    case OP_BIT_AND: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack,r_dst,var_int((int64_t)var_to_ld(heap_get(stack,r_a)) & (int64_t)var_to_ld(heap_get(stack,r_b))));
      break;
    }

    case OP_BIT_OR: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack,r_dst,var_int((int64_t)var_to_ld(heap_get(stack,r_a)) | (int64_t)var_to_ld(heap_get(stack,r_b))));
      break;
    }

    case OP_BIT_XOR: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack,r_dst,var_int((int64_t)var_to_ld(heap_get(stack,r_a)) ^ (int64_t)var_to_ld(heap_get(stack,r_b))));
      break;
    }

    case OP_BIT_NOT: {
      uint16_t r_src = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      heap_set(stack,r_dst,var_int(~(int64_t)var_to_ld(heap_get(stack,r_src))));
      break;
    }

    case OP_BIT_SHL: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      uint64_t shift=(uint64_t)var_to_ld(heap_get(stack,r_b)); uint64_t res=shift<64?((uint64_t)var_to_ld(heap_get(stack,r_a))<<shift):0; heap_set(stack,r_dst,var_uint(res));
      break;
    }

    case OP_BIT_SHR: {
      uint16_t r_a = read_u16(vm);
      uint16_t r_b = read_u16(vm);
      uint16_t r_dst = read_u16(vm);
      uint64_t shift=(uint64_t)var_to_ld(heap_get(stack,r_b)); uint64_t res=shift<64?((uint64_t)var_to_ld(heap_get(stack,r_a))>>shift):0; heap_set(stack,r_dst,var_uint(res));
      break;
    }

    case OP_INC: {
      uint16_t r_reg = read_u16(vm);
      heap_set(stack,r_reg,lep_add(heap_get(stack,r_reg),var_int(1)));
      break;
    }

    case OP_DEC: {
      uint16_t r_reg = read_u16(vm);
      heap_set(stack,r_reg,lep_sub(heap_get(stack,r_reg),var_int(1)));
      break;
    }

    case OP_RETURN: {
      uint16_t ret_val_reg = read_u16(vm);
      uint16_t dest_caller_reg = read_u16(vm);
      LEPVar result = heap_get(stack, ret_val_reg);
      if (vm->frame_count <= 1) { running = false; break; }
      vm->frame_count--;
      vm->ip = vm->frames[vm->frame_count].return_ip;
      heap_set(stack, dest_caller_reg, result);
      break;
    }

    case OP_CALL_VAR: {
      uint16_t local_func_idx = read_u16(vm);
      uint8_t argc = vm->bytecode[vm->ip++];
      uint16_t args_base_reg = read_u16(vm);
      LEPVar func = FRAME.locals[local_func_idx];
      if (func.type != FUNC) {
        vm_error(vm, "OP_CALL_VAR: Variable local no es funcion");
        running = false;
        break;
      }
      CallFrame *frame = &vm->frames[vm->frame_count++];
      frame->return_ip = vm->ip;
      for (uint8_t i = 0; i < argc; i++) {
        frame->locals[i] = heap_get(stack, args_base_reg + i);
      }
      vm->ip = (size_t)var_func_id(func);
      break;
    }

    case OP_ARRAY_NEW: {
      uint16_t count = read_u16(vm);
      uint16_t src_base_reg = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      LEPArray *arr = malloc(sizeof(LEPArray));
      arr->capacity = count ? count : 1;
      arr->len = count;
      arr->items = malloc(sizeof(LEPVar) * arr->capacity);
      for (uint16_t i = 0; i < count; i++) {
        arr->items[i] = heap_get(stack, src_base_reg + i);
      }
      heap_set(stack, dest_reg, var_array(arr));
      break;
    }

    case OP_ARRAY_GET: {
      uint16_t arr_reg = read_u16(vm);
      uint16_t idx_reg = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      LEPVar arr_v = heap_get(stack, arr_reg);
      LEPVar idx_v = heap_get(stack, idx_reg);
      if (arr_v.type == ARRAY) {
        LEPArray *arr = var_array_get(arr_v);
        size_t idx = (var_is_integral(idx_v) ? (size_t)var_to_ld(idx_v) : 0);
        if (arr && idx < arr->len) heap_set(stack, dest_reg, arr->items[idx]);
      }
      break;
    }

    case OP_ARRAY_SET: {
      uint16_t arr_reg = read_u16(vm);
      uint16_t idx_reg = read_u16(vm);
      uint16_t val_reg = read_u16(vm);
      LEPVar arr_v = heap_get(stack, arr_reg);
      LEPVar idx_v = heap_get(stack, idx_reg);
      if (arr_v.type == ARRAY) {
        LEPArray *arr = var_array_get(arr_v);
        size_t idx = (var_is_integral(idx_v) ? (size_t)var_to_ld(idx_v) : 0);
        if (arr && idx < arr->len) arr->items[idx] = heap_get(stack, val_reg);
      }
      break;
    }

    case OP_PKG_NEW: {
      uint16_t field_count = read_u16(vm);
      uint16_t src_base_pairs = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      LEPPackageField *head = NULL;
      for (uint16_t i = 0; i < field_count; i++) {
        LEPVar name_v = heap_get(stack, src_base_pairs + (i * 2));
        LEPVar val_v = heap_get(stack, src_base_pairs + (i * 2) + 1);
        const char *key = (name_v.type == STRING) ? (const char*)var_string_get(name_v) : "?";
        LEPPackageField *f = malloc(sizeof(LEPPackageField));
        f->key = strdup(key);
        f->value = val_v;
        f->hidden = false;
        f->next = head;
        head = f;
      }
      heap_set(stack, dest_reg, var_pkg(head));
      break;
    }

    case OP_PKG_GET: {
      uint16_t nlen = read_u16(vm);
      char name[256];
      size_t clen = nlen < 255 ? nlen : 255;
      memcpy(name, vm->bytecode + vm->ip, clen); name[clen] = '\0';
      vm->ip += nlen;
      uint16_t pkg_reg = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      LEPVar pkg_v = heap_get(stack, pkg_reg);
      if (pkg_v.type == PACKAGE) {
        LEPVar result = LEP_ZERO;
        for (LEPPackageField *f = var_pkg_get(pkg_v); f; f = f->next) {
          if (strcmp(f->key, name) == 0) { result = f->value; break; }
        }
        heap_set(stack, dest_reg, result);
      }
      break;
    }

    case OP_PKG_SET: {
      uint16_t nlen = read_u16(vm);
      char name[256];
      size_t clen = nlen < 255 ? nlen : 255;
      memcpy(name, vm->bytecode + vm->ip, clen); name[clen] = '\0';
      vm->ip += nlen;
      uint16_t pkg_reg = read_u16(vm);
      uint16_t val_reg = read_u16(vm);
      LEPVar pkg_v = heap_get(stack, pkg_reg);
      if (pkg_v.type == PACKAGE) {
        bool found = false;
        for (LEPPackageField *f = var_pkg_get(pkg_v); f; f = f->next) {
          if (strcmp(f->key, name) == 0) { f->value = heap_get(stack, val_reg); found = true; break; }
        }
        if (!found) {
          LEPPackageField *nf = malloc(sizeof(LEPPackageField));
          nf->key = strdup(name);
          nf->value = heap_get(stack, val_reg);
          nf->hidden = false;
          nf->next = var_pkg_get(pkg_v);
          pkg_v.payload.ptr = nf;
        }
      }
      break;
    }

    case OP_TRY_SETUP: {
      int16_t off = read_i16(vm);
      if (vm->try_frame_count >= MAX_TRY_FRAMES) { vm_error(vm, "Try stack overflow"); break; }
      TryFrame *tf = &vm->try_frames[vm->try_frame_count++];
      tf->catch_ip = (size_t)((ssize_t)vm->ip + off);
      tf->stack_size = stack->amount; /* Guardamos el estado del Smart_heap indexado*/
      tf->frame_count = vm->frame_count;
      break;
    }

    case OP_TRY_END: {
      if (vm->try_frame_count > 0) vm->try_frame_count--;
      break;
    }

    case OP_THROW: {
      uint16_t err_reg = read_u16(vm);
      uint16_t dest_catch_reg = read_u16(vm);
      LEPVar err = heap_get(stack, err_reg);
      if (vm->try_frame_count == 0) {
        text_red(stderr); fprintf(stderr, "[lepvm] Excepcion no capturada"); reset_colors(stderr);
        if (err.type == STRING) fprintf(stderr, ": %s", var_string_get(err));
        fprintf(stderr, "\n"); running = false; break;
      }
      TryFrame *tf = &vm->try_frames[--vm->try_frame_count];
      stack->amount = (int)tf->stack_size;
      vm->frame_count = tf->frame_count;
      vm->ip = tf->catch_ip;
      heap_set(stack, dest_catch_reg, err);
      break;
    }

    case OP_STORE_LOCAL: {
      uint16_t src_reg = read_u16(vm);
      uint16_t local_idx = read_u16(vm);
      FRAME.locals[local_idx] = heap_get(stack, src_reg);
      break;
    }

    case OP_LOAD_LOCAL: {
      uint16_t local_idx = read_u16(vm);
      uint16_t dest_reg = read_u16(vm);
      heap_set(stack, dest_reg, FRAME.locals[local_idx]);
      break;
    }

    case OP_CALL_METHOD: {
      uint16_t func_reg = read_u16(vm);
      uint8_t argc = vm->bytecode[vm->ip++];
      uint16_t args_base_reg = read_u16(vm);
      uint16_t receiver_reg = read_u16(vm);
      LEPVar func = heap_get(stack, func_reg);
      LEPVar recv = heap_get(stack, receiver_reg);
      if (func.type != FUNC) {
        vm_error(vm, "OP_CALL_METHOD: No es funcion"); running = false; break;
      }
      CallFrame *frame = &vm->frames[vm->frame_count++];
      frame->return_ip = vm->ip;
      frame->locals[0] = recv; /* locals[0] es 'me'*/
      for (uint8_t i = 0; i < argc; i++) {
        frame->locals[i + 1] = heap_get(stack, args_base_reg + i);
      }
      vm->ip = (size_t)var_func_id(func);
      break;
    }

    case OP_THIS_GET: {
      uint16_t nlen = read_u16(vm);
      char name[256];
      size_t clen = nlen < 255 ? nlen : 255;
      memcpy(name, vm->bytecode + vm->ip, clen); name[clen] = '\0';
      vm->ip += nlen;
      uint16_t dest_reg = read_u16(vm);
      LEPVar self = FRAME.locals[0];
      if (self.type == PACKAGE) {
        LEPVar result = LEP_ZERO;
        for (LEPPackageField *f = var_pkg_get(self); f; f = f->next) {
          if (strcmp(f->key, name) == 0) { result = f->value; break; }
        }
        heap_set(stack, dest_reg, result);
      }
      break;
    }

    case OP_THIS_SET: {
      uint16_t nlen = read_u16(vm);
      char name[256];
      size_t clen = nlen < 255 ? nlen : 255;
      memcpy(name, vm->bytecode + vm->ip, clen); name[clen] = '\0';
      vm->ip += nlen;
      uint16_t val_reg = read_u16(vm);
      LEPVar self = FRAME.locals[0];
      if (self.type == PACKAGE) {
        bool found = false;
        for (LEPPackageField *f = var_pkg_get(self); f; f = f->next) {
          if (strcmp(f->key, name) == 0) { f->value = heap_get(stack, val_reg); found = true; break; }
        }
        if (!found) {
          LEPPackageField *nf = malloc(sizeof(LEPPackageField));
          nf->key = strdup(name);
          nf->value = heap_get(stack, val_reg);
          nf->hidden = true;
          nf->next = var_pkg_get(self);
          self.payload.ptr = nf;
        }
      }
      break;
    }

    default:
      vm_error(vm, "Opcode no implementado o desconocido");
      running = false;
      break;
    }
  }
}