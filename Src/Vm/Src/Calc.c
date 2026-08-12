#include <stdint.h>
#include <uchar.h>

typedef struct {
  unsigned _BitInt(1) signo;
  unsigned _BitInt(1) exponente;
  unsigned _BitInt(4) entero;
  unsigned _BitInt(2) fraccion;
} __attribute__((packed)) PaxoNum8;

typedef struct {
  unsigned _BitInt(1) signo;
  unsigned _BitInt(4) exponente;
  unsigned _BitInt(5) entero;
  unsigned _BitInt(6) fraccion;
} __attribute__((packed)) PaxoNum16;

typedef struct {
  unsigned _BitInt(1) signo;
  unsigned _BitInt(6) exponente;
  unsigned _BitInt(12) entero;
  unsigned _BitInt(13) fraccion;
} __attribute__((packed)) PaxoNum32;

typedef struct {
  unsigned _BitInt(1) signo;
  unsigned _BitInt(10) exponente;
  unsigned _BitInt(26) entero;
  unsigned _BitInt(27) fraccion;
} __attribute__((packed)) PaxoNum64;

typedef struct {
  PaxoNum8 real;
  PaxoNum8 imaginario;
} __attribute__((packed)) PaxoCom8;

typedef struct {
  PaxoNum16 real;
  PaxoNum16 imaginario;
} __attribute__((packed)) PaxoCom16;

typedef struct {
  PaxoNum32 real;
  PaxoNum32 imaginario;
} __attribute__((packed)) PaxoCom32;

typedef struct {
  PaxoNum64 real;
  PaxoNum64 imaginario
} __attribute__((packed)) PaxoCom64;

typedef unsigned _BitInt(2) PaxoBool;

enum type {
  NUM8,
  NUM16,
  NUM32,
  NUM64,
  CHAR8,
  CHAR16,
  CHAR32,
  COM8,
  COM16,
  COM32,
  COM64,
  TRIT,
  BOOL,
  MON32,
  MON64,
  MON128,
  POINT,
  FUNC
};

typedef struct {
  int8_t type;
  union {
    union {
      PaxoNum8 number8;
      char chara8;
    } v8;
    union {
      PaxoNum16 number16;
      char16_t chara16;
      PaxoCom8 com16;
    } v16;
    union {
      PaxoNum32 number32;
      char32_t chara32;
      PaxoCom16 com32;
      _Decimal32 mon32;
    } v32;
    union {
      PaxoCom32 com64;
      PaxoNum64 number64;
      _Decimal64 mon64;
    } v64;
    union {
      PaxoCom64 com64;
      _Decimal128 mon128;
    } v128;
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

// Funciones numericas
// 8 bits
PaxoNum8 add_num8(PaxoNum8 a, PaxoNum8 b) {
  const uint8_t sesgo = 0;
  int16_t val_a = a.fraccion + ((int16_t)a.entero * 4);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  int16_t val_b = b.fraccion + ((int16_t)b.entero * 4);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int8_t exp_a = a.exponente - sesgo;
  int8_t exp_b = b.exponente - sesgo;
  int8_t exp;

  uint8_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  int16_t suma = val_a + val_b;
  uint16_t abs_suma = (suma < 0) ? -(uint16_t)suma : (uint16_t)suma;

  PaxoNum8 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 6)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < 0)
    exp = 0;
  if (exp > 1)
    exp = 1;

  result.exponente = (unsigned _BitInt(1))(exp + sesgo);
  result.entero = (unsigned _BitInt(4))((abs_suma >> 2) & 0xf);
  result.fraccion = (unsigned _BitInt(2))(abs_suma & 0x3);
  return result;
}

PaxoNum8 sub_num8(PaxoNum8 a, PaxoNum8 b) {
  const uint8_t sesgo = 0;
  int16_t val_a = a.fraccion + ((int16_t)a.entero * 4);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  int16_t val_b = b.fraccion + ((int16_t)b.entero * 4);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int8_t exp_a = a.exponente - sesgo;
  int8_t exp_b = b.exponente - sesgo;
  int8_t exp;

  uint8_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  int16_t suma = val_a - val_b;
  uint16_t abs_suma = (suma < 0) ? -(uint8_t)suma : (uint8_t)suma;

  PaxoNum8 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 6)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < 0)
    exp = 0;
  if (exp > 1)
    exp = 1;

  result.exponente = (unsigned _BitInt(1))(exp + sesgo);
  result.entero = (unsigned _BitInt(4))((abs_suma >> 2) & 0xf);
  result.fraccion = (unsigned _BitInt(2))(abs_suma & 0x3);
  return result;
}

PaxoNum8 mul_num8(PaxoNum8 a, PaxoNum8 b) {
  const uint8_t sesgo = 0;
  int8_t val_a = a.fraccion + ((int8_t)a.entero * 4);
  int8_t val_b = b.fraccion + ((int8_t)b.entero * 4);

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  int16_t mult = ((int16_t)val_a * val_b) >> 2;
  int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

  while (mult >= (1ULL << 6)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < 0)
    exp_final = 0;
  if (exp_final > 1)
    exp_final = 1;

  PaxoNum8 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(1))exp_final;
  result.entero = (unsigned _BitInt(4))((mult >> 2) & 0xf);
  result.fraccion = (unsigned _BitInt(2))(mult & 0x3);
  return result;
}

PaxoNum8 div_num8(PaxoNum8 a, PaxoNum8 b) {
  const uint8_t sesgo = 0;
  int8_t val_a = a.fraccion + ((int8_t)a.entero * 4);
  int8_t val_b = b.fraccion + ((int8_t)b.entero * 4);

  if (val_b == 0) {
    PaxoNum8 error = {0, 0, 0, 0};
    return error;
  }

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  int16_t mult = ((int16_t)val_a << 2) / val_b;

  int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

  while (mult >= (1ULL << 6)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < 0)
    exp_final = 0;
  if (exp_final > 1)
    exp_final = 1;

  PaxoNum8 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(1))exp_final;
  result.entero = (unsigned _BitInt(4))((mult >> 6) & 0xf);
  result.fraccion = (unsigned _BitInt(2))(mult & 0x3);
  return result;
}

// 16 bits
PaxoNum16 add_num16(PaxoNum16 a, PaxoNum16 b) {
  const uint8_t sesgo = 7;
  int32_t val_a = a.fraccion + ((int32_t)a.entero * 64);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  int32_t val_b = b.fraccion + ((int32_t)b.entero * 64);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int8_t exp_a = a.exponente - sesgo;
  int8_t exp_b = b.exponente - sesgo;
  int8_t exp;

  uint8_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  int32_t suma = val_a + val_b;
  uint32_t abs_suma = (suma < 0) ? -(uint32_t)suma : (uint32_t)suma;

  PaxoNum16 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 11)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < -7)
    exp = -7;
  if (exp > 8)
    exp = 8;

  result.exponente = (unsigned _BitInt(4))(exp + sesgo);
  result.entero = (unsigned _BitInt(5))((abs_suma >> 6) & 0x1f);
  result.fraccion = (unsigned _BitInt(6))(abs_suma & 0x3f);
  return result;
}

PaxoNum16 sub_num16(PaxoNum16 a, PaxoNum16 b) {
  const uint8_t sesgo = 7;
  int32_t val_a = a.fraccion + ((int32_t)a.entero * 64);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  int32_t val_b = b.fraccion + ((int32_t)b.entero * 64);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int8_t exp_a = a.exponente - sesgo;
  int8_t exp_b = b.exponente - sesgo;
  int8_t exp;

  uint8_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  int32_t suma = val_a - val_b;
  uint32_t abs_suma = (suma < 0) ? -(uint32_t)suma : (uint32_t)suma;

  PaxoNum16 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma > (1ULL << 11)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < -7)
    exp = -7;
  if (exp > 8)
    exp = 8;

  result.exponente = (unsigned _BitInt(4))(exp + sesgo);
  result.entero = (unsigned _BitInt(5))((abs_suma >> 6) & 0x1f);
  result.fraccion = (unsigned _BitInt(6))(abs_suma & 0x3f);
  return result;
}

PaxoNum16 mul_num16(PaxoNum16 a, PaxoNum16 b) {
  const uint8_t sesgo = 7;
  int16_t val_a = a.fraccion + ((int16_t)a.entero * 64);
  int16_t val_b = b.fraccion + ((int16_t)b.entero * 64);

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  int32_t mult = ((int32_t)val_a * val_b) >> 6;
  int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

  while (mult >= (1ULL << 11)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < 0)
    exp_final = 0;
  if (exp_final > 15)
    exp_final = 15;

  PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(4))exp_final;
  result.entero = (unsigned _BitInt(5))((mult >> 6) & 0x1f);
  result.fraccion = (unsigned _BitInt(6))(mult & 0x3f);
  return result;
}

PaxoNum16 div_num16(PaxoNum16 a, PaxoNum16 b) {
  const uint8_t sesgo = 7;
  int16_t val_a = a.fraccion + ((int16_t)a.entero * 64);
  int16_t val_b = b.fraccion + ((int16_t)b.entero * 64);

  if (val_b == 0) {
    PaxoNum16 error = {0, 0, 0, 0};
    return error;
  }

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  int32_t mult = ((int32_t)val_a << 6) / val_b;

  int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

  while (mult >= (1ULL << 11)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < -7)
    exp_final = -7;
  if (exp_final > 8)
    exp_final = 8;

  PaxoNum16 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(4))exp_final;
  result.entero = (unsigned _BitInt(5))((mult >> 6) & 0x1f);
  result.fraccion = (unsigned _BitInt(6))(mult & 0x3f);
  return result;
}

// 32 bits
PaxoNum32 add_num32(PaxoNum32 a, PaxoNum32 b) {
  const uint8_t sesgo = 31;
  int64_t val_a = a.fraccion + ((int64_t)a.entero * 8192);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  int64_t val_b = b.fraccion + ((int64_t)b.entero * 8192);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int16_t exp_a = a.exponente - sesgo;
  int16_t exp_b = b.exponente - sesgo;
  int16_t exp;

  uint8_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  int64_t suma = val_a + val_b;
  uint64_t abs_suma = (suma < 0) ? -(uint64_t)suma : (uint64_t)suma;

  PaxoNum32 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 25)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < -31)
    exp = -31;
  if (exp > 32)
    exp = 32;

  result.exponente = (unsigned _BitInt(6))(exp + sesgo);
  result.entero = (unsigned _BitInt(12))((abs_suma >> 13) & 0xfff);
  result.fraccion = (unsigned _BitInt(13))(abs_suma & 0x1fff);
  return result;
}

PaxoNum32 sub_num32(PaxoNum32 a, PaxoNum32 b) {
  const uint8_t sesgo = 31;
  int64_t val_a = a.fraccion + ((int64_t)a.entero * 8192);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  int64_t val_b = b.fraccion + ((int64_t)b.entero * 8192);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int16_t exp_a = a.exponente - sesgo;
  int16_t exp_b = b.exponente - sesgo;
  int16_t exp;

  uint8_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  int64_t suma = val_a - val_b;
  uint64_t abs_suma = (suma < 0) ? -(uint64_t)suma : (uint64_t)suma;

  PaxoNum32 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 25)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < -31)
    exp = -31;
  if (exp > 32)
    exp = 32;

  result.exponente = (unsigned _BitInt(6))(exp + sesgo);
  result.entero = (unsigned _BitInt(12))((abs_suma >> 13) & 0xfff);
  result.fraccion = (unsigned _BitInt(13))(abs_suma & 0x1fff);
  return result;
}

PaxoNum32 mul_num32(PaxoNum32 a, PaxoNum32 b) {
  const uint8_t sesgo = 31;
  int32_t val_a = a.fraccion + ((int32_t)a.entero * 8192);
  int32_t val_b = b.fraccion + ((int32_t)b.entero * 8192);

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  int64_t mult = ((int64_t)val_a * val_b) >> 13;
  int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

  while (mult >= (1ULL << 25)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < -31)
    exp_final = -31;
  if (exp_final > 32)
    exp_final = 32;

  PaxoNum32 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(6))exp_final;
  result.entero = (unsigned _BitInt(12))((mult >> 13) & 0xfff);
  result.fraccion = (unsigned _BitInt(13))(mult & 0x1fff);
  return result;
}

PaxoNum32 div_num32(PaxoNum32 a, PaxoNum32 b) {
  const uint8_t sesgo = 31;
  int32_t val_a = a.fraccion + ((int32_t)a.entero * 8192);
  int32_t val_b = b.fraccion + ((int32_t)b.entero * 8192);

  if (val_b == 0) {
    PaxoNum32 error = {0, 0, 0, 0};
    return error;
  }

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  int64_t mult = ((int64_t)val_a << 13) / val_b;

  int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

  while (mult >= (1ULL << 25)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < -31)
    exp_final = -31;
  if (exp_final > 32)
    exp_final = 32;

  PaxoNum32 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(6))exp_final;
  result.entero = (unsigned _BitInt(12))((mult >> 13) & 0xfff);
  result.fraccion = (unsigned _BitInt(13))(mult & 0x1fff);
  return result;
}

// 64 bits
PaxoNum64 add_num64(PaxoNum64 a, PaxoNum64 b) {
  const uint16_t sesgo = 511;
  _BitInt(128) val_a = a.fraccion + ((_BitInt(128))a.entero * 134217728);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  _BitInt(128) val_b = b.fraccion + ((_BitInt(128))b.entero * 134217728);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int16_t exp_a = a.exponente - sesgo;
  int16_t exp_b = b.exponente - sesgo;
  int16_t exp;

  uint16_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  _BitInt(128) suma = val_a + val_b;
  unsigned _BitInt(128) abs_suma =
      (suma < 0) ? -(unsigned _BitInt(128))suma : (unsigned _BitInt(128))suma;

  PaxoNum64 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 53)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < -511)
    exp = -511;
  if (exp > 512)
    exp = 512;

  result.exponente = (unsigned _BitInt(10))(exp + sesgo);
  result.entero = (unsigned _BitInt(26))((abs_suma >> 27) & 0x3ffffff);
  result.fraccion = (unsigned _BitInt(27))(abs_suma & 0x7ffffff);
  return result;
}

PaxoNum64 sub_num64(PaxoNum64 a, PaxoNum64 b) {
  const uint16_t sesgo = 511;
  _BitInt(128) val_a = a.fraccion + ((_BitInt(128))a.entero * 134217728LL);
  val_a = (a.signo >= 1) ? -val_a : val_a;
  _BitInt(128) val_b = b.fraccion + ((_BitInt(128))b.entero * 134217728LL);
  val_b = (b.signo >= 1) ? -val_b : val_b;

  int16_t exp_a = a.exponente - sesgo;
  int16_t exp_b = b.exponente - sesgo;
  int16_t exp;

  uint16_t diff;
  if (exp_a > exp_b) {
    diff = exp_a - exp_b;
    for (int i = 0; i < diff; i++) {
      val_b /= 10;
      exp_b++;
    }

    exp = exp_b;
  } else if (exp_b > exp_a) {
    diff = exp_b - exp_a;
    for (int i = 0; i < diff; i++) {
      val_a /= 10;
      exp_a++;
    }

    exp = exp_a;
  } else {
    exp = exp_a;
  }

  _BitInt(128) suma = val_a - val_b;
  unsigned _BitInt(128) abs_suma =
      (suma < 0) ? -(unsigned _BitInt(128))suma : (unsigned _BitInt(128))suma;

  PaxoNum64 result;
  result.signo = (suma < 0) ? 1 : 0;

  while (abs_suma >= (1ULL << 53)) {
    abs_suma /= 10;
    exp++;
  }

  if (exp < -511)
    exp = -511;
  if (exp > 512)
    exp = 512;

  result.exponente = (unsigned _BitInt(10))(exp + sesgo);
  result.entero = (unsigned _BitInt(26))((abs_suma >> 27) & 0x3ffffff);
  result.fraccion = (unsigned _BitInt(27))(abs_suma & 0x7ffffff);
  return result;
}

PaxoNum64 mul_num64(PaxoNum64 a, PaxoNum64 b) {
  const uint16_t sesgo = 511;
  int64_t val_a = a.fraccion + ((int64_t)a.entero * 134217728LL);
  int64_t val_b = b.fraccion + ((int64_t)b.entero * 134217728LL);

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  _BitInt(128) mult = ((_BitInt(128))val_a * val_b) >> 27;
  int16_t exp_final = (int16_t)a.exponente + (int16_t)b.exponente - sesgo;

  while (mult >= (1ULL << 53)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < -511)
    exp_final = -511;
  if (exp_final > 512)
    exp_final = 512;

  PaxoNum64 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(10))exp_final;
  result.entero = (unsigned _BitInt(26))((mult >> 27) & 0x3ffffff);
  result.fraccion = (unsigned _BitInt(27))(mult & 0x7ffffff);
  return result;
}

PaxoNum64 div_num64(PaxoNum64 a, PaxoNum64 b) {
  const uint16_t sesgo = 511;
  int64_t val_a = a.fraccion + ((int64_t)a.entero * 134217728LL);
  int64_t val_b = b.fraccion + ((int64_t)b.entero * 134217728LL);

  if (val_b == 0) {
    PaxoNum64 error = {0, 0, 0, 0};
    return error;
  }

  uint8_t signo_final = (a.signo != b.signo) ? 1 : 0;
  _BitInt(128) mult = ((_BitInt(128))val_a << 27) / val_b;

  int16_t exp_final = (int16_t)a.exponente - (int16_t)b.exponente + sesgo;

  while (mult >= (1ULL << 53)) {
    mult /= 10;
    exp_final++;
  }

  if (exp_final < -511)
    exp_final = -511;
  if (exp_final > 512)
    exp_final = 512;

  PaxoNum64 result;
  result.signo = signo_final;
  result.exponente = (unsigned _BitInt(10))exp_final;
  result.entero = (unsigned _BitInt(26))((mult >> 27) & 0x3ffffff);
  result.fraccion = (unsigned _BitInt(27))(mult & 0x7ffffff);
  return result;
}