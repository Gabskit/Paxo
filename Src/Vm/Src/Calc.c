#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char char8_t;
typedef uint32_t char32_t;
typedef uint8_t LEPBool;

#define BIASNUM 7
#define LEP_VAL_SHIFT 47u
#define REF_SUB_STRING 0u
#define REF_SUB_ARRAY 1u
#define REF_SUB_PKG 2u
#define REF_SUB_FUNC 3u
#define REF_SUB_PIN 4u

typedef struct {
	uint64_t signo: 1;
	uint64_t exp: 5;
	uint64_t mantisa: 54;
} __attribute__((packed)) Number;

typedef struct {
	struct {
		uint32_t signo: 1;
		uint32_t exp: 2;
		uint32_t mantisa: 27;
	} real;
	struct {
		uint32_t signo: 1;
		uint32_t exp: 2;
		uint32_t mantisa: 27;
	} imaginary;
} __attribute__((packed)) Complex;

static inline uint64_t man_maxnum(void) { return 9999999999999999ULL;}
static inline uint32_t man_maxcom(void) { return 99999999; }

/*Tipos de datos
num tag 0 signo 1 exp 5 mantisa 54 
char tag 1 32 bits
trit tag 2 2 bits ∅ • ✓
bool tag 3 1 bit .× .✓
point tag 4 puntero
func tag 5 función se usa el puntero hacia la función 
string tag 6 cadena de texto
array tag 7 cadenas
pkg tag 8 paquete
color tag 9 rgba 8 bits por canal
complejo tag 10 parte real e imaginaria [2x [signo 1 exp 2 mantisa 27 ]]*/

typedef enum : uint8_t {
    NUM, CHAR, TRIT, BOOL, POINT, FUNC,
    STRING, ARRAY, PACKAGE, COLOR, COMPLEX
} LEPType;

typedef struct {
    LEPType type : 4;                 // 4 bits de tipo (0 a 15)
    uint64_t payload : 60; // 60 bits de datos 
} __attribute__((packed)) LEPVar;

#define LEP_VAL_SHIFT 47u
#define REF_SUB_STRING 0u
#define REF_SUB_ARRAY 1u
#define REF_SUB_PKG 2u
#define REF_SUB_FUNC 3u
#define REF_SUB_PIN 4u


typedef struct LEPPackageField {
  char *key;
  struct LEPPackageField *next;
  LEPVar value;
  bool hidden; // campo privado (declarado con 'local' dentro del pkg)
} LEPPackageField;

typedef struct {
  LEPVar *items;
  size_t len;
  size_t capacity;
} LEPArray;

typedef struct LEPObject {
  void *ptr;
  uint8_t type;
} LEPObject;

static LEPObject *LEP_objects = NULL;
static uint32_t LEP_object_count = 0;
static uint32_t LEP_object_capacity = 0;

static inline uint32_t LEP_object_add(void *ptr, uint8_t type) {
  if (LEP_object_count == LEP_object_capacity) {
    LEP_object_capacity =
        LEP_object_capacity ? LEP_object_capacity * 2 : 256;
    LEP_objects =
        realloc(LEP_objects, sizeof(LEPObject) * LEP_object_capacity);
  }
  LEP_objects[LEP_object_count] = (LEPObject){.ptr = ptr, .type = type};
  return LEP_object_count++;
}

static inline void *LEP_object_ptr(LEPVar v) {
  return LEP_objects[(v.payload >> 21) & 0xFFFFFFFFULL].ptr;
}

static inline uint32_t LEP_object_intern(void *ptr, uint8_t type) {
  for (uint32_t i = 0; i < LEP_object_count; i++) {
    if (LEP_objects[i].ptr == ptr && LEP_objects[i].type == type)
      return i;
  }
  return LEP_object_add(ptr, type);
}

// ==========================================
// 3. CONSTRUCTORES / ACCESORES
// ==========================================

static inline LEPVar var_num(Number n) {
    uint64_t pnum = (((uint64_t)n.signo & 0x1ULL) << 59)
                  | (((uint64_t)n.exp & 0x1FULL) << 54)
          | ((uint64_t)n.mantisa & 0x3FFFFFFFFFFFFFULL);

    return (LEPVar){
        .type = NUM,
        .payload = pnum
    };
}

static inline Number var_num_get(LEPVar v) {
    uint64_t data = (uint64_t)v.payload;
    return (Number){
        .signo = (uint8_t)((data >> 59) & 0x1ULL),
        .exp = (uint8_t)((data >> 54) & 0x1FULL),
      .mantisa = data & 0x3FFFFFFFFFFFFFULL
    };
}

static inline LEPVar var_bool(bool b) {
  return (LEPVar){BOOL, b };
}

static inline bool var_bool_get(LEPVar v) { return v.payload & 0x1u; }

static inline LEPVar var_trit(uint8_t t) {
  return (LEPVar){TRIT, t};
}

static inline uint8_t var_trit_get(LEPVar v) {
  return (uint8_t)(v.payload & 0x3u);
}

static inline LEPVar var_char(char32_t c) {
  return (LEPVar){CHAR, c};
}

static inline char32_t var_char_get(LEPVar v) {
  return (char32_t)(v.payload & 0xFFFFFFFFULL);
}

static inline LEPVar var_color(uint32_t rgba) {
  return (LEPVar){COLOR, rgba};
}

static inline uint32_t var_color_get(LEPVar v) {
  return (uint32_t)(v.payload & 0xFFFFFFFFULL);
}

static inline LEPVar var_ref(uint32_t sub, uint32_t punt, uint16_t aux) {
  return (LEPVar){
      .type = POINT,
      .payload = ((uint64_t)(sub & 0x7u) << 18) |
                 ((uint64_t)(punt & 0xFFFFFFFFu) << 21) |
                 ((uint64_t)(aux & 0x1FFFu) << LEP_VAL_SHIFT)};
}

static inline uint32_t var_ref_sub_get(LEPVar v) {
  return (uint32_t)((v.payload >> 18) & 0x7u);
}

static inline uint32_t var_ref_punt_get(LEPVar v) {
  return (uint32_t)((v.payload >> 21) & 0xFFFFFFFFULL);
}

static inline uint16_t var_ref_aux_get(LEPVar v) {
  return (uint16_t)((v.payload >> LEP_VAL_SHIFT) & 0x7Fu);
}

static inline LEPVar var_string(const char *s) {
  return var_ref(REF_SUB_STRING, LEP_object_intern((void *)s, STRING), 0);
}

static inline const char *var_string_get(LEPVar v) {
  return (const char *)LEP_object_ptr(v);
}

static inline LEPVar var_array(LEPArray *a) {
  return var_ref(REF_SUB_ARRAY, LEP_object_add(a, ARRAY), 0);
}

static inline LEPArray *var_array_get(LEPVar v) {
  return (LEPArray *)LEP_object_ptr(v);
}

static inline LEPVar var_pkg(LEPPackageField *f) {
  return var_ref(REF_SUB_PKG, LEP_object_add(f, PACKAGE), 0);
}

static inline LEPPackageField *var_pkg_get(LEPVar v) {
  return (LEPPackageField *)LEP_object_ptr(v);
}

static inline LEPVar var_func(uint32_t func_id, uint8_t param_count) {
  return var_ref(REF_SUB_FUNC, func_id, param_count);
}

static inline uint32_t var_func_id(LEPVar v) { return var_ref_punt_get(v); }

static inline uint8_t var_func_params(LEPVar v) {
  return (uint8_t)var_ref_aux_get(v);
}

static inline LEPVar var_pin(uint32_t id) {
  return var_ref(REF_SUB_PIN, id, 0);
}

static inline uint32_t var_pin_get(LEPVar v) { return var_ref_punt_get(v); }

static inline LEPVar var_complex(Complex ni) {
  uint64_t payload = ((uint64_t)ni.real.signo << 59) |
                     ((uint64_t)ni.real.exp << 57) |
                     ((uint64_t)ni.real.mantisa << 30) |
                     ((uint64_t)ni.imaginary.signo << 29) |
                     ((uint64_t)ni.imaginary.exp << 27) |
                     (uint64_t)ni.imaginary.mantisa;
  return (LEPVar){COMPLEX, payload};
}

static inline Complex var_complex_get(LEPVar v) {
  uint64_t payload = v.payload;
  Complex ni = {0};
  ni.real.signo = (payload >> 59) & 1u;
  ni.real.exp = (payload >> 57) & 0x3u;
  ni.real.mantisa = (payload >> 30) & 0x7FFFFFFu;
  ni.imaginary.signo = (payload >> 29) & 1u;
  ni.imaginary.exp = (payload >> 27) & 0x3u;
  ni.imaginary.mantisa = payload & 0x7FFFFFFu;
  return ni;
}

static inline bool var_is_num(LEPVar v) {
  return v.type == NUM;
}

static inline LEPType var_type(LEPVar v) {
  return v.type;
}

// ==========================================
// 5me  OPERACIONES ARITMÉTICAS: 64 BITS Number
/* signo 1 exp 5 mantisa 54
sumas resta multiplicación división etc.
*/

// ==========================================

static inline unsigned __int128 num_pow4(uint16_t n) {
  unsigned __int128 r = 1;
  while (n--)
    r *= 4;
  return r;
}

static inline unsigned __int128 num_pow10(uint16_t n) {
  unsigned __int128 r = 1;
  while (n--)
    r *= 10;
  return r;
}

enum {
  num_MEDIO = 0, // al más cercano, .5 lejos de cero
  num_ARRIBA = 1 // hacia fuera: primer techo válido del escaneo
};

// Busca la representación más fina de ±V·10^e / 2^50
static inline Number num_repack(uint8_t signo, __int128 V, int16_t e,
                                uint8_t modo) {
  (void)modo;
  if (V == 0)
    return (Number){0, BIASNUM, 0};
  unsigned __int128 mag = V < 0 ? (unsigned __int128)-V : (unsigned __int128)V;
  while (mag > man_maxnum() && e < 31) {
    mag = (mag + 5) / 10;
    e++;
  }
  while (mag && mag % 10 == 0 && e < 31) {
    mag /= 10;
    e++;
  }
  if (e < -BIASNUM)
    return (Number){0, BIASNUM, 0};
  if (e > 31 - BIASNUM)
    return (Number){signo, 31, man_maxnum()};
  return (Number){signo, (uint8_t)(e + BIASNUM), (uint64_t)mag};
}

#if 0

  if (V == 0)
    return (Number){0, (uint16_t) BIASNUM, 0};

  unsigned __int128 mag =
      (V < 0) ? (unsigned __int128)(-V) : (unsigned __int128)V;
  while (mag % 10 == 0) { // décadas exactas fuera del camino
    mag /= 10;
    e++;
  }

  unsigned __int128 num, den;

  int16_t s_start = e - 16;
  if (s_start < e_min)
    s_start = e_min;
  int16_t s_end = e + 16;
  if (s_end > e_max)
    s_end = e_max;

  // --- paso 1: ajuste exacto ---
  for (int16_t s = s_start; s <= s_end; s++) {
    for (int16_t p = MP64_FRAC; p >= 0; p--) {
      mp64_fraccion(mag, e, s, (uint16_t)p, &num, &den);
      if (num % den != 0)
        continue;
      unsigned __int128 bc = num / den;
      if (bc >= 1 && bc <= bc_max)
        return (Number){signo, (uint16_t)(s + BIAS64), (uint64_t)bc,
                       (uint16_t)p};
      if (bc == 0)
        break; // con p menores sería aún más pequeño
    }
  }

  // --- paso 2: redondeo ---
  int have = 0;
  uint64_t b_bc = 0;
  int16_t b_s = 0, b_p = 0;
  unsigned __int128 b_Q = 0, b_R = 0, b_D = 1;

  for (int16_t s = s_start; s <= s_end; s++) {
    for (int16_t p = MP64_FRAC; p >= 0; p--) {
      mp64_fraccion(mag, e, s, (uint16_t)p, &num, &den);
      uint64_t bc = (modo == MP64_ARRIBA) ? (uint64_t)((num + den - 1) / den)
                                          : (uint64_t)((num + den / 2) / den);
      if (bc < 1 || bc > bc_max)
        continue;
      if (modo == MP64_ARRIBA)
        return (Number){signo, (uint16_t)(s + BIAS64), (uint64_t)bc,
                       (uint16_t)p};

      // Cálculo exacto del error normalizado a la década e
      unsigned __int128 valc = (unsigned __int128)bc << (2 * (MP64_FRAC - p));
      unsigned __int128 N, D;
      if (s <= e) {
        unsigned __int128 target = mag * num64_pow10((uint16_t)(e - s));
        N = (valc > target) ? (valc - target) : (target - valc);
        D = num64_pow10((uint16_t)(e - s));
      } else {
        unsigned __int128 scaled_val = valc * num64_pow10((uint16_t)(s - e));
        N = (scaled_val > mag) ? (scaled_val - mag) : (mag - scaled_val);
        D = 1;
      }

      unsigned __int128 Q = N / D;
      unsigned __int128 R = N % D;

      bool better = false;
      if (!have) {
        better = true;
      } else if (Q < b_Q) {
        better = true;
      } else if (Q == b_Q) {
        unsigned __int128 lhs = R * b_D;
        unsigned __int128 rhs = b_R * D;
        if (lhs < rhs) {
          better = true;
        } else if (lhs == rhs) {
          if (s < b_s || (s == b_s && (p > b_p || bc > b_bc)))
            better = true;
        }
      }

      if (better) {
        have = 1;
        b_bc = bc;
        b_s = s;
        b_p = p;
        b_Q = Q;
        b_R = R;
        b_D = D;
      }
    }
  }
  if (have)
    return (Number){signo, (uint16_t)(b_s + BIAS64), (uint64_t)b_bc,
                   (uint16_t)b_p};

  // sin candidato: desborde -> saturación; subflujo -> cero
  mp64_fraccion(mag, e, e_max, 0, &num, &den);
  return ((num + den / 2) > den * (unsigned __int128)bc_max)
             ? (Number){signo, (uint16_t)(e_max + BIAS64), bc_max, 0}
             : (Number){0, (uint16_t)BIAS64, 0, 0};
}

#endif

static inline __int128 number_signed_mantisa(Number n) {
  __int128 value = n.mantisa;
  return n.signo ? -value : value;
}

static inline Number add_num(Number a, Number b) {
  int16_t ea = (int16_t)a.exp - BIASNUM;
  int16_t eb = (int16_t)b.exp - BIASNUM;
  int16_t e = ea < eb ? ea : eb;
  __int128 va = number_signed_mantisa(a);
  __int128 vb = number_signed_mantisa(b);
  for (int16_t i = 0; i < ea - e; i++) va *= 10;
  for (int16_t i = 0; i < eb - e; i++) vb *= 10;
  __int128 result = va + vb;
  return num_repack(result < 0, result < 0 ? -result : result, e, num_MEDIO);
}

static inline Number sub_num(Number a, Number b) {
  b.signo = !b.signo;
  return add_num(a, b);
}

static inline Number mul_num(Number a, Number b) {
  __int128 result = number_signed_mantisa(a) * number_signed_mantisa(b);
  int16_t e = (int16_t)a.exp + (int16_t)b.exp - 2 * BIASNUM;
  return num_repack(result < 0, result < 0 ? -result : result, e, num_MEDIO);
}

static inline Number div_num(Number a, Number b) {
  if (b.mantisa == 0)
    return (Number){0, BIASNUM, 0};
  __int128 numerator = number_signed_mantisa(a) * 1000000000000LL;
  __int128 result = numerator / number_signed_mantisa(b);
  int16_t e = (int16_t)a.exp - (int16_t)b.exp - 12;
  return num_repack(result < 0, result < 0 ? -result : result, e, num_MEDIO);
}

static inline int cmp_num(Number a, Number b) {
  if (a.mantisa == 0 && b.mantisa == 0)
    return 0;
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;
  int16_t ea = (int16_t)a.exp - BIASNUM;
  int16_t eb = (int16_t)b.exp - BIASNUM;
  __int128 va = number_signed_mantisa(a);
  __int128 vb = number_signed_mantisa(b);
  while (ea < eb) { va /= 10; ea++; }
  while (eb < ea) { vb /= 10; eb++; }
  return va < vb ? -1 : va > vb ? 1 : 0;
}

#if 0
  int16_t ea = (int16_t)a.exp - BIAS64;
  int16_t eb = (int16_t)b.exp - BIAS64;
  int16_t e = (ea < eb) ? ea : eb;

  __int128 ma = num64_canon(a), mb = num64_canon(b);
  if (ea > eb)
    ma *= num64_pow10((uint16_t)(ea - eb));
  else if (eb > ea)
    mb *= num64_pow10((uint16_t)(eb - ea));

  __int128 suma = ma + mb;
  uint8_t sg = (suma < 0) ? 1 : 0;
  __int128 ab = sg ? -suma : suma;

  if (a.signo == b.signo) {
    unsigned __int128 ama =
        (ma < 0) ? (unsigned __int128)-ma : (unsigned __int128)ma;
    unsigned __int128 amb =
        (mb < 0) ? (unsigned __int128)-mb : (unsigned __int128)mb;
    unsigned __int128 dm = (ama > amb) ? ama : amb;
    __int128 rc = num64_canon(r);
    unsigned __int128 rm =
        (rc < 0) ? (unsigned __int128)-rc : (unsigned __int128)rc;
    int16_t er = (int16_t)r.exp - BIAS64;
    unsigned __int128 rv, dv;
    if (er >= e) {
      rv = rm * num64_pow10((uint16_t)(er - e));
      dv = dm;
    } else {
      rv = rm;
      dv = dm * num64_pow10((uint16_t)(e - er));
    }
    if (rv <= dv && (unsigned __int128)ab > dm)
      r = num64_repack(sg, ab, e, MP64_ARRIBA);
  }
  return r;
}

static inline Number sub_num(Number a, Number b) {
  if (b.bc == 0)
    return a;
  b.signo = !b.signo;
  return add_num(a, b);
}

static inline Number mul_num(Number a, Number b) {
  if (a.bc == 0 || b.bc == 0)
    return (Number){0, (uint16_t)BIASNUM, 0};
  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  __int128 va = num64_canon(a), vb = num64_canon(b);
  unsigned __int128 ua =
      (va < 0) ? (unsigned __int128)-va : (unsigned __int128)va;
  unsigned __int128 ub =
      (vb < 0) ? (unsigned __int128)-vb : (unsigned __int128)vb;

  int16_t e_res = (int16_t)((a.exp - BIAS64) + (b.exp - BIAS64));

  while ((ua >> 50) * (ub >> 50) >= ((unsigned __int128)1 << 60)) {
    if (ua >= ub)
      ua = (ua + 5) / 10;
    else
      ub = (ub + 5) / 10;
    e_res++;
  }

  unsigned __int128 mask50 = ((unsigned __int128)1 << 50) - 1;
  unsigned __int128 ha = ua >> 50, la = ua & mask50;
  unsigned __int128 hb = ub >> 50, lb = ub & mask50;
  unsigned __int128 term0 = (la * lb + ((unsigned __int128)1 << 49)) >> 50;
  unsigned __int128 term1 = ha * lb + hb * la;
  unsigned __int128 term2 = ha * hb;
  unsigned __int128 V = (term2 << 50) + term1 + term0;

  return num64_repack(signo_res, (__int128)V, e_res, MP64_MEDIO);
}

static inline Number div_num(Number a, Number b) {
  if (b.bc == 0 || a.bc == 0)
    return (Number){0, (uint16_t)BIASNUM, 0};
  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  __int128 va = num64_canon(a), vb = num64_canon(b);
  unsigned __int128 ua =
      (va < 0) ? (unsigned __int128)-va : (unsigned __int128)va;
  unsigned __int128 ub =
      (vb < 0) ? (unsigned __int128)-vb : (unsigned __int128)vb;

  int16_t e_res = (int16_t)((a.exp - BIASNUM) - (b.exp - BIASNUM));

  while (ua >= ((unsigned __int128)1 << 75)) {
    ua = (ua + 5) / 10;
    e_res++;
  }

  unsigned __int128 numerador = ua << 50;
  unsigned __int128 V = numerador / ub + ((numerador % ub) * 2 >= ub);

  return num_repack(signo_res, (__int128)V, e_res, MP64_MEDIO);
}

static inline int cmp_num(Number a, Number b) {
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;

  int16_t ea = (int16_t)a.exp - BIASNUM;
  int16_t eb = (int16_t)b.exp - BIASNUM;
  int16_t k = (ea > eb) ? ea : eb;
  int64_t ca = num_canon(a) * (int64_t)num_pow10((uint16_t)(k - ea));
  int64_t cb = num_canon(b) * (int64_t)num_pow10((uint16_t)(k - eb));

  if (ca < cb)
    return -1;
  if (ca > cb)
    return 1;
  return 0;
}

#endif