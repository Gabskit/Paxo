#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char char8_t;
typedef uint32_t char32_t;
typedef uint8_t LEPBool;

#define BIASNUM 15
#define LEP_VAL_SHIFT 3u
#define REF_SUB_STRING 0u
#define REF_SUB_ARRAY 1u
#define REF_SUB_PKG 2u
#define REF_SUB_FUNC 3u
#define REF_SUB_PIN 4u

typedef struct {
	uint64_t signo: 1;
	uint64_t exp: 5;
	uint64_t mantisa: 54;
} Number;

typedef struct {
	struct {
		uint32_t signo: 1;
		uint32_t exp: 5;
		uint32_t mantisa: 24;
	} real;
	struct {
		uint32_t signo: 1;
		uint32_t exp: 5;
		uint32_t mantisa: 24;
	} imaginary;
} Complex;

static inline uint64_t man_maxnum(void) { return 9999999999999999ULL; }
static inline uint32_t man_maxcom(void) { return 9999999; }

/* Tipos de datos */
typedef enum type : uint8_t {
    NUM, CHAR, TRIT, BOOL, POINT, FUNC,
    STRING, ARRAY, PACKAGE, COLOR, COMPLEX
} LEPType;

typedef struct {
    LEPType type : 4;         // 4 bits de tipo (0 a 15)
    uint64_t payload : 60;    // 60 bits de datos 
} __attribute__((packed)) LEPVar;

#define LEP_ZERO ((LEPVar){ .type = NUM, .payload = 0 })

typedef struct LEPPackageField {
  char *key;
  struct LEPPackageField *next;
  LEPVar value;
  bool hidden;
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

static inline uint32_t LEP_object_intern(void *ptr, uint8_t type) {
  for (uint32_t i = 0; i < LEP_object_count; i++) {
    if (LEP_objects[i].ptr == ptr && LEP_objects[i].type == type)
      return i;
  }
  return LEP_object_add(ptr, type);
}

// ==========================================
// CONSTRUCTORES / ACCESORES
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
  return (LEPVar){.type = BOOL, .payload = b};
}

static inline bool var_bool_get(LEPVar v) { return v.payload & 0x1u; }

static inline LEPVar var_trit(uint8_t t) {
  return (LEPVar){.type = TRIT, .payload = t};
}

static inline uint8_t var_trit_get(LEPVar v) {
  return (uint8_t)(v.payload & 0x3u);
}

static inline LEPVar var_char(char32_t c) {
  return (LEPVar){.type = CHAR, .payload = c};
}

static inline char32_t var_char_get(LEPVar v) {
  return (char32_t)(v.payload & 0xFFFFFFFFULL);
}

static inline LEPVar var_color(uint32_t rgba) {
  return (LEPVar){.type = COLOR, .payload = rgba};
}

static inline uint32_t var_color_get(LEPVar v) {
  return (uint32_t)(v.payload & 0xFFFFFFFFULL);
}

static inline LEPVar var_ref(uint32_t sub, uint32_t punt, uint16_t aux) {
  return (LEPVar){
      .type = POINT,
      .payload = ((uint64_t)(sub & 0x7u) << 0) |
                 ((uint64_t)(aux & 0x1FFFu) << 3) |
                 ((uint64_t)(punt & 0xFFFFFFFFu) << 16)};
}

static inline uint32_t var_ref_sub_get(LEPVar v) {
  return (uint32_t)(v.payload & 0x7u);
}

static inline uint32_t var_ref_punt_get(LEPVar v) {
  return (uint32_t)((v.payload >> 16) & 0xFFFFFFFFULL);
}

static inline uint16_t var_ref_aux_get(LEPVar v) {
  return (uint16_t)((v.payload >> LEP_VAL_SHIFT) & 0x1FFFu);
}

static inline void *LEP_object_ptr(LEPVar v) {
  return LEP_objects[var_ref_punt_get(v)].ptr;
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
  return (LEPVar){.type = COMPLEX, .payload = payload};
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
// OPERACIONES ARITMÉTICAS: Number
// ==========================================

enum {
  num_MEDIO = 0,
  num_ARRIBA = 1
};

static inline Number num_repack(uint8_t signo, __int128 V, int16_t e, uint8_t modo) {
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

static inline __int128 number_signed_mantisa(Number n) {
  __int128 value = n.mantisa;
  return n.signo ? -value : value;
}

static inline __int128 pow10_128(int16_t exp) {
    __int128 result = 1;
    __int128 base = 10;
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

static inline Number add_num(Number a, Number b) {
    int16_t ea = (int16_t)a.exp - BIASNUM;
    int16_t eb = (int16_t)b.exp - BIASNUM;
    int16_t e = ea < eb ? ea : eb;
    
    __int128 va = number_signed_mantisa(a);
    __int128 vb = number_signed_mantisa(b);
    
    if (ea > e) va *= pow10_128(ea - e);
    if (eb > e) vb *= pow10_128(eb - e);
    
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
  if (a.mantisa == 0 && b.mantisa == 0) return 0;
  if (a.signo != b.signo) return a.signo ? -1 : 1;
  
  int16_t ea = (int16_t)a.exp - BIASNUM;
  int16_t eb = (int16_t)b.exp - BIASNUM;
  
  __int128 va = number_signed_mantisa(a);
  __int128 vb = number_signed_mantisa(b);
  
  if (ea > eb) {
      va *= pow10_128(ea - eb);
  } else if (eb > ea) {
      vb *= pow10_128(eb - ea);
  }
  
  return va < vb ? -1 : (va > vb ? 1 : 0);
}

#define BIASCOMP 1u

static inline Number complex_part_to_num(uint32_t signo, uint32_t exp, uint32_t mantisa) {
    int16_t real_exp = (int16_t)exp - BIASCOMP;
    uint8_t num_exp = (uint8_t)(real_exp + BIASNUM);
    return (Number){
        .signo = (uint64_t)signo,
        .exp = num_exp,
        .mantisa = (uint64_t)mantisa
    };
}

static inline void num_to_complex_part(Number n, uint32_t *signo, uint32_t *exp, uint32_t *mantisa) {
    *signo = (uint32_t)n.signo;
    int16_t real_exp = (int16_t)n.exp - BIASNUM;
    int16_t comp_exp = real_exp + BIASCOMP;
    if (comp_exp < 0) comp_exp = 0;
    if (comp_exp > 3) comp_exp = 3;
    
    uint64_t mag = n.mantisa;
    while (mag > man_maxcom() && comp_exp < 3) {
        mag = (mag + 5) / 10;
        comp_exp++;
    }
    if (mag > man_maxcom()) mag = man_maxcom();
    
    *exp = (uint32_t)comp_exp;
    *mantisa = (uint32_t)mag;
}

static inline Complex add_complex(Complex a, Complex b) {
    Number ar = complex_part_to_num(a.real.signo, a.real.exp, a.real.mantisa);
    Number ai = complex_part_to_num(a.imaginary.signo, a.imaginary.exp, a.imaginary.mantisa);
    Number br = complex_part_to_num(b.real.signo, b.real.exp, b.real.mantisa);
    Number bi = complex_part_to_num(b.imaginary.signo, b.imaginary.exp, b.imaginary.mantisa);

    Number rr = add_num(ar, br);
    Number ri = add_num(ai, bi);

    uint32_t rs, re, rm, is, ie, im;
    num_to_complex_part(rr, &rs, &re, &rm);
    num_to_complex_part(ri, &is, &ie, &im);

    return (Complex){
        .real = { .signo = rs, .exp = re, .mantisa = rm },
        .imaginary = { .signo = is, .exp = ie, .mantisa = im }
    };
}


static inline Complex sub_complex(Complex a, Complex b) {
    Number ar = complex_part_to_num(a.real.signo, a.real.exp, a.real.mantisa);
    Number ai = complex_part_to_num(a.imaginary.signo, a.imaginary.exp, a.imaginary.mantisa);
    Number br = complex_part_to_num(b.real.signo, b.real.exp, b.real.mantisa);
    Number bi = complex_part_to_num(b.imaginary.signo, b.imaginary.exp, b.imaginary.mantisa);

    Number rr = sub_num(ar, br);
    Number ri = sub_num(ai, bi);

    uint32_t rs, re, rm, is, ie, im;
    num_to_complex_part(rr, &rs, &re, &rm);
    num_to_complex_part(ri, &is, &ie, &im);

    return (Complex){
        .real = { .signo = rs, .exp = re, .mantisa = rm },
        .imaginary = { .signo = is, .exp = ie, .mantisa = im }
    };
}

static inline Complex mul_complex(Complex a, Complex b) {
    Number ar = complex_part_to_num(a.real.signo, a.real.exp, a.real.mantisa);
    Number ai = complex_part_to_num(a.imaginary.signo, a.imaginary.exp, a.imaginary.mantisa);
    Number br = complex_part_to_num(b.real.signo, b.real.exp, b.real.mantisa);
    Number bi = complex_part_to_num(b.imaginary.signo, b.imaginary.exp, b.imaginary.mantisa);

    Number ac = mul_num(ar, br);
    Number bd = mul_num(ai, bi);
    Number ad = mul_num(ar, bi);
    Number bc = mul_num(ai, br);

    Number rr = sub_num(ac, bd);
    Number ri = add_num(ad, bc);

    uint32_t rs, re, rm, is, ie, im;
    num_to_complex_part(rr, &rs, &re, &rm);
    num_to_complex_part(ri, &is, &ie, &im);

    return (Complex){
        .real = { .signo = rs, .exp = re, .mantisa = rm },
        .imaginary = { .signo = is, .exp = ie, .mantisa = im }
    };
}

static inline Complex div_complex(Complex a, Complex b) {
    Number ar = complex_part_to_num(a.real.signo, a.real.exp, a.real.mantisa);
    Number ai = complex_part_to_num(a.imaginary.signo, a.imaginary.exp, a.imaginary.mantisa);
    Number br = complex_part_to_num(b.real.signo, b.real.exp, b.real.mantisa);
    Number bi = complex_part_to_num(b.imaginary.signo, b.imaginary.exp, b.imaginary.mantisa);

    Number denom = add_num(mul_num(br, br), mul_num(bi, bi));
    if (denom.mantisa == 0)
        return (Complex){{0}, {0}};

    Number nr = add_num(mul_num(ar, br), mul_num(ai, bi));
    Number ni = sub_num(mul_num(ai, br), mul_num(ar, bi));

    Number rr = div_num(nr, denom);
    Number ri = div_num(ni, denom);

    uint32_t rs, re, rm, is, ie, im;
    num_to_complex_part(rr, &rs, &re, &rm);
    num_to_complex_part(ri, &is, &ie, &im);

    return (Complex){
        .real = { .signo = rs, .exp = re, .mantisa = rm },
        .imaginary = { .signo = is, .exp = ie, .mantisa = im }
    };
}