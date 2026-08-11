#include "Calc.c"
#include <stdint.h>

PaxoNum16 num8tonum16(PaxoNum8 num) {
  PaxoNum16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(4))num.exponente;
  result.entero = (unsigned _BitInt(5))num.entero;
  result.fraccion = (unsigned _BitInt(6))((num.fraccion * 64) / 4);
  return result;
}

PaxoNum32 num8tonum32(PaxoNum8 num) {
  PaxoNum32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(6))num.exponente;
  result.entero = (unsigned _BitInt(12))num.entero;
  result.fraccion = (unsigned _BitInt(13))((num.fraccion * 8192) / 4);
  return result;
}

PaxoNum64 num8tonum64(PaxoNum8 num) {
  PaxoNum64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(10))num.exponente;
  result.entero = (unsigned _BitInt(26))num.entero;
  result.fraccion = (unsigned _BitInt(27))((num.fraccion * 134217728LL) / 4);
  return result;
}
