#pragma once
#include <stdint.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// 1. ESTRUCTURAS MOBILE POINT (REVISIÓN ALGO_2)
// ==========================================

typedef struct {
  uint16_t signo : 1;
  uint16_t exp : 2;
  uint16_t bc : 10; // 5 bit-chunks
  uint16_t p : 3;   // 6 posiciones
} __attribute__((packed)) Num16;

typedef struct {
  uint64_t signo : 1;
  uint64_t exp : 10;
  uint64_t bc : 48; // 24 bit-chunks
  uint64_t p : 5;   // 25 posiciones
} __attribute__((packed)) Num64;

typedef unsigned _BitInt(2) PaxoBool;

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

typedef struct PaxoVar PaxoVar;

typedef struct PaxoPackageField {
  char *key;
  struct PaxoPackageField *next;
  PaxoVar *value;
} PaxoPackageField;

typedef struct {
  PaxoVar *items;
  size_t len;
  size_t capacity;
} PaxoArray;

struct PaxoVar {
  uint8_t type;
  union {
    char8_t chara;
    Num16 number16;
    Num64 number64;
    PaxoBool bit;
    void *puntero;
    bool truebool;
    struct {
      uint32_t func_id;
      void *closure_env;
      uint8_t param_count;
    } __attribute__((packed)) func;
    PaxoArray *array;
    PaxoPackageField *pkg;
  } as;
};

// Macro auxiliar para propagar el punto fijo de mayor precision
#define PROPAGAR_P(a, b) ((a.p > b.p) ? a.p : b.p)

// ==========================================
// 3. OPERACIONES ARITMÉTICAS: 16 BITS (MP16)
// ==========================================

static inline Num16 add_num16(Num16 a, Num16 b) {
  if (a.bc == 0)
    return b;
  if (b.bc == 0)
    return a;

  const int16_t sesgo = 1, exp_max = 3;
  const uint16_t bc_max = 1023; // 10 bits (0x3FF)

  int16_t exp_a = (int16_t)a.exp - sesgo;
  int16_t exp_b = (int16_t)b.exp - sesgo;

  if (exp_a < exp_b) {
    Num16 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;
  if (diff_exp > 2)
    return (Num16){.signo = a.signo, .exp = a.exp, .bc = a.bc,
                   .p = PROPAGAR_P(a, b)};

  int64_t val_a = (int64_t)a.bc;
  int64_t val_b = (int64_t)b.bc;

  for (int16_t i = 0; i < diff_exp; i++)
    val_a *= 10;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > bc_max) {
    abs_suma = (abs_suma + 9) / 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    abs_suma = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .bc = (uint16_t)abs_suma,
                 .p = PROPAGAR_P(a, b)};
}

static inline Num16 sub_num16(Num16 a, Num16 b) {
  if (b.bc == 0)
    return a;
  b.signo = !b.signo;
  return add_num16(a, b);
}

static inline Num16 mul_num16(Num16 a, Num16 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num16){0, (uint16_t)1, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 1, exp_max = 3;
  const uint16_t bc_max = 1023;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.bc * b.bc;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > bc_max) {
    mult = (mult + 9) / 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    mult = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .bc = (uint16_t)mult,
                 .p = PROPAGAR_P(a, b)};
}

static inline Num16 div_num16(Num16 a, Num16 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num16){0, (uint16_t)1, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 1, exp_max = 3, escala = 3;
  const uint16_t bc_max = 1023;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.bc * 1000ULL; // 10^3
  uint64_t div = num_a / b.bc;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > bc_max) {
    div = (div + 9) / 10;
    exp_res++;
  }

  if (div == 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    div = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num16){0, (uint16_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .bc = (uint16_t)div,
                 .p = PROPAGAR_P(a, b)};
}

// ==========================================
// 5. OPERACIONES ARITMÉTICAS: 64 BITS (MP64)
// ==========================================

Num64 add_num64(Num64 a, Num64 b) {
  if (a.bc == 0)
    return b;
  if (b.bc == 0)
    return a;

  const int16_t sesgo = 511, exp_max = 1023;
  const uint64_t bc_max = 281474976710655ULL; // 48 bits (0xFFFFFFFFFFFF)

  int16_t exp_a = (int16_t)a.exp - sesgo;
  int16_t exp_b = (int16_t)b.exp - sesgo;

  if (exp_a < exp_b) {
    Num64 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;
  if (diff_exp > 12)
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

  while (abs_suma > bc_max) {
    abs_suma /= 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    abs_suma = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)abs_suma,
                 .p = PROPAGAR_P(a, b)};
}

static inline Num64 sub_num64(Num64 a, Num64 b) {
  if (b.bc == 0)
    return a;
  b.signo = !b.signo;
  return add_num64(a, b);
}

static inline Num64 mul_num64(Num64 a, Num64 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num64){0, (uint64_t)511, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 511, exp_max = 1023;
  const uint64_t bc_max = 281474976710655ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.bc * b.bc;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > bc_max) {
    mult /= 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    mult = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)mult,
                 .p = PROPAGAR_P(a, b)};
}

static inline Num64 div_num64(Num64 a, Num64 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num64){0, (uint64_t)511, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 511, exp_max = 1023, escala = 12;
  const uint64_t bc_max = 281474976710655ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.bc * 1000000000000ULL; // 10^12
  unsigned _BitInt(128) div = num_a / b.bc;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > bc_max) {
    div /= 10;
    exp_res++;
  }

  if (div == 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max) {
    exp_almacenado = exp_max;
    div = bc_max;
  }
  if (exp_almacenado < 0)
    return (Num64){0, (uint64_t)sesgo, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)div,
                 .p = PROPAGAR_P(a, b)};
}

// ==========================================
// 6. COMPARACIONES MOBILE POINT
//    Retorna: -1 si a < b, 0 si a == b, 1 si a > b
// ==========================================

static inline uint16_t bc_max16(void) { return 1023; }
static inline uint64_t bc_max64(void) { return 281474976710655ULL; }

static inline int cmp_num16(Num16 a, Num16 b) {
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;

  const int16_t sesgo = 1;
  int16_t exp_a = (int16_t)a.exp - sesgo;
  int16_t exp_b = (int16_t)b.exp - sesgo;

  int64_t val_a = (int64_t)a.bc;
  int64_t val_b = (int64_t)b.bc;

  if (exp_a > exp_b) {
    int16_t diff = exp_a - exp_b;
    for (int16_t i = 0; i < diff && val_a <= (int64_t)bc_max16(); i++)
      val_a *= 10;
  } else if (exp_b > exp_a) {
    int16_t diff = exp_b - exp_a;
    for (int16_t i = 0; i < diff && val_b <= (int64_t)bc_max16(); i++)
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

static inline int cmp_num64(Num64 a, Num64 b) {
  if (a.signo != b.signo)
    return a.signo ? -1 : 1;

  __int128 val_a = (__int128)a.bc;
  __int128 val_b = (__int128)b.bc;

  int16_t bias_a = (int16_t)a.exp - 511;
  int16_t bias_b = (int16_t)b.exp - 511;

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
