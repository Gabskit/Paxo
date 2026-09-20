#pragma once
#include "Calc.c"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char char8_t;
typedef uint32_t char32_t;

static inline bool lep_truthy(LEPVar v) {
    switch (v.type) {
        case BOOL: return v.payload.boolean;
        case TRIT: return v.payload.trit != 0;
        case INT: return v.payload.integer != 0;
        case UINT: return v.payload.uinteger != 0;
        case CHAR: return v.payload.chara != 0;
        case SFP: return v.payload.fp16 != 0;
        case FP: return v.payload.fp64 != 0;
        case DEC: return v.payload.dec64 != 0;
        case FRAC: return v.payload.frac != 0;
        case ACCUM: return v.payload.accum != 0;
        case STRING: return v.payload.utf8 && v.payload.utf8[0] != '\0';
        case POINT: case FUNC: case ARRAY: case PACKAGE: return v.payload.ptr != NULL;
        default: return false;
    }
}

static inline LEPBool booltotrit(bool bit) { return bit ? 1 : 0; }
static inline bool trittobool(LEPBool trit) { return trit == 1; }
static inline int64_t booltoint(bool bit) { return bit ? 1 : 0; }
static inline LEPBool inttotrit(int64_t n) { return n <= 0 ? 0 : n >= 2 ? 2 : 1; }
static inline char32_t inttochar(int64_t n) { return (char32_t)n; }
static inline int64_t tritoint(LEPBool t) { return (int64_t)t; }
static inline char8_t trittochar(LEPBool trit) { return trit == 2 ? '2' : trit == 1 ? '1' : '0'; }
static inline LEPBool chartotrit(char8_t c) { return c == '2' ? 2 : c == '1' ? 1 : 0; }
static inline int64_t chartoint(char32_t c) { return (int64_t)c; }

static inline const char8_t *readbool(bool bit) {
    return bit ? (const char8_t *)"true" : (const char8_t *)"false";
}

static inline const char8_t *readtrit(LEPBool trit) {
    switch (trit) { case 1: return (const char8_t *)"1"; case 2: return (const char8_t *)"2"; default: return (const char8_t *)"0"; }
}

static inline const char8_t *readchar32(char32_t c) {
    static char8_t buffer[8];
    if (c < 0x80) { buffer[0]=(char8_t)c; buffer[1]='\0'; }
    else if (c < 0x800) { buffer[0]=(char8_t)(0xC0|(c>>6)); buffer[1]=(char8_t)(0x80|(c&0x3F)); buffer[2]='\0'; }
    else if (c < 0x10000) { buffer[0]=(char8_t)(0xE0|(c>>12)); buffer[1]=(char8_t)(0x80|((c>>6)&0x3F)); buffer[2]=(char8_t)(0x80|(c&0x3F)); buffer[3]='\0'; }
    else { buffer[0]=(char8_t)(0xF0|(c>>18)); buffer[1]=(char8_t)(0x80|((c>>12)&0x3F)); buffer[2]=(char8_t)(0x80|((c>>6)&0x3F)); buffer[3]=(char8_t)(0x80|(c&0x3F)); buffer[4]='\0'; }
    return buffer;
}

static inline const char8_t *readint(int64_t n) { static char8_t b[64]; snprintf((char*)b,sizeof(b),"%lld",(long long)n); return b; }
static inline const char8_t *readuint(uint64_t n) { static char8_t b[64]; snprintf((char*)b,sizeof(b),"%llu",(unsigned long long)n); return b; }
static inline const char8_t *readfp(double n) { static char8_t b[128]; snprintf((char*)b,sizeof(b),"%.18g",n); return b; }
static inline const char8_t *readnum(LEPVar v) {
    switch (v.type) {
        case INT: return readint(var_int_get(v));
        case UINT: return readuint(var_uint_get(v));
        case SFP: return readfp((double)var_fp16_get(v));
        case FP: return readfp(var_fp64_get(v));
        case DEC: return readfp((double)var_dec_get(v));
        default: return (const char8_t *)"0";
    }
}

static inline const char8_t *readvar(LEPVar v) {
    switch (v.type) {
        case BOOL: return readbool(var_bool_get(v));
        case TRIT: return readtrit(var_trit_get(v));
        case CHAR: return readchar32(var_char_get(v));
        case STRING: return var_string_get(v);
        case INT: case UINT: case SFP: case FP: case DEC: case FRAC: case ACCUM: return readnum(v);
        default: return (const char8_t *)"<value>";
    }
}
