#pragma once
#include <stdint.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// 1. DEFINICIÓN DE ESTRUCTURAS MOBILE POINT
// ==========================================

typedef struct {
  uint8_t signo : 1;
  uint8_t exp : 2;
  uint8_t hp : 4;
  uint8_t p : 1;
} __attribute__((packed)) Num8;

typedef struct {
  uint16_t signo : 1;
  uint16_t exp : 5;
  uint16_t hp : 8;
  uint16_t p : 2;
} __attribute__((packed)) Num16;

typedef struct {
  uint32_t signo : 1;
  uint32_t exp : 8;
  uint32_t hp : 20;
  uint32_t p : 3;
} __attribute__((packed)) Num32;

typedef struct {
  uint64_t signo : 1;
  uint64_t exp : 7;
  uint64_t hp : 52;
  uint64_t p : 4;
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

// ==========================================
// 2. OPERACIONES ARITMÉTICAS: 8 BITS (MP8)
// ==========================================

Num8 add_num8(Num8 a, Num8 b) {
  if (a.hp == 0)
    return b;
  if (b.hp == 0)
    return a;

  const int8_t sesgo = 1, exp_max = 3;
  const uint8_t hp_max = 15; // 4 bits (0xF)

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
  if (diff_exp > 2)
    return a;

  int64_t val_a = (int64_t)a.hp;
  int64_t val_b = (int64_t)b.hp;

  for (int8_t i = 0; i < diff_exp; i++) {
    val_a *= 20; // Escala base 20
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num8){0, 0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > hp_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num8){0, 0, 0, 0};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num8){0, 0, 0, 0};

  return (Num8){.signo = signo_res,
                .exp = (uint8_t)exp_almacenado,
                .hp = (uint8_t)abs_suma,
                .p = a.p};
}

Num8 sub_num8(Num8 a, Num8 b) {
  b.signo = !b.signo;
  return add_num8(a, b);
}

Num8 mul_num8(Num8 a, Num8 b) {
  if (a.hp == 0 || b.hp == 0)
    return (Num8){0, 0, 0, 0};
  const int8_t sesgo = 1, exp_max = 3;
  const uint8_t hp_max = 15;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.hp * b.hp;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > hp_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num8){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num8){.signo = signo_res,
                .exp = (uint8_t)exp_almacenado,
                .hp = (uint8_t)mult,
                .p = a.p};
}

Num8 div_num8(Num8 a, Num8 b) {
  if (b.hp == 0 || a.hp == 0)
    return (Num8){0, 0, 0, 0};
  const int8_t sesgo = 1, exp_max = 3, escala = 2;
  const uint8_t hp_max = 15;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.hp * 400ULL; // 20^2
  uint64_t div = num_a / b.hp;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > hp_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num8){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num8){.signo = signo_res,
                .exp = (uint8_t)exp_almacenado,
                .hp = (uint8_t)div,
                .p = a.p};
}

// ==========================================
// 3. OPERACIONES ARITMÉTICAS: 16 BITS (MP16)
// ==========================================

Num16 add_num16(Num16 a, Num16 b) {
  if (a.hp == 0)
    return b;
  if (b.hp == 0)
    return a;

  const int16_t sesgo = 15, exp_max = 31;
  const uint16_t hp_max = 255; // 8 bits (0xFF)

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
  if (diff_exp > 3)
    return a;

  int64_t val_a = (int64_t)a.hp;
  int64_t val_b = (int64_t)b.hp;

  for (int16_t i = 0; i < diff_exp; i++) {
    val_a *= 20;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num16){0, 0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > hp_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num16){0, 0, 0, 0};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num16){0, 0, 0, 0};

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .hp = (uint16_t)abs_suma,
                 .p = a.p};
}

Num16 sub_num16(Num16 a, Num16 b) {
  b.signo = !b.signo;
  return add_num16(a, b);
}

Num16 mul_num16(Num16 a, Num16 b) {
  if (a.hp == 0 || b.hp == 0)
    return (Num16){0, 0, 0, 0};
  const int16_t sesgo = 15, exp_max = 31;
  const uint16_t hp_max = 255;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.hp * b.hp;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > hp_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num16){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .hp = (uint16_t)mult,
                 .p = a.p};
}

Num16 div_num16(Num16 a, Num16 b) {
  if (b.hp == 0 || a.hp == 0)
    return (Num16){0, 0, 0, 0};
  const int16_t sesgo = 15, exp_max = 31, escala = 3;
  const uint16_t hp_max = 255;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.hp * 8000ULL; // 20^3
  uint64_t div = num_a / b.hp;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > hp_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num16){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num16){.signo = signo_res,
                 .exp = (uint16_t)exp_almacenado,
                 .hp = (uint16_t)div,
                 .p = a.p};
}

// ==========================================
// 4. OPERACIONES ARITMÉTICAS: 32 BITS (MP32)
// ==========================================

Num32 add_num32(Num32 a, Num32 b) {
  if (a.hp == 0)
    return b;
  if (b.hp == 0)
    return a;

  const int16_t sesgo = 127, exp_max = 255;
  const uint32_t hp_max = 1048575; // 20 bits (0xFFFFF)

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

  _BitInt(128) val_a = (_BitInt(128))a.hp;
  _BitInt(128) val_b = (_BitInt(128))b.hp;

  for (int16_t i = 0; i < diff_exp; i++) {
    val_a *= 20;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num32){0, 0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > hp_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num32){0, 0, 0, 0};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num32){0, 0, 0, 0};

  return (Num32){.signo = signo_res,
                 .exp = (uint32_t)exp_almacenado,
                 .hp = (uint32_t)abs_suma,
                 .p = a.p};
}

Num32 sub_num32(Num32 a, Num32 b) {
  b.signo = !b.signo;
  return add_num32(a, b);
}

Num32 mul_num32(Num32 a, Num32 b) {
  if (a.hp == 0 || b.hp == 0)
    return (Num32){0, 0, 0, 0};
  const int16_t sesgo = 127, exp_max = 255;
  const uint32_t hp_max = 1048575;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.hp * b.hp;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > hp_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num32){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num32){.signo = signo_res,
                 .exp = (uint32_t)exp_almacenado,
                 .hp = (uint32_t)mult,
                 .p = a.p};
}

Num32 div_num32(Num32 a, Num32 b) {
  if (b.hp == 0 || a.hp == 0)
    return (Num32){0, 0, 0, 0};
  const int16_t sesgo = 127, exp_max = 255, escala = 5;
  const uint32_t hp_max = 1048575;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.hp * 3200000ULL; // 20^5
  unsigned _BitInt(128) div = num_a / b.hp;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > hp_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num32){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num32){.signo = signo_res,
                 .exp = (uint32_t)exp_almacenado,
                 .hp = (uint32_t)div,
                 .p = a.p};
}

// ==========================================
// 5. OPERACIONES ARITMÉTICAS: 64 BITS (MP64)
// ==========================================

Num64 add_num64(Num64 a, Num64 b) {
  if (a.hp == 0)
    return b;
  if (b.hp == 0)
    return a;

  const int16_t sesgo = 63, exp_max = 127;
  const uint64_t hp_max = 4503599627370495ULL; // 52 bits

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

  _BitInt(128) val_a = (_BitInt(128))a.hp;
  _BitInt(128) val_b = (_BitInt(128))b.hp;

  for (int16_t i = 0; i < diff_exp; i++) {
    val_a *= 20;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num64){0, 0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  while (abs_suma > hp_max) {
    abs_suma /= 20;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num64){0, 0, 0, 0};

  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;
  if (exp_almacenado < 0)
    return (Num64){0, 0, 0, 0};

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .hp = (uint64_t)abs_suma,
                 .p = a.p};
}

Num64 sub_num64(Num64 a, Num64 b) {
  b.signo = !b.signo;
  return add_num64(a, b);
}

Num64 mul_num64(Num64 a, Num64 b) {
  if (a.hp == 0 || b.hp == 0)
    return (Num64){0, 0, 0, 0};
  const int16_t sesgo = 63, exp_max = 127;
  const uint64_t hp_max = 4503599627370495ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.hp * b.hp;
  int16_t exp_res = ((int16_t)a.exp - sesgo) + ((int16_t)b.exp - sesgo);

  while (mult > hp_max) {
    mult /= 20;
    exp_res++;
  }

  if (mult == 0)
    return (Num64){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .hp = (uint64_t)mult,
                 .p = a.p};
}

Num64 div_num64(Num64 a, Num64 b) {
  if (b.hp == 0 || a.hp == 0)
    return (Num64){0, 0, 0, 0};
  const int16_t sesgo = 63, exp_max = 127, escala = 8;
  const uint64_t hp_max = 4503599627370495ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.hp * 25600000000ULL; // 20^8
  unsigned _BitInt(128) div = num_a / b.hp;
  int16_t exp_res =
      ((int16_t)a.exp - sesgo) - ((int16_t)b.exp - sesgo) - escala;

  while (div > hp_max) {
    div /= 20;
    exp_res++;
  }

  if (div == 0)
    return (Num64){0, 0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num64){.signo = signo_res,
                 .exp = (uint64_t)exp_almacenado,
                 .hp = (uint64_t)div,
                 .p = a.p};
}
