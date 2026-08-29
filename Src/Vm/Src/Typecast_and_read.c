#pragma once
#include "Calc.c"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char char8_t;
typedef uint32_t char32_t;

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
// CONVERSIONES NUM-MP ↔ PUNTO FIJO / DECIMAL
// ==========================================

// fxp → num64 respetando la escala: bc = |value| · 10^(-scale)
static inline Num64 fxp_to_num64(PaxoFxp f) {
  Num64 r = {0};
  if (f.value == 0)
    return (Num64){0, (uint64_t)BIAS64, 0, f.scale};
  uint64_t mag = (f.value < 0) ? (uint64_t)-(int64_t)f.value : (uint64_t)f.value;
  uint8_t p = f.scale;
  while (p > 0 && mag % 10 == 0) { // normaliza ceros finales
    mag /= 10;
    p--;
  }
  r.exp = (uint64_t)BIAS64;
  while (mag > bc_max64() && r.exp < 255) { // satura la mantisa
    mag = (mag + 5) / 10;
    if (p > 0)
      p--;
    else
      r.exp++;
  }
  r.signo = f.value < 0;
  r.bc = mag;
  r.p = p;
  return r;
}

// fxp → num16 reempaquetando el valor decimal más fino
static inline Num16 fxp_to_num16(PaxoFxp f) {
  if (f.value == 0)
    return (Num16){0, (uint16_t)BIAS16, 0, 0};
  uint64_t mag = (f.value < 0) ? (uint64_t)-(int64_t)f.value : (uint64_t)f.value;
  int16_t e = -(int16_t)f.scale;
  while (mag % 10 == 0 && e < 32760) { // décadas exactas fuera del camino
    mag /= 10;
    e++;
  }
  while (mag > ((uint64_t)1 << 50)) { // cabe en el reempaquetado
    mag = (mag + 5) / 10;
    e++;
  }
  return num16_repack(f.value < 0 ? 1u : 0u, (int64_t)(mag << 10), e,
                      MP16_MEDIO);
}

// num64 → fxp a la escala pedida: redondea al entero más cercano; si la
// magnitud no cabe en 13 bits, fxp_pack baja la escala (reempaqueta) hasta
// caber y satura en los bordes del formato.
static inline PaxoFxp num64_to_fxp(Num64 n, uint8_t scale_target) {
  if (n.bc == 0)
    return fxp_pack(0, scale_target);
  int64_t expo = (int64_t)n.exp - (int64_t)BIAS64 - (int64_t)n.p +
                 (int64_t)scale_target;
  long double rl = roundl((long double)n.bc * powl(10.0L, (long double)expo));
  if (n.signo)
    rl = -rl;
  if (!isfinite(rl))
    return fxp_pack(n.signo ? -FXP_MAG_MAX : FXP_MAG_MAX, scale_target);
  return fxp_pack((int64_t)rl, scale_target);
}

// pdec (BCD) → num64 respetando la escala: bc = magnitud · 10^(-scale),
// normalizando los ceros finales (como num64 → pdec a la inversa).
static inline Num64 pdec_to_num64(PaxoPdec d) {
  Num64 r = {0};
  uint64_t mag = (uint64_t)pdec_magnitude(d);
  if (mag == 0)
    return (Num64){0, (uint64_t)BIAS64, 0, d.scale};
  uint8_t p = d.scale;
  while (p > 0 && mag % 10 == 0) { // normaliza ceros finales
    mag /= 10;
    p--;
  }
  r.exp = (uint64_t)BIAS64;
  while (mag > bc_max64()) { // satura la mantisa
    mag = (mag + 5) / 10;
    if (p > 0)
      p--;
    else
      r.exp++;
  }
  r.signo = d.signo;
  r.bc = mag;
  r.p = p;
  return r;
}

// num64 → pdec (BCD) a la escala pedida: redondea al entero más cercano de
// magnitud (hasta 13 dígitos); saturado en los bordes del formato decimal.
static inline PaxoPdec num64_to_pdec(Num64 n, uint8_t scale_target) {
  if (n.bc == 0)
    return pdec_from_int64(0, scale_target);
  int64_t expo = (int64_t)n.exp - (int64_t)BIAS64 - (int64_t)n.p +
                 (int64_t)scale_target;
  long double rl = roundl((long double)n.bc * powl(10.0L, (long double)expo));
  if (n.signo)
    rl = -rl;
  if (!isfinite(rl))
    return pdec_from_int64(n.signo ? -PAXO_PDEC_MAX_MAG : PAXO_PDEC_MAX_MAG,
                           scale_target);
  return pdec_from_int64((int64_t)rl, scale_target);
}

// ==========================================
// COMPLEJOS: PUENTES DE COMPONENTE A MP16 / MP64
// ==========================================

// Componente numérico (num16/num64/int/pdec) → MP64
static inline Num64 complex_comp64(PaxoVar v) {
  switch (var_type(v)) {
  case NUM16:
    return num16tonum64(var_num16_get(v));
  case NUM64:
    return var_num64_get(v);
  case INT_FP:
    return fxp_to_num64(var_fxp_get(v));
  case PKDEC:
    return pdec_to_num64(var_pkdec_get(v));
  default:
    return (Num64){0, (uint64_t)BIAS64, 0, 0};
  }
}

// Componente numérico → MP16 (aproxima; para explícito cast a sni)
static inline Num16 complex_comp16(PaxoVar v) {
  return num64tonum16(complex_comp64(v));
}

// ¿Es cero el valor de un componente?
static inline bool complex_comp_zero(PaxoVar v) {
  switch (var_type(v)) {
  case NUM16:
    return var_num16_get(v).bc == 0;
  case NUM64:
    return var_num64_get(v).bc == 0;
  case INT_FP:
    return var_fxp_get(v).value == 0;
  case PKDEC:
    return pdec_is_zero(var_pkdec_get(v));
  default:
    return false;
  }
}

static inline bool var_complex_is_zero(PaxoComplex c) {
  return complex_comp_zero(c.re) && complex_comp_zero(c.im);
}

// ==========================================
// PUENTE A REALES (long double) PARA NATIVOS DE MATEMÁTICA
// ==========================================

static inline long double num64_to_ld(Num64 n) {
  return (n.signo ? -1.0L : 1.0L) * (long double)n.bc *
         powl(10.0L, (long double)((int)n.exp - (int)BIAS64 - (int)n.p));
}

static inline long double num16_to_ld(Num16 n) {
  return num64_to_ld(num16tonum64(n));
}

// Valor real de cualquier operando numérico (MP16/MP64/int/pdec).
static inline long double var_to_ld(PaxoVar v) {
  switch (var_type(v)) {
  case NUM16:
    return num16_to_ld(var_num16_get(v));
  case NUM64:
    return num64_to_ld(var_num64_get(v));
  case INT_FP:
    return (long double)var_fxp_get(v).value *
           powl(10.0L, -(long double)var_fxp_get(v).scale);
  case PKDEC: {
    PaxoPdec d = var_pkdec_get(v);
    long double mag = (long double)pdec_magnitude(d);
    return (d.signo ? -mag : mag) *
           powl(10.0L, -(long double)d.scale);
  }
  default:
    return 0.0L;
  }
}

// Empaca un real en Num64 con hasta ~15 dígitos significativos, normaliza
// los ceros finales y satura/baja a cero en los bordes del formato.
static inline Num64 num64_from_ld(long double v) {
  Num64 r = {0};
  if (v == 0.0L || !isfinite(v))
    return (Num64){0, (uint64_t)BIAS64, 0, 0};
  r.signo = v < 0;
  long double m = fabsl(v);
  int e = (int)floorl(log10l(m));
  uint64_t bc = (uint64_t)roundl(m * powl(10.0L, 14 - e));
  int t = e - 14;
  while (bc > bc_max64()) { // cabe en la mantisa
    bc = (bc + 5) / 10;
    t++;
  }
  while (bc % 10 == 0 && bc > 0) { // ceros finales fuera del camino
    bc /= 10;
    if (t < 0)
      t++;
    else
      r.exp++;
  }
  r.p = (t < 0 && -t <= 25) ? (uint64_t)(-t) : 0;
  r.exp += (uint64_t)(BIAS64 + (t < 0 ? 0 : t));
  if (r.exp > 255) {
    r.exp = 255;
    r.bc = bc_max64();
  } else if ((int64_t)r.exp < 0) {
    return (Num64){0, (uint64_t)BIAS64, 0, 0};
  }
  r.bc = bc;
  return r;
}

// Real redondeado a la escala pedida como PaxoFxp (satura en los bordes).
static inline PaxoFxp fxp_from_real(long double v, uint8_t scale) {
  long double r = roundl(v * powl(10.0L, (long double)scale));
  if (r > (long double)FXP_MAG_MAX)
    r = FXP_MAG_MAX;
  if (r < -(long double)FXP_MAG_MAX)
    r = -FXP_MAG_MAX;
  return fxp_pack((int64_t)r, scale);
}

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
    unsigned __int128 val = num.bc;
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

// Formatea un valor escalado de punto fijo (int):
//   value · 10^(-scale), manteniendo la escala declarada.
static inline const char8_t *readint(PaxoFxp f) {
  static char8_t buffer[176];
  int32_t v = f.value;
  int32_t s = f.scale > FXP_SCALE_MAX ? FXP_SCALE_MAX : (int32_t)f.scale;
  if (s == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%d", v);
    return buffer;
  }
  int32_t div = 1;
  for (int32_t i = 0; i < s; i++)
    div *= 10;
  int32_t ip = v / div;
  int32_t fp = (v < 0 ? -v : v) % div;
  snprintf((char *)buffer, sizeof(buffer), "%d.%0*d", ip, (int)s, fp);
  return buffer;
}

// Formatea un decimal empaquetado BCD: magnitud · 10^(-scale), manteniendo
// la escala declarada (los dígitos BCD garantizan formato decimal exacto).
static inline const char8_t *readpdec(PaxoPdec d) {
  static char8_t buffer[176];
  int64_t mag = pdec_magnitude(d);
  int32_t s = d.scale > FXP_SCALE_MAX ? FXP_SCALE_MAX : (int32_t)d.scale;
  if (s == 0) {
    snprintf((char *)buffer, sizeof(buffer), "%s%lld",
             d.signo && mag ? "-" : "", (long long)mag);
    return buffer;
  }
  int64_t div = 1;
  for (int32_t i = 0; i < s; i++)
    div *= 10;
  int64_t ip = mag / div;
  uint64_t fp = (uint64_t)(mag % div);
  snprintf((char *)buffer, sizeof(buffer), "%s%lld.%0*llu",
           d.signo && mag ? "-" : "", (long long)ip, (int)s,
           (unsigned long long)fp);
  return buffer;
}

// Formatea un componente de número complejo (num16/num64/int/pdec) copiando
// a un buffer propio (los lectores usan buffers estáticos compartidos).
static inline void complex_comp_str(PaxoVar v, char8_t *out, size_t cap) {
  const char8_t *src = u8"0";
  switch (var_type(v)) {
  case NUM16:
    src = readnum16(var_num16_get(v), 1);
    break;
  case NUM64:
    src = readnum64(var_num64_get(v), 1);
    break;
  case INT_FP:
    src = readint(var_fxp_get(v));
    break;
  case PKDEC:
    src = readpdec(var_pkdec_get(v));
    break;
  default:
    break;
  }
  size_t n = 0;
  for (; src[n] && n < cap - 1; n++)
    out[n] = src[n];
  out[n] = '\0';
}

// Formatea un complejo como "re±imi" (p.ej. "3+4i", "2.5-0.25i").
static inline const char8_t *readcomplex(PaxoComplex c) {
  static char8_t buffer[320];
  char8_t re_s[176];
  char8_t im_s[176];
  complex_comp_str(c.re, re_s, sizeof(re_s));
  complex_comp_str(c.im, im_s, sizeof(im_s));
  bool im_neg = im_s[0] == '-';
  if (im_neg) {
    size_t n = 0;
    while (im_s[n + 1]) {
      n++;
      im_s[n - 1] = im_s[n];
    }
    im_s[n - 1] = '\0';
  }
  const char *re = re_s[0] ? (const char *)re_s : "0";
  const char *im = im_s[0] ? (const char *)im_s : "0";
  if (im[0] == '0' && im[1] != '.') /* magnitud cero: solo "0i" */ {
    snprintf((char *)buffer, sizeof(buffer), "%s+%si", re, "0");
  } else {
    snprintf((char *)buffer, sizeof(buffer), "%s%s%si", re, im_neg ? "-" : "+",
             im);
  }
  return buffer;
}