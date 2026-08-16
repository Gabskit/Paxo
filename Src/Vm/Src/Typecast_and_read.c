#pragma once
#include "Calc.c"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <uchar.h>

typedef unsigned char char8_t;

// ==========================================
// SESGOS DE EXPONENTE Y BASE
// ==========================================
// Num8:  exp:2 -> Bias = 1
// Num16: exp:5 -> Bias = 15
// Num32: exp:8 -> Bias = 127
// Num64: exp:7 -> Bias = 63

// ==========================================
// CONVERSIÓN DE TIPOS MOBILE POINT
// ==========================================

// --- 8 BITS A OTROS ---
Num16 num8tonum16(Num8 num) {
  Num16 result;
  result.signo = num.signo;
  result.exp = num.exp + 14; // 15 - 1
  result.hp = (uint16_t)num.hp << 4; // Escala de 1 a 2 nibbles
  result.p = num.p;
  return result;
}

Num32 num8tonum32(Num8 num) {
  Num32 result;
  result.signo = num.signo;
  result.exp = num.exp + 126; // 127 - 1
  result.hp = (uint32_t)num.hp << 16; // Escala de 1 a 5 nibbles
  result.p = num.p;
  return result;
}

Num64 num8tonum64(Num8 num) {
  Num64 result;
  result.signo = num.signo;
  result.exp = num.exp + 62; // 63 - 1
  result.hp = (uint64_t)num.hp << 48; // Escala de 1 a 13 nibbles
  result.p = num.p;
  return result;
}

// --- 16 BITS A OTROS ---
Num8 num16tonum8(Num16 num) {
  Num8 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 14;
  result.exp = new_exp < 0 ? 0 : (new_exp > 3 ? 3 : new_exp);
  result.hp = (uint8_t)(num.hp >> 4);
  result.p = num.p & 0x1;
  return result;
}

Num32 num16tonum32(Num16 num) {
  Num32 result;
  result.signo = num.signo;
  result.exp = num.exp + 112; // 127 - 15
  result.hp = (uint32_t)num.hp << 12;
  result.p = num.p;
  return result;
}

Num64 num16tonum64(Num16 num) {
  Num64 result;
  result.signo = num.signo;
  result.exp = num.exp + 48; // 63 - 15
  result.hp = (uint64_t)num.hp << 44;
  result.p = num.p;
  return result;
}

// --- 32 BITS A OTROS ---
Num8 num32tonum8(Num32 num) {
  Num8 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 126;
  result.exp = new_exp < 0 ? 0 : (new_exp > 3 ? 3 : new_exp);
  result.hp = (uint8_t)(num.hp >> 16);
  result.p = num.p & 0x1;
  return result;
}

Num16 num32tonum16(Num32 num) {
  Num16 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 112;
  result.exp = new_exp < 0 ? 0 : (new_exp > 31 ? 31 : new_exp);
  result.hp = (uint16_t)(num.hp >> 12);
  result.p = num.p & 0x3;
  return result;
}

Num64 num32tonum64(Num32 num) {
  Num64 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 64; // 63 - 127
  result.exp = new_exp < 0 ? 0 : (new_exp > 127 ? 127 : new_exp);
  result.hp = (uint64_t)num.hp << 32;
  result.p = num.p;
  return result;
}

// --- 64 BITS A OTROS ---
Num8 num64tonum8(Num64 num) {
  Num8 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 62;
  result.exp = new_exp < 0 ? 0 : (new_exp > 3 ? 3 : new_exp);
  result.hp = (uint8_t)(num.hp >> 48);
  result.p = num.p & 0x1;
  return result;
}

Num16 num64tonum16(Num64 num) {
  Num16 result;
  result.signo = num.signo;
  int new_exp = (int)num.exp - 48;
  result.exp = new_exp < 0 ? 0 : (new_exp > 31 ? 31 : new_exp);
  result.hp = (uint16_t)(num.hp >> 44);
  result.p = num.p & 0x3;
  return result;
}

Num32 num64tonum32(Num64 num) {
  Num32 result;
  result.signo = num.signo;
  result.exp = num.exp + 64; // 127 - 63
  result.hp = (uint32_t)(num.hp >> 32);
  result.p = num.p & 0x7;
  return result;
}

// --- CONVERSIÓN CON TRIT / BOOL ---
Num8 trittonum8(PaxoBool trit) {
  Num8 result = {0};
  result.exp = 1; // Bias 1 = 20^0
  result.hp = (uint8_t)trit;
  return result;
}

Num16 trittonum16(PaxoBool trit) {
  Num16 result = {0};
  result.exp = 15; // Bias 15 = 20^0
  result.hp = (uint16_t)trit;
  return result;
}

Num32 trittonum32(PaxoBool trit) {
  Num32 result = {0};
  result.exp = 127; // Bias 127 = 20^0
  result.hp = (uint32_t)trit;
  return result;
}

Num64 trittonum64(PaxoBool trit) {
  Num64 result = {0};
  result.exp = 63; // Bias 63 = 20^0
  result.hp = (uint64_t)trit;
  return result;
}

PaxoBool num8totrit(Num8 num) { return (num.hp < 3) ? (PaxoBool)num.hp : 0; }
PaxoBool num16totrit(Num16 num) { return (num.hp < 3) ? (PaxoBool)num.hp : 0; }
PaxoBool num32totrit(Num32 num) { return (num.hp < 3) ? (PaxoBool)num.hp : 0; }
PaxoBool num64totrit(Num64 num) { return (num.hp < 3) ? (PaxoBool)num.hp : 0; }

Num8 booltonum8(bool bit) {
  Num8 result = {0};
  result.exp = 1;
  result.hp = bit ? 1 : 0;
  return result;
}

Num16 booltonum16(bool bit) {
  Num16 result = {0};
  result.exp = 15;
  result.hp = bit ? 1 : 0;
  return result;
}

Num32 booltonum32(bool bit) {
  Num32 result = {0};
  result.exp = 127;
  result.hp = bit ? 1 : 0;
  return result;
}

Num64 booltonum64(bool bit) {
  Num64 result = {0};
  result.exp = 63;
  result.hp = bit ? 1 : 0;
  return result;
}

bool num8tobool(Num8 num) { return (num.hp != 0); }
bool num16tobool(Num16 num) { return (num.hp != 0); }
bool num32tobool(Num32 num) { return (num.hp != 0); }
bool num64tobool(Num64 num) { return (num.hp != 0); }

PaxoBool booltotrit(bool bit) { return bit ? 1 : 0; }
bool trittobool(PaxoBool trit) { return (trit == 1); }

// ==========================================
// LECTURA / FORMATEO DE CADENAS
// ==========================================

const char8_t *readtrit(PaxoBool trit) {
  if (trit == 0) return u8"×";
  if (trit == 1) return u8"•";
  return u8"✓";
}

const char8_t *readbool(bool bit) {
  return bit ? u8"true" : u8"false";
}

const char8_t *readnum8(Num8 num, PaxoBool rep) {
  static char8_t buffer[64];
  int exp_real = (int)num.exp - 1; // Bias = 1

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 20^(%d)",
             num.signo ? "-" : "", (unsigned)num.hp, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.hp / (num.p ? 16.0 : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.6g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | HP:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.hp, (unsigned)num.p);
  }
  return buffer;
}

const char8_t *readnum16(Num16 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 15; // Bias = 15

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 20^(%d)",
             num.signo ? "-" : "", (unsigned)num.hp, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.hp / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.10g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | HP:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.hp, (unsigned)num.p);
  }
  return buffer;
}

const char8_t *readnum32(Num32 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 127; // Bias = 127

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%X × 20^(%d)",
             num.signo ? "-" : "", (unsigned)num.hp, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.hp / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.15g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | HP:0x%X | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned)num.hp, (unsigned)num.p);
  }
  return buffer;
}

const char8_t *readnum64(Num64 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exp - 63; // Bias = 63

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s0x%llX × 20^(%d)",
             num.signo ? "-" : "", (unsigned long long)num.hp, exp_real);
  } else if (rep == 1) {
    double mantissa = (double)num.hp / (num.p ? pow(16.0, num.p) : 1.0);
    double val = (num.signo ? -1.0 : 1.0) * mantissa * pow(20.0, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.20g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | HP:0x%llX | P:%u]",
             (unsigned)num.signo, (unsigned)num.exp, (unsigned long long)num.hp, (unsigned)num.p);
  }
  return buffer;
}
