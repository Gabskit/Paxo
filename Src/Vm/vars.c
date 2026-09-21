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
uint32_t lep_push_var(LEPEnv* env, LEPType type, LEPSize size, void* raw_data, size_t bytes) {
    uint32_t var_id = env->var_count++;
    env->tags[var_id].type = type;
    env->tags[var_id].bytesize = size;
    env->tags[var_id].offset = env->pivot; 

    void* dest = (void*)((uintptr_t)env->start_ptr + env->pivot);
    memcpy(dest, raw_data, bytes); 
    
    env->pivot += bytes; 
    return var_id; 
}

void* lep_get_var_data(LEPEnv* env, uint32_t var_id) {
    uint32_t offset = env->tags[var_id].offset;
    return (void*)((uintptr_t)env->start_ptr + offset);
}

// 5. La nueva Macro de Inserción Dinámica
// Crea un puntero temporal usando Literales Compuestos &(tipo){X} y lo empuja a la Arena
#define LEP_PUSH(ENV, X) _Generic((X), \
    /* Enteros */ \
    int:                   lep_push_var(ENV, INT,  M, &(int64_t){(X)}, sizeof(int64_t)), \
    long:                  lep_push_var(ENV, INT,  M, &(int64_t){(X)}, sizeof(int64_t)), \
    long long:             lep_push_var(ENV, INT,  M, &(int64_t){(X)}, sizeof(int64_t)), \
    unsigned int:          lep_push_var(ENV, UINT, M, &(uint64_t){(X)}, sizeof(uint64_t)), \
    unsigned long:         lep_push_var(ENV, UINT, M, &(uint64_t){(X)}, sizeof(uint64_t)), \
    unsigned long long:    lep_push_var(ENV, UINT, M, &(uint64_t){(X)}, sizeof(uint64_t)), \
    \
    /* Caracteres, Bools y Trits */ \
    char32_t:              lep_push_var(ENV, CHAR, S,   &(char32_t){(X)}, sizeof(char32_t)), \
    LEPBool:               lep_push_var(ENV, TRIT, XXS, &(LEPBool){(X)}, sizeof(LEPBool)), \
    bool:                  lep_push_var(ENV, BOOL, XXS, &(bool){(X)}, sizeof(bool)), \
    \
    /* Flotantes y Decimales */ \
    _Float16:              lep_push_var(ENV, SFP, XS, &(_Float16){(X)}, sizeof(_Float16)), \
    float:                 lep_push_var(ENV, FP,  M,  &(double){(X)}, sizeof(double)), \
    double:                lep_push_var(ENV, FP,  M,  &(double){(X)}, sizeof(double)), \
    decimal64:             lep_push_var(ENV, DEC, M,  &(decimal64){(X)}, sizeof(decimal64)), \
    \
    /* Complejos */ \
    _Float16 _Complex:     lep_push_var(ENV, SCOM, S, &(_Float16 _Complex){(X)}, sizeof(_Float16 _Complex)), \
    double _Complex:       lep_push_var(ENV, COM,  L, &(double _Complex){(X)}, sizeof(double _Complex)), \
    \
    /* Cadenas (Guardamos el puntero a la cadena original) */ \
    char*:                 lep_push_var(ENV, STRING, M, &(char*){(X)}, sizeof(char*)), \
    const char*:           lep_push_var(ENV, STRING, M, &(const char*){(X)}, sizeof(const char*)), \
    \
    /* Estructuras Complejas */ \
    color:                 lep_push_var(ENV, COLOR, M, &(color){(X)}, sizeof(color)), \
    LEPFunction:           lep_push_var(ENV, FUNC,  M, &(LEPFunction){(X)}, sizeof(LEPFunction)) \
)
