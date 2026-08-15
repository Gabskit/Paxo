#include <stdint.h>
#include <uchar.h>

// ==========================================
// 1. DEFINICIÓN DE ESTRUCTURAS (C23)
// ==========================================

typedef struct {
  unsigned _BitInt(1) signo : 1;
  unsigned _BitInt(3) exponente : 3; // Max: 7, Sesgo: 3
  unsigned _BitInt(4) entero : 4;    // Max: 15
} __attribute__((packed)) Num8;

typedef struct {
  unsigned _BitInt(1) signo : 1;
  unsigned _BitInt(5) exponente : 5; // Max: 31, Sesgo: 15
  unsigned _BitInt(10) entero : 10;  // Max: 1,023
} __attribute__((packed)) Num16;

typedef struct {
  unsigned _BitInt(1) signo : 1;
  unsigned _BitInt(8) exponente : 8; // Max: 255, Sesgo: 127
  unsigned _BitInt(23) entero : 23;  // Max: 8,388,607
} __attribute__((packed)) Num32;

typedef struct {
  unsigned _BitInt(1) signo : 1;
  unsigned _BitInt(11) exponente : 11; // Max: 2047, Sesgo: 1023
  unsigned _BitInt(52) entero : 52;    // Max: 4,503,599,627,370,495
} __attribute__((packed)) Num64;

typedef unsigned _BitInt(2) PaxoBool;

enum type {
  NUM8,
  NUM16,
  NUM32,
  NUM64,
  CHAR8,
  CHAR16,
  CHAR32,
  TRIT,
  BOOL,
  POINT,
  FUNC
};

typedef struct {
  int8_t type;
  union {
    union {
      Num8 number8;
      char chara8;
    } v8;
    union {
      Num16 number16;
      char16_t chara16;
    } v16;
    union {
      Num32 number32;
      char32_t chara32;
    } v32;
    union {
      Num64 number64;
    } v64;
    union {
      PaxoBool bit;
      void *puntero;
      bool truebool;
    } sys;
    struct {
      uint32_t func_id;
      void *closure_env;
    } __attribute__((packed)) func;
  } as;
} PaxoVar;

// ==========================================
// 2. OPERACIONES ARITMÉTICAS: 8 BITS
// ==========================================

Num8 add_num8(Num8 a, Num8 b) {
  const int8_t sesgo = 3, exp_max = 7;
  const uint8_t i_max = 15;

  int8_t exp_a = (int8_t)a.exponente - sesgo;
  int8_t exp_b = (int8_t)b.exponente - sesgo;
  int8_t exp_target = (exp_a < exp_b) ? exp_a : exp_b;

  int64_t val_a = (int64_t)a.entero;
  for (int8_t i = 0; i < (exp_a - exp_target); i++)
    val_a *= 10;
  if (a.signo)
    val_a = -val_a;

  int64_t val_b = (int64_t)b.entero;
  for (int8_t i = 0; i < (exp_b - exp_target); i++)
    val_b *= 10;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num8){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_target;

  while (abs_suma > i_max) {
    abs_suma /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && abs_suma > 0) {
    abs_suma /= 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num8){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num8){.signo = signo_res,
                .exponente = (unsigned _BitInt(3))exp_almacenado,
                .entero = (unsigned _BitInt(4))abs_suma};
}

Num8 sub_num8(Num8 a, Num8 b) {
  b.signo = !b.signo;
  return add_num8(a, b);
}

Num8 mul_num8(Num8 a, Num8 b) {
  if (a.entero == 0 || b.entero == 0)
    return (Num8){0, 0, 0};
  const int8_t sesgo = 3, exp_max = 7;
  const uint8_t i_max = 15;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.entero * b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) + ((int16_t)b.exponente - sesgo);

  while (mult > i_max) {
    mult /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && mult > 0) {
    mult /= 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num8){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num8){.signo = signo_res,
                .exponente = (unsigned _BitInt(3))exp_almacenado,
                .entero = (unsigned _BitInt(4))mult};
}

Num8 div_num8(Num8 a, Num8 b) {
  if (b.entero == 0 || a.entero == 0)
    return (Num8){0, 0, 0};
  const int8_t sesgo = 3, exp_max = 7, escala = 4;
  const uint8_t i_max = 15;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.entero * 10000ULL;
  uint64_t div = num_a / b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) - ((int16_t)b.exponente - sesgo) - escala;

  while (div > i_max) {
    div /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && div > 0) {
    div /= 10;
    exp_res++;
  }

  if (div == 0)
    return (Num8){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num8){.signo = signo_res,
                .exponente = (unsigned _BitInt(3))exp_almacenado,
                .entero = (unsigned _BitInt(4))div};
}

// ==========================================
// 3. OPERACIONES ARITMÉTICAS: 16 BITS
// ==========================================

Num16 add_num16(Num16 a, Num16 b) {
  const int16_t sesgo = 15, exp_max = 31;
  const uint16_t i_max = 1023;

  int16_t exp_a = (int16_t)a.exponente - sesgo;
  int16_t exp_b = (int16_t)b.exponente - sesgo;
  int16_t exp_target = (exp_a < exp_b) ? exp_a : exp_b;

  int64_t val_a = (int64_t)a.entero;
  for (int16_t i = 0; i < (exp_a - exp_target); i++)
    val_a *= 10;
  if (a.signo)
    val_a = -val_a;

  int64_t val_b = (int64_t)b.entero;
  for (int16_t i = 0; i < (exp_b - exp_target); i++)
    val_b *= 10;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num16){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_target;

  while (abs_suma > i_max) {
    abs_suma /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && abs_suma > 0) {
    abs_suma /= 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num16){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num16){.signo = signo_res,
                 .exponente = (unsigned _BitInt(5))exp_almacenado,
                 .entero = (unsigned _BitInt(10))abs_suma};
}

Num16 sub_num16(Num16 a, Num16 b) {
  b.signo = !b.signo;
  return add_num16(a, b);
}

Num16 mul_num16(Num16 a, Num16 b) {
  if (a.entero == 0 || b.entero == 0)
    return (Num16){0, 0, 0};
  const int16_t sesgo = 15, exp_max = 31;
  const uint16_t i_max = 1023;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t mult = (uint64_t)a.entero * b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) + ((int16_t)b.exponente - sesgo);

  while (mult > i_max) {
    mult /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && mult > 0) {
    mult /= 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num16){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num16){.signo = signo_res,
                 .exponente = (unsigned _BitInt(5))exp_almacenado,
                 .entero = (unsigned _BitInt(10))mult};
}

Num16 div_num16(Num16 a, Num16 b) {
  if (b.entero == 0 || a.entero == 0)
    return (Num16){0, 0, 0};
  const int16_t sesgo = 15, exp_max = 31, escala = 5;
  const uint16_t i_max = 1023;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  uint64_t num_a = (uint64_t)a.entero * 100000ULL;
  uint64_t div = num_a / b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) - ((int16_t)b.exponente - sesgo) - escala;

  while (div > i_max) {
    div /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && div > 0) {
    div /= 10;
    exp_res++;
  }

  if (div == 0)
    return (Num16){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num16){.signo = signo_res,
                 .exponente = (unsigned _BitInt(5))exp_almacenado,
                 .entero = (unsigned _BitInt(10))div};
}

// ==========================================
// 4. OPERACIONES ARITMÉTICAS: 32 BITS
// ==========================================

Num32 add_num32(Num32 a, Num32 b) {
  const int16_t sesgo = 127, exp_max = 255;
  const uint32_t i_max = 8388607;

  int16_t exp_a = (int16_t)a.exponente - sesgo;
  int16_t exp_b = (int16_t)b.exponente - sesgo;
  int16_t exp_target = (exp_a < exp_b) ? exp_a : exp_b;

  _BitInt(128) val_a = (_BitInt(128))a.entero;
  for (int16_t i = 0; i < (exp_a - exp_target); i++)
    val_a *= 10;
  if (a.signo)
    val_a = -val_a;

  _BitInt(128) val_b = (_BitInt(128))b.entero;
  for (int16_t i = 0; i < (exp_b - exp_target); i++)
    val_b *= 10;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num32){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_target;

  while (abs_suma > i_max) {
    abs_suma /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && abs_suma > 0) {
    abs_suma /= 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num32){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num32){.signo = signo_res,
                 .exponente = (unsigned _BitInt(8))exp_almacenado,
                 .entero = (unsigned _BitInt(23))abs_suma};
}

Num32 sub_num32(Num32 a, Num32 b) {
  b.signo = !b.signo;
  return add_num32(a, b);
}

Num32 mul_num32(Num32 a, Num32 b) {
  if (a.entero == 0 || b.entero == 0)
    return (Num32){0, 0, 0};
  const int16_t sesgo = 127, exp_max = 255;
  const uint32_t i_max = 8388607;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.entero * b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) + ((int16_t)b.exponente - sesgo);

  while (mult > i_max) {
    mult /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && mult > 0) {
    mult /= 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num32){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num32){.signo = signo_res,
                 .exponente = (unsigned _BitInt(8))exp_almacenado,
                 .entero = (unsigned _BitInt(23))mult};
}

Num32 div_num32(Num32 a, Num32 b) {
  if (b.entero == 0 || a.entero == 0)
    return (Num32){0, 0, 0};
  const int16_t sesgo = 127, exp_max = 255, escala = 12;
  const uint32_t i_max = 8388607;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.entero * 1000000000000LL;
  unsigned _BitInt(128) div = num_a / b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) - ((int16_t)b.exponente - sesgo) - escala;

  while (div > i_max) {
    div /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && div > 0) {
    div /= 10;
    exp_res++;
  }

  if (div == 0)
    return (Num32){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num32){.signo = signo_res,
                 .exponente = (unsigned _BitInt(8))exp_almacenado,
                 .entero = (unsigned _BitInt(23))div};
}

// ==========================================
// 5. OPERACIONES ARITMÉTICAS: 64 BITS
// ==========================================

Num64 add_num64(Num64 a, Num64 b) {
  const int16_t sesgo = 1023, exp_max = 2047;
  const uint64_t i_max = 4503599627370495ULL;

  int16_t exp_a = (int16_t)a.exponente - sesgo;
  int16_t exp_b = (int16_t)b.exponente - sesgo;
  int16_t exp_target = (exp_a < exp_b) ? exp_a : exp_b;

  _BitInt(128) val_a = (_BitInt(128))a.entero;
  for (int16_t i = 0; i < (exp_a - exp_target); i++)
    val_a *= 10;
  if (a.signo)
    val_a = -val_a;

  _BitInt(128) val_b = (_BitInt(128))b.entero;
  for (int16_t i = 0; i < (exp_b - exp_target); i++)
    val_b *= 10;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num64){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_target;

  while (abs_suma > i_max) {
    abs_suma /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && abs_suma > 0) {
    abs_suma /= 10;
    exp_res++;
  }

  if (abs_suma == 0)
    return (Num64){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num64){.signo = signo_res,
                 .exponente = (unsigned _BitInt(11))exp_almacenado,
                 .entero = (unsigned _BitInt(52))abs_suma};
}

Num64 sub_num64(Num64 a, Num64 b) {
  b.signo = !b.signo;
  return add_num64(a, b);
}

Num64 mul_num64(Num64 a, Num64 b) {
  if (a.entero == 0 || b.entero == 0)
    return (Num64){0, 0, 0};
  const int16_t sesgo = 1023, exp_max = 2047;
  const uint64_t i_max = 4503599627370495ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) mult = (unsigned _BitInt(128))a.entero * b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) + ((int16_t)b.exponente - sesgo);

  while (mult > i_max) {
    mult /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && mult > 0) {
    mult /= 10;
    exp_res++;
  }

  if (mult == 0)
    return (Num64){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num64){.signo = signo_res,
                 .exponente = (unsigned _BitInt(11))exp_almacenado,
                 .entero = (unsigned _BitInt(52))mult};
}

Num64 div_num64(Num64 a, Num64 b) {
  if (b.entero == 0 || a.entero == 0)
    return (Num64){0, 0, 0};
  const int16_t sesgo = 1023, exp_max = 2047, escala = 15;
  const uint64_t i_max = 4503599627370495ULL;

  uint8_t signo_res = (a.signo != b.signo) ? 1 : 0;
  unsigned _BitInt(128) num_a =
      (unsigned _BitInt(128))a.entero * 1000000000000000ULL;
  unsigned _BitInt(128) div = num_a / b.entero;
  int16_t exp_res =
      ((int16_t)a.exponente - sesgo) - ((int16_t)b.exponente - sesgo) - escala;

  while (div > i_max) {
    div /= 10;
    exp_res++;
  }
  while ((exp_res + sesgo) < 0 && div > 0) {
    div /= 10;
    exp_res++;
  }

  if (div == 0)
    return (Num64){0, 0, 0};
  int16_t exp_almacenado = exp_res + sesgo;
  if (exp_almacenado > exp_max)
    exp_almacenado = exp_max;

  return (Num64){.signo = signo_res,
                 .exponente = (unsigned _BitInt(11))exp_almacenado,
                 .entero = (unsigned _BitInt(52))div};
}
