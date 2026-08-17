#pragma once
#include <stdint.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// 1. ESTRUCTURAS MOBILE POINT (REVISIÓN ALGO_2)
// ==========================================

typedef struct {
  uint8_t signo : 1;
  uint8_t exp : 1;
  uint8_t bc : 4; // 2 bit-chunks
  uint8_t p : 2;  // 3 posiciones
} __attribute__((packed)) Num8;

typedef struct {
  uint16_t signo : 1;
  uint16_t exp : 2;
  uint16_t bc : 10; // 5 bit-chunks
  uint16_t p : 3;   // 6 posiciones
} __attribute__((packed)) Num16;

typedef struct {
  uint32_t signo : 1;
  uint32_t exp : 5;
  uint32_t bc : 22; // 11 bit-chunks
  uint32_t p : 4;   // 12 posiciones
} __attribute__((packed)) Num32;

typedef struct {
  uint64_t signo : 1;
  uint64_t exp : 10;
  uint64_t bc : 48; // 24 bit-chunks
  uint64_t p : 5;   // 25 posiciones
} __attribute__((packed)) Num64;

typedef unsigned _BitInt(2) PaxoBool;

enum type { NUM8, NUM16, NUM32, NUM64, CHAR, TRIT, BOOL, POINT, FUNC };

typedef struct {
  uint8_t type;
  union {
    Num8 number8;
    char8_t chara;
    Num16 number16;
    Num32 number32;
    Num64 number64;
    PaxoBool bit;
    void *puntero;
    bool truebool;
    struct {
      uint32_t func_id;
      void *closure_env;
    } __attribute__((packed)) func;
  } as;
} PaxoVar;

// Macro auxiliar para propagar el punto fijo de mayor precision
#define PROPAGAR_P(a, b) ((a.p > b.p) ? a.p : b.p)

// ==========================================
// 2. OPERACIONES ARITMÉTICAS: 8 BITS (MP8)
// ==========================================

Num8 add_num8(Num8 a, Num8 b) {
  if (a.bc == 0)
    return b;
  if (b.bc == 0)
    return a;

  const int8_t sesgo = 0, exp_max = 1;
  const uint8_t bc_max = 15; // 4 bits (0xF)

  int8_t exp_a = (int8_t)a.exp - sesgo;
  int8_t exp_b = (int8_t)b.exp - sesgo;

  if (exp_a < exp_b) {
    Num8 temp = a;
    a = b;
    b = temp;
    int8_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int8_t diff_exp = exp_a - exp_b;
  if (diff_exp > 1)
    return a;

  int64_t val_a = (int64_t)a.bc;
  int64_t val_b = (int64_t)b.bc;

  for (int8_t i = 0; i < diff_exp; i++)
    val_a *= 20;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > bc_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num8){.signo = signo_res,
                .exp = (uint8_t)exp_almacenado,
                .bc = (uint8_t)abs_suma,
                .p = PROPAGAR_P(a, b)};
}

Num8 sub_num8(Num8 a, Num8 b) {
  b.signo = !b.signo;
  return add_num8(a, b);
}

Num8 mul_num8(Num8 a, Num8 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};
  const int8_t sesgo = 0, exp_max = 1;
  const uint8_t bc_max = 15;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.bc * b.bc;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > bc_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num8){.signo = signo_res,
                .exp = (uint8_t)exp_almacenado,
                .bc = (uint8_t)mult,
                .p = PROPAGAR_P(a, b)};
}

Num8 div_num8(Num8 a, Num8 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};
  const int8_t sesgo = 0, exp_max = 1, escala = 2;
  const uint8_t bc_max = 15;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.bc * 400ULL; // 20^2
  uint64_t div = num_a / b.bc;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > bc_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num8){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num8){.signo = signo_res,
                .exp = (uint8_t)exp_almacenado,
                .bc = (uint8_t)div,
                .p = PROPAGAR_P(a, b)};
}

// ==========================================
// 3. OPERACIONES ARITMÉTICAS: 16 BITS (MP16)
// ==========================================

Num16 add_num16(Num16 a, Num16 b) {
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
    return a;

  int64_t val_a = (int64_t)a.bc;
  int64_t val_b = (int64_t)b.bc;

  for (int16_t i = 0; i < diff_exp; i++)
    val_a *= 20;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > bc_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .bc = (uint16_t)abs_suma,
                 .p = PROPAGAR_P(a, b)};
}

Num16 sub_num16(Num16 a, Num16 b) {
  b.signo = !b.signo;
  return add_num16(a, b);
}

Num16 mul_num16(Num16 a, Num16 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 1, exp_max = 3;
  const uint16_t bc_max = 1023;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.bc * b.bc;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > bc_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .bc = (uint16_t)mult,
                 .p = PROPAGAR_P(a, b)};
}

Num16 div_num16(Num16 a, Num16 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 1, exp_max = 3, escala = 3;
  const uint16_t bc_max = 1023;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.bc * 8000ULL; // 20^3
  uint64_t div = num_a / b.bc;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > bc_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num16){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .bc = (uint16_t)div,
                 .p = PROPAGAR_P(a, b)};
}

// ==========================================
// 4. OPERACIONES ARITMÉTICAS: 32 BITS (MP32)
// ==========================================

Num32 add_num32(Num32 a, Num32 b) {
  if (a.bc == 0)
    return b;
  if (b.bc == 0)
    return a;

  const int16_t sesgo = 15, exp_max = 31;
  const uint32_t bc_max = 4194303; // 22 bits (0x3FFFFF)

  int16_t exp_a = (int16_t)a.exp - sesgo;
  int16_t exp_b = (int16_t)b.exp - sesgo;

  if (exp_a < exp_b) {
    Num32 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;
  if (diff_exp > 5)
    return a;

  _BitInt(128) val_a = (_BitInt(128))a.bc;
  _BitInt(128) val_b = (_BitInt(128))b.bc;

  for (int16_t i = 0; i < diff_exp; i++)
    val_a *= 20;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > bc_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num32){.signo = signo_res,
                 .exp = (uint32_t)exp_almacenado,
                 .bc = (uint32_t)abs_suma,
                 .p = PROPAGAR_P(a, b)};
}

Num32 sub_num32(Num32 a, Num32 b) {
  b.signo = !b.signo;
  return add_num32(a, b);
}

Num32 mul_num32(Num32 a, Num32 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 15, exp_max = 31;
  const uint32_t bc_max = 4194303;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.bc * b.bc;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > bc_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num32){.signo = signo_res,
                 .exp = (uint32_t)exp_almacenado,
                 .bc = (uint32_t)mult,
                 .p = PROPAGAR_P(a, b)};
}

Num32 div_num32(Num32 a, Num32 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 15, exp_max = 31, escala = 5;
  const uint32_t bc_max = 4194303;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.bc * 3200000ULL; // 20^5
  unsigned _BitInt(128) div = num_a / b.bc;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > bc_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num32){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num32){.signo = signo_res,
                 .exp = (uint32_t)exp_almacenado,
                 .bc = (uint32_t)div,
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
    return a;

  _BitInt(128) val_a = (_BitInt(128))a.bc;
  _BitInt(128) val_b = (_BitInt(128))b.bc;

  for (int16_t i = 0; i < diff_exp; i++)
    val_a *= 20;

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > bc_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)abs_suma,
                 .p = PROPAGAR_P(a, b)};
}

Num64 sub_num64(Num64 a, Num64 b) {
  b.signo = !b.signo;
  return add_num64(a, b);
}

Num64 mul_num64(Num64 a, Num64 b) {
  if (a.bc == 0 || b.bc == 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 511, exp_max = 1023;
  const uint64_t bc_max = 281474976710655ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.bc * b.bc;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > bc_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)mult,
                 .p = PROPAGAR_P(a, b)};
}

Num64 div_num64(Num64 a, Num64 b) {
  if (b.bc == 0 || a.bc == 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};
  const int16_t sesgo = 511, exp_max = 1023, escala = 12;
  const uint64_t bc_max = 281474976710655ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.bc * 4096000000000000ULL; // 20^12
  unsigned _BitInt(128) div = num_a / b.bc;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > bc_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num64){0, 0, 0, PROPAGAR_P(a, b)};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .bc = (uint64_t)div,
                 .p = PROPAGAR_P(a, b)};
}
