#pragma once
#include "Calc.c"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// SESGOS DE EXPONENTE Y BASE (REVISIÓN ALGO_2)
// ==========================================
// Num8:  exp:1  -> Bias = 0
// Num16: exp:2  -> Bias = 1
// Num32: exp:5  -> Bias = 15
// Num64: exp:10 -> Bias = 511

// ==========================================
// CONVERSIÓN DE TIPOS MOBILE POINT
// ==========================================

static inline Num64 num16tonum64(Num16 num) {
  Num64 result;
  result.signo = num.signo;
  result.bc = (uint64_t)num.bc;
  result.exp = (uint64_t)((int)num.exp + 510); // bias 1 → 511
  result.p = (uint64_t)num.p;
  return result;
}

static inline Num16 num64tonum16(Num64 num) {
  Num16 result;
  result.signo = num.signo;
  result.p = num.p & 0x7;
  uint64_t bc = num.bc;
  int64_t exp = (int64_t)num.exp - 510; // bias 511 → 1
  while (bc > 1023) {
    bc = (bc + 9) / 10;
    exp++;
  }
  if (exp < 0)
    exp = 0;
  if (exp > 3)
    exp = 3;
  result.exp = (uint16_t)exp;
  result.bc = (uint16_t)bc;
  return result;
}

// --- CONVERSIÓN CON TRIT / BOOL ---

static inline Num16 trittonum16(PaxoBool trit) {
  Num16 result = {0};
  result.exp = 1; // Bias 1 = 10^0
  result.bc = (uint16_t)trit;
  return result;
}

static inline Num64 trittonum64(PaxoBool trit) {
  Num64 result = {0};
  result.exp = 511; // Bias 511 = 10^0
  result.bc = (uint64_t)trit;
  return result;
}

static inline PaxoBool num16totrit(Num16 num) {
  return (num.bc < 3) ? (PaxoBool)num.bc : 0;
}
static inline PaxoBool num64totrit(Num64 num) {
  return (num.bc < 3) ? (PaxoBool)num.bc : 0;
}

static inline Num16 booltonum16(bool bit) {
  Num16 result = {0};
  result.exp = 1;
  result.bc = bit ? 1 : 0;
  return result;
}

static inline Num64 booltonum64(bool bit) {
  Num64 result = {0};
  result.exp = 511;
  result.bc = bit ? 1 : 0;
  return result;
}

static inline bool num16tobool(Num16 num) { return (num.bc != 0); }
static inline bool num64tobool(Num64 num) { return (num.bc != 0); }

static inline PaxoBool booltotrit(bool bit) { return bit ? 1 : 0; }
static inline bool trittobool(PaxoBool trit) { return (trit == 1); }

// ==========================================
// LECTURA / FORMATEO DE CADENAS
// ==========================================

static inline const char8_t *readtrit(PaxoBool trit) {
  if (trit == 0)
    return u8"×";
  if (trit == 1)
    return u8"•";
  return u8"✓";
}

static inline const char8_t *readbool(bool bit) { return bit ? u8"true" : u8"false"; }

static inline const char8_t *readnum16(Num16 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 1; // Bias = 1

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 10^(%d)",
             num.signo ? "-" : "", (unsigned)num.bc, exp_real);
  } else if (rep == 1) {
    int total_exp = exp_real - (int)num.p;
    uint32_t val = (uint32_t)num.bc;
    if (total_exp >= 0) {
      for (int i = 0; i < total_exp; i++) val *= 10;
      snprintf((char *)buffer, sizeof(buffer), "%s%u",
               num.signo ? "-" : "", val);
    } else {
      int frac = -total_exp;
      char temp[32];
      int len = snprintf(temp, sizeof(temp), "%u", val);
      if (len <= frac) {
        snprintf((char *)buffer, sizeof(buffer), "%s0.%.*s%s",
                 num.signo ? "-" : "", frac - len,
                 "00000000000000000000", temp);
      } else {
        snprintf((char *)buffer, sizeof(buffer), "%s%.*s.%s",
                 num.signo ? "-" : "", len - frac, temp, temp + len - frac);
      }
    }
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}

static inline const char8_t *readnum64(Num64 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 511; // Bias = 511

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%llX × 10^(%d)",
             num.signo ? "-" : "", (unsigned long long)num.bc, exp_real);
  } else if (rep == 1) {
    int total_exp = exp_real - (int)num.p;
    unsigned _BitInt(128) val = num.bc;
    if (total_exp >= 0) {
      for (int i = 0; i < total_exp; i++) val *= 10;
      snprintf((char *)buffer, sizeof(buffer), "%s%llu",
               num.signo ? "-" : "", (unsigned long long)val);
    } else {
      int frac = -total_exp;
      char temp[64];
      int len = snprintf(temp, sizeof(temp), "%llu", (unsigned long long)val);
      if (len <= frac) {
        snprintf((char *)buffer, sizeof(buffer), "%s0.%.*s%s",
                 num.signo ? "-" : "", frac - len,
                 "00000000000000000000", temp);
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
