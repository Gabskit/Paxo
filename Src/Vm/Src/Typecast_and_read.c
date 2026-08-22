#pragma once
#include "Calc.c"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// SESGOS DE EXPONENTE (MP REVISIÓN)
// Num16: exp:2  -> Bias = 1
// Num64: exp:8  -> Bias = 127
// ==========================================

// Conversión que PRESERVA EL VALOR decimal:
//   v = bc · 2^(-2p) · 10^(e) = (bc · 25^p) · 10^(e - 2p)
static inline Num64 num16tonum64(Num16 num) {
  static const uint64_t pow25[MP16_FRAC + 1] = {1,     25,     625,
                                                15625, 390625, 9765625};
  Num64 result = {0};
  result.signo = num.signo;
  if (num.bc == 0)
    return result;

  int16_t g = (int16_t)((int16_t)num.exp - BIAS16 - 2 * (int16_t)num.p);
  uint64_t bc = (uint64_t)num.bc * pow25[num.p];
  uint16_t p64 = 0;
  if (g >= 0) {
    bc *= num16_pow10((uint16_t)g);
  } else {
    int16_t falta = -g;
    p64 = (falta > 25) ? 25 : (uint16_t)falta; // límite de p en Num64
    bc *= num16_pow10((uint16_t)(falta - p64));
  }
  while (bc % 10 == 0 && p64 > 0) { // normaliza ceros finales
    bc /= 10;
    p64--;
  }
  result.bc = bc;
  result.p = p64;
  result.exp = (uint64_t)BIAS64;
  return result;
}

// Conversión que PRESERVA EL VALOR decimal: lleva el Num64 a unidades de
// 1/1024 y reempaqueta buscando la representación más fina
static inline Num16 num64tonum16(Num64 num) {
  if (num.bc == 0)
    return (Num16){0, (uint16_t)BIAS16, 0, 0};

  uint64_t bc = num.bc;
  int16_t e = (int16_t)((int64_t)num.exp - (int64_t)BIAS64 - (int64_t)num.p);
  while (bc % 10 == 0 && e < 32767) { // décadas exactas fuera del camino
    bc /= 10;
    e++;
  }
  while (bc > ((uint64_t)1 << 50)) { // cabe en el reempaquetado
    bc = (bc + 5) / 10;
    e++;
  }
  return num16_repack(num.signo, (int64_t)(bc << 10), e, MP16_MEDIO);
}

// --- CONVERSIÓN CON TRIT / BOOL ---

static inline Num16 trittonum16(PaxoBool trit) {
  Num16 result = {0};
  result.exp = BIAS16; // 10^0
  result.bc = (uint16_t)trit;
  return result;
}

static inline Num64 trittonum64(uint8_t trit) {
  Num64 result = {0};
  result.exp = BIAS64; // 10^0
  result.bc = (uint64_t)trit;
  return result;
}

static inline uint8_t num16totrit(Num16 num) {
  return (num.bc < 3) ? (uint8_t)num.bc : 0;
}

static inline uint8_t num64totrit(Num64 num) {
  return (num.bc < 3) ? (uint8_t)num.bc : 0;
}

static inline Num16 booltonum16(bool bit) {
  Num16 result = {0};
  result.exp = BIAS16;
  result.bc = bit ? 1 : 0;
  return result;
}

static inline Num64 booltonum64(bool bit) {
  Num64 result = {0};
  result.exp = BIAS64;
  result.bc = bit ? 1 : 0;
  return result;
}

static inline bool num16tobool(Num16 num) { return (num.bc != 0); }
static inline bool num64tobool(Num64 num) { return (num.bc != 0); }

static inline uint8_t booltotrit(bool bit) { return bit ? 1 : 0; }
static inline bool trittobool(uint8_t trit) { return (trit == 1); }

// ==========================================
// LECTURA / FORMATEO DE CADENAS
// ==========================================

static inline const char8_t *readtrit(uint8_t trit) {
  if (trit == 0)
    return u8"×";
  if (trit == 1)
    return u8"•";
  return u8"✓";
}

static inline const char8_t *readbool(bool bit) {
  return bit ? u8"true" : u8"false";
}

static inline const char8_t *readchar32(char32_t c) {
  static char8_t buffer[8];
  if (c < 0x80) {
    buffer[0] = (char8_t)c;
    buffer[1] = '\0';
  } else if (c < 0x800) {
    buffer[0] = (char8_t)(0xC0 | (c >> 6));
    buffer[1] = (char8_t)(0x80 | (c & 0x3F));
    buffer[2] = '\0';
  } else if (c < 0x10000) {
    buffer[0] = (char8_t)(0xE0 | (c >> 12));
    buffer[1] = (char8_t)(0x80 | ((c >> 6) & 0x3F));
    buffer[2] = (char8_t)(0x80 | (c & 0x3F));
    buffer[3] = '\0';
  } else {
    buffer[0] = (char8_t)(0xF0 | (c >> 18));
    buffer[1] = (char8_t)(0x80 | ((c >> 12) & 0x3F));
    buffer[2] = (char8_t)(0x80 | ((c >> 6) & 0x3F));
    buffer[3] = (char8_t)(0x80 | (c & 0x3F));
    buffer[4] = '\0';
  }
  return buffer;
}

static inline const char8_t *readnum16(Num16 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - BIAS16;

  if (rep == 0) {
    // descomposición radix mixto: bc · 2^(-2p) · 10^(exp-BIAS)
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X · 2^-%u · 10^(%d)",
             (num.signo && num.bc) ? "-" : "", (unsigned)num.bc,
             (unsigned)(2 * num.p), exp_real);
  } else if (rep == 1) {
    // valor decimal exacto: v = (bc·25^p)·10^(exp-BIAS) / 10^(2p)
    static const uint64_t pow25[MP16_FRAC + 1] = {1,     25,     625,
                                                  15625, 390625, 9765625};
    uint64_t val = (uint64_t)num.bc * pow25[num.p];
    int frac = 2 * (int)num.p;
    if (exp_real >= 0)
      val *= num16_pow10((uint16_t)exp_real);
    else
      frac += -exp_real;

    char temp[32];
    int len =
        snprintf((char *)temp, sizeof(temp), "%llu", (unsigned long long)val);
    while (frac > 0 && len > 1 && temp[len - 1] == '0') { // ceros finales
      len--;
      frac--;
    }

    char8_t *out = buffer;
    if (num.signo && num.bc != 0)
      *out++ = '-';
    if (len <= frac) {
      *out++ = '0';
      *out++ = '.';
      for (int i = 0; i < frac - len; i++)
        *out++ = '0';
      memcpy(out, temp, (size_t)len);
      out += len;
    } else {
      memcpy(out, temp, (size_t)(len - frac));
      out += len - frac;
      if (frac > 0) {
        *out++ = '.';
        memcpy(out, temp + (len - frac), (size_t)frac);
        out += frac;
      }
    }
    *out = '\0';
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}

static inline const char8_t *readnum64(Num64 num, PaxoBool rep) {
  static char8_t buffer[160];
  int exp_real = (int)num.exp - BIAS64;

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%llX × 10^(%d)",
             num.signo ? "-" : "", (unsigned long long)num.bc, exp_real);
  } else if (rep == 1) {
    int total_exp = exp_real - (int)num.p;
    unsigned _BitInt(128) val = num.bc;
    if (total_exp >= 0) {
      for (int i = 0; i < total_exp; i++)
        val *= 10;
      snprintf((char *)buffer, sizeof(buffer), "%s%llu", num.signo ? "-" : "",
               (unsigned long long)val);
    } else {
      int frac = -total_exp;
      char temp[64];
      int len = snprintf(temp, sizeof(temp), "%llu", (unsigned long long)val);
      if (len <= frac) {
        snprintf((char *)buffer, sizeof(buffer), "%s0.%.*s%s",
                 num.signo ? "-" : "", frac - len, "00000000000000000000",
                 temp);
      } else {
        snprintf((char *)buffer, sizeof(buffer), "%s%.*s.%s",
                 num.signo ? "-" : "", len - frac, temp, temp + len - frac);
      }
    }
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%llX | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned long long)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}
