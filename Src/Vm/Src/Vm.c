/* Light Environment Processing VM (LEP-VM) */
#pragma once
#include "Calc.c"
#include "Deque.c"
#include "Functions.c"
#include "Typecast_and_read.c"
#include "termcolor-c.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define MAX_FRAMES 128
#define MAX_TRY_FRAMES 64

typedef struct {
  size_t return_ip;
  PaxoVar locals[256];
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

// El tipo pdec (decimal empaquetado) está deprecado. Avisamos una sola vez por
// proceso cuando se ejecuta una operación sobre un valor pdec; el tipo sigue
// funcionando (retrocompatibilidad) pero recomienda usar int/var.
static int pdec_deprecation_warned = 0;
static void vm_warn_pdec(void) {
  if (pdec_deprecation_warned)
    return;
  pdec_deprecation_warned = 1;
  text_yellow(stderr);
  fprintf(stderr, "[lepvm aviso]");
  reset_colors(stderr);
  fprintf(stderr, " el tipo 'pdec' (decimal empaquetado) está deprecado: ya no "
                  "garantiza números únicos sin error y quedará sin soporte. "
                  "Usa 'int' (punto fijo) o 'var'.\n");
}

typedef enum {
  OP_PUSH,
  OP_POP,
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
  // --- Comparación (push VBOOL) ---
  OP_EQ,
  OP_NEQ,
  OP_LT,
  OP_GT,
  OP_LTE,
  OP_GTE,
  // --- Lógicos ---
  OP_AND,
  OP_OR,
  OP_NOT,
  // --- Bitwise ---
  OP_BIT_AND,
  OP_BIT_OR,
  OP_BIT_NOT,
  OP_BIT_XOR,
  OP_BIT_SHL,  // •«
  OP_BIT_SHR,  // »•
  // --- Incremento/Decremento ---
  OP_INC,
  OP_DEC,
  OP_RETURN,
  OP_CALL_VAR,
  // --- Arrays ---
  OP_ARRAY_NEW,  // [uint16_t count] — pops count elements, pushes ARRAY
  OP_ARRAY_GET,  // pops index (NUM64) + array, pushes element
  OP_ARRAY_SET,  // pops value + index (NUM64) + array, sets element
  // --- Packages ---
  OP_PKG_NEW,    // [uint16_t field_count] — pops field_count name/value pairs, pushes PACKAGE
  OP_PKG_GET,    // [uint16_t name_len] [chars...] — pops package, pushes field value
  OP_PKG_SET,    // [uint16_t name_len] [chars...] — pops value + package, sets field
  // --- Try/Catch ---
  OP_TRY_SETUP,  // [int16_t catch_offset] — pushes try frame, catch target = ip + catch_offset
  OP_TRY_END,    // pops try frame, jumps past catch block
  OP_THROW,      // pops error value, unwinds to nearest catch handler
  OP_STORE_LOCAL, // [uint16_t index] — stores to frame-local variable
  OP_LOAD_LOCAL,  // [uint16_t index] — loads from frame-local variable
} PaxoOpcode;

void vm_init(VM *vm, const uint8_t *bytecode, size_t bytecode_size) {
  vm->bytecode = bytecode;
  vm->bytecode_size = bytecode_size;
  vm->ip = 0;
}

// Helpers seguros para lectura sin problemas de alineación
static inline uint16_t read_u16(VM *vm) {
  uint16_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(uint16_t));
  vm->ip += sizeof(uint16_t);
  return val;
}

static inline int16_t read_i16(VM *vm) {
  int16_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(int16_t));
  vm->ip += sizeof(int16_t);
  return val;
}

void vm_error(VM *vm, const char *msg);

static inline bool var_is_num_type(enum type t) {
  return t == NUM16 || t == NUM64;
}

static inline bool var_is_fxp_type(enum type t) {
  return t == INT_FP || t == PKDEC;
}

static inline bool var_is_numeric(enum type t) {
  return var_is_num_type(t) || var_is_fxp_type(t);
}

static inline Num64 var_num_as64(PaxoVar v) {
  return (var_type(v) == NUM16) ? num16tonum64(var_num16_get(v))
                                : var_num64_get(v);
}

static inline PaxoVar fxp_to_var(PaxoFxp f) {
  return var_int_fp(f.value, f.scale);
}

// Lleva un operando al dominio de punto fijo (int) de la escala pedida
// (num → fxp; INT_FP se mantiene tal cual).
static inline PaxoFxp var_as_fxp(PaxoVar v, uint8_t scale) {
  switch (var_type(v)) {
  case NUM16:
    return num64_to_fxp(num16tonum64(var_num16_get(v)), scale);
  case NUM64:
    return num64_to_fxp(var_num64_get(v), scale);
  case INT_FP:
    return var_fxp_get(v);
  default:
    return fxp_pack(0, scale);
  }
}

// Lleva un operando al dominio BCD (pdec). MP se redondea a la escala
// pedida; INT_FP se convierte sin pérdida (mantiene su propia escala).
static inline PaxoPdec var_to_pdec(PaxoVar v, uint8_t num_scale) {
  switch (var_type(v)) {
  case PKDEC:
    return var_pkdec_get(v);
  case INT_FP: {
    PaxoFxp f = var_fxp_get(v);
    return pdec_from_int64((int64_t)f.value, f.scale);
  }
  case NUM16:
    return num64_to_pdec(num16tonum64(var_num16_get(v)), num_scale);
  case NUM64:
    return num64_to_pdec(var_num64_get(v), num_scale);
  default:
    return pdec_from_int64(0, 0);
  }
}

// Valor entero (con signo) de un operando para operaciones bit a bit; los MP
// se redondean a entero y los fxp/pdec usan su entero escalado (mantissa).
static inline int64_t var_bit_value(PaxoVar v) {
  switch (var_type(v)) {
  case INT_FP:
    return (int64_t)var_fxp_get(v).value;
  case PKDEC:
    return pdec_value(var_pkdec_get(v));
  case NUM16: {
    long double rl = roundl((long double)var_num16_get(v).bc *
                            powl(10.0L, (long double)((int)var_num16_get(v).exp -
                                                       (int)BIAS16 -
                                                       (int)var_num16_get(v).p)));
    return (int64_t)rl;
  }
  case NUM64:
    return (int64_t)roundl((long double)var_num64_get(v).bc *
                           powl(10.0L, (long double)((int)var_num64_get(v).exp -
                                                     (int)BIAS64 -
                                                     (int)var_num64_get(v).p)));
  default:
    return 0;
  }
}

static inline bool var_is_complex_type(enum type t) {
  return t == COMPLEX || t == COMPLEX16;
}

// Representa un operando como par (re, im); un escalar se trata como (x + 0i)
// conservando su sistema numérico (num16/num64) — el tipo deprecado pdec se
// lleva al dominio MP64.
static inline PaxoComplex complex_of_operand(PaxoVar v) {
  if (var_is_complex_type(var_type(v)))
    return var_complex_get(v);
  PaxoComplex c = {.re = v, .im = 0};
  switch (var_type(v)) {
  case INT_FP:
    c.kind = LEP_COMPLEX_KIND_NI;
    c.im = var_num64((Num64){0, BIAS64, 0, 0});
    break;
  case PKDEC:
    c.kind = LEP_COMPLEX_KIND_NI;
    c.im = var_num64((Num64){0, BIAS64, 0, 0});
    break;
  case NUM64:
    c.kind = LEP_COMPLEX_KIND_NI;
    c.im = var_num64((Num64){0, BIAS64, 0, 0});
    break;
  default:
    c.kind = LEP_COMPLEX_KIND_SNI;
    c.im = var_num16((Num16){0, BIAS16, 0, 0});
    break;
  }
  return c;
}

// Sistema del resultado: MP64 (ni) domina, luego MP16 (sni).
static inline int complex_domain(PaxoComplex a, PaxoComplex b) {
  int da = (a.kind == LEP_COMPLEX_KIND_SNI) ? 0 : 1;
  int db = (b.kind == LEP_COMPLEX_KIND_SNI) ? 0 : 1;
  return (da > db ? da : db) ? LEP_COMPLEX_KIND_NI : LEP_COMPLEX_KIND_SNI;
}

// Empaqueta (re, im) en el sistema elegido
static inline PaxoVar complex_pack(int domain, long double re, long double im) {
  if (domain == LEP_COMPLEX_KIND_NI)
    return var_complex_ni(num64_from_ld(re), num64_from_ld(im));
  return var_complex_sni(num64tonum16(num64_from_ld(re)),
                         num64tonum16(num64_from_ld(im)));
}

static inline PaxoVar complex_add(PaxoVar a, PaxoVar b) {
  PaxoComplex ca = complex_of_operand(a), cb = complex_of_operand(b);
  int dom = complex_domain(ca, cb);
  return complex_pack(dom, var_to_ld(ca.re) + var_to_ld(cb.re),
                      var_to_ld(ca.im) + var_to_ld(cb.im));
}

static inline PaxoVar complex_sub(PaxoVar a, PaxoVar b) {
  PaxoComplex ca = complex_of_operand(a), cb = complex_of_operand(b);
  int dom = complex_domain(ca, cb);
  return complex_pack(dom, var_to_ld(ca.re) - var_to_ld(cb.re),
                      var_to_ld(ca.im) - var_to_ld(cb.im));
}

static inline PaxoVar complex_mul(PaxoVar a, PaxoVar b) {
  PaxoComplex ca = complex_of_operand(a), cb = complex_of_operand(b);
  int dom = complex_domain(ca, cb);
  long double ar = var_to_ld(ca.re), ai = var_to_ld(ca.im);
  long double br = var_to_ld(cb.re), bi = var_to_ld(cb.im);
  return complex_pack(dom, ar * br - ai * bi, ar * bi + ai * br);
}

// División: (a+bi)/(c+di) = (ac+bd)/(c²+d²) + (bc-ad)/(c²+d²)i.
// Devuelve LEP_NO_VALUE si el divisor es cero (para vm_error en el intérprete).
static inline PaxoVar complex_div(PaxoVar a, PaxoVar b) {
  PaxoComplex ca = complex_of_operand(a), cb = complex_of_operand(b);
  int dom = complex_domain(ca, cb);
  long double ar = var_to_ld(ca.re), ai = var_to_ld(ca.im);
  long double br = var_to_ld(cb.re), bi = var_to_ld(cb.im);
  long double denom = br * br + bi * bi;
  if (denom == 0.0L)
    return LEP_NO_VALUE;
  return complex_pack(dom, (ar * br + ai * bi) / denom,
                      (ai * br - ar * bi) / denom);
}

static inline Num64 zero_num64(void) {
  Num64 z = {0};
  z.exp = BIAS64;
  return z;
}
static inline Num16 zero_num16(void) {
  Num16 z = {0};
  z.exp = BIAS16;
  return z;
}

// Escalar completo (MP16/MP64/int/pdec/bool/trit/char) → MP64
static inline Num64 scalar_to64(PaxoVar v) {
  switch (var_type(v)) {
  case VBOOL:
    return booltonum64(var_bool_get(v));
  case TRIT:
    return trittonum64(var_trit_get(v));
  case CHAR: {
    Num64 c = {0};
    c.bc = (uint64_t)var_char_get(v);
    c.exp = BIAS64;
    return c;
  }
  default:
    return complex_comp64(v);
  }
}

// Escalar completo → MP16 (aproxima)
static inline Num16 scalar_to16(PaxoVar v) {
  return num64tonum16(scalar_to64(v));
}

// Comparación numérica entre dos operadores (MP16/MP64/int/pdec), exacta en
// el dominio de los tipos nuevos; los pdec y los int se comparan entre sí
// decimalmente y contra MP se promueven a MP64.
static inline int cmp_any(PaxoVar a, PaxoVar b) {
  enum type ta = var_type(a), tb = var_type(b);
  if (var_is_complex_type(ta) || var_is_complex_type(tb)) {
    PaxoComplex ca = complex_of_operand(a), cb = complex_of_operand(b);
    int r = cmp_any(ca.re, cb.re);
    if (r)
      return r;
    return cmp_any(ca.im, cb.im);
  }
  if (ta == PKDEC || tb == PKDEC) {
    vm_warn_pdec();
    if (ta == PKDEC && tb == PKDEC)
      return pdec_cmp(var_pkdec_get(a), var_pkdec_get(b));
    if (ta == INT_FP)
      return pdec_cmp(pdec_from_int64((int64_t)var_fxp_get(a).value,
                                      var_fxp_get(a).scale),
                      var_pkdec_get(b));
    if (tb == INT_FP)
      return pdec_cmp(var_pkdec_get(a),
                      pdec_from_int64((int64_t)var_fxp_get(b).value,
                                      var_fxp_get(b).scale));
    a = var_num64(pdec_to_num64(var_pkdec_get(a)));
    b = var_num64(pdec_to_num64(var_pkdec_get(b)));
    ta = tb = NUM64;
  } else if (var_is_fxp_type(ta) && var_is_fxp_type(tb)) {
    return cmp_fxp(var_fxp_get(a), var_fxp_get(b));
  }
  if (var_is_fxp_type(ta))
    a = var_num64(fxp_to_num64(var_fxp_get(a)));
  if (var_is_fxp_type(tb))
    b = var_num64(fxp_to_num64(var_fxp_get(b)));
  ta = var_type(a);
  tb = var_type(b);
  if (ta == NUM64 || tb == NUM64)
    return cmp_num64(var_num_as64(a), var_num_as64(b));
  return cmp_num16(var_num16_get(a), var_num16_get(b));
}

static inline bool var_truthy(PaxoVar v) {
  switch (var_type(v)) {
  case VBOOL:
    return var_bool_get(v);
  case TRIT:
    return var_trit_get(v) == 1;
  case INT_FP:
    return var_fxp_get(v).value != 0;
  case PKDEC:
    return !pdec_is_zero(var_pkdec_get(v));
  case COMPLEX:
  case COMPLEX16:
    return !var_complex_is_zero(var_complex_get(v));
  default:
    return false;
  }
}

static inline size_t var_to_index(PaxoVar v) {
  switch (var_type(v)) {
  case NUM16:
    return (size_t)var_num16_get(v).bc;
  case NUM64:
    return (size_t)var_num64_get(v).bc;
  case INT_FP:
  case PKDEC: {
    // trunca el valor escalado a entero: pdec(2500,3)=2.500 -> índice 2
    int64_t value;
    uint8_t scale;
    if (var_type(v) == INT_FP) {
      value = (int64_t)var_fxp_get(v).value;
      scale = var_fxp_get(v).scale;
    } else {
      value = pdec_magnitude(var_pkdec_get(v));
      scale = var_pkdec_get(v).scale;
    }
    uint64_t div = 1;
    for (uint8_t i = 0; i < scale; i++)
      div *= 10;
    if (value < 0)
      value = -value;
    value /= (int64_t)div;
    return (value > 0) ? (size_t)value : 0;
  }
  default:
    return 0;
  }
}

void vm_run(VM *vm, Deque *stack, PaxoVar *globals) {
  bool running = true;

  while (running) {
    if (vm->ip >= vm->bytecode_size) {
      vm_error(vm, "IP fuera de los limites del bytecode");
      break;
    }
    uint8_t op = vm->bytecode[vm->ip++];

    switch (op) {
    case OP_PUSH: {
      uint8_t var_type_tag = vm->bytecode[vm->ip++];
      PaxoVar val = 0;

      switch (var_type_tag) {
      case NUM16: {
        uint16_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = var_num16(num16_unpack(raw));
        break;
      }
      case NUM64: {
        uint64_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = var_num64((Num64){.signo = raw & 1,
                                .exp = (raw >> 1) & 0xFF,
                                .bc = (raw >> 9) & bc_max64(),
                                .p = (raw >> 59)});
        break;
      }
      case VBOOL:
        val = var_bool(vm->bytecode[vm->ip++] != 0);
        break;
      case TRIT:
        val = var_trit(vm->bytecode[vm->ip++] & 0x3);
        break;
      case CHAR:
        val = var_char((char32_t)vm->bytecode[vm->ip++]);
        break;
      case COLOR: {
        uint8_t r = vm->bytecode[vm->ip++];
        uint8_t g = vm->bytecode[vm->ip++];
        uint8_t b = vm->bytecode[vm->ip++];
        uint8_t a = vm->bytecode[vm->ip++];
        val = var_color(((uint32_t)r << 24) | ((uint32_t)g << 16) |
                        ((uint32_t)b << 8) | a);
        break;
      }
      case INT_FP:
      case PKDEC: {
        uint8_t scale = vm->bytecode[vm->ip++];
        int16_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = (var_type_tag == INT_FP) ? var_int_fp(raw, scale)
                                        : var_pkdec(raw, scale);
        break;
      }
      case POINT: {
        uint64_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = var_pin((uint32_t)raw);
        break;
      }
      case COMPLEX: {
        uint64_t raw_re, raw_im;
        memcpy(&raw_re, vm->bytecode + vm->ip, sizeof(raw_re));
        memcpy(&raw_im, vm->bytecode + vm->ip + sizeof(raw_re),
               sizeof(raw_im));
        vm->ip += sizeof(raw_re) + sizeof(raw_im);
        val = var_complex_ni((Num64){.signo = raw_re & 1,
                                     .exp = (raw_re >> 1) & 0xFF,
                                     .bc = (raw_re >> 9) & bc_max64(),
                                     .p = (raw_re >> 59)},
                             (Num64){.signo = raw_im & 1,
                                     .exp = (raw_im >> 1) & 0xFF,
                                     .bc = (raw_im >> 9) & bc_max64(),
                                     .p = (raw_im >> 59)});
        break;
      }
      case COMPLEX16: {
        uint16_t raw_re, raw_im;
        memcpy(&raw_re, vm->bytecode + vm->ip, sizeof(raw_re));
        memcpy(&raw_im, vm->bytecode + vm->ip + sizeof(raw_re),
               sizeof(raw_im));
        vm->ip += sizeof(raw_re) + sizeof(raw_im);
        val = var_complex_sni(num16_unpack(raw_re), num16_unpack(raw_im));
        break;
      }
      case STRING: {
        uint16_t len = read_u16(vm);
        val = var_string((const char *)(vm->bytecode + vm->ip));
        vm->ip += len + 1;
        break;
      }
      case FUNC: {
        uint16_t offset = read_u16(vm);
        uint8_t param_count = vm->bytecode[vm->ip++];
        val = var_func(offset, param_count);
        break;
      }
      default:
        vm_error(vm, "tipo de valor desconocido en bytecode");
        running = false;
        break;
      }

      deque_push_back(stack, val);
      break;
    }

    case OP_POP: {
      deque_pop_back(stack);
      break;
    }

#define ARITH_OP(name, op16, op64, opfxp, oppdec, oppcpx)                     \
  case name: {                                                                 \
    PaxoVar b = deque_pop_back(stack);                                         \
    PaxoVar a = deque_pop_back(stack);                                         \
    enum type ta = var_type(a), tb = var_type(b);                              \
    PaxoVar res = LEP_ZERO;                                                   \
    if (var_is_complex_type(ta) || var_is_complex_type(tb)) {                  \
      res = oppcpx(a, b);                                                      \
      if (res == LEP_NO_VALUE) {                                              \
        vm_error(vm, "división entre cero en complejo");                        \
        running = false;                                                       \
        deque_push_back(stack, LEP_ZERO);                                     \
        break;                                                                 \
      }                                                                        \
    } else if (var_is_numeric(ta) && var_is_numeric(tb)) {                     \
      if (ta == PKDEC || tb == PKDEC) {                                        \
        /* decimal empaquetado (BCD): deprecado, opera en el dominio pdec */    \
        vm_warn_pdec();                                                        \
        uint8_t scale = (ta == PKDEC) ? var_pkdec_get(a).scale                 \
                                      : var_pkdec_get(b).scale;                \
        PaxoPdec pa = var_to_pdec(a, scale);                                   \
        PaxoPdec pb = var_to_pdec(b, scale);                                   \
        res = pdec_to_var(oppdec(pa, pb));                                     \
      } else if (ta == INT_FP || tb == INT_FP) {                               \
        /* punto fijo / entero: opera siempre en el dominio fxp */             \
        if (ta == INT_FP && tb == INT_FP) {                                    \
          PaxoFxp r = opfxp(var_fxp_get(a), var_fxp_get(b));                   \
          res = fxp_to_var(r);                                                 \
        } else {                                                               \
          /* mixto int + MP: promueve el número a la escala del int */         \
          uint8_t scale = (ta == INT_FP) ? var_fxp_get(a).scale                \
                                          : var_fxp_get(b).scale;              \
          PaxoFxp fa = var_as_fxp(a, scale);                                   \
          PaxoFxp fb = var_as_fxp(b, scale);                                   \
          PaxoFxp r = opfxp(fa, fb);                                           \
          res = fxp_to_var(r);                                                 \
        }                                                                      \
      } else if (ta == NUM64 || tb == NUM64) {                                 \
        Num64 r = op64(var_num_as64(a), var_num_as64(b));                      \
        res = var_num64(r);                                                    \
      } else {                                                                 \
        Num16 r = op16(var_num16_get(a), var_num16_get(b));                    \
        res = var_num16(r);                                                    \
      }                                                                        \
    } else {                                                                   \
      vm_error(vm, "tipos incompatibles en operación aritmética");             \
    }                                                                          \
    deque_push_back(stack, res);                                               \
    break;                                                                     \
  }

    ARITH_OP(OP_ADD, add_num16, add_num64, add_fxp, pdec_add, complex_add)
    ARITH_OP(OP_SUB, sub_num16, sub_num64, sub_fxp, pdec_sub, complex_sub)
    ARITH_OP(OP_MUL, mul_num16, mul_num64, mul_fxp, pdec_mul, complex_mul)
    ARITH_OP(OP_DIV, div_num16, div_num64, div_fxp, pdec_div, complex_div)

#undef ARITH_OP

    case OP_LOAD_VAR: {
      uint16_t index = read_u16(vm);
      deque_push_back(stack, globals[index]);
      break;
    }

    case OP_STORE_VAR: {
      uint16_t index = read_u16(vm);
      globals[index] = deque_pop_back(stack);
      break;
    }

    case OP_PRINT: {
      PaxoVar val = deque_pop_back(stack);
      const char8_t *str = NULL;

      switch (var_type(val)) {
      case NUM16:
        str = readnum16(var_num16_get(val), 1);
        break;
      case NUM64:
        str = readnum64(var_num64_get(val), 1);
        break;
      case VBOOL:
        str = readbool(var_bool_get(val));
        break;
      case CHAR:
        str = readchar32(var_char_get(val));
        break;
      case INT_FP:
        str = readint(var_fxp_get(val));
        break;
      case PKDEC:
        str = readpdec(var_pkdec_get(val));
        break;
      default:
        break;
      }

      if (str) {
        printf("%s\n", (const char *)str);
      }
      break;
    }

    case OP_JUMP: {
      int16_t offset = read_i16(vm);
      vm->ip += offset;
      break;
    }

    case OP_JUMP_IF_FALSE: {
      int16_t offset = read_i16(vm);
      PaxoVar condition = deque_pop_back(stack);

      bool is_false = false;
      if (var_type(condition) == VBOOL)
        is_false = !var_bool_get(condition);
      else if (var_type(condition) == TRIT)
        is_false = (var_trit_get(condition) == 0);
      else if (var_type(condition) == INT_FP)
        is_false = (var_fxp_get(condition).value == 0);
      else if (var_type(condition) == PKDEC)
        is_false = pdec_is_zero(var_pkdec_get(condition));
      else if (var_type(condition) == COMPLEX || var_type(condition) == COMPLEX16)
        is_false = var_complex_is_zero(var_complex_get(condition));

      if (is_false) {
        vm->ip += offset;
      }
      break;
    }
    case OP_CAST: {
      uint8_t target_type = vm->bytecode[vm->ip++];
      PaxoVar val = deque_pop_back(stack);
      enum type src = var_type(val);

      if (src == target_type) {
        deque_push_back(stack, val);
        break;
      }

      PaxoVar res = 0;
      if (target_type == POINT)
        res = var_pin(0);

      switch (src) {
      case NUM16: {
        Num16 n = var_num16_get(val);
        switch (target_type) {
        case NUM64:
          res = var_num64(num16tonum64(n));
          break;
        case VBOOL:
          res = var_bool(num16tobool(n));
          break;
        case TRIT:
          res = var_trit(num16totrit(n));
          break;
        case CHAR:
          res = var_char((char32_t)(n.bc > bc_max16() ? bc_max16() : n.bc));
          break;
        case INT_FP: {
          Num64 u = num16tonum64(n);
          res = fxp_to_var(num64_to_fxp(u, 0));
          break;
        }
        case PKDEC: {
          Num64 u = num16tonum64(n);
          uint8_t sc = (u.p < 15) ? (uint8_t)u.p : 15;
          res = pdec_to_var(num64_to_pdec(u, sc));
          break;
        }
        case COMPLEX:
          res = var_complex_ni(num16tonum64(n), zero_num64());
          break;
        case COMPLEX16:
          res = var_complex_sni(n, zero_num16());
          break;
        case COLOR: {
          uint32_t rgba = ((uint32_t)n.bc & 0xFFFFFFu);
          res = var_color((rgba << 8) | 0xFFu);
          break;
        }
        default:
          break;
        }
        break;
      }
      case NUM64: {
        Num64 n = var_num64_get(val);
        switch (target_type) {
        case NUM16:
          res = var_num16(num64tonum16(n));
          break;
        case VBOOL:
          res = var_bool(num64tobool(n));
          break;
        case TRIT:
          res = var_trit(num64totrit(n));
          break;
        case CHAR:
          res = var_char((char32_t)(n.bc & 0xFF));
          break;
        case INT_FP:
          res = fxp_to_var(num64_to_fxp(n, 0));
          break;
        case PKDEC: {
          uint8_t sc = (n.p < 15) ? (uint8_t)n.p : 15;
          res = pdec_to_var(num64_to_pdec(n, sc));
          break;
        }
        case COLOR: {
          uint32_t rgba = (uint32_t)(n.bc & 0xFFFFFFFFULL);
          res = var_color((rgba << 8) | 0xFFu);
          break;
        }
        case COMPLEX:
          res = var_complex_ni(n, zero_num64());
          break;
        case COMPLEX16:
          res = var_complex_sni(num64tonum16(n), zero_num16());
          break;
        default:
          break;
        }
        break;
      }
      case VBOOL: {
        bool b = var_bool_get(val);
        switch (target_type) {
        case NUM16:
          res = var_num16(booltonum16(b));
          break;
        case NUM64:
          res = var_num64(booltonum64(b));
          break;
        case TRIT:
          res = var_trit(booltotrit(b));
          break;
        case INT_FP:
          res = fxp_to_var(num64_to_fxp(booltonum64(b), 0));
          break;
        case PKDEC:
          res = pdec_to_var(num64_to_pdec(booltonum64(b), 0));
          break;
        case COMPLEX:
          res = var_complex_ni(booltonum64(b), zero_num64());
          break;
        case COMPLEX16:
          res = var_complex_sni(booltonum16(b), zero_num16());
          break;
        default:
          break;
        }
        break;
      }
      case TRIT: {
        uint8_t t = var_trit_get(val);
        switch (target_type) {
        case NUM16:
          res = var_num16(trittonum16(t));
          break;
        case NUM64:
          res = var_num64(trittonum64(t));
          break;
        case VBOOL:
          res = var_bool(trittobool(t));
          break;
        case INT_FP:
          res = fxp_to_var(num64_to_fxp(trittonum64(t), 0));
          break;
        case PKDEC:
          res = pdec_to_var(num64_to_pdec(trittonum64(t), 0));
          break;
        case COMPLEX:
          res = var_complex_ni(trittonum64(t), zero_num64());
          break;
        case COMPLEX16:
          res = var_complex_sni(trittonum16(t), zero_num16());
          break;
        default:
          break;
        }
        break;
      }
      case CHAR: {
        char32_t c = var_char_get(val);
        switch (target_type) {
        case NUM16: {
          Num16 conv = {0};
          conv.bc = (c > bc_max16()) ? bc_max16() : (uint16_t)c;
          conv.exp = BIAS16;
          conv.p = 0;
          res = var_num16(conv);
          break;
        }
        case NUM64: {
          Num64 conv = {0};
          conv.bc = (uint64_t)c;
          conv.exp = BIAS64;
          conv.p = 0;
          res = var_num64(conv);
          break;
        }
        case VBOOL:
          res = var_bool(c != 0);
          break;
        case TRIT:
          res = var_trit(c < 3 ? (uint8_t)c : 0);
          break;
        case INT_FP: {
          Num64 conv = {0};
          conv.bc = (uint64_t)c;
          conv.exp = BIAS64;
          res = fxp_to_var(num64_to_fxp(conv, 0));
          break;
        }
        case PKDEC: {
          Num64 conv = {0};
          conv.bc = (uint64_t)c;
          conv.exp = BIAS64;
          res = pdec_to_var(num64_to_pdec(conv, 0));
          break;
        }
        case COMPLEX:
        case COMPLEX16: {
          Num64 conv = {0};
          conv.bc = (uint64_t)c;
          conv.exp = BIAS64;
          res = (target_type == COMPLEX)
                    ? var_complex_ni(conv, zero_num64())
                    : var_complex_sni(num64tonum16(conv), zero_num16());
          break;
        }
        default:
          break;
        }
        break;
      }
      case STRING: {
        if (target_type == CHAR) {
          const char *s = var_string_get(val);
          res = var_char((s && s[0]) ? (char32_t)(uint8_t)s[0] : 0);
        }
        break;
      }
      case INT_FP: {
        PaxoFxp f = var_fxp_get(val);
        switch (target_type) {
        case NUM64:
          res = var_num64(fxp_to_num64(f));
          break;
        case NUM16:
          res = var_num16(fxp_to_num16(f));
          break;
        case PKDEC:
          // int → pdec: convierte el entero escalado a dígitos BCD (exacto)
          res = pdec_to_var(pdec_from_int64((int64_t)f.value, f.scale));
          break;
        case VBOOL:
          res = var_bool(num64tobool(fxp_to_num64(f)));
          break;
        case TRIT:
          res = var_trit(num64totrit(fxp_to_num64(f)));
          break;
        case CHAR: {
          Num64 conv = fxp_to_num64(f);
          res = var_char((char32_t)(conv.bc & 0xFF));
          break;
        }
        case COMPLEX:
          res = var_complex_ni(fxp_to_num64(f), zero_num64());
          break;
        case COMPLEX16:
          res = var_complex_sni(fxp_to_num16(f), zero_num16());
          break;
        default:
          break;
        }
        break;
      }
      case PKDEC: {
        PaxoPdec d = var_pkdec_get(val);
        switch (target_type) {
        case NUM64:
          res = var_num64(pdec_to_num64(d));
          break;
        case NUM16:
          res = var_num16(num64tonum16(pdec_to_num64(d)));
          break;
        case INT_FP:
          // pdec → int: redondea a entero (mismo criterio que num64 → int)
          res = fxp_to_var(num64_to_fxp(pdec_to_num64(d), 0));
          break;
        case VBOOL: {
          Num64 n = pdec_to_num64(d);
          res = var_bool(num64tobool(n));
          break;
        }
        case TRIT: {
          Num64 n = pdec_to_num64(d);
          res = var_trit(num64totrit(n));
          break;
        }
        case CHAR: {
          Num64 n = pdec_to_num64(d);
          res = var_char((char32_t)(n.bc & 0xFF));
          break;
        }
        case COMPLEX: {
          Num64 n = pdec_to_num64(d);
          res = var_complex_ni(n, zero_num64());
          break;
        }
        case COMPLEX16: {
          Num64 n = pdec_to_num64(d);
          res = var_complex_sni(num64tonum16(n), zero_num16());
          break;
        }
        default:
          break;
        }
        break;
      }
      case COLOR: {
        uint32_t rgba = var_color_get(val);
        switch (target_type) {
        case NUM64: {
          Num64 conv = {0};
          conv.bc = (uint64_t)rgba;
          conv.exp = BIAS64;
          conv.p = 0;
          res = var_num64(conv);
          break;
        }
        default:
          break;
        }
        break;
      }
      case COMPLEX:
      case COMPLEX16: {
        PaxoComplex c = var_complex_get(val);
        if (target_type == COMPLEX) { // sni → ni (ni → ni ya filtrado arriba)
          res = var_complex_ni(complex_comp64(c.re), complex_comp64(c.im));
          break;
        }
        if (target_type == COMPLEX16) { // ni → sni
          res = var_complex_sni(complex_comp16(c.re), complex_comp16(c.im));
          break;
        }
        // complejo → escalar: usa la parte real
        Num64 re = complex_comp64(c.re);
        switch (target_type) {
        case NUM64:
          res = var_num64(re);
          break;
        case NUM16:
          res = var_num16(num64tonum16(re));
          break;
        case INT_FP:
          res = fxp_to_var(num64_to_fxp(re, 0));
          break;
        case PKDEC: {
          uint8_t sc = (re.p < 15) ? (uint8_t)re.p : 15;
          res = pdec_to_var(num64_to_pdec(re, sc));
          break;
        }
        case VBOOL:
          res = var_bool(num64tobool(re));
          break;
        case TRIT:
          res = var_trit(num64totrit(re));
          break;
        case CHAR:
          res = var_char((char32_t)(re.bc & 0xFF));
          break;
        default:
          break;
        }
        break;
      }
      default:
        break;
      }

      deque_push_back(stack, res);
      break;
    }

    case OP_CALL: {
      uint16_t target_ip = read_u16(vm);
      if (vm->frame_count >= MAX_FRAMES) {
        vm_error(vm, "desbordamiento de pila de llamadas");
        running = false;
        break;
      }
      vm->frames[vm->frame_count++] = (CallFrame){.return_ip = vm->ip};
      vm->ip = target_ip;
      break;
    }

    case OP_CALL_NATIVE: {
      uint16_t native_id = read_u16(vm);
      uint8_t argc = vm->bytecode[vm->ip++];
      PaxoVar args[16];
      for (int i = argc - 1; i >= 0; i--)
        args[i] = deque_pop_back(stack);

      PaxoVar result = native_call(native_id, args, argc);
      if (result != LEP_NO_VALUE)
        deque_push_back(stack, result);
      break;
    }

    case OP_RETURN: {
      if (vm->frame_count == 0) {
        running = false;
        break;
      }
      vm->ip = vm->frames[--vm->frame_count].return_ip;
      break;
    }

    case OP_CALL_VAR: {
      uint8_t argc = vm->bytecode[vm->ip++];
      PaxoVar func_val = deque_pop_back(stack);
      if (var_type(func_val) != FUNC) {
        vm_error(vm, "se esperaba una función");
        running = false;
        break;
      }

      PaxoVar args[256];
      for (int i = argc - 1; i >= 0; i--)
        args[i] = deque_pop_back(stack);

      CallFrame *frame = &vm->frames[vm->frame_count++];
      frame->return_ip = vm->ip;
      for (int i = 0; i < argc; i++)
        frame->locals[i] = args[i];

      vm->ip = var_func_id(func_val);
      break;
    }

    // ==========================================
    // FRAME LOCAL VARIABLES
    // ==========================================
    case OP_STORE_LOCAL: {
      uint16_t index = read_u16(vm);
      vm->frames[vm->frame_count - 1].locals[index] = deque_pop_back(stack);
      break;
    }

    case OP_LOAD_LOCAL: {
      uint16_t index = read_u16(vm);
      deque_push_back(stack, vm->frames[vm->frame_count - 1].locals[index]);
      break;
    }

    // ==========================================
    // ARRAYS
    // ==========================================
    case OP_ARRAY_NEW: {
      uint16_t count = read_u16(vm);
      PaxoArray *arr = malloc(sizeof(PaxoArray));
      arr->len = count;
      arr->capacity = count > 0 ? count : 4;
      arr->items = malloc(sizeof(PaxoVar) * arr->capacity);
      for (int i = count - 1; i >= 0; i--)
        arr->items[i] = deque_pop_back(stack);
      deque_push_back(stack, var_array(arr));
      break;
    }

    case OP_ARRAY_GET: {
      PaxoVar idx_val = deque_pop_back(stack);
      PaxoVar arr_val = deque_pop_back(stack);
      if (var_type(arr_val) != ARRAY) {
        vm_error(vm, "se esperaba un array");
        running = false;
        break;
      }
      if (var_is_complex_type(var_type(idx_val))) {
        vm_error(vm, "los complejos no pueden indexar arrays");
        running = false;
        break;
      }
      size_t idx = var_to_index(idx_val);
      if (idx >= var_array_get(arr_val)->len) {
        vm_error(vm, "índice fuera de rango");
        running = false;
        break;
      }
      deque_push_back(stack, var_array_get(arr_val)->items[idx]);
      break;
    }

    case OP_ARRAY_SET: {
      PaxoVar value = deque_pop_back(stack);
      PaxoVar idx_val = deque_pop_back(stack);
      PaxoVar arr_val = deque_pop_back(stack);
      if (var_type(arr_val) != ARRAY) {
        vm_error(vm, "se esperaba un array");
        running = false;
        break;
      }
      if (var_is_complex_type(var_type(idx_val))) {
        vm_error(vm, "los complejos no pueden indexar arrays");
        running = false;
        break;
      }
      size_t idx = var_to_index(idx_val);
      if (idx >= var_array_get(arr_val)->len) {
        vm_error(vm, "índice fuera de rango");
        running = false;
        break;
      }
      var_array_get(arr_val)->items[idx] = value;
      break;
    }

    // ==========================================
    // PACKAGES
    // ==========================================
    case OP_PKG_NEW: {
      uint16_t field_count = read_u16(vm);
      PaxoPackageField *head = NULL;
      for (uint16_t i = 0; i < field_count; i++) {
        PaxoVar val = deque_pop_back(stack);
        uint16_t name_len = read_u16(vm);
        char *name = malloc(name_len + 1);
        memcpy(name, vm->bytecode + vm->ip, name_len);
        name[name_len] = '\0';
        vm->ip += name_len;
        PaxoPackageField *field = malloc(sizeof(PaxoPackageField));
        field->key = name;
        field->value = val;
        field->hidden = vm->bytecode[vm->ip++] != 0; // flag de visibilidad
        field->next = head;
        head = field;
      }
      deque_push_back(stack, var_pkg(head));
      break;
    }

    case OP_PKG_GET: {
      uint16_t name_len = read_u16(vm);
      char name[256];
      memcpy(name, vm->bytecode + vm->ip, name_len);
      name[name_len] = '\0';
      vm->ip += name_len;
      PaxoVar pkg_val = deque_pop_back(stack);
      if (var_type(pkg_val) != PACKAGE) {
        vm_error(vm, "se esperaba un package");
        running = false;
        break;
      }
      PaxoPackageField *f = var_pkg_get(pkg_val);
      bool found = false;
      while (f) {
        if (strcmp(f->key, name) == 0) {
          found = true;
          break;
        }
        f = f->next;
      }
      if (found) {
        if (f->hidden) {
          vm_error(vm, "campo privado");
          running = false;
          break;
        }
        deque_push_back(stack, f->value);
      }
      if (!found) {
        vm_error(vm, "campo no encontrado");
        running = false;
        break;
      }
      break;
    }

    case OP_PKG_SET: {
      uint16_t name_len = read_u16(vm);
      char name[256];
      memcpy(name, vm->bytecode + vm->ip, name_len);
      name[name_len] = '\0';
      vm->ip += name_len;
      PaxoVar value = deque_pop_back(stack);
      PaxoVar pkg_val = deque_pop_back(stack);
      if (var_type(pkg_val) != PACKAGE) {
        vm_error(vm, "se esperaba un package");
        running = false;
        break;
      }
      PaxoPackageField *f = var_pkg_get(pkg_val);
      while (f) {
        if (strcmp(f->key, name) == 0) {
          if (f->hidden) {
            vm_error(vm, "campo privado");
            running = false;
            break;
          }
          f->value = value;
          break;
        }
        f = f->next;
      }
      break;
    }

    // ==========================================
    // TRY / CATCH / THROW
    // ==========================================
    case OP_TRY_SETUP: {
      int16_t catch_offset = read_i16(vm);
      if (vm->try_frame_count >= MAX_TRY_FRAMES) {
        vm_error(vm, "demasiados try/catch anidados");
        running = false;
        break;
      }
      TryFrame *tf = &vm->try_frames[vm->try_frame_count++];
      tf->catch_ip = vm->ip + catch_offset;
      tf->stack_size = deque_size(stack);
      tf->frame_count = vm->frame_count;
      break;
    }

    case OP_TRY_END: {
      int16_t end_offset = read_i16(vm);
      if (vm->try_frame_count > 0)
        vm->try_frame_count--;
      vm->ip += end_offset;
      break;
    }

    case OP_THROW: {
      PaxoVar error_val = deque_pop_back(stack);
      if (vm->try_frame_count == 0) {
        vm_error(vm, "throw sin try/catch");
        running = false;
        break;
      }
      TryFrame *tf = &vm->try_frames[--vm->try_frame_count];
      while (deque_size(stack) > tf->stack_size)
        deque_pop_back(stack);
      vm->frame_count = tf->frame_count;
      deque_push_back(stack, error_val);
      vm->ip = tf->catch_ip;
      break;
    }

    case OP_JUMP_IF_TRUE: {
      int16_t offset = read_i16(vm);
      PaxoVar condition = deque_pop_back(stack);

      if (var_truthy(condition)) {
        vm->ip += offset;
      }
      break;
    }

    // ==========================================
    // COMPARACIONES (result -> VBOOL)
    // ==========================================
#define c_eq(c)  ((c) == 0)
#define c_neq(c) ((c) != 0)
#define c_lt(c)  ((c) < 0)
#define c_gt(c)  ((c) > 0)
#define c_lte(c) ((c) <= 0)
#define c_gte(c) ((c) >= 0)

#define CMP_NUMBERS(chose)                                                    \
  do {                                                                        \
    int c = cmp_any(a, b);                                                    \
    result_bool = chose(c);                                                   \
  } while (0)

#define CMP_BOTH(same_kind, expr)                                             \
  do {                                                                        \
    if (ta == tb && ta == same_kind)                                          \
      result_bool = (expr);                                                   \
  } while (0)

    case OP_EQ: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if ((var_is_numeric(ta) && var_is_numeric(tb)) ||
          var_is_complex_type(ta) || var_is_complex_type(tb)) {
        CMP_NUMBERS(c_eq);
      } else {
        CMP_BOTH(VBOOL, var_bool_get(a) == var_bool_get(b));
        CMP_BOTH(TRIT, var_trit_get(a) == var_trit_get(b));
        CMP_BOTH(CHAR, var_char_get(a) == var_char_get(b));
        CMP_BOTH(POINT, var_pin_get(a) == var_pin_get(b));
        CMP_BOTH(STRING,
                 strcmp(var_string_get(a), var_string_get(b)) == 0);
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_NEQ: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = true;
      if (var_is_numeric(ta) && var_is_numeric(tb)) {
        CMP_NUMBERS(c_neq);
      } else if (ta == tb) {
        result_bool = false;
        CMP_BOTH(VBOOL, var_bool_get(a) != var_bool_get(b));
        CMP_BOTH(TRIT, var_trit_get(a) != var_trit_get(b));
        CMP_BOTH(CHAR, var_char_get(a) != var_char_get(b));
        CMP_BOTH(POINT, var_pin_get(a) != var_pin_get(b));
        CMP_BOTH(STRING,
                 strcmp(var_string_get(a), var_string_get(b)) != 0);
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_LT: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_numeric(ta) && var_is_numeric(tb)) {
        CMP_NUMBERS(c_lt);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) < var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_GT: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_numeric(ta) && var_is_numeric(tb)) {
        CMP_NUMBERS(c_gt);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) > var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_LTE: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_numeric(ta) && var_is_numeric(tb)) {
        CMP_NUMBERS(c_lte);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) <= var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_GTE: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_numeric(ta) && var_is_numeric(tb)) {
        CMP_NUMBERS(c_gte);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) >= var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

#undef CMP_BOTH
#undef CMP_NUMBERS
#undef c_eq
#undef c_neq
#undef c_lt
#undef c_gt
#undef c_lte
#undef c_gte

    // ==========================================
    // LÓGICOS (VBOOL / TRIT)
    // ==========================================
    case OP_AND: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      deque_push_back(stack, var_bool(var_truthy(a) && var_truthy(b)));
      break;
    }

    case OP_OR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      deque_push_back(stack, var_bool(var_truthy(a) || var_truthy(b)));
      break;
    }

    case OP_NOT: {
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a);
      bool result_bool = true;
      if (ta == VBOOL)
        result_bool = !var_bool_get(a);
      else if (ta == TRIT)
        result_bool = (var_trit_get(a) == 0);
      else if (ta == INT_FP)
        result_bool = (var_fxp_get(a).value == 0);
      else if (ta == PKDEC)
        result_bool = pdec_is_zero(var_pkdec_get(a));
      else if (ta == COMPLEX || ta == COMPLEX16)
        result_bool = var_complex_is_zero(var_complex_get(a));
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    // ==========================================
    // BITWISE (VBOOL / TRIT / CHAR)
    // ==========================================
    case OP_BIT_AND: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == VBOOL && var_type(b) == VBOOL) {
        res = var_bool((int)var_bool_get(a) & (int)var_bool_get(b));
      } else if (var_type(a) == TRIT && var_type(b) == TRIT) {
        res = var_trit(var_trit_get(a) & var_trit_get(b));
      } else if (var_is_fxp_type(var_type(a)) || var_is_fxp_type(var_type(b))) {
        bool to_pdec = (var_type(a) == PKDEC || var_type(b) == PKDEC);
        if (to_pdec) vm_warn_pdec();
        int64_t r = var_bit_value(a) & var_bit_value(b);
        res = to_pdec ? pdec_to_var(pdec_from_int64(r, 0))
                      : fxp_to_var(fxp_pack(r, 0));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_OR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == VBOOL && var_type(b) == VBOOL) {
        res = var_bool((int)var_bool_get(a) | (int)var_bool_get(b));
      } else if (var_type(a) == TRIT && var_type(b) == TRIT) {
        res = var_trit(var_trit_get(a) | var_trit_get(b));
      } else if (var_is_fxp_type(var_type(a)) || var_is_fxp_type(var_type(b))) {
        bool to_pdec = (var_type(a) == PKDEC || var_type(b) == PKDEC);
        if (to_pdec) vm_warn_pdec();
        int64_t r = var_bit_value(a) | var_bit_value(b);
        res = to_pdec ? pdec_to_var(pdec_from_int64(r, 0))
                      : fxp_to_var(fxp_pack(r, 0));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_NOT: {
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      switch (var_type(a)) {
      case VBOOL:
        res = var_bool(!var_bool_get(a));
        break;
      case TRIT:
        res = var_trit(~var_trit_get(a) & 0x3u);
        break;
      case CHAR:
        res = var_char(~var_char_get(a) & 0xFFFFFFFFu);
        break;
      case INT_FP: {
        PaxoFxp f = var_fxp_get(a);
        res = fxp_to_var(fxp_pack((int64_t)~(int64_t)f.value, f.scale));
        break;
      }
      case PKDEC: {
        vm_warn_pdec();
        PaxoPdec d = var_pkdec_get(a);
        res = pdec_to_var(pdec_from_int64(~pdec_value(d), d.scale));
        break;
      }
      default:
        break;
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_XOR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == VBOOL && var_type(b) == VBOOL) {
        res = var_bool(var_bool_get(a) ^ var_bool_get(b));
      } else if (var_type(a) == TRIT && var_type(b) == TRIT) {
        res = var_trit(var_trit_get(a) ^ var_trit_get(b));
      } else if (var_is_fxp_type(var_type(a)) || var_is_fxp_type(var_type(b))) {
        bool to_pdec = (var_type(a) == PKDEC || var_type(b) == PKDEC);
        if (to_pdec) vm_warn_pdec();
        int64_t r = var_bit_value(a) ^ var_bit_value(b);
        res = to_pdec ? pdec_to_var(pdec_from_int64(r, 0))
                      : fxp_to_var(fxp_pack(r, 0));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_SHL: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == CHAR && var_type(b) == CHAR) {
        res = var_char(var_char_get(a) << var_char_get(b));
      } else if (var_type(a) == NUM64 && var_type(b) == NUM64) {
        Num64 r = var_num64_get(a);
        r.bc = var_num64_get(a).bc << var_num64_get(b).bc;
        res = var_num64(r);
      } else if (var_type(a) == NUM16 && var_type(b) == NUM16) {
        Num16 r = var_num16_get(a);
        r.bc = var_num16_get(a).bc << var_num16_get(b).bc;
        res = var_num16(r);
      } else if (var_is_fxp_type(var_type(a)) || var_is_fxp_type(var_type(b))) {
        bool to_pdec = (var_type(a) == PKDEC || var_type(b) == PKDEC);
        if (to_pdec) vm_warn_pdec();
        int64_t bv = var_bit_value(b);
        int32_t sh = (bv < 0) ? 0 : (bv > 63 ? 63 : (int32_t)bv);
        int64_t r = var_bit_value(a) << sh;
        res = to_pdec ? pdec_to_var(pdec_from_int64(r, 0))
                      : fxp_to_var(fxp_pack(r, 0));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_SHR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == CHAR && var_type(b) == CHAR) {
        res = var_char(var_char_get(a) >> var_char_get(b));
      } else if (var_type(a) == NUM64 && var_type(b) == NUM64) {
        Num64 r = var_num64_get(a);
        r.bc = var_num64_get(a).bc >> var_num64_get(b).bc;
        res = var_num64(r);
      } else if (var_type(a) == NUM16 && var_type(b) == NUM16) {
        Num16 r = var_num16_get(a);
        r.bc = var_num16_get(a).bc >> var_num16_get(b).bc;
        res = var_num16(r);
      } else if (var_is_fxp_type(var_type(a)) || var_is_fxp_type(var_type(b))) {
        bool to_pdec = (var_type(a) == PKDEC || var_type(b) == PKDEC);
        if (to_pdec) vm_warn_pdec();
        int64_t bv = var_bit_value(b);
        int32_t sh = (bv < 0) ? 0 : (bv > 63 ? 63 : (int32_t)bv);
        int64_t r = var_bit_value(a) >> sh;
        res = to_pdec ? pdec_to_var(pdec_from_int64(r, 0))
                      : fxp_to_var(fxp_pack(r, 0));
      }
      deque_push_back(stack, res);
      break;
    }

    // ==========================================
    // INC / DEC
    // ==========================================
    case OP_INC: {
      PaxoVar a = deque_pop_back(stack);
      switch (var_type(a)) {
      case NUM16: {
        Num16 one = {0};
        one.bc = 1;
        one.exp = BIAS16;
        a = var_num16(add_num16(var_num16_get(a), one));
        break;
      }
      case NUM64: {
        Num64 one = {0};
        one.bc = 1;
        one.exp = BIAS64;
        a = var_num64(add_num64(var_num64_get(a), one));
        break;
      }
      case INT_FP: {
        PaxoFxp one = {.value = 1, .scale = 0};
        a = fxp_to_var(add_fxp(var_fxp_get(a), one));
        break;
      }
      case PKDEC: {
        vm_warn_pdec();
        PaxoPdec one = pdec_from_int64(1, 0);
        a = pdec_to_var(pdec_add(var_pkdec_get(a), one));
        break;
      }
      default:
        break;
      }
      deque_push_back(stack, a);
      break;
    }

    case OP_DEC: {
      PaxoVar a = deque_pop_back(stack);
      switch (var_type(a)) {
      case NUM16: {
        Num16 one = {0};
        one.bc = 1;
        one.exp = BIAS16;
        a = var_num16(sub_num16(var_num16_get(a), one));
        break;
      }
      case NUM64: {
        Num64 one = {0};
        one.bc = 1;
        one.exp = BIAS64;
        a = var_num64(sub_num64(var_num64_get(a), one));
        break;
      }
      case INT_FP: {
        PaxoFxp one = {.value = 1, .scale = 0};
        a = fxp_to_var(sub_fxp(var_fxp_get(a), one));
        break;
      }
      case PKDEC: {
        vm_warn_pdec();
        PaxoPdec one = pdec_from_int64(1, 0);
        a = pdec_to_var(pdec_sub(var_pkdec_get(a), one));
        break;
      }
      default:
        break;
      }
      deque_push_back(stack, a);
      break;
    }

    case OP_HALT:
    default:
      running = false;
      break;
    }
  }
}

void vm_error(VM *vm, const char *msg) {
  text_red(stderr);
  fprintf(stderr, "[lepvm error]");
  reset_colors(stderr);
  fprintf(stderr, " en IP 0x%04zX: %s\n", vm->ip, msg);
}
