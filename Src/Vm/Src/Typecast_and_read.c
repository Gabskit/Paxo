#include "Calc.c"
#include <stdint.h>

//Conversion de tipos
//8 bits
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

//16 bits
PaxoNum8 num16tonum8(PaxoNum16 num) {
	PaxoNum8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(1))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  result.fraccion = (unsigned _BitInt(2))((num.fraccion * 4) / 64);
  return result;}

PaxoNum32 num16tonum32(PaxoNum16 num) {
	PaxoNum32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(6))num.exponente;
  result.entero = (unsigned _BitInt(12))num.entero;
  result.fraccion = (unsigned _BitInt(13))((num.fraccion * 8192) / 64);
  return result;}

PaxoNum64 num16tonum64(PaxoNum16 num) {
	PaxoNum64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(10))num.exponente;
  result.entero = (unsigned _BitInt(26))num.entero;
  result.fraccion = (unsigned _BitInt(27))((num.fraccion * 134217728LL) / 64);
  return result;}

//32 bits
PaxoNum8 num32tonum8(PaxoNum32 num) {
	PaxoNum8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(1))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  result.fraccion = (unsigned _BitInt(2))((num.fraccion * 4) / 8192);
  return result;}

PaxoNum16 num32tonum16(PaxoNum32 num) {
	PaxoNum16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(4))num.exponente;
  result.entero = (unsigned _BitInt(5))num.entero;
  result.fraccion = (unsigned _BitInt(6))((num.fraccion * 64) / 8192);
  return result;}

PaxoNum64 num32tonum64(PaxoNum64 num) {
	PaxoNum64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(10))num.exponente;
  result.entero = (unsigned _BitInt(26))num.entero;
  result.fraccion = (unsigned _BitInt(27))((num.fraccion * 134217728LL) / 8192);
  return result;}

//64 bits
PaxoNum8 num64tonum8(PaxoNum64 num) {
	PaxoNum8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(1))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  result.fraccion = (unsigned _BitInt(2))((num.fraccion * 4) / 134217728LL);
  return result;}

PaxoNum16 num64tonum16(PaxoNum64 num) {
	PaxoNum16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(4))num.exponente;
  result.entero = (unsigned _BitInt(5))num.entero;
  result.fraccion = (unsigned _BitInt(6))((num.fraccion * 64) / 134217728LL);
  return result;}

PaxoNum32 num64tonum32(PaxoNum64 num) {
	PaxoNum32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(6))num.exponente;
  result.entero = (unsigned _BitInt(12))num.entero;
  result.fraccion = (unsigned _BitInt(13))((num.fraccion * 8192) / 134217728LL);
  return result;}

//trit a num
PaxoNum8 trittonum8(PaxoBool trit) {
	PaxoNum8 result;
	result.signo = 0;
	result.exponente = 0;
	result.entero = (unsigned _BitInt(4))trit;
	result.fraccion = 0;
	return result;}

PaxoNum16 trittonum16(PaxoBool trit) {
	PaxoNum16 result;
	result.signo = 0;
	result.exponente = 0;
	result.entero = (unsigned _BitInt(5))trit;
	result.fraccion = 0;
	return result;}

PaxoNum32 trittonum32(PaxoBool trit) {
	PaxoNum32 result;
	result.signo = 0;
	result.exponente = 0;
	result.entero = (unsigned _BitInt(12))trit;
	result.fraccion = 0;
	return result;}

PaxoNum64 trittonum64(PaxoBool trit) {
	PaxoNum64 result;
	result.signo = 0;
	result.exponente = 0;
	result.entero = (unsigned _BitInt(26))trit;
	result.fraccion = 0;
	return result;}

//num to trit
PaxoBool num8totrit(PaxoNum8 num) {
	PaxoBool result = (num.entero < 3)? (PaxoBool)num.entero : 0;
	return result;}

PaxoBool num16totrit(PaxoNum16 num) {
	PaxoBool result = (num.entero < 3)? (PaxoBool)num.entero : 0;
	return result;}

PaxoBool num32totrit(PaxoNum32 num) {
	PaxoBool result = (num.entero < 3)? (PaxoBool)num.entero : 0;
	return result;}

PaxoBool num64totrit(PaxoNum64 num) {
	PaxoBool result = (num.entero < 3)? (PaxoBool)num.entero : 0;
	return result;}

//