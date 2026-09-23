// lep_ffi.h
#ifndef LEP_FFI_H
#define LEP_FFI_H

#include <stdint.h>
#include <stdbool.h>

// Cabecera simplificada para definir funciones FFI de LEP
#define LEP_FN(name) LEPVar name(const LEPFFIAPI* api, const LEPVar* args, int arg_count)

// Macros de extracción de argumentos con casting implícito
#define ARG_INT(idx)     api->get_int(args[idx])
#define ARG_DOUBLE(idx)  api->get_double(args[idx])
#define ARG_STRING(idx)  api->get_string(args[idx])
#define ARG_PTR(idx)     api->get_ptr(args[idx])

// Macros de retorno
#define RET_INT(val)     return api->make_int(val)
#define RET_DOUBLE(val)  return api->make_double(val)
#define RET_STRING(val)  return api->make_string(val)
#define RET_PTR(ptr)     return api->make_ptr(ptr)
#define RET_NIL()        return api->make_int(0) // o el valor nulo de tu NaN-boxing


typedef uint64_t LEPVar; // Representación de variables en LEP (NaN-boxing / Mobile Point)
typedef struct LEPEnv LEPEnv;
typedef struct LEPNativeRegistry LEPNativeRegistry;

// Firma de cualquier función nativa expuesta por un plugin
typedef LEPVar (*LEPNativeFn)(LEPEnv *env, const LEPVar *args, uint8_t argc);

// API que la VM ofrece al plugin durante y después de la inicialización
typedef struct {
    // Registro de símbolos
    bool (*register_fn)(LEPNativeRegistry *reg, const char *name, LEPNativeFn fn, uint8_t min_args, uint8_t max_args);
    
    // Extracción de datos desde LEPVar
    int32_t (*to_int)(LEPVar v);
    double (*to_float)(LEPVar v);
    const char* (*to_string)(LEPEnv *env, LEPVar v);
    void* (*to_pointer)(LEPVar v);

    // Creación de LEPVar
    LEPVar (*make_int)(int32_t val);
    LEPVar (*make_float)(double val);
    LEPVar (*make_string)(LEPEnv *env, const char *str);
    LEPVar (*make_pointer)(void *ptr);
    LEPVar (*make_null)(void);
} LEPFFIAPI;

// Punto de entrada obligatorio que debe exportar cada módulo (.so / .dll)
typedef bool (*LEPModuleInitFn)(LEPNativeRegistry *reg, const LEPFFIAPI *api);

#endif
