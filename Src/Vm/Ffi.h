#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vars.c"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t (*PaxoNativeFn)(LEPEnv *env, const uint32_t *args, uint8_t argc);

typedef struct PaxoNativeRegistry PaxoNativeRegistry;

typedef struct {
    bool (*register_fn)(PaxoNativeRegistry *, const char *, PaxoNativeFn, uint8_t, uint8_t);
    uint32_t (*call_name)(PaxoNativeRegistry *, LEPEnv *, const char *, const uint32_t *, uint8_t, bool *);
} PaxoFFIAPI;

typedef bool (*PaxoFFIModuleInit)(PaxoNativeRegistry *, const PaxoFFIAPI *);

struct PaxoNativeRegistry {
    void *entries;
    size_t len;
    size_t cap;
    void *modules;
    size_t module_len;
    size_t module_cap;
    uint32_t next_dynamic_id;
};

void paxo_ffi_init(PaxoNativeRegistry *r);
void paxo_ffi_destroy(PaxoNativeRegistry *r);
bool paxo_ffi_register(PaxoNativeRegistry *r, const char *name, PaxoNativeFn fn, uint8_t min_args, uint8_t max_args);
uint32_t paxo_ffi_call_id(PaxoNativeRegistry *r, LEPEnv *env, uint32_t id, const uint32_t *args, uint8_t argc, bool *ok);
uint32_t paxo_ffi_call_name(PaxoNativeRegistry *r, LEPEnv *env, const char *name, const uint32_t *args, uint8_t argc, bool *ok);
bool paxo_ffi_load(PaxoNativeRegistry *r, const char *path);
void paxo_ffi_unload_all(PaxoNativeRegistry *r);
const char *paxo_ffi_name(PaxoNativeRegistry *r, uint32_t id);

#ifdef __cplusplus
}
#endif
