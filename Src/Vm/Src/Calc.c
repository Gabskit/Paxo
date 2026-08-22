#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <uchar.h>

typedef unsigned char char8_t;
typedef unsigned _BitInt(2) PaxoBool;

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
  BOOL,
  POINT,
  FUNC,
  STRING,
  ARRAY,
  PACKAGE
};

// ==========================================
// 2. NANBOX 64 BITS
//    número : MP64 directo            (p != 26)
//    bit    : 00 ················· x 11010
//    trit   : 01 ················ xx 11010
//    char   : 10 ··········[char32]·· 11010
//    ref    : 11 ···[aux16][punt32]·· 11010
//    num16  : MP16 embebido, marcador reservado 11011
// ==========================================

typedef uint64_t PaxoVar;

#define PAXO_MARK_BOX 0x1AULL
#define PAXO_MARK_N16 0x1BULL
#define PAXO_MARK_MASK 0x1FULL
#define PAXO_VAL_SHIFT 5

#define PAXO_TAG_BIT 0x0ULL
#define PAXO_TAG_TRIT 0x1ULL
#define PAXO_TAG_CHAR 0x2ULL
#define PAXO_TAG_REF 0x3ULL

#define REF_SUB_ARRAY 0u
#define REF_SUB_PKG 1u
#define REF_SUB_STRING 2u
#define REF_SUB_FUNC 3u
#define REF_SUB_PIN 4u

#define PAXO_NO_VALUE UINT64_MAX

typedef struct PaxoPackageField {
  char *key;
  struct PaxoPackageField *next;
  PaxoVar value;
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
  return (uint16_t)((n.signo) | ((uint16_t)n.exp << 1) |
                    ((uint16_t)n.bc << 3) | ((uint16_t)n.p << 13));
}

static inline Num16 num16_unpack(uint16_t raw) {
  return (Num16){.signo = raw & 1,
                 .exp = (raw >> 1) & 0x3,
                 .bc = (raw >> 3) & 0x3FF,
                 .p = (raw >> 13)};
}

static inline PaxoVar var_num16(Num16 n) {
  return ((PaxoVar)num16_pack(n) << PAXO_VAL_SHIFT) | PAXO_MARK_N16;
}

#define PAXO_ZERO var_num16((Num16){0})

static inline Num16 var_num16_get(PaxoVar v) {
  return num16_unpack((uint16_t)(v >> PAXO_VAL_SHIFT));
}

static inline PaxoVar var_bool(bool b) {
  return (PAXO_TAG_BIT << 62) | PAXO_MARK_BOX |
         ((PaxoVar)(b ? 1u : 0u) << PAXO_VAL_SHIFT);
}

static inline bool var_bool_get(PaxoVar v) {
  return (v >> PAXO_VAL_SHIFT) & 1;
}

static inline PaxoVar var_trit(uint8_t t) {
  return (PAXO_TAG_TRIT << 62) | PAXO_MARK_BOX |
         ((PaxoVar)(t & 0x3u) << PAXO_VAL_SHIFT);
}

static inline uint8_t var_trit_get(PaxoVar v) {
  return (uint8_t)((v >> PAXO_VAL_SHIFT) & 0x3u);
}

static inline PaxoVar var_char(char32_t c) {
  return (PAXO_TAG_CHAR << 62) | PAXO_MARK_BOX |
         ((PaxoVar)c << PAXO_VAL_SHIFT);
}

static inline char32_t var_char_get(PaxoVar v) {
  return (char32_t)((v >> PAXO_VAL_SHIFT) & 0xFFFFFFFFULL);
}

static inline PaxoVar var_ref(uint32_t sub, uint32_t punt, uint16_t aux13) {
  return (PAXO_TAG_REF << 62) | PAXO_MARK_BOX |
         ((PaxoVar)(sub & 0x7u) << 18) |
         ((PaxoVar)(aux13 & 0x1FFFu) << PAXO_VAL_SHIFT) |
         ((PaxoVar)punt << 21);
}

static inline uint32_t var_ref_sub_get(PaxoVar v) {
  return (uint32_t)((v >> 18) & 0x7u);
}

static inline uint32_t var_ref_punt_get(PaxoVar v) {
  return (uint32_t)((v >> 21) & 0xFFFFFFFFULL);
}

static inline uint16_t var_ref_aux_get(PaxoVar v) {
  return (uint16_t)((v >> PAXO_VAL_SHIFT) & 0x1FFFu);
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

static inline bool var_is_num(PaxoVar v) {
  uint32_t mark = (uint32_t)(v & PAXO_MARK_MASK);
  return mark != PAXO_MARK_BOX && mark != PAXO_MARK_N16;
}

static inline enum type var_type(PaxoVar v) {
  switch (v & PAXO_MARK_MASK) {
  case PAXO_MARK_BOX:
    switch (v >> 62) {
    case PAXO_TAG_BIT:
      return BOOL;
    case PAXO_TAG_TRIT:
      return TRIT;
    case PAXO_TAG_CHAR:
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
      default:
        return POINT;
      }
    }
  case PAXO_MARK_N16:
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
enum { MP16_MEDIO = 0,   // al más cercano, .5 lejos de cero
       MP16_ARRIBA = 1 // hacia fuera: primer techo válido del escaneo
};

// num/den = valor leído en la década s con la frontera p
static inline void mp16_fraccion(uint64_t mag, int16_t e, int16_t s,
                                 uint16_t p, unsigned _BitInt(128) *num,
                                 unsigned _BitInt(128) *den) {
  *den = (unsigned _BitInt(128))1 << 10; // 4^MP16_FRAC
  *num = (unsigned _BitInt(128))mag * mp16_pow4(p);
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

  unsigned _BitInt(128) num, den;

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
  unsigned _BitInt(128) objetivo = (unsigned _BitInt(128))mag;
  for (int16_t i = 0; i < e - base; i++)
    objetivo *= 10;

  int have = 0;
  uint64_t b_bc = 0;
  int16_t b_s = 0, b_p = 0;
  unsigned _BitInt(128) b_err = 0;
  for (int16_t s = e_min; s <= e_max; s++) {
    for (int16_t p = MP16_FRAC; p >= 0; p--) {
      mp16_fraccion(mag, e, s, (uint16_t)p, &num, &den);
      uint64_t bc =
          (modo == MP16_ARRIBA) ? (uint64_t)((num + den - 1) / den)
                                : (uint64_t)((num + den / 2) / den);
      if (bc < 1 || bc > bc_max)
        continue;
      if (modo == MP16_ARRIBA)
        return (Num16){signo, (uint16_t)(s + BIAS16), (uint16_t)bc,
                       (uint16_t)p};
      // |objetivo − canon(bc,p)·10^(s−base)|
      unsigned _BitInt(128) valc =
          (unsigned _BitInt(128))bc << (2 * (MP16_FRAC - p));
      for (int16_t i = 0; i < s - base; i++)
        valc *= 10;
      unsigned _BitInt(128) err =
          (valc > objetivo) ? valc - objetivo : objetivo - valc;
      if (!have || err < b_err ||
          (err == b_err &&
           (s < b_s || (s == b_s && (p > b_p || bc > b_bc))))) {
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
  return ((num + den / 2) > den * (unsigned _BitInt(128))bc_max)
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
    return (Num64){.signo = a.signo, .exp = a.exp, .bc = a.bc,
                   .p = PROPAGAR_P(a, b)};

  _BitInt(128) val_a = (_BitInt(128))a.bc;
  _BitInt(128) val_b = (_BitInt(128))b.bc;

  for (int16_t i = 0; i < diff_exp; i++)
    val_a *= 10;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;

  if (suma == 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
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

  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.bc * b.bc;

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

  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.bc * 1000000000000000ULL; // 10^15
  unsigned _BitInt(128) div = num_a / b.bc;

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
