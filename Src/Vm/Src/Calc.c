#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * TIPOS BASICOS
 * ============================================================ */

typedef unsigned char char8_t;
typedef uint32_t char32_t;
typedef uint8_t LEPBool;


/* ============================================================
 * TAGS DEL TAGGED UNION
 * ============================================================ */

typedef enum type : uint8_t {
    INT,
    UINT,

    CHAR,
    TRIT,
    BOOL,

    POINT,
    FUNC,

    STRING,
    ARRAY,
    PACKAGE,
    COLOR,

    SCOM,
    COM,

    SFP,
    FP,
    DEC,

    FRAC,
    ACCUM
} LEPType;


/* ============================================================
 * REFERENCIAS
 *
 * El tag ya identifica que contiene ptr.
 *
 * POINT   -> objeto/puntero LEP
 * FUNC    -> descriptor de funcion
 * ARRAY   -> LEPArray
 * PACKAGE -> LEPPackageField
 * ============================================================ */

typedef struct {
    void *ptr;
} LEPPoint;

typedef struct {
    uint32_t ip;
    uint32_t param_count;
} LEPFunction;


/* ============================================================
 * VALOR PRINCIPAL
 * ============================================================ */

typedef struct {
    LEPType type;

    union {

        /* ----------------------------------------------------
         * ENTEROS
         * ---------------------------------------------------- */

        int64_t integer;
        uint64_t uinteger;


        /* ----------------------------------------------------
         * CARACTERES / BOOLEANOS
         * ---------------------------------------------------- */

        char32_t chara;
        LEPBool trit;
        bool boolean;


        /* ----------------------------------------------------
         * FLOAT / DECIMAL
         * ---------------------------------------------------- */

        _Float16 fp16;
        double fp64;
        _Decimal64 dec64;


        /* ----------------------------------------------------
         * COMPLEJOS
         * ---------------------------------------------------- */

        _Float16 _Complex com16;
        double _Complex com64;


        /* ----------------------------------------------------
         * PUNTO FIJO
         * ---------------------------------------------------- */

        _Sat long long _Fract frac;
        _Sat long _Accum accum;


        /* ----------------------------------------------------
         * COLOR
         * ---------------------------------------------------- */

        struct {
            uint8_t codify;
            uint32_t val;
        } color;


        /* ----------------------------------------------------
         * STRING
         * ---------------------------------------------------- */

        const char8_t *utf8;


        /* ----------------------------------------------------
         * REFERENCIAS
         * ---------------------------------------------------- */

        LEPPoint point;
        LEPFunction function;

        void *ptr;

    } payload;

} LEPVar;


/* ============================================================
 * PACKAGE
 * ============================================================ */

typedef struct LEPPackageField {

    char *key;

    struct LEPPackageField *next;

    LEPVar value;

    bool hidden;

} LEPPackageField;


/* ============================================================
 * ARRAY
 * ============================================================ */

typedef struct {

    LEPVar *items;

    size_t len;

    size_t capacity;

} LEPArray;


/* ============================================================
 * OBJECT
 *
 * Opcionalmente puede usarse como tabla de objetos administrados.
 * ============================================================ */

typedef struct LEPObject {

    void *ptr;

    LEPType type;

} LEPObject;


/* ============================================================
 * CONSTRUCTORES
 * ============================================================ */

static inline LEPVar var_int(int64_t value)
{
    return (LEPVar){
        .type = INT,
        .payload.integer = value
    };
}


static inline LEPVar var_uint(uint64_t value)
{
    return (LEPVar){
        .type = UINT,
        .payload.uinteger = value
    };
}


static inline LEPVar var_char(char32_t value)
{
    return (LEPVar){
        .type = CHAR,
        .payload.chara = value
    };
}


static inline LEPVar var_bool(bool value)
{
    return (LEPVar){
        .type = BOOL,
        .payload.boolean = value
    };
}


static inline LEPVar var_trit(LEPBool value)
{
    return (LEPVar){
        .type = TRIT,
        .payload.trit = value
    };
}


static inline LEPVar var_fp16(_Float16 value)
{
    return (LEPVar){
        .type = SFP,
        .payload.fp16 = value
    };
}


static inline LEPVar var_fp64(double value)
{
    return (LEPVar){
        .type = FP,
        .payload.fp64 = value
    };
}


static inline LEPVar var_dec(_Decimal64 value)
{
    return (LEPVar){
        .type = DEC,
        .payload.dec64 = value
    };
}


static inline LEPVar var_com16(_Float16 _Complex value)
{
    return (LEPVar){
        .type = SCOM,
        .payload.com16 = value
    };
}


static inline LEPVar var_com64(double _Complex value)
{
    return (LEPVar){
        .type = COM,
        .payload.com64 = value
    };
}


static inline LEPVar var_frac(_Sat long long _Fract value)
{
    return (LEPVar){
        .type = FRAC,
        .payload.frac = value
    };
}


static inline LEPVar var_accum(_Sat long _Accum value)
{
    return (LEPVar){
        .type = ACCUM,
        .payload.accum = value
    };
}


static inline LEPVar var_color(uint8_t codify, uint32_t value)
{
    return (LEPVar){
        .type = COLOR,
        .payload.color = {
            .codify = codify,
            .val = value
        }
    };
}


static inline LEPVar var_string(const char8_t *value)
{
    return (LEPVar){
        .type = STRING,
        .payload.utf8 = value
    };
}


static inline LEPVar var_point(void *ptr)
{
    return (LEPVar){
        .type = POINT,
        .payload.point = {
            .ptr = ptr
        }
    };
}


static inline LEPVar var_func(uint32_t ip, uint32_t param_count)
{
    return (LEPVar){
        .type = FUNC,
        .payload.function = {
            .ip = ip,
            .param_count = param_count
        }
    };
}


static inline LEPVar var_array(LEPArray *array)
{
    return (LEPVar){
        .type = ARRAY,
        .payload.ptr = array
    };
}


static inline LEPVar var_package(LEPPackageField *package)
{
    return (LEPVar){
        .type = PACKAGE,
        .payload.ptr = package
    };
}


/* ============================================================
 * ACCESORES
 * ============================================================ */

static inline LEPType var_type(LEPVar v)
{
    return v.type;
}


static inline int64_t var_int_get(LEPVar v)
{
    return v.payload.integer;
}


static inline uint64_t var_uint_get(LEPVar v)
{
    return v.payload.uinteger;
}


static inline char32_t var_char_get(LEPVar v)
{
    return v.payload.chara;
}


static inline bool var_bool_get(LEPVar v)
{
    return v.payload.boolean;
}


static inline LEPBool var_trit_get(LEPVar v)
{
    return v.payload.trit;
}


static inline _Float16 var_fp16_get(LEPVar v)
{
    return v.payload.fp16;
}


static inline double var_fp64_get(LEPVar v)
{
    return v.payload.fp64;
}


static inline _Decimal64 var_dec_get(LEPVar v)
{
    return v.payload.dec64;
}


static inline _Float16 _Complex var_com16_get(LEPVar v)
{
    return v.payload.com16;
}


static inline double _Complex var_com64_get(LEPVar v)
{
    return v.payload.com64;
}


static inline _Sat long long _Fract var_frac_get(LEPVar v)
{
    return v.payload.frac;
}


static inline _Sat long _Accum var_accum_get(LEPVar v)
{
    return v.payload.accum;
}


static inline uint8_t var_color_codify_get(LEPVar v)
{
    return v.payload.color.codify;
}


static inline uint32_t var_color_get(LEPVar v)
{
    return v.payload.color.val;
}


static inline const char8_t *var_string_get(LEPVar v)
{
    return v.payload.utf8;
}


static inline void *var_point_get(LEPVar v)
{
    return v.payload.point.ptr;
}


static inline uint32_t var_func_ip_get(LEPVar v)
{
    return v.payload.function.ip;
}


static inline uint32_t var_func_params_get(LEPVar v)
{
    return v.payload.function.param_count;
}


static inline LEPArray *var_array_get(LEPVar v)
{
    return (LEPArray *)v.payload.ptr;
}


static inline LEPPackageField *var_package_get(LEPVar v)
{
    return (LEPPackageField *)v.payload.ptr;
}


/* ============================================================
 * PREDICADOS
 * ============================================================ */

static inline bool var_is_int(LEPVar v)
{
    return v.type == INT;
}


static inline bool var_is_uint(LEPVar v)
{
    return v.type == UINT;
}


static inline bool var_is_number(LEPVar v)
{
    return v.type == INT ||
           v.type == UINT ||
           v.type == SFP ||
           v.type == FP ||
           v.type == DEC ||
           v.type == FRAC ||
           v.type == ACCUM;
}


static inline bool var_is_complex(LEPVar v)
{
    return v.type == SCOM ||
           v.type == COM;
}


static inline bool var_is_reference(LEPVar v)
{
    return v.type == POINT ||
           v.type == FUNC ||
           v.type == STRING ||
           v.type == ARRAY ||
           v.type == PACKAGE;
}


static inline bool var_is_bool(LEPVar v)
{
    return v.type == BOOL;
}


static inline bool var_is_trit(LEPVar v)
{
    return v.type == TRIT;
}



/* ============================================================
 * UTILIDADES DEL NUEVO TAGGED UNION
 * ============================================================ */

#define LEP_ZERO ((LEPVar){ .type = INT, .payload.integer = 0 })

static inline bool var_is_float(LEPVar v) {
    return v.type == SFP || v.type == FP || v.type == DEC;
}

static inline bool var_is_integral(LEPVar v) {
    return v.type == INT || v.type == UINT || v.type == CHAR;
}

static inline long double var_to_ld(LEPVar v) {
    switch (v.type) {
        case INT: return (long double)v.payload.integer;
        case UINT: return (long double)v.payload.uinteger;
        case CHAR: return (long double)v.payload.chara;
        case SFP: return (long double)v.payload.fp16;
        case FP: return (long double)v.payload.fp64;
        case DEC: return (long double)v.payload.dec64;
        case FRAC: return (long double)v.payload.frac;
        case ACCUM: return (long double)v.payload.accum;
        case BOOL: return v.payload.boolean ? 1.0L : 0.0L;
        case TRIT: return (long double)v.payload.trit;
        default: return 0.0L;
    }
}

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
        case POINT: return v.payload.point.ptr != NULL;
        case FUNC: return true;
        case ARRAY: return v.payload.ptr != NULL;
        case PACKAGE: return v.payload.ptr != NULL;
        default: return false;
    }
}

static inline int lep_cmp(LEPVar a, LEPVar b) {
    long double x = var_to_ld(a), y = var_to_ld(b);
    return x < y ? -1 : (x > y ? 1 : 0);
}

/* Compatibilidad de lectura para codigo nativo antiguo. Estos nombres no
 * representan tags antiguos: NUM se traduce a FP y COMPLEX a COM. */
typedef struct { int signo; int exp; uint64_t mantisa; } Number;
#define NUM FP
#define COMPLEX COM
#define BIASNUM 0
static inline Number var_num_get(LEPVar v) { Number n={0,0,0}; long double x=var_to_ld(v); if(x<0){n.signo=1;x=-x;} n.mantisa=(uint64_t)x; return n; }
static inline LEPVar var_num(Number n) { long double x=(long double)n.mantisa; if(n.signo)x=-x; return var_fp64((double)x); }
static inline bool numtobool(Number n){return n.mantisa!=0;}
static inline Number booltonum(bool b){return (Number){0,0,b?1:0};}
static inline bool trittobool(LEPBool t){return t!=0;}
static inline Number trittonum(LEPBool t){return (Number){0,0,t};}
static inline LEPBool numtotrit(Number n){return (LEPBool)(n.mantisa ? 2 : 0);}
static inline LEPBool booltotrit(bool b){return b?2:0;}
static inline char32_t numtochar(Number n){return (char32_t)n.mantisa;}
static inline int cmp_num(Number a, Number b){return a.mantisa<b.mantisa?-1:(a.mantisa>b.mantisa?1:0);}
static inline Number add_num(Number a,Number b){return (Number){0,0,a.mantisa+b.mantisa};}
static inline Number sub_num(Number a,Number b){return (Number){0,0,a.mantisa-b.mantisa};}
static inline Number mul_num(Number a,Number b){return (Number){0,0,a.mantisa*b.mantisa};}
static inline Number div_num(Number a,Number b){return b.mantisa?(Number){0,0,a.mantisa/b.mantisa}:(Number){0,0,0};}

/* Legacy reference predicates now resolve directly through the tag. */
enum { REF_SUB_NONE=0, REF_SUB_STRING=1, REF_SUB_ARRAY=2, REF_SUB_PKG=3, REF_SUB_FUNC=4 };
static inline int var_ref_sub_get(LEPVar v){
    switch(v.type){case STRING:return REF_SUB_STRING;case ARRAY:return REF_SUB_ARRAY;case PACKAGE:return REF_SUB_PKG;case FUNC:return REF_SUB_FUNC;default:return REF_SUB_NONE;}
}
static inline uint32_t var_func_id(LEPVar v){ return v.payload.function.ip; }
static inline void *var_func_get(LEPVar v){ return (void *)(uintptr_t)v.payload.function.ip; }