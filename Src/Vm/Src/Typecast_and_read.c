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

// --- 8 BITS A OTROS ---
Num16 num8tonum16(Num8 num) {
  Num16 result;
  result.signo = num.signo;
  result.exp = num.exp + 1;          // 1 - 0
  result.bc = (uint16_t)num.bc << 6; // Escala de 4 a 10 bits
  result.p = num.p;
  return result;
}

Num32 num8tonum32(Num8 num) {
  Num32 result;
  result.signo = num.signo;
  result.exp = num.exp + 15;          // 15 - 0
  result.bc = (uint32_t)num.bc << 18; // Escala de 4 a 22 bits
  result.p = num.p;
  return result;
}

Num64 num8tonum64(Num8 num) {
  Num64 result;
  result.signo = num.signo;
  result.exp = num.exp + 511;         // 511 - 0
  result.bc = (uint64_t)num.bc << 44; // Escala de 4 a 48 bits
  result.p = num.p;
  return result;
}

// --- 16 BITS A OTROS ---
Num8 num16tonum8(Num16 num) {
  Num8 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 1; // 0 - 1
  result.exp = new_exp < 0 ? 0 : (new_exp > 1 ? 1 : new_exp);
  result.bc = (uint8_t)(num.bc >> 6);
  result.p = num.p & 0x3; // Trunca a 2 bits
  return result;
}

Num32 num16tonum32(Num16 num) {
  Num32 result;
  result.signo = num.signo;
  result.exp = num.exp + 14;          // 15 - 1
  result.bc = (uint32_t)num.bc << 12; // Escala de 10 a 22 bits
  result.p = num.p;
  return result;
}

Num64 num16tonum64(Num16 num) {
  Num64 result;
  result.signo = num.signo;
  result.exp = num.exp + 510;         // 511 - 1
  result.bc = (uint64_t)num.bc << 38; // Escala de 10 a 48 bits
  result.p = num.p;
  return result;
}

// --- 32 BITS A OTROS ---
Num8 num32tonum8(Num32 num) {
  Num8 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 15; // 0 - 15
  result.exp = new_exp < 0 ? 0 : (new_exp > 1 ? 1 : new_exp);
  result.bc = (uint8_t)(num.bc >> 18);
  result.p = num.p & 0x3; // Trunca a 2 bits
  return result;
}

Num16 num32tonum16(Num32 num) {
  Num16 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 14; // 1 - 15
  result.exp = new_exp < 0 ? 0 : (new_exp > 3 ? 3 : new_exp);
  result.bc = (uint16_t)(num.bc >> 12);
  result.p = num.p & 0x7; // Trunca a 3 bits
  return result;
}

Num64 num32tonum64(Num32 num) {
  Num64 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp + 496; // 511 - 15
  result.exp = new_exp < 0 ? 0 : (new_exp > 1023 ? 1023 : new_exp);
  result.bc = (uint64_t)num.bc << 26; // Escala de 22 a 48 bits
  result.p = num.p;
  return result;
}

// --- 64 BITS A OTROS ---
Num8 num64tonum8(Num64 num) {
  Num8 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 511; // 0 - 511
  result.exp = new_exp < 0 ? 0 : (new_exp > 1 ? 1 : new_exp);
  result.bc = (uint8_t)(num.bc >> 44);
  result.p = num.p & 0x3; // Trunca a 2 bits
  return result;
}

Num16 num64tonum16(Num64 num) {
  Num16 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 510; // 1 - 511
  result.exp = new_exp < 0 ? 0 : (new_exp > 3 ? 3 : new_exp);
  result.bc = (uint16_t)(num.bc >> 38);
  result.p = num.p & 0x7; // Trunca a 3 bits
  return result;
}

Num32 num64tonum32(Num64 num) {
  Num32 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 496; // 15 - 511
  result.exp = new_exp < 0 ? 0 : (new_exp > 31 ? 31 : new_exp);
  result.bc = (uint32_t)(num.bc >> 26);
  result.p = num.p & 0xF; // Trunca a 4 bits
  return result;
}

// --- CONVERSIÓN CON TRIT / BOOL ---
Num8 trittonum8(PaxoBool trit) {
  Num8 result = {0};
  result.exp = 0; // Bias 0 = 20^0
  result.bc = (uint8_t)trit;
  return result;
}

Num16 trittonum16(PaxoBool trit) {
  Num16 result = {0};
  result.exp = 1; // Bias 1 = 20^0
  result.bc = (uint16_t)trit;
  return result;
}

Num32 trittonum32(PaxoBool trit) {
  Num32 result = {0};
  result.exp = 15; // Bias 15 = 20^0
  result.bc = (uint32_t)trit;
  return result;
}

Num64 trittonum64(PaxoBool trit) {
  Num64 result = {0};
  result.exp = 511; // Bias 511 = 20^0
  result.bc = (uint64_t)trit;
  return result;
}

PaxoBool num8totrit(Num8 num) { return (num.bc < 3) ? (PaxoBool)num.bc : 0; }
PaxoBool num16totrit(Num16 num) { return (num.bc < 3) ? (PaxoBool)num.bc : 0; }
PaxoBool num32totrit(Num32 num) { return (num.bc < 3) ? (PaxoBool)num.bc : 0; }
PaxoBool num64totrit(Num64 num) { return (num.bc < 3) ? (PaxoBool)num.bc : 0; }

Num8 booltonum8(bool bit) {
  Num8 result = {0};
  result.exp = 0;
  result.bc = bit ? 1 : 0;
  return result;
}

Num16 booltonum16(bool bit) {
  Num16 result = {0};
  result.exp = 1;
  result.bc = bit ? 1 : 0;
  return result;
}

Num32 booltonum32(bool bit) {
  Num32 result = {0};
  result.exp = 15;
  result.bc = bit ? 1 : 0;
  return result;
}

Num64 booltonum64(bool bit) {
  Num64 result = {0};
  result.exp = 511;
  result.bc = bit ? 1 : 0;
  return result;
}

bool num8tobool(Num8 num) { return (num.bc != 0); }
bool num16tobool(Num16 num) { return (num.bc != 0); }
bool num32tobool(Num32 num) { return (num.bc != 0); }
bool num64tobool(Num64 num) { return (num.bc != 0); }

PaxoBool booltotrit(bool bit) { return bit ? 1 : 0; }
bool trittobool(PaxoBool trit) { return (trit == 1); }

// ==========================================
// LECTURA / FORMATEO DE CADENAS
// ==========================================

const char8_t *readtrit(PaxoBool trit) {
  if (trit == 0)
    return u8"×";
  if (trit == 1)
    return u8"•";
  return u8"✓";
}

const char8_t *readbool(bool bit) { return bit ? u8"true" : u8"false"; }

const char8_t *readnum8(Num8 num, PaxoBool rep) {
  static char8_t buffer[64];
  int exp_real = (int)num.exp - 0; // Bias = 0

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 20^(%d)",
             num.signo ? "-" : "", (unsigned)num.bc, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.bc / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.6g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}

const char8_t *readnum16(Num16 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 1; // Bias = 1

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 20^(%d)",
             num.signo ? "-" : "", (unsigned)num.bc, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.bc / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.10g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}

const char8_t *readnum32(Num32 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 15; // Bias = 15

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 20^(%d)",
             num.signo ? "-" : "", (unsigned)num.bc, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.bc / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.15g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}

const char8_t *readnum64(Num64 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 511; // Bias = 511

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%llX × 20^(%d)",
             num.signo ? "-" : "", (unsigned long long)num.bc, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.bc / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.20g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | BC:0x%llX | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned long long)num.bc,
             (unsigned)num.p);
  }
  return buffer;
}
