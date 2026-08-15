#include "Calc.c"
#include <math.h> // Define pow
#include <stdint.h>
#include <stdio.h> // Define snprintf
#include <uchar.h> // Define char8_t en C23

typedef unsigned char char8_t;

// ==========================================
// CONVERSIÓN DE TIPOS 
// ==========================================

// --- 8 BITS A OTROS ---
Num16 num8tonum16(Num8 num) {
  Num16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(5))(num.exponente + 12); // 15 - 3
  result.entero = (unsigned _BitInt(10))num.entero;
  return result;
}

Num32 num8tonum32(Num8 num) {
  Num32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(8))(num.exponente + 124); // 127 - 3
  result.entero = (unsigned _BitInt(23))num.entero;
  return result;
}

Num64 num8tonum64(Num8 num) {
  Num64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(11))(num.exponente + 1020); // 1023 - 3
  result.entero = (unsigned _BitInt(52))num.entero;
  return result;
}

// --- 16 BITS A OTROS ---
Num8 num16tonum8(Num16 num) {
  Num8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(3))(num.exponente - 12); // 3 - 15
  result.entero = (unsigned _BitInt(4))num.entero;
  return result;
}

Num32 num16tonum32(Num16 num) {
  Num32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(8))(num.exponente + 112); // 127 - 15
  result.entero = (unsigned _BitInt(23))num.entero;
  return result;
}

Num64 num16tonum64(Num16 num) {
  Num64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(11))(num.exponente + 1008); // 1023 - 15
  result.entero = (unsigned _BitInt(52))num.entero;
  return result;
}

// --- 32 BITS A OTROS ---
Num8 num32tonum8(Num32 num) {
  Num8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(3))(num.exponente - 124); // 3 - 127
  result.entero = (unsigned _BitInt(4))num.entero;
  return result;
}

Num16 num32tonum16(Num32 num) {
  Num16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(5))(num.exponente - 112); // 15 - 127
  result.entero = (unsigned _BitInt(10))num.entero;
  return result;
}

Num64 num32tonum64(Num32 num) {
  Num64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(11))(num.exponente + 896); // 1023 - 127
  result.entero = (unsigned _BitInt(52))num.entero;
  return result;
}

// --- 64 BITS A OTROS ---
Num8 num64tonum8(Num64 num) {
  Num8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(3))(num.exponente - 1020); // 3 - 1023
  result.entero = (unsigned _BitInt(4))num.entero;
  return result;
}

Num16 num64tonum16(Num64 num) {
  Num16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(5))(num.exponente - 1008); // 15 - 1023
  result.entero = (unsigned _BitInt(10))num.entero;
  return result;
}

Num32 num64tonum32(Num64 num) {
  Num32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(8))(num.exponente - 896); // 127 - 1023
  result.entero = (unsigned _BitInt(23))num.entero;
  return result;
}

// trit a num
Num8 trittonum8(PaxoBool trit) {
  Num8 result;
  result.signo = 0;
  result.exponente = 3;
  result.entero = (unsigned _BitInt(4))trit;
  return result;
}

Num16 trittonum16(PaxoBool trit) {
  Num16 result;
  result.signo = 0;
  result.exponente = 15;
  result.entero = (unsigned _BitInt(10))trit;
  return result;
}

Num32 trittonum32(PaxoBool trit) {
  Num32 result;
  result.signo = 0;
  result.exponente = 127;
  result.entero = (unsigned _BitInt(23))trit;
  return result;
}

Num64 trittonum64(PaxoBool trit) {
  Num64 result;
  result.signo = 0;
  result.exponente = 1023;
  result.entero = (unsigned _BitInt(52))trit;
  return result;
}

// num to trit
PaxoBool num8totrit(Num8 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

PaxoBool num16totrit(Num16 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

PaxoBool num32totrit(Num32 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

PaxoBool num64totrit(Num64 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

// bool a num
Num8 booltonum8(bool bit) {
  Num8 result;
  result.signo = 0;
  result.exponente = 3;
  result.entero = (unsigned _BitInt(4))bit;
  return result;
}

Num16 booltonum16(bool bit) {
  Num16 result;
  result.signo = 0;
  result.exponente = 15;
  result.entero = (unsigned _BitInt(10))bit;
  return result;
}

Num32 booltonum32(bool bit) {
  Num32 result;
  result.signo = 0;
  result.exponente = 127;
  result.entero = (unsigned _BitInt(23))bit;
  return result;
}

Num64 booltonum64(bool bit) {
  Num64 result;
  result.signo = 0;
  result.exponente = 1023;
  result.entero = (unsigned _BitInt(52))bit;
  return result;
}

// num a bool
bool num8tobool(Num8 num) { return (num.entero != 0); }

bool num16tobool(Num16 num) { return (num.entero != 0); }

bool num32tobool(Num32 num) { return (num.entero != 0); }

bool num64tobool(Num64 num) { return (num.entero != 0); }

PaxoBool booltotrit(bool bit) { return bit ? 1 : 0; }

bool trittobool(PaxoBool trit) { return (trit == 1); }

// interpretación
const char8_t *readtrit(PaxoBool trit) {
  if (trit == 0) {
    return u8"×";
  } else if (trit == 1) {
    return u8"•";
  } else {
    return u8"✓";
  }
}

const char8_t *readbool(bool bit) {
  if (bit) {
    return u8"true";
  } else {
    return u8"false";
  }
}

const char8_t *readnum8(Num8 num, PaxoBool rep) {
  static char8_t buffer[64];
  int exp_real = (int)num.exponente - 3; // Sesgo = 3
  if (rep == 0) {
    // Formato en notación científica: "-15 × 10^(-3)"
    snprintf((char *)buffer, sizeof(buffer), "%s%u × 10^(%d)",
             num.signo ? "-" : "", (unsigned)num.entero, exp_real);
  } else if (rep == 1) {
    double val = (num.signo ? -1.0 : 1.0) * num.entero * pow(10, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.10g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | I:%u]",
             (unsigned)num.signo, (unsigned)num.exponente,
             (unsigned)num.entero);
  }
  return buffer;
}

const char8_t *readnum16(Num16 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exponente - 15;

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s%u × 10^(%d)",
             num.signo ? "-" : "", (unsigned)num.entero, exp_real);
  } else if (rep == 1) {
    double val =
        (num.signo ? -1.0 : 1.0) * (double)num.entero * pow(10, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.15g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | I:%u]",
             (unsigned)num.signo, (unsigned)num.exponente,
             (unsigned)num.entero);
  }
  return buffer;
}

const char8_t *readnum32(Num32 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exponente - 127;

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s%llu × 10^(%d)",
             num.signo ? "-" : "", (unsigned long long)num.entero, exp_real);
  } else if (rep == 1) {
    double val = (num.signo ? -1.0 : 1.0) * (double)num.entero *
                 pow(10.0, (double)exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.20g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | I:%llu]",
             (unsigned)num.signo, (unsigned)num.exponente,
             (unsigned long long)num.entero);
  }
  return buffer;
}

const char8_t *readnum64(Num64 num, PaxoBool rep) {
  static char8_t buffer[128];
  int exp_real = (int)num.exponente - 1023;

  if (rep == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s%llu × 10^(%d)",
             num.signo ? "-" : "", (unsigned long long)num.entero, exp_real);
  } else if (rep == 1) {
    double val =
        (num.signo ? -1.0 : 1.0) * (double)num.entero * pow(10, exp_real);
    snprintf((char *)buffer, sizeof(buffer), "%.25g", val);
  } else {
    snprintf((char *)buffer, sizeof(buffer), "[S:%u | E:%u | I:%llu]",
             (unsigned)num.signo, (unsigned)num.exponente,
             (unsigned long long)num.entero);
  }
  return buffer;
}