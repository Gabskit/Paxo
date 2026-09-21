#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <uchar.h>
#include <complex.h>
#include "dconfig.h"
#include "decContext.h"
#include "decimal64.h"

// Protección contra redefinición
#ifndef __STDC_UTF_16__
typedef uint16_t char16_t;
#endif

#ifndef __STDC_UTF_32__
typedef uint32_t char32_t;
#endif

#if !defined(__cpp_char8_t) && !defined(__STDC_VERSION_CHAR8_T__)
typedef unsigned char char8_t;
#endif

typedef uint8_t LEPBool;

typedef struct {
    uint8_t codify;
    uint32_t val;
} color;

// 1. Enums acotados a 8 bits
typedef enum type : uint8_t {
    INT, UINT,
    CHAR, TRIT, BOOL,
    FUNC,
    STRING, ARRAY, PACKAGE, COLOR,
    SCOM, COM,
    SFP, FP, DEC,
} LEPType;

typedef enum sizes : uint8_t {
    XXS = 1,
    XS  = 2,
    S   = 4,
    M   = 8,
    L   = 16,
} LEPSize;

// 2. Mapas de Memoria
typedef struct {
    LEPType type;      
    LEPSize bytesize;  
    uint32_t offset;   
} LEPVartag;

typedef struct {
    void* start_ptr;      
    size_t pivot;         
    
    LEPVartag* tags;      
    size_t var_count;     
} LEPEnv;

// 3. Estructuras Complejas (Ahora almacenan IDs, no estructuras pesadas)
typedef struct LEPPackageVar {
    uint32_t var_id;
    bool hidden;
} LEPPackageVar;

typedef struct LEPPackageSymbol {
    char* name;
    LEPPackageVar var;
} LEPPackageSymbol;

typedef struct LEPPackageInstance {
    char* name;
    LEPPackageSymbol* symbols;
    size_t count;
    size_t capacity;
    bool is_frozen;
} LEPPackageInstance;

typedef struct LEPArray {
    uint32_t *item_ids;
    size_t len;
    size_t capacity;
} LEPArray;

typedef struct {
    uint32_t ip;
    uint32_t param_count;
} LEPFunction;

// 4. Funciones de Arena
static inline uint32_t lep_push_var(LEPEnv* env, LEPType type, LEPSize size, void* raw_data, size_t bytes) {
    uint32_t var_id = env->var_count++;
    env->tags[var_id].type = type;
    env->tags[var_id].bytesize = size;
    env->tags[var_id].offset = env->pivot; 

    void* dest = (void*)((uintptr_t)env->start_ptr + env->pivot);
    memcpy(dest, raw_data, bytes); 
    
    env->pivot += bytes; 
    return var_id; 
}

static inline void* lep_get_var_data(LEPEnv* env, uint32_t var_id) {
    uint32_t offset = env->tags[var_id].offset;
    return (void*)((uintptr_t)env->start_ptr + offset);
}

// 5. La nueva Macro de Inserción Dinámica
// Crea un puntero temporal usando Literales Compuestos &(tipo){X} y lo empuja a la Arena
static inline uint32_t lep_push_i64(LEPEnv *env, int64_t x) { return lep_push_var(env, INT, M, &x, sizeof(x)); }
static inline uint32_t lep_push_u64(LEPEnv *env, uint64_t x) { return lep_push_var(env, UINT, M, &x, sizeof(x)); }
static inline uint32_t lep_push_bool(LEPEnv *env, bool x) { return lep_push_var(env, BOOL, XXS, &x, sizeof(x)); }
static inline uint32_t lep_push_fp16(LEPEnv *env, _Float16 x) { return lep_push_var(env, SFP, XS, &x, sizeof(x)); }
static inline uint32_t lep_push_fp64(LEPEnv *env, double x) { return lep_push_var(env, FP, M, &x, sizeof(x)); }
static inline uint32_t lep_push_dec64(LEPEnv *env, decimal64 x) { return lep_push_var(env, DEC, M, &x, sizeof(x)); }
static inline uint32_t lep_push_string_ptr(LEPEnv *env, const char *x) { return lep_push_var(env, STRING, M, &x, sizeof(x)); }
static inline uint32_t lep_push_char32(LEPEnv *env, char32_t x) { return lep_push_var(env, CHAR, S, &x, sizeof(x)); }

/* C11/C23 _Generic cannot distinguish typedef aliases such as char32_t/uint32_t.
 * The associations below therefore use only distinct standard types. */
#define LEP_PUSH(ENV, X) _Generic((X), \
    int: lep_push_i64, \
    long: lep_push_i64, \
    long long: lep_push_i64, \
    unsigned long: lep_push_u64, \
    unsigned long long: lep_push_u64, \
    bool: lep_push_bool, \
    _Float16: lep_push_fp16, \
    float: lep_push_fp64, \
    double: lep_push_fp64, \
    decimal64: lep_push_dec64, \
    char*: lep_push_string_ptr, \
    const char*: lep_push_string_ptr, \
    char32_t: lep_push_char32 \
)(ENV, (X))

#ifndef LEP_AS
#define LEP_AS(ENV, ID, TYPE) (*(TYPE*)lep_get_var_data((ENV), (ID)))
#endif

#ifndef LEP_TRANS_USE
#define LEP_TRANS_USE
static inline void lep_transmute_var(LEPEnv* env, uint32_t id, LEPType type, LEPSize size, const void* data, size_t bytes) {
    if (!env || id >= env->var_count) return;
    void *dst = lep_get_var_data(env, id);
    env->tags[id].type = type;
    env->tags[id].bytesize = size;
    if (dst && data && bytes) memcpy(dst, data, bytes);
}
#endif
