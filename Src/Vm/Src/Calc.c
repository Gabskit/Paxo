#pragma once
#include <stdint.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// 1. DEFINICIÓN DE ESTRUCTURAS (C23)
// ==========================================
typedef struct {
  unsigned _BitInt(4) signo : 1;
  unsigned _BitInt(4) exponente : 2; // Max: 3, Sesgo: 1
  unsigned _BitInt(4) entero : 1;    // Max: 1
} __attribute__((packed)) Num4;

typedef struct {
  unsigned _BitInt(6) signo : 1;
  unsigned _BitInt(6) exponente : 2; // Max: 3, Sesgo: 1
  unsigned _BitInt(6) entero : 3;    // Max: 7
} __attribute__((packed)) Num6;

typedef struct {
  uint8_t signo : 1;
  uint8_t exponente : 3; // Max: 7, Sesgo: 3
  uint8_t entero : 4;    // Max: 15
} __attribute__((packed)) Num8;

typedef struct {
  uint16_t signo : 1;
  uint16_t exponente : 5; // Max: 31, Sesgo: 15
  uint16_t entero : 10;   // Max: 1,023
} __attribute__((packed)) Num16;

typedef struct {
  uint32_t signo : 1;
  uint32_t exponente : 8; // Max: 255, Sesgo: 127
  uint32_t entero : 23;   // Max: 8,388,607
} __attribute__((packed)) Num32;

typedef struct {
  uint64_t signo : 1;
  uint64_t exponente : 11; // Max: 2047, Sesgo: 1023
  uint64_t entero : 52;    // Max: 4,503,599,627,370,495
} __attribute__((packed)) Num64;

typedef unsigned _BitInt(2) PaxoBool;

enum type {
  NUM4,
  NUM6,
  NUM8,
  NUM16,
  NUM32,
  NUM64,
  CHAR,
  TRIT,
  BOOL,
  POINT,
  FUNC
};

typedef struct {
  uint8_t type;
  union {
    Num4 number4;
    Num6 number6;
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
// 2. OPERACIONES ARITMÉTICAS: 8 BITS
// ==========================================

Num8 add_num8(Num8 a, Num8 b) {
  if (a.entero == 0)
    return b;
  if (b.entero == 0)
    return a;

  const int8_t sesgo = 3, exp_max = 7;
  const uint8_t i_max = 15;

  int8_t exp_a = (int8_t)a.exponente - sesgo;
  int8_t exp_b = (int8_t)b.exponente - sesgo;

  // Garantizar que 'a' sea el de exponente mayor o igual
  if (exp_a < exp_b) {
    Num8 temp = a;
    a = b;
    b = temp;
    int8_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int8_t diff_exp = exp_a - exp_b;

  // Barrera: Descartar 'b' si la diferencia supera 2 dígitos decimales
  if (diff_exp > 2)
    return a;

  int64_t val_a = (int64_t)a.entero;
  int64_t val_b = (int64_t)b.entero;

  for (int8_t i = 0; i < diff_exp; i++) {
    val_a *= 10;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num8){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

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
  if (exp_almacenado < 0)
    return (Num8){0, 0, 0};

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
  if (a.entero == 0)
    return b;
  if (b.entero == 0)
    return a;

  const int16_t sesgo = 15, exp_max = 31;
  const uint16_t i_max = 1023;

  int16_t exp_a = (int16_t)a.exponente - sesgo;
  int16_t exp_b = (int16_t)b.exponente - sesgo;

  if (exp_a < exp_b) {
    Num16 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;

  // Barrera: Descartar 'b' si la diferencia supera 4 dígitos decimales
  if (diff_exp > 4)
    return a;

  int64_t val_a = (int64_t)a.entero;
  int64_t val_b = (int64_t)b.entero;

  for (int16_t i = 0; i < diff_exp; i++) {
    val_a *= 10;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  int64_t suma = val_a + val_b;
  if (suma == 0)
    return (Num16){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  uint64_t abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

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
  if (exp_almacenado < 0)
    return (Num16){0, 0, 0};

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
  if (a.entero == 0)
    return b;
  if (b.entero == 0)
    return a;

  const int16_t sesgo = 127, exp_max = 255;
  const uint32_t i_max = 8388607; // 2^23 - 1

  int16_t exp_a = (int16_t)a.exponente - sesgo;
  int16_t exp_b = (int16_t)b.exponente - sesgo;

  // Asegurar que 'a' tenga el exponente más alto
  if (exp_a < exp_b) {
    Num32 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;

  // Límite de seguridad: Si la diferencia supera los 7 dígitos
  // decimales que caben en 23 bits binarios, descartamos 'b'.
  if (diff_exp > 7)
    return a;

  // Recuperamos el uso seguro de tu tipo _BitInt(128)
  _BitInt(128) val_a = (_BitInt(128))a.entero;
  _BitInt(128) val_b = (_BitInt(128))b.entero;

  for (int16_t i = 0; i < diff_exp; i++) {
    val_a *= 10;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num32){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

  // Normalización decimal original[span_3](start_span)[span_3](end_span)
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
  if (exp_almacenado < 0)
    return (Num32){0, 0, 0};

  // Casteos estrictos a _BitInt tal y como en tu
  // código[span_4](start_span)[span_4](end_span)
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
  if (a.entero == 0)
    return b;
  if (b.entero == 0)
    return a;

  const int16_t sesgo = 1023, exp_max = 2047;
  const uint64_t i_max = 4503599627370495ULL;

  int16_t exp_a = (int16_t)a.exponente - sesgo;
  int16_t exp_b = (int16_t)b.exponente - sesgo;

  if (exp_a < exp_b) {
    Num64 temp = a;
    a = b;
    b = temp;
    int16_t exp_temp = exp_a;
    exp_a = exp_b;
    exp_b = exp_temp;
  }

  int16_t diff_exp = exp_a - exp_b;

  // Barrera: Descartar 'b' si la diferencia supera 16 dígitos decimales
  if (diff_exp > 16)
    return a;

  _BitInt(128) val_a = (_BitInt(128))a.entero;
  _BitInt(128) val_b = (_BitInt(128))b.entero;

  for (int16_t i = 0; i < diff_exp; i++) {
    val_a *= 10;
  }

  if (a.signo)
    val_a = -val_a;
  if (b.signo)
    val_b = -val_b;

  _BitInt(128) suma = val_a + val_b;
  if (suma == 0)
    return (Num64){0, 0, 0};

  uint8_t signo_res = (suma < 0) ? 1 : 0;
  unsigned _BitInt(128) abs_suma = (suma < 0) ? -suma : suma;
  int16_t exp_res = exp_b;

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
  if (exp_almacenado < 0)
    return (Num64){0, 0, 0};

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
