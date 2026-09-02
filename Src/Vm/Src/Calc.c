#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char char8_t;
typedef uint32_t char32_t;
typedef uint8_t PaxoBool;

// ==========================================
// 1. MOBILE POINT (REVISIÓN MP + NANBOX)
//    MP16: [s | 2e | 5bc | p3]
//    MP64: [s | 8e | 25bc | p5]
// ==========================================

#define BIAS16 1
#define BIAS64 127

typedef struct {
  uint16_t signo : 1;
  uint16_t exp : 2;
  uint16_t bc : 10; // 5 bit-chunks
  uint16_t p : 3;   // 6 posiciones
} __attribute__((packed)) Num16;

typedef struct {
  uint64_t signo : 1;
  uint64_t exp : 8;
  uint64_t bc : 50; // 25 bit-chunks
  uint64_t p : 5;   // 26 posiciones
} __attribute__((packed)) Num64;

static inline uint16_t bc_max16(void) { return 1023; }
static inline uint64_t bc_max64(void) { return (1ULL << 50) - 1; }

enum type {
  NUM16,
  NUM64,
  CHAR,
  TRIT,
  VBOOL,
  POINT,
  FUNC,
  STRING,
  ARRAY,
  PACKAGE,
  INT_FP,
  PKDEC,
  COLOR,
  COMPLEX,   // ni: general (componentes MP64)
  COMPLEX16  // sni: componentes num16
};

// ==========================================
// 2. NANBOX 64 BITS (spec Nanbox.md)
//    número : MP64 directo            (p != 26)
//    bit    : 00 ················· x 11010
//    trit   : 01 ················ xx 11010
//    char   : 10 ··········[char32]·· 11010
//    ref    : 11 ···[aux16][punt32]·· 11010
//    color  : 10 ·····[f][8r][8g][8b][8a] 11010
//    int/pd : t pppp ·· s ··[13 bits]···· 11011
//    MP16   : [43 padding][16 bits mp16]  11100
// ==========================================

typedef uint64_t PaxoVar;

static inline enum type var_type(PaxoVar v);

#define LEP_MARK_BOX   0x1AULL // 11010
#define LEP_MARK_FXPKD 0x1BULL // 11011 (fixed point/int + packed decimal)
#define LEP_MARK_N16   0x1CULL // 11100 (MP16)
#define LEP_MARK_MASK  0x1FULL
#define LEP_VAL_SHIFT  5

// refinamiento de color dentro del marcador BOX, tag CHAR (10)
#define LEP_COLOR_FLAG (1ULL << 37)

#define LEP_TAG_BIT 0x0ULL
#define LEP_TAG_TRIT 0x1ULL
#define LEP_TAG_CHAR 0x2ULL
#define LEP_TAG_REF 0x3ULL

#define REF_SUB_ARRAY 0u
#define REF_SUB_PKG 1u
#define REF_SUB_STRING 2u
#define REF_SUB_FUNC 3u
#define REF_SUB_PIN 4u
#define REF_SUB_COMPLEX 5u

#define LEP_NO_VALUE UINT64_MAX

typedef struct PaxoPackageField {
  char *key;
  struct PaxoPackageField *next;
  PaxoVar value;
  bool hidden; // campo privado (declarado con 'local' dentro del pkg)
} PaxoPackageField;

typedef struct {
  PaxoVar *items;
  size_t len;
  size_t capacity;
} PaxoArray;

typedef struct PaxoObject {
  void *ptr;
  uint8_t type;
} PaxoObject;

static PaxoObject *paxo_objects = NULL;
static uint32_t paxo_object_count = 0;
static uint32_t paxo_object_capacity = 0;

static inline uint32_t paxo_object_add(void *ptr, uint8_t type) {
  if (paxo_object_count == paxo_object_capacity) {
    paxo_object_capacity =
        paxo_object_capacity ? paxo_object_capacity * 2 : 256;
    paxo_objects =
        realloc(paxo_objects, sizeof(PaxoObject) * paxo_object_capacity);
  }
  paxo_objects[paxo_object_count] = (PaxoObject){.ptr = ptr, .type = type};
  return paxo_object_count++;
}

static inline void *paxo_object_ptr(PaxoVar v) {
  return paxo_objects[(v >> 21) & 0xFFFFFFFFULL].ptr;
}

static inline uint32_t paxo_object_intern(void *ptr, uint8_t type) {
  for (uint32_t i = 0; i < paxo_object_count; i++) {
    if (paxo_objects[i].ptr == ptr && paxo_objects[i].type == type)
      return i;
  }
  return paxo_object_add(ptr, type);
}

// ==========================================
// 3. CONSTRUCTORES / ACCESORES
// ==========================================

static inline PaxoVar var_num64(Num64 n) {
  if (n.p > 25)
    n.p = 25;
  return (uint64_t)n.signo | ((uint64_t)n.exp << 1) | ((uint64_t)n.bc << 9) |
         ((uint64_t)n.p << 59);
}

static inline Num64 var_num64_get(PaxoVar v) {
  return (Num64){.signo = (uint64_t)(v & 1),
                 .exp = (v >> 1) & 0xFF,
                 .bc = (v >> 9) & bc_max64(),
                 .p = (v >> 59)};
}

static inline uint16_t num16_pack(Num16 n) {
  if (n.p > 5)
    n.p = 5;
  return (uint16_t)((n.signo) | ((uint16_t)n.exp << 1) | ((uint16_t)n.bc << 3) |
                    ((uint16_t)n.p << 13));
}

static inline Num16 num16_unpack(uint16_t raw) {
  return (Num16){.signo = raw & 1,
                 .exp = (raw >> 1) & 0x3,
                 .bc = (raw >> 3) & 0x3FF,
                 .p = (raw >> 13)};
}

static inline PaxoVar var_num16(Num16 n) {
  return ((PaxoVar)num16_pack(n) << LEP_VAL_SHIFT) | LEP_MARK_N16;
}

#define LEP_ZERO var_num16((Num16){0})

static inline Num16 var_num16_get(PaxoVar v) {
  return num16_unpack((uint16_t)(v >> LEP_VAL_SHIFT));
}

static inline PaxoVar var_bool(bool b) {
  return (LEP_TAG_BIT << 62) | LEP_MARK_BOX |
         ((PaxoVar)(b ? 1u : 0u) << LEP_VAL_SHIFT);
}

static inline bool var_bool_get(PaxoVar v) { return (v >> LEP_VAL_SHIFT) & 1; }

static inline PaxoVar var_trit(uint8_t t) {
  return (LEP_TAG_TRIT << 62) | LEP_MARK_BOX |
         ((PaxoVar)(t & 0x3u) << LEP_VAL_SHIFT);
}

static inline uint8_t var_trit_get(PaxoVar v) {
  return (uint8_t)((v >> LEP_VAL_SHIFT) & 0x3u);
}

static inline PaxoVar var_char(char32_t c) {
  return (LEP_TAG_CHAR << 62) | LEP_MARK_BOX | ((PaxoVar)c << LEP_VAL_SHIFT);
}

static inline char32_t var_char_get(PaxoVar v) {
  return (char32_t)((v >> LEP_VAL_SHIFT) & 0xFFFFFFFFULL);
}

// color: RGBA empaquetado en bits [5..36] + flag 11010 (mismo tag que char,
// distinguido por LEP_COLOR_FLAG en el bit 37; los codepoints utf32 <= 0x1FFFFF
// nunca lo activan).
static inline PaxoVar var_color(uint32_t rgba) {
  return (LEP_TAG_CHAR << 62) | LEP_COLOR_FLAG | LEP_MARK_BOX |
         ((PaxoVar)rgba << LEP_VAL_SHIFT);
}

static inline uint32_t var_color_get(PaxoVar v) {
  return (uint32_t)((v >> LEP_VAL_SHIFT) & 0xFFFFFFFFULL);
}

// fixed point / int (marcador 11011, t=0): NO es decimal empaquetado.
//   t(1)=0 pppp(4) ··(2 pad) s(1) xxxxx(13) ···(30 pad+5 marcador)
//   value = entero escalado con signo en las 13 bits
typedef struct {
  int16_t value;  // entero escalado con signo
  uint8_t scale;  // pppp (0..15) dígitos fraccionarios
} PaxoFxp;

static inline PaxoVar var_fxp(PaxoFxp f) {
  if (f.scale > 15)
    f.scale = 15;
  int16_t v = f.value;
  uint8_t sign = v < 0 ? 1 : 0;
  uint16_t mag = v < 0 ? (uint16_t)(-(int32_t)v) : (uint16_t)v;
  PaxoVar out = (uint64_t)(f.scale & 0xF) << 59;
  out |= (uint64_t)sign << 56;
  out |= (uint64_t)(mag & 0x1FFFu) << 43;
  return out | LEP_MARK_FXPKD;
}

static inline PaxoFxp var_fxp_get(PaxoVar v) {
  PaxoFxp f;
  f.scale = (uint8_t)((v >> 59) & 0xF);
  int16_t mag = (int16_t)((v >> 43) & 0x1FFFu);
  f.value = ((v >> 56) & 1) ? (int16_t)(-mag) : mag;
  return f;
}

static inline PaxoVar var_int_fp(int16_t value, uint8_t scale) {
  return var_fxp((PaxoFxp){.value = value, .scale = scale});
}

// decimal empaquetado (packed decimal) real — BCD, marcador 11011, t=1:
// cada dígito decimal vive en un nibble; signo y escala por separado.
//   t(1)=1 pppp(4) s(1) ·(1 pad) d12..d0 (52 bits = 13 dígitos BCD) 11011
//   d0 (unidades) en bits 5..8, d12 (la más significativa) en bits 53..56.
//   valor = (-1)^signo · Σ d_i·10^i · 10^(-pppp)
#define LEP_PDEC_DIGITS 13
#define LEP_PDEC_DIG_SHIFT 5
#define LEP_PDEC_SIGN_SHIFT 58
#define LEP_PDEC_MAX_MAG ((int64_t)9999999999999LL) // 13 dígitos

typedef struct {
  uint8_t digits[LEP_PDEC_DIGITS]; // dígito BCD 0..9, d[0] = unidades
  uint8_t signo;                    // 0 positivo, 1 negativo
  uint8_t scale;                    // pppp (0..15) dígitos fraccionarios
} PaxoPdec;

// Empaca 13 dígitos BCD (magnitud) en un marmita nanbox de tipo PKDEC.
static inline PaxoVar var_pkdec_pack(uint64_t mag, uint8_t signo, uint8_t scale) {
  if (scale > 15)
    scale = 15;
  if (mag > (uint64_t)LEP_PDEC_MAX_MAG)
    mag = (uint64_t)LEP_PDEC_MAX_MAG;
  PaxoVar out = 1ULL << 63;
  out |= (uint64_t)(scale & 0xF) << 59;
  out |= (uint64_t)(signo & 1) << LEP_PDEC_SIGN_SHIFT;
  for (int i = 0; mag && i < LEP_PDEC_DIGITS; i++) {
    out |= (uint64_t)(mag % 10) << (LEP_PDEC_DIG_SHIFT + 4 * i);
    mag /= 10;
  }
  return out | LEP_MARK_FXPKD;
}

// Literal / constructor: valor escalado con signo (int16, como lo emite el
// bytecode) convertido a dígitos BCD.
static inline PaxoVar var_pkdec(int16_t value, uint8_t scale) {
  uint64_t mag = (value < 0) ? (uint64_t)(-(int32_t)value) : (uint64_t)value;
  return var_pkdec_pack(mag, (value < 0) ? 1 : 0, scale);
}

static inline PaxoVar pdec_to_var(PaxoPdec d) {
  uint64_t mag = 0, pow10 = 1;
  for (int i = 0; i < LEP_PDEC_DIGITS; i++) {
    mag += (uint64_t)(d.digits[i] & 0xF) * pow10;
    pow10 *= 10;
  }
  return var_pkdec_pack(mag, d.signo, d.scale);
}

static inline PaxoPdec var_pkdec_get(PaxoVar v) {
  PaxoPdec d;
  d.scale = (uint8_t)((v >> 59) & 0xF);
  d.signo = (uint8_t)((v >> LEP_PDEC_SIGN_SHIFT) & 1);
  for (int i = 0; i < LEP_PDEC_DIGITS; i++)
    d.digits[i] = (uint8_t)((v >> (LEP_PDEC_DIG_SHIFT + 4 * i)) & 0xF);
  return d;
}

static inline int64_t pdec_magnitude(PaxoPdec d) {
  int64_t m = 0, pow10 = 1;
  for (int i = 0; i < LEP_PDEC_DIGITS; i++) {
    m += (int64_t)(d.digits[i] & 0xF) * pow10;
    pow10 *= 10;
  }
  return m;
}

static inline int64_t pdec_value(PaxoPdec d) {
  int64_t m = pdec_magnitude(d);
  return d.signo ? -m : m;
}

static inline bool pdec_is_zero(PaxoPdec d) { return pdec_magnitude(d) == 0; }

// Construye dígitos BCD desde un entero con signo (clampa a 13 dígitos).
static inline PaxoPdec pdec_from_int64(int64_t v, uint8_t scale) {
  PaxoPdec d = {0};
  d.scale = scale > 15 ? 15 : scale;
  if (v < 0) {
    d.signo = 1;
    v = -v;
  }
  if (v > LEP_PDEC_MAX_MAG)
    v = LEP_PDEC_MAX_MAG;
  for (int i = 0; v && i < LEP_PDEC_DIGITS; i++) {
    d.digits[i] = (uint8_t)(v % 10);
    v /= 10;
  }
  return d;
}

static inline PaxoVar var_ref(uint32_t sub, uint32_t punt, uint16_t aux13) {
  return (LEP_TAG_REF << 62) | LEP_MARK_BOX | ((PaxoVar)(sub & 0x7u) << 18) |
         ((PaxoVar)(aux13 & 0x1FFFu) << LEP_VAL_SHIFT) | ((PaxoVar)punt << 21);
}

static inline uint32_t var_ref_sub_get(PaxoVar v) {
  return (uint32_t)((v >> 18) & 0x7u);
}

static inline uint32_t var_ref_punt_get(PaxoVar v) {
  return (uint32_t)((v >> 21) & 0xFFFFFFFFULL);
}

static inline uint16_t var_ref_aux_get(PaxoVar v) {
  return (uint16_t)((v >> LEP_VAL_SHIFT) & 0x1FFFu);
}

static inline PaxoVar var_string(const char *s) {
  return var_ref(REF_SUB_STRING, paxo_object_intern((void *)s, STRING), 0);
}

static inline const char *var_string_get(PaxoVar v) {
  return (const char *)paxo_object_ptr(v);
}

static inline PaxoVar var_array(PaxoArray *a) {
  return var_ref(REF_SUB_ARRAY, paxo_object_add(a, ARRAY), 0);
}

static inline PaxoArray *var_array_get(PaxoVar v) {
  return (PaxoArray *)paxo_object_ptr(v);
}

static inline PaxoVar var_pkg(PaxoPackageField *f) {
  return var_ref(REF_SUB_PKG, paxo_object_add(f, PACKAGE), 0);
}

static inline PaxoPackageField *var_pkg_get(PaxoVar v) {
  return (PaxoPackageField *)paxo_object_ptr(v);
}

static inline PaxoVar var_func(uint32_t func_id, uint8_t param_count) {
  return var_ref(REF_SUB_FUNC, func_id, param_count);
}

static inline uint32_t var_func_id(PaxoVar v) { return var_ref_punt_get(v); }

static inline uint8_t var_func_params(PaxoVar v) {
  return (uint8_t)var_ref_aux_get(v);
}

static inline PaxoVar var_pin(uint32_t id) {
  return var_ref(REF_SUB_PIN, id, 0);
}

static inline uint32_t var_pin_get(PaxoVar v) { return var_ref_punt_get(v); }

// ==========================================
// 4. NÚMEROS COMPLEJOS (tipo ni / sni)
//    Representación: ref a un objeto { re, im } donde cada componente es un
//    nanbox numérico (num16, num64 o int). La aritmética sigue el sistema de
//    los operandos: MP64 = ni, MP16 = sni. (El dominio BCD exacto / pdec fue
//    eliminado al deprecarse el tipo pdec.)
// ==========================================

#define LEP_COMPLEX_KIND_SNI 0u // componentes num16 (tipo sni)
#define LEP_COMPLEX_KIND_NI 1u  // componentes num64 (tipo ni)
#define LEP_COMPLEX_KIND_MASK 0x1FFFu

typedef struct {
  uint16_t kind; // LEP_COMPLEX_KIND_*
  PaxoVar re;
  PaxoVar im;
} PaxoComplex;

static inline PaxoVar var_complex_of(PaxoComplex c) {
  return var_ref(REF_SUB_COMPLEX, paxo_object_add(
                                      (PaxoComplex *)memcpy(
                                          malloc(sizeof(PaxoComplex)), &c,
                                          sizeof(PaxoComplex)),
                                      COMPLEX),
                 c.kind);
}

static inline PaxoComplex var_complex_get(PaxoVar v) {
  return *(PaxoComplex *)paxo_object_ptr(v);
}

static inline uint16_t var_complex_kind(PaxoVar v) {
  return var_ref_aux_get(v) & LEP_COMPLEX_KIND_MASK;
}

// construye según el tipo declarado: ni → MP64, sni → MP16
static inline PaxoVar var_complex_ni(Num64 re, Num64 im) {
  PaxoComplex c = {.kind = LEP_COMPLEX_KIND_NI, .re = var_num64(re),
                   .im = var_num64(im)};
  return var_complex_of(c);
}

static inline PaxoVar var_complex_sni(Num16 re, Num16 im) {
  PaxoComplex c = {.kind = LEP_COMPLEX_KIND_SNI, .re = var_num16(re),
                   .im = var_num16(im)};
  return var_complex_of(c);
}

static inline PaxoVar var_complex_scalar(PaxoVar x) {
  PaxoComplex c = {.re = x, .im = 0};
  switch (var_type(x)) {
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
  return var_complex_of(c);
}

static inline PaxoVar var_complex_zero_ni(void) {
  return var_complex_ni((Num64){0, BIAS64, 0, 0}, (Num64){0, BIAS64, 0, 0});
}

static inline PaxoVar var_complex_zero_sni(void) {
  return var_complex_sni((Num16){0, BIAS16, 0, 0}, (Num16){0, BIAS16, 0, 0});
}

static inline bool var_is_num(PaxoVar v) {
  uint32_t mark = (uint32_t)(v & LEP_MARK_MASK);
  return mark != LEP_MARK_BOX && mark != LEP_MARK_N16 &&
         mark != LEP_MARK_FXPKD;
}

static inline enum type var_type(PaxoVar v) {
  switch (v & LEP_MARK_MASK) {
  case LEP_MARK_BOX:
    switch (v >> 62) {
    case LEP_TAG_BIT:
      return VBOOL;
    case LEP_TAG_TRIT:
      return TRIT;
    case LEP_TAG_CHAR:
      if (v & LEP_COLOR_FLAG)
        return COLOR;
      return CHAR;
    default:
      switch (var_ref_sub_get(v)) {
      case REF_SUB_ARRAY:
        return ARRAY;
      case REF_SUB_PKG:
        return PACKAGE;
      case REF_SUB_STRING:
        return STRING;
      case REF_SUB_FUNC:
        return FUNC;
      case REF_SUB_COMPLEX:
        return (var_complex_kind(v) == LEP_COMPLEX_KIND_SNI) ? COMPLEX16
                                                              : COMPLEX;
      default:
        return POINT;
      }
    }
  case LEP_MARK_FXPKD:
    return (v >> 63) ? PKDEC : INT_FP;
  case LEP_MARK_N16:
    return NUM16;
  default:
    return NUM64;
  }
}

// Macro auxiliar para propagar el punto fijo de mayor precision
#define PROPAGAR_P(a, b) ((a.p > b.p) ? a.p : b.p)

// ==========================================
// 4. OPERACIONES ARITMÉTICAS: 16 BITS (MP16)
//    Radix mixto:  v = bc · 2^(-2p) · 10^(exp-BIAS)
//    Mantisa binaria pura; el punto salta en celdas de 2 bits y el
//    exponente cuenta décadas. Dominio canónico de trabajo
//    (unidades de 1/1024):  val = entero·1024 + fracción
//      canon(n) = bc << 2·(FRAC - p)
//      v = canon(n) · 10^(exp - BIAS) / 1024
// ==========================================

#define MP16_FRAC 5 // celdas de 2 bits que puede cruzar el punto

static inline uint64_t mp16_pow4(uint16_t n) {
  uint64_t r = 1;
  while (n--)
    r *= 4;
  return r;
}

static inline uint64_t num16_pow10(uint16_t n) {
  uint64_t r = 1;
  while (n--)
    r *= 10;
  return r;
}

// numerador canónico con signo en unidades de 1/1024
static inline int64_t num16_canon(Num16 n) {
  int64_t m = (int64_t)n.bc << (2 * (MP16_FRAC - n.p));
  return n.signo ? -m : m;
}

// modos de redondeo del reempaquetado
enum {
  MP16_MEDIO = 0, // al más cercano, .5 lejos de cero
  MP16_ARRIBA = 1 // hacia fuera: primer techo válido del escaneo
};

// num/den = valor leído en la década s con la frontera p
static inline void mp16_fraccion(uint64_t mag, int16_t e, int16_t s, uint16_t p,
                                 unsigned __int128 *num,
                                 unsigned __int128 *den) {
  *den = (unsigned __int128)1 << 10; // 4^MP16_FRAC
  *num = (unsigned __int128)mag * mp16_pow4(p);
  int16_t d = e - s;
  if (d >= 0)
    *num *= num16_pow10((uint16_t)d);
  else
    *den *= num16_pow10((uint16_t)(-d));
}

// Busca la representación más fina de ±V·10^e/1024:
//  paso 1: si algún (s,p) lo expresa EXACTO — década menor y luego p mayor
//  paso 2: el más cercano (empate lejos de cero); en modo ARRIBA toma el
//          primer techo válido del escaneo para subir sin clavarse
static inline Num16 num16_repack(uint8_t signo, int64_t V, int16_t e,
                                 uint8_t modo) {
  const int16_t e_min = -1, e_max = 3 - (int16_t)BIAS16;
  const uint16_t bc_max = bc_max16();

  if (V == 0)
    return (Num16){0, (uint16_t)BIAS16, 0, 0};

  uint64_t mag = (V < 0) ? (uint64_t)(-V) : (uint64_t)V;
  while (mag % 10 == 0) { // décadas exactas fuera del camino
    mag /= 10;
    e++;
  }

  unsigned __int128 num, den;

  // --- paso 1: ajuste exacto ---
  for (int16_t s = e_min; s <= e_max; s++) {
    for (int16_t p = MP16_FRAC; p >= 0; p--) {
      mp16_fraccion(mag, e, s, (uint16_t)p, &num, &den);
      if (num % den != 0)
        continue;
      uint64_t bc = (uint64_t)(num / den);
      if (bc >= 1 && bc <= bc_max)
        return (Num16){signo, (uint16_t)(s + BIAS16), (uint16_t)bc,
                       (uint16_t)p};
      if (bc == 0)
        break; // con p menores sería aún más pequeño
    }
  }

  // --- paso 2: redondeo ---
  // El error se mide en unidades canónicas de una década base común
  // (la más fina del escaneo) para que comparar décadas sea justo
  const int16_t base = e_min;
  unsigned __int128 objetivo = (unsigned __int128)mag;
  for (int16_t i = 0; i < e - base; i++)
    objetivo *= 10;

  int have = 0;
  uint64_t b_bc = 0;
  int16_t b_s = 0, b_p = 0;
  unsigned __int128 b_err = 0;
  for (int16_t s = e_min; s <= e_max; s++) {
    for (int16_t p = MP16_FRAC; p >= 0; p--) {
      mp16_fraccion(mag, e, s, (uint16_t)p, &num, &den);
      uint64_t bc = (modo == MP16_ARRIBA) ? (uint64_t)((num + den - 1) / den)
                                          : (uint64_t)((num + den / 2) / den);
      if (bc < 1 || bc > bc_max)
        continue;
      if (modo == MP16_ARRIBA)
        return (Num16){signo, (uint16_t)(s + BIAS16), (uint16_t)bc,
                       (uint16_t)p};
      // |objetivo − canon(bc,p)·10^(s−base)|
      unsigned __int128 valc = (unsigned __int128)bc << (2 * (MP16_FRAC - p));
      for (int16_t i = 0; i < s - base; i++)
        valc *= 10;
      unsigned __int128 err =
          (valc > objetivo) ? valc - objetivo : objetivo - valc;
      if (!have || err < b_err ||
          (err == b_err && (s < b_s || (s == b_s && (p > b_p || bc > b_bc))))) {
        have = 1;
        b_bc = bc;
        b_s = s;
        b_p = p;
        b_err = err;
      }
    }
  }
  if (have)
    return (Num16){signo, (uint16_t)(b_s + BIAS16), (uint16_t)b_bc,
                   (uint16_t)b_p};

  // sin candidato: desborde -> saturación; subflujo -> cero
  mp16_fraccion(mag, e, e_max, 0, &num, &den);
  return ((num + den / 2) > den * (unsigned __int128)bc_max)
             ? (Num16){signo, (uint16_t)(e_max + BIAS16), bc_max, 0}
             : (Num16){0, (uint16_t)BIAS16, 0, 0};
}

static inline Num16 add_num16(Num16 a, Num16 b) {
  if (a.bc == 0)
    return b;
  if (b.bc == 0)
    return a;

  int16_t ea = (int16_t)a.exp - BIAS16;
  int16_t eb = (int16_t)b.exp - BIAS16;
  int16_t e = (ea < eb) ? ea : eb;

  // lleva ambos numeradores canónicos a la década común más fina
  int64_t ma = num16_canon(a), mb = num16_canon(b);
  if (ea > eb)
    ma *= (int64_t)num16_pow10((uint16_t)(ea - eb));
  else if (eb > ea)
    mb *= (int64_t)num16_pow10((uint16_t)(eb - ea));

  int64_t suma = ma + mb;
  uint8_t sg = (suma < 0) ? 1 : 0;
  int64_t ab = sg ? -suma : suma;

  Num16 r = num16_repack(sg, ab, e, MP16_MEDIO);

  // Transición suave en el techo (señales iguales): si el redondeo se
  // quedó en el escalón del operando dominante pero la suma exacta ya lo
  // supera, sube al siguiente (1023+1 -> 1025, 1025+1 -> 1027.5, ...)
  if (a.signo == b.signo) {
    uint64_t ama = (ma < 0) ? (uint64_t)-ma : (uint64_t)ma;
    uint64_t amb = (mb < 0) ? (uint64_t)-mb : (uint64_t)mb;
    uint64_t dm = (ama > amb) ? ama : amb;
    int64_t rc = num16_canon(r);
    uint64_t rm = (rc < 0) ? (uint64_t)-rc : (uint64_t)rc;
    int16_t er = (int16_t)r.exp - BIAS16;
    uint64_t rv, dv;
    if (er >= e) {
      rv = rm * num16_pow10((uint16_t)(er - e));
      dv = dm;
    } else {
      rv = rm;
      dv = dm * num16_pow10((uint16_t)(e - er));
    }
    if (rv <= dv && (uint64_t)ab > dm)
      r = num16_repack(sg, ab, e, MP16_ARRIBA);
  }
  return r;
}

static inline Num16 sub_num16(Num16 a, Num16 b) {
  if (b.bc == 0)
    return a;
  b.signo = !b.signo;
  return add_num16(a, b);
}

static inline Num16 mul_num16(Num16 a, Num16 b) {
  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  int64_t va = num16_canon(a), vb = num16_canon(b);
  if (va == 0 || vb == 0)
    return (Num16){0, (uint16_t)BIAS16, 0, 0};
  uint64_t ua = (va < 0) ? (uint64_t)-va : (uint64_t)va;
  uint64_t ub = (vb < 0) ? (uint64_t)-vb : (uint64_t)vb;

  // canon_a · canon_b / 4^FRAC, redondeo al más cercano (.5 lejos de cero)
  uint64_t prod = ua * ub;
  uint64_t V = (prod >> 10) + ((prod & 1023) >= 512);
  return num16_repack(signo_res, (int64_t)V,
                      (int16_t)((a.exp - BIAS16) + (b.exp - BIAS16)),
                      MP16_MEDIO);
}

static inline Num16 div_num16(Num16 a, Num16 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num16){0, (uint16_t)BIAS16, 0, 0};
  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  int64_t va = num16_canon(a), vb = num16_canon(b);
  uint64_t ua = (va < 0) ? (uint64_t)-va : (uint64_t)va;
  uint64_t ub = (vb < 0) ? (uint64_t)-vb : (uint64_t)vb;

  // (canon_a << 10) / canon_b con redondeo al más cercano
  uint64_t numerador = ua << 10;
  uint64_t V = numerador / ub + ((numerador % ub) * 2 >= ub);
  return num16_repack(signo_res, (int64_t)V,
                      (int16_t)((a.exp - BIAS16) - (b.exp - BIAS16)),
                      MP16_MEDIO);
}

// ==========================================
// 5. OPERACIONES ARITMÉTICAS: 64 BITS (MP64)
//    El valor es v = bc · 10^(exp-BIAS-p); p cuenta décadas fraccionarias
//    y debe entrar en la alineación (no solo exp)
// ==========================================

Num64 add_num64(Num64 a, Num64 b) {
  if (a.bc == 0)
    return b;
  if (b.bc == 0)
    return a;

  const int16_t sesgo = BIAS64, exp_max = 255;
  const uint64_t bc_max = bc_max64();

  // décadas netas de cada operando (exp menos su punto fijo p)
  int16_t exp_a = (int16_t)a.exp - sesgo - (int16_t)a.p;
  int16_t exp_b = (int16_t)b.exp - sesgo - (int16_t)b.p;

  if (exp_a < exp_b) {
    Num64 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;
  if (diff_exp > 15)
    return (Num64){
        .signo = a.signo, .exp = a.exp, .bc = a.bc, .p = PROPAGAR_P(a, b)};

  __int128 val_a = (__int128)a.bc;
  __int128 val_b = (__int128)b.bc;

  for (int16_t i = 0; i < diff_exp; i++)
    val_a *= 10;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  __int128 suma = val_a + val_b;

  if (suma == 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned __int128 abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  // Suavizado en el techo: la subida de década redondea con techo para que
  // sumar 1 siempre avance (sin regresión ni quedarse clavado)
  while (abs_suma > bc_max) {
    abs_suma = (abs_suma + 9) / 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  // el p propagado vuelve al exponente almacenado para conservar la década
  uint16_t p_res = PROPAGAR_P(a, b);
  int16_t exp_almacenado = exp_res + (int16_t)p_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    abs_suma = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)abs_suma,
                 .p = p_res};
}

static inline Num64 sub_num64(Num64 a, Num64 b) {
  if (b.bc == 0)
    return a;
  b.signo = !b.signo;
  return add_num64(a, b);
}

static inline Num64 mul_num64(Num64 a, Num64 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num64){0, (uint64_t)BIAS64, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = BIAS64, exp_max = 255;
  const uint64_t bc_max = bc_max64();

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint16_t p_res = PROPAGAR_P(a, b);

  // el producto suma las décadas netas de ambos operandos
  int16_t exp_res = ((int16_t)a.exp - sesgo - (int16_t)a.p) +
                    ((int16_t)b.exp - sesgo - (int16_t)b.p);

  unsigned __int128 mult = (unsigned __int128)a.bc * b.bc;

  // Suavizado en el techo: la subida de década redondea con techo
  while (mult > bc_max) {
    mult = (mult + 9) / 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num64){0, (uint64_t)sesgo, 0, p_res};
  // el p propagado vuelve al exponente almacenado para conservar la década
  int16_t exp_almacenado = exp_res + (int16_t)p_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    mult = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num64){0, (uint64_t)sesgo, 0, p_res};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)mult,
                 .p = p_res};
}

static inline Num64 div_num64(Num64 a, Num64 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num64){0, (uint64_t)BIAS64, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = BIAS64, exp_max = 255, escala = 15;
  const uint64_t bc_max = bc_max64();

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint16_t p_res = PROPAGAR_P(a, b);

  // el cociente resta las décadas netas del divisor
  int16_t exp_res = ((int16_t)a.exp - sesgo - (int16_t)a.p) -
                    ((int16_t)b.exp - sesgo - (int16_t)b.p) - escala;

  unsigned __int128 num_a =
      (unsigned __int128)a.bc * 1000000000000000ULL; // 10^15
  unsigned __int128 div = num_a / b.bc;

  // Suavizado en el techo: la subida de década redondea con techo
  while (div > bc_max) {
    div = (div + 9) / 10;
    exp_res++;
  }

  if (div == 0)
    return (Num64){0, (uint64_t)sesgo, 0, p_res};
  // el p propagado vuelve al exponente almacenado para conservar la década
  int16_t exp_almacenado = exp_res + (int16_t)p_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    div = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num64){0, (uint64_t)sesgo, 0, p_res};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)div,
                 .p = p_res};
}

// ==========================================
// 6. COMPARACIONES MOBILE POINT
//    Retorna: -1 si a < b, 0 si a == b, 1 si a > b
// ==========================================

static inline int cmp_num16(Num16 a, Num16 b) {
  if (a.bc == 0 && b.bc == 0)
    return 0;
  if (a.bc == 0)
    return b.signo ? 1 : -1;
  if (b.bc == 0)
    return a.signo ? -1 : 1;
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;

  // compara los valores canónicos llevando ambos a la década mayor
  int16_t ea = (int16_t)a.exp - BIAS16;
  int16_t eb = (int16_t)b.exp - BIAS16;
  int16_t k = (ea > eb) ? ea : eb;
  int64_t ca = num16_canon(a) * (int64_t)num16_pow10((uint16_t)(k - ea));
  int64_t cb = num16_canon(b) * (int64_t)num16_pow10((uint16_t)(k - eb));

  if (ca < cb)
    return -1;
  if (ca > cb)
    return 1;
  return 0;
}

static inline int cmp_num64(Num64 a, Num64 b) {
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;

  __int128 val_a = (__int128)a.bc;
  __int128 val_b = (__int128)b.bc;

  // décadas netas: el punto fijo p resta del exponente
  int16_t bias_a = (int16_t)a.exp - BIAS64 - (int16_t)a.p;
  int16_t bias_b = (int16_t)b.exp - BIAS64 - (int16_t)b.p;

  if (bias_a > bias_b) {
    int16_t diff = bias_a - bias_b;
    for (int16_t i = 0; i < diff && val_a <= (__int128)bc_max64(); i++)
      val_a *= 10;
  } else if (bias_b > bias_a) {
    int16_t diff = bias_b - bias_a;
    for (int16_t i = 0; i < diff && val_b <= (__int128)bc_max64(); i++)
      val_b *= 10;
  }

  if (a.signo) {
    val_a = -val_a;
    val_b = -val_b;
  }

  if (val_a < val_b)
    return -1;
  if (val_a > val_b)
    return 1;
  return 0;
}

// ==========================================
// 7. ARITMÉTICA DE PUNTO FIJO (INT_FP, PaxoFxp) Y DECIMAL EMPAQUETADO
//    (PKDEC, PaxoPdec BCD). Son dos representaciones distintas (Nanbox.md §3.6):
//    - int  = entero escalado con signo en 13 bits (real = value·10^(-scale)).
//    - pdec = dígitos BCD en nibbles con signo y escala separados (real =
//             Σ dígitos·10^i · 10^(-scale)); carry/borrow decimal exacto.
// ==========================================

#define FXP_SCALE_MAX 15
#define FXP_MAG_MAX ((int64_t)0x1FFF) // 13 bits

static inline int64_t fxp_div10_round(int64_t v) {
  int64_t m = v < 0 ? -v : v;
  m = (m + 5) / 10;
  return v < 0 ? -m : m;
}

// Baja la escala (dividiendo y redondeando) hasta que la magnitud quepa en
// 13 bits; si incluso en escala 0 desborda, satura al límite del formato.
static inline PaxoFxp fxp_pack(int64_t r, uint8_t scale) {
  while ((r > FXP_MAG_MAX || r < -FXP_MAG_MAX) && scale > 0) {
    r = fxp_div10_round(r);
    scale--;
  }
  if (r > FXP_MAG_MAX)
    r = FXP_MAG_MAX;
  if (r < -FXP_MAG_MAX)
    r = -FXP_MAG_MAX;
  return (PaxoFxp){.value = (int16_t)r, .scale = scale};
}

static inline PaxoFxp add_fxp(PaxoFxp a, PaxoFxp b) {
  uint8_t s = (a.scale > b.scale) ? a.scale : b.scale;
  int64_t av = (int64_t)a.value * num16_pow10((uint16_t)(s - a.scale));
  int64_t bv = (int64_t)b.value * num16_pow10((uint16_t)(s - b.scale));
  return fxp_pack(av + bv, s);
}

static inline PaxoFxp sub_fxp(PaxoFxp a, PaxoFxp b) {
  b.value = (int16_t)-b.value;
  return add_fxp(a, b);
}

static inline PaxoFxp mul_fxp(PaxoFxp a, PaxoFxp b) {
  int64_t r = (int64_t)a.value * b.value;
  int32_t s = (int32_t)a.scale + (int32_t)b.scale;
  while (s > FXP_SCALE_MAX) {
    r = fxp_div10_round(r);
    s--;
  }
  return fxp_pack(r, (uint8_t)s);
}

static inline PaxoFxp div_fxp(PaxoFxp a, PaxoFxp b) {
  if (a.value == 0 || b.value == 0)
    return (PaxoFxp){.value = 0, .scale = 0};
  // cociente con la mayor escala de los operandos, sin pasarse de 15
  int32_t s = (a.scale > b.scale) ? a.scale : b.scale;
  while (s > 0 && ((int32_t)b.scale - (int32_t)a.scale + s) > FXP_SCALE_MAX)
    s--;
  int32_t e = (int32_t)b.scale - (int32_t)a.scale + s;
  int64_t num = a.value;
  for (int32_t i = 0; i < e; i++)
    num *= 10;
  int64_t q = num / b.value;
  int64_t rem = num % b.value;
  int64_t rm = rem < 0 ? -rem : rem;
  int64_t dm = b.value < 0 ? -(int64_t)b.value : (int64_t)b.value;
  if (rm * 2 >= dm) // redondeo .5 lejos de cero
    q += (q >= 0) ? 1 : -1;
  return fxp_pack(q, (uint8_t)s);
}

// --- decimal empaquetado (BCD): PaxoPdec -------------------------------------
// Álgebra decimal exacta: magnitudes alineadas en acumulador de 128 bits y
// resultado repaqueteado a dígitos BCD (carry/borrow decimal sobre dígitos).

// Lleva una magnitud (escala, signo) a dígitos BCD, saturado a 13 dígitos.
// No baja la escala: la precisión decimal se conserva al máximo.
static inline PaxoPdec pdec_from_mag128(unsigned __int128 m, uint8_t scale,
                                        uint8_t signo) {
  PaxoPdec r = {0};
  r.scale = scale > 15 ? 15 : scale;
  r.signo = signo & 1;
  if (m > (unsigned __int128)LEP_PDEC_MAX_MAG)
    m = (unsigned __int128)LEP_PDEC_MAX_MAG;
  for (int i = 0; m && i < LEP_PDEC_DIGITS; i++) {
    r.digits[i] = (uint8_t)(m % 10);
    m /= 10;
  }
  return r;
}

// Alinea la magnitud a la escala target multiplicando por 10.
static inline unsigned __int128 pdec_mag_to_scale(PaxoPdec d, uint8_t target) {
  unsigned __int128 m = (unsigned __int128)pdec_magnitude(d);
  for (uint8_t i = d.scale; i < target; i++)
    m *= 10;
  return m;
}

// suma (o resta con signo opuesto) decimal exacta.
static inline PaxoPdec pdec_add(PaxoPdec a, PaxoPdec b) {
  uint8_t s = (a.scale > b.scale) ? a.scale : b.scale;
  unsigned __int128 am = pdec_mag_to_scale(a, s);
  unsigned __int128 bm = pdec_mag_to_scale(b, s);
  if (a.signo == b.signo)
    return pdec_from_mag128(am + bm, s, a.signo);
  if (am >= bm)
    return pdec_from_mag128(am - bm, s, a.signo);
  return pdec_from_mag128(bm - am, s, b.signo);
}

static inline PaxoPdec pdec_sub(PaxoPdec a, PaxoPdec b) {
  b.signo ^= 1;
  return pdec_add(a, b);
}

// Compara dos valores decimales (exacto, sin pasar por num64).
static inline int pdec_cmp(PaxoPdec a, PaxoPdec b) {
  uint8_t s = (a.scale > b.scale) ? a.scale : b.scale;
  unsigned __int128 av = pdec_mag_to_scale(a, s);
  unsigned __int128 bv = pdec_mag_to_scale(b, s);
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;
  if (av == bv)
    return 0;
  return (av > bv) ? (a.signo ? -1 : 1) : (a.signo ? 1 : -1);
}

// multiplicación decimal: producto de magnitudes, escala sumada; baja la
// escala solo si pasa de 15 (redondeando el dígito perdido).
static inline PaxoPdec pdec_mul(PaxoPdec a, PaxoPdec b) {
  unsigned __int128 m = (unsigned __int128)pdec_magnitude(a) *
                        (unsigned __int128)pdec_magnitude(b);
  int32_t s = (int32_t)a.scale + (int32_t)b.scale;
  while (s > FXP_SCALE_MAX) {
    m = (m + 5) / 10;
    s--;
  }
  return pdec_from_mag128(m, (uint8_t)s, a.signo ^ b.signo);
}

// división decimal con redondeo .5 lejos de cero, a la mayor escala.
static inline PaxoPdec pdec_div(PaxoPdec a, PaxoPdec b) {
  uint8_t signo = a.signo ^ b.signo;
  if (pdec_is_zero(a) || pdec_is_zero(b))
    return pdec_from_int64(0, 0);
  int32_t s = (a.scale > b.scale) ? a.scale : b.scale;
  while (s > 0 && ((int32_t)b.scale - (int32_t)a.scale + s) > FXP_SCALE_MAX)
    s--;
  int32_t e = (int32_t)b.scale - (int32_t)a.scale + s;
  unsigned __int128 num = (unsigned __int128)pdec_magnitude(a);
  for (int32_t i = 0; i < e; i++)
    num *= 10;
  unsigned __int128 dm = (unsigned __int128)pdec_magnitude(b);
  unsigned __int128 q = num / dm;
  unsigned __int128 rem = num % dm;
  if ((rem * 2) >= dm) // redondeo .5 lejos de cero
    q++;
  return pdec_from_mag128(q, (uint8_t)s, signo);
}

static inline PaxoPdec pdec_neg(PaxoPdec a) {
  a.signo ^= 1;
  return a;
}

static inline PaxoPdec pdec_abs(PaxoPdec a) {
  a.signo = 0;
  return a;
}

static inline PaxoFxp neg_fxp(PaxoFxp a) {
  a.value = (int16_t)-a.value;
  return a;
}

static inline PaxoFxp abs_fxp(PaxoFxp a) {
  if (a.value < 0)
    a.value = (int16_t)-a.value;
  return a;
}

// Compara valores escalados llevando ambos a la mayor escala.
static inline int cmp_fxp(PaxoFxp a, PaxoFxp b) {
  uint8_t s = (a.scale > b.scale) ? a.scale : b.scale;
  int64_t av = (int64_t)a.value * num16_pow10((uint16_t)(s - a.scale));
  int64_t bv = (int64_t)b.value * num16_pow10((uint16_t)(s - b.scale));
  if (av < bv)
    return -1;
  if (av > bv)
    return 1;
  return 0;
}
