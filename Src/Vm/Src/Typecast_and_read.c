#include "Calc.c"
#include <stdint.h>

// Conversion de tipos
// 8 bits
Num16 num8tonum16(Num8 num) {
  Num16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(5))num.exponente;
  result.entero = (unsigned _BitInt(10))num.entero;
  return result;
}

Num32 num8tonum32(Num8 num) {
  Num32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(8))num.exponente;
  result.entero = (unsigned _BitInt(23))num.entero;
  return result;
}

Num64 num8tonum64(Num8 num) {
  Num64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(11))num.exponente;
  result.entero = (unsigned _BitInt(52))num.entero;
  return result;
}

// 16 bits
Num8 num16tonum8(Num16 num) {
  Num8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(3))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  return result;
}

Num32 num16tonum32(Num16 num) {
  Num32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(8))num.exponente;
  result.entero = (unsigned _BitInt(23))num.entero;
  return result;
}

Num64 num16tonum64(Num16 num) {
  Num64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(11))num.exponente;
  result.entero = (unsigned _BitInt(52))num.entero;
  return result;
}

// 32 bits
Num8 num32tonum8(Num32 num) {
  Num8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(3))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  return result;
}

Num16 num32tonum16(Num32 num) {
  Num16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(5))num.exponente;
  result.entero = (unsigned _BitInt(10))num.entero;
  return result;
}

Num64 num32tonum64(Num32 num) {
  Num64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(11))num.exponente;
  result.entero = (unsigned _BitInt(52))num.entero;
  return result;
}

// 64 bits
Num8 num64tonum8(Num64 num) {
  Num8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(3))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  return result;
}

Num16 num64tonum16(Num64 num) {
  Num16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(5))num.exponente;
  result.entero = (unsigned _BitInt(10))num.entero;
  return result;
}

Num32 num64tonum32(Num64 num) {
  Num32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(8))num.exponente;
  result.entero = (unsigned _BitInt(23))num.entero;
  return result;
}

// trit a num
Num8 trittonum8(PaxoBool trit) {
  Num8 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(4))trit;
  return result;
}

Num16 trittonum16(PaxoBool trit) {
  Num16 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(10))trit;
  return result;
}

Num32 trittonum32(PaxoBool trit) {
  Num32 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(23))trit;
  return result;
}

Num64 trittonum64(PaxoBool trit) {
  Num64 result;
  result.signo = 0;
  result.exponente = 0;
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
  result.exponente = 0;
  result.entero = (unsigned _BitInt(4))bit;
  return result;
}

Num16 booltonum16(bool bit) {
  Num16 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(10))bit;
  return result;
}

Num32 booltonum32(bool bit) {
  Num32 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(23))bit;
  return result;
}

Num64 booltonum64(bool bit) {
  Num64 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(52))bit;
  return result;
}

// num a bool
bool num8tobool(Num8 num) { return (num.entero != 0 || num.fraccion != 0); }

bool num16tobool(Num16 num) { return (num.entero != 0 || num.fraccion != 0); }

bool num32tobool(Num32 num) { return (num.entero != 0 || num.fraccion != 0); }

bool num64tobool(Num64 num) { return (num.entero != 0 || num.fraccion != 0); }

PaxoBool booltotrit(bool bit) { return bit ? 1 : 0; }

bool trittobool(PaxoBool trit) { return (trit == 1); }
