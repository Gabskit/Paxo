#pragma once
#include "Calc.c"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char char8_t;
typedef uint32_t char32_t;

static inline LEPBool booltotrit(bool bit) { return bit ? 1 : 0; }
static inline bool trittobool(LEPBool trit) { return (trit == 1); }

static inline Number booltonum(bool bit) {
  return bit ? (Number){0, BIASNUM, 1} : (LEPVar){0};
}

static inline bool numtobool(Number n) {
  return n.mantisa != 0;
}
static inline LEPBool numtotrit(Number n) {
  return n.mantisa > 2 ? 2 : n.mantisa != 0 ? 1 : 0;
}

static inline Number trittonum(LEPBool trit) {
  return trit == 2 ? (Number){0, BIASNUM, 2} : (Number){0, BIASNUM, trit};
}

static inline char8_t trittochar(LEPBool trit) {
  return trit == 2 ? '2' : trit == 1 ? '1' : '0';
}

static inline LEPBool chartotrit(char8_t c) {
  return c == '2' ? 2 : c == '1' ? 1 : 0;
}

static inline const char8_t *readbool(bool bit) {
  return bit ? (const char8_t *)"true" : (const char8_t *)"false";
}

static inline const char8_t *readtrit(LEPBool trit) {
  switch (trit) {
  case 1:
    return (const char8_t *)"1";
  case 2:
    return (const char8_t *)"2";
  default:
    return (const char8_t *)"0";
  }
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

static inline void format_number(Number n, char8_t *buffer, size_t size) {
  long double value = (long double)n.mantisa *
                      powl(10.0L, (long double)((int)n.exp - BIASNUM));
  if (n.signo)
    value = -value;
  snprintf((char *)buffer, size, "%.18Lg", value);
}

static inline const char8_t *readnum(Number n) {
  static char8_t buffer[320];
  format_number(n, buffer, sizeof(buffer));
  return buffer;
}

// Formatea un complejo como "re±imi" (p.ej. "3+4i", "2.5-0.25i").
static inline const char8_t *readcomplex(Complex c) {
  static char8_t buffer[320];
  Number real = {
      .signo = c.real.signo,
      .exp = c.real.exp,
      .mantisa = c.real.mantisa,
  };
  Number imaginary = {
      .signo = c.imaginary.signo,
      .exp = c.imaginary.exp,
      .mantisa = c.imaginary.mantisa,
  };
  char8_t re_buffer[160];
  char8_t im_buffer[160];
  format_number(real, re_buffer, sizeof(re_buffer));
  format_number(imaginary, im_buffer, sizeof(im_buffer));
  const char8_t *re_s = re_buffer;
  const char8_t *im_s = im_buffer;
  bool im_neg = im_s[0] == '-';
  if (im_neg) {
    im_s++;
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