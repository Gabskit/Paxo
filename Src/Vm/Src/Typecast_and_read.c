#include "Calc.c"
#include <stdint.h>

// Conversion de tipos
// 8 bits
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

// 16 bits
PaxoNum8 num16tonum8(PaxoNum16 num) {
  PaxoNum8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(1))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  result.fraccion = (unsigned _BitInt(2))((num.fraccion * 4) / 64);
  return result;
}

PaxoNum32 num16tonum32(PaxoNum16 num) {
  PaxoNum32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(6))num.exponente;
  result.entero = (unsigned _BitInt(12))num.entero;
  result.fraccion = (unsigned _BitInt(13))((num.fraccion * 8192) / 64);
  return result;
}

PaxoNum64 num16tonum64(PaxoNum16 num) {
  PaxoNum64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(10))num.exponente;
  result.entero = (unsigned _BitInt(26))num.entero;
  result.fraccion = (unsigned _BitInt(27))((num.fraccion * 134217728LL) / 64);
  return result;
}

// 32 bits
PaxoNum8 num32tonum8(PaxoNum32 num) {
  PaxoNum8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(1))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  result.fraccion = (unsigned _BitInt(2))((num.fraccion * 4) / 8192);
  return result;
}

PaxoNum16 num32tonum16(PaxoNum32 num) {
  PaxoNum16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(4))num.exponente;
  result.entero = (unsigned _BitInt(5))num.entero;
  result.fraccion = (unsigned _BitInt(6))((num.fraccion * 64) / 8192);
  return result;
}

PaxoNum64 num32tonum64(PaxoNum64 num) {
  PaxoNum64 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(10))num.exponente;
  result.entero = (unsigned _BitInt(26))num.entero;
  result.fraccion = (unsigned _BitInt(27))((num.fraccion * 134217728LL) / 8192);
  return result;
}

// 64 bits
PaxoNum8 num64tonum8(PaxoNum64 num) {
  PaxoNum8 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(1))num.exponente;
  result.entero = (unsigned _BitInt(4))num.entero;
  result.fraccion = (unsigned _BitInt(2))((num.fraccion * 4) / 134217728LL);
  return result;
}

PaxoNum16 num64tonum16(PaxoNum64 num) {
  PaxoNum16 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(4))num.exponente;
  result.entero = (unsigned _BitInt(5))num.entero;
  result.fraccion = (unsigned _BitInt(6))((num.fraccion * 64) / 134217728LL);
  return result;
}

PaxoNum32 num64tonum32(PaxoNum64 num) {
  PaxoNum32 result;
  result.signo = num.signo;
  result.exponente = (unsigned _BitInt(6))num.exponente;
  result.entero = (unsigned _BitInt(12))num.entero;
  result.fraccion = (unsigned _BitInt(13))((num.fraccion * 8192) / 134217728LL);
  return result;
}

// trit a num
PaxoNum8 trittonum8(PaxoBool trit) {
  PaxoNum8 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(4))trit;
  result.fraccion = 0;
  return result;
}

PaxoNum16 trittonum16(PaxoBool trit) {
  PaxoNum16 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(5))trit;
  result.fraccion = 0;
  return result;
}

PaxoNum32 trittonum32(PaxoBool trit) {
  PaxoNum32 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(12))trit;
  result.fraccion = 0;
  return result;
}

PaxoNum64 trittonum64(PaxoBool trit) {
  PaxoNum64 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(26))trit;
  result.fraccion = 0;
  return result;
}

// num to trit
PaxoBool num8totrit(PaxoNum8 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

PaxoBool num16totrit(PaxoNum16 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

PaxoBool num32totrit(PaxoNum32 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

PaxoBool num64totrit(PaxoNum64 num) {
  PaxoBool result = (num.entero < 3) ? (PaxoBool)num.entero : 0;
  return result;
}

// bool a num
PaxoNum8 booltonum8(bool bit) {
  PaxoNum8 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(4))bit;
  result.fraccion = 0;
  return result;
}

PaxoNum16 booltonum16(bool bit) {
  PaxoNum16 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(5))bit;
  result.fraccion = 0;
  return result;
}

PaxoNum32 booltonum32(bool bit) {
  PaxoNum32 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(12))bit;
  result.fraccion = 0;
  return result;
}

PaxoNum64 booltonum64(bool bit) {
  PaxoNum64 result;
  result.signo = 0;
  result.exponente = 0;
  result.entero = (unsigned _BitInt(26))bit;
  result.fraccion = 0;
  return result;
}

// num a bool
bool num8tobool(PaxoNum8 num) { return (num.entero != 0 || num.fraccion != 0); }

bool num16tobool(PaxoNum16 num) {
  return (num.entero != 0 || num.fraccion != 0);
}

bool num32tobool(PaxoNum32 num) {
  return (num.entero != 0 || num.fraccion != 0);
}

bool num64tobool(PaxoNum64 num) {
  return (num.entero != 0 || num.fraccion != 0);
}

// ==========================================
// Conversiones entre Bool (Binario) y Trit (Ternario PaxoBool)
// ==========================================

// Bool binario (false/true) -> PaxoBool (0: false, 1: true)
PaxoBool booltotrit(bool bit) { return bit ? 1 : 0; }

// PaxoBool (0: false, 1: true, 2: unknown) -> Bool binario
// Regla: Solo el trit 1 (verdadero) evalúa a true; 0 (falso) y 2
// (indeterminado) evalúan a false.
bool trittobool(PaxoBool trit) { return (trit == 1); }

// De PaxoNum a Decimal Monetario
// 32 bits
_Decimal32 num8todecimal32(PaxoNum8 num) {
  double val = (double)num.entero + ((double)num.fraccion / 4.0);
  int exp_real = (int)num.exponente - 0; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal32)val;
}

_Decimal32 num16todecimal32(PaxoNum16 num) {
  double val = (double)num.entero + ((double)num.fraccion / 64.0);
  int exp_real = (int)num.exponente - 7; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal32)val;
}

_Decimal32 num32todecimal32(PaxoNum32 num) {
  double val = (double)num.entero + ((double)num.fraccion / 8192.0);
  int exp_real = (int)num.exponente - 31; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal32)val;
}

_Decimal32 num64todecimal32(PaxoNum64 num) {
  double val = (double)num.entero + ((double)num.fraccion / 134217728.0);
  int exp_real = (int)num.exponente - 511; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal32)val;
}

// 64 bits
_Decimal64 num8todecimal64(PaxoNum8 num) {
  double val = (double)num.entero + ((double)num.fraccion / 4.0);
  int exp_real = (int)num.exponente - 0; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal64)val;
}

_Decimal64 num16todecimal64(PaxoNum16 num) {
  double val = (double)num.entero + ((double)num.fraccion / 64.0);
  int exp_real = (int)num.exponente - 7; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal64)val;
}

_Decimal64 num32todecimal64(PaxoNum32 num) {
  double val = (double)num.entero + ((double)num.fraccion / 8192.0);
  int exp_real = (int)num.exponente - 31; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal64)val;
}

_Decimal64 num64todecimal64(PaxoNum64 num) {
  double val = (double)num.entero + ((double)num.fraccion / 134217728.0);
  int exp_real = (int)num.exponente - 511; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal64)val;
}

// 128 bits
_Decimal128 num8todecimal128(PaxoNum8 num) {
  double val = (double)num.entero + ((double)num.fraccion / 4.0);
  int exp_real = (int)num.exponente - 0; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal128)val;
}

_Decimal128 num16todecimal128(PaxoNum16 num) {
  double val = (double)num.entero + ((double)num.fraccion / 64.0);
  int exp_real = (int)num.exponente - 7; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal128)val;
}

_Decimal128 num32todecimal128(PaxoNum32 num) {
  double val = (double)num.entero + ((double)num.fraccion / 8192.0);
  int exp_real = (int)num.exponente - 31; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal128)val;
}

_Decimal128 num64todecimal128(PaxoNum64 num) {
  double val = (double)num.entero + ((double)num.fraccion / 134217728.0);
  int exp_real = (int)num.exponente - 511; // Sesgo = 0
  val *= pow(10.0, exp_real);
  if (num.signo)
    val = -val;
  return (_Decimal128)val;
}

// De Decimal Monetario a PaxoNum8
// 8 bits
PaxoNum8 decimal32tonum8(_Decimal32 dec) {
  PaxoNum8 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  // Normalizar si la parte entera supera la capacidad (4 bits = máx 15)
  while (val >= 16.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(1))(exp_real + 0); // Sesgo = 0
  result.entero = (unsigned _BitInt(4))(entero & 0x0F);
  result.fraccion = (unsigned _BitInt(2))((uint32_t)(fraccion * 4.0) & 0x03);

  return result;
}

PaxoNum8 decimal64tonum8(_Decimal64 dec) {
  PaxoNum8 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  // Normalizar si la parte entera supera la capacidad (4 bits = máx 15)
  while (val >= 16.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(1))(exp_real + 0); // Sesgo = 0
  result.entero = (unsigned _BitInt(4))(entero & 0x0F);
  result.fraccion = (unsigned _BitInt(2))((uint32_t)(fraccion * 4.0) & 0x03);

  return result;
}

PaxoNum8 decimal128tonum8(_Decimal128 dec) {
  PaxoNum8 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  // Normalizar si la parte entera supera la capacidad (4 bits = máx 15)
  while (val >= 16.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(1))(exp_real + 0); // Sesgo = 0
  result.entero = (unsigned _BitInt(4))(entero & 0x0F);
  result.fraccion = (unsigned _BitInt(2))((uint32_t)(fraccion * 4.0) & 0x03);

  return result;
}

// 16 bits
PaxoNum16 decimal32tonum16(_Decimal32 dec) {
  PaxoNum16 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 32.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(4))(exp_real + 7); // Sesgo = 0
  result.entero = (unsigned _BitInt(5))(entero & 0x1F);
  result.fraccion = (unsigned _BitInt(6))((uint32_t)(fraccion * 64.0) & 0x3f);

  return result;
}

PaxoNum16 decimal64onum16(_Decimal64 dec) {
  PaxoNum16 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 32.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(4))(exp_real + 7); // Sesgo = 0
  result.entero = (unsigned _BitInt(5))(entero & 0x1F);
  result.fraccion = (unsigned _BitInt(6))((uint32_t)(fraccion * 64.0) & 0x3f);

  return result;
}

PaxoNum16 decimal128tonum16(_Decimal128 dec) {
  PaxoNum16 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 32.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(4))(exp_real + 7); // Sesgo = 0
  result.entero = (unsigned _BitInt(5))(entero & 0x1F);
  result.fraccion = (unsigned _BitInt(6))((uint32_t)(fraccion * 64.0) & 0x3f);

  return result;
}

// 32 bits
PaxoNum32 decimal32tonum32(_Decimal32 dec) {
  PaxoNum32 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 4096.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(6))(exp_real + 31); // Sesgo = 0
  result.entero = (unsigned _BitInt(12))(entero & 0xfff);
  result.fraccion =
      (unsigned _BitInt(13))((uint32_t)(fraccion * 8192.0) & 0x1fff);

  return result;
}

PaxoNum32 decimal64tonum32(_Decimal64 dec) {
  PaxoNum32 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 4096.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(6))(exp_real + 31); // Sesgo = 0
  result.entero = (unsigned _BitInt(12))(entero & 0xfff);
  result.fraccion =
      (unsigned _BitInt(13))((uint32_t)(fraccion * 8192.0) & 0x1fff);

  return result;
}

PaxoNum32 decimal128tonum32(_Decimal128 dec) {
  PaxoNum32 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 4096.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint32_t entero = (uint32_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(6))(exp_real + 31); // Sesgo = 0
  result.entero = (unsigned _BitInt(12))(entero & 0xfff);
  result.fraccion =
      (unsigned _BitInt(13))((uint32_t)(fraccion * 8192.0) & 0x1fff);

  return result;
}

//64 bits
PaxoNum64 decimal32tonum32(_Decimal32 dec) {
  PaxoNum64 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 67108864.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint64_t entero = (uint64_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(10))(exp_real + 31); // Sesgo = 0
  result.entero = (unsigned _BitInt(26))(entero & 0x3ffffff);
  result.fraccion =
      (unsigned _BitInt(27))((uint64_t)(fraccion * 134217728.0) & 0x7ffffff);

  return result;
}

PaxoNum64 decimal64tonum32(_Decimal64 dec) {
  PaxoNum64 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 67108864.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint64_t entero = (uint64_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(10))(exp_real + 31); // Sesgo = 0
  result.entero = (unsigned _BitInt(26))(entero & 0x3ffffff);
  result.fraccion =
      (unsigned _BitInt(27))((uint64_t)(fraccion * 134217728.0) & 0x7ffffff);

  return result;
}

PaxoNum64 decimal128tonum32(_Decimal128 dec) {
  PaxoNum64 result;
  double val = (double)dec;

  result.signo = (val < 0) ? 1 : 0;
  if (val < 0)
    val = -val;

  int exp_real = 0;

  while (val >= 67108864.0 && exp_real < 1) {
    val /= 10.0;
    exp_real++;
  }
  // Normalizar si es muy pequeño
  while (val < 1.0 && val > 0.0 && exp_real > 0) {
    val *= 10.0;
    exp_real--;
  }

  uint64_t entero = (uint64_t)val;
  double fraccion = val - entero;

  result.exponente = (unsigned _BitInt(10))(exp_real + 31); // Sesgo = 0
  result.entero = (unsigned _BitInt(26))(entero & 0x3ffffff);
  result.fraccion =
      (unsigned _BitInt(27))((uint64_t)(fraccion * 134217728.0) & 0x7ffffff);

  return result;
}

// ==========================================
// Decimal <-> Booleano Binario / Ternario
// ==========================================

// Decimal a bool binario
bool decimaltobool(_Decimal64 dec) { return (dec != 0.0dd); }

// Bool binario a Decimal
_Decimal64 booltodecimal(bool bit) { return bit ? 1.0dd : 0.0dd; }

// Decimal a PaxoBool (trit)
PaxoBool decimaltotrit(_Decimal64 dec) {
  if (dec == 0.0dd)
    return 0; // false
	if (dec >= 2.0dd)
		return 2; 
  return 1;   // true
}

// PaxoBool (trit) a Decimal
_Decimal64 trittodecimal(PaxoBool trit) {
  if (trit == 1)
    return 1.0dd;
	else if (trit == 2)
		return 2.0dd
  return 0.0dd;
}