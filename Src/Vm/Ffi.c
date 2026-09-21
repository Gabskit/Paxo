#include "Ffi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include <windows.h>
typedef HMODULE PaxoDso;
#define PAXO_DSO_OPEN(p) LoadLibraryA(p)
#define PAXO_DSO_SYM(h,n) GetProcAddress((h),(n))
#define PAXO_DSO_CLOSE(h) FreeLibrary(h)
#else
#include <dlfcn.h>
typedef void *PaxoDso;
#define PAXO_DSO_OPEN(p) dlopen((p), RTLD_NOW | RTLD_LOCAL)
#define PAXO_DSO_SYM(h,n) dlsym((h),(n))
#define PAXO_DSO_CLOSE(h) dlclose(h)
#endif

typedef struct {
    char *name;
    PaxoNativeFn fn;
    uint8_t min_args;
    uint8_t max_args;
    uint32_t id;
} PaxoNativeEntry;

typedef struct {
    PaxoDso handle;
    char *path;
} PaxoFFIModule;

static PaxoNativeEntry *entries(PaxoNativeRegistry *r) { return (PaxoNativeEntry *)r->entries; }
static PaxoFFIModule *modules(PaxoNativeRegistry *r) { return (PaxoFFIModule *)r->modules; }

static bool grow_entries(PaxoNativeRegistry *r) {
    if (r->len < r->cap) return true;
    size_t cap = r->cap ? r->cap * 2 : 32;
    PaxoNativeEntry *p = realloc(r->entries, cap * sizeof(*p));
    if (!p) return false;
    r->entries = p; r->cap = cap; return true;
}

static bool grow_modules(PaxoNativeRegistry *r) {
    if (r->module_len < r->module_cap) return true;
    size_t cap = r->module_cap ? r->module_cap * 2 : 8;
    PaxoFFIModule *p = realloc(r->modules, cap * sizeof(*p));
    if (!p) return false;
    r->modules = p; r->module_cap = cap; return true;
}

void paxo_ffi_init(PaxoNativeRegistry *r) {
    memset(r, 0, sizeof(*r));
    r->next_dynamic_id = 1000;
}

void paxo_ffi_unload_all(PaxoNativeRegistry *r) {
    PaxoFFIModule *m = modules(r);
    for (size_t i = r->module_len; i > 0; --i) {
        if (m[i - 1].handle) PAXO_DSO_CLOSE(m[i - 1].handle);
        free(m[i - 1].path);
    }
    r->module_len = 0;
}

void paxo_ffi_destroy(PaxoNativeRegistry *r) {
    paxo_ffi_unload_all(r);
    PaxoNativeEntry *e = entries(r);
    for (size_t i = 0; i < r->len; ++i) free(e[i].name);
    free(r->entries); free(r->modules); memset(r, 0, sizeof(*r));
}

bool paxo_ffi_register(PaxoNativeRegistry *r, const char *name, PaxoNativeFn fn, uint8_t min_args, uint8_t max_args) {
    if (!r || !name || !*name || !fn || min_args > max_args) return false;
    PaxoNativeEntry *e = entries(r);
    for (size_t i = 0; i < r->len; ++i) {
        if (strcmp(e[i].name, name) == 0) {
            e[i].fn = fn; e[i].min_args = min_args; e[i].max_args = max_args; return true;
        }
    }
    if (!grow_entries(r)) return false;
    e = entries(r);
    e[r->len].name = strdup(name);
    if (!e[r->len].name) return false;
    e[r->len].fn = fn;
    e[r->len].min_args = min_args;
    e[r->len].max_args = max_args;
    e[r->len].id = r->next_dynamic_id++;
    r->len++;
    return true;
}

const char *paxo_ffi_name(PaxoNativeRegistry *r, uint32_t id) {
    PaxoNativeEntry *e = entries(r);
    for (size_t i = 0; i < r->len; ++i) if (e[i].id == id) return e[i].name;
    return NULL;
}

uint32_t paxo_ffi_call_id(PaxoNativeRegistry *r, LEPEnv *env, uint32_t id, const uint32_t *args, uint8_t argc, bool *ok) {
    if (ok) *ok = false;
    PaxoNativeEntry *e = entries(r);
    for (size_t i = 0; i < r->len; ++i) {
        if (e[i].id != id) continue;
        if (argc < e[i].min_args || argc > e[i].max_args) return 0;
        uint32_t result = e[i].fn(env, args, argc);
        if (ok) *ok = true;
        return result;
    }
    return 0;
}

uint32_t paxo_ffi_call_name(PaxoNativeRegistry *r, LEPEnv *env, const char *name, const uint32_t *args, uint8_t argc, bool *ok) {
    if (ok) *ok = false;
    PaxoNativeEntry *e = entries(r);
    for (size_t i = 0; i < r->len; ++i) {
        if (strcmp(e[i].name, name) == 0) return paxo_ffi_call_id(r, env, e[i].id, args, argc, ok);
    }
    return 0;
}

bool paxo_ffi_load(PaxoNativeRegistry *r, const char *path) {
    if (!r || !path || !*path) return false;
    PaxoDso handle = PAXO_DSO_OPEN(path);
    if (!handle) return false;
    PaxoFFIModuleInit init = (PaxoFFIModuleInit)PAXO_DSO_SYM(handle, "paxo_module_init");
    if (!init) { PAXO_DSO_CLOSE(handle); return false; }
    PaxoFFIAPI api = { paxo_ffi_register, paxo_ffi_call_name };
    if (!init(r, &api)) { PAXO_DSO_CLOSE(handle); return false; }
    if (!grow_modules(r)) { PAXO_DSO_CLOSE(handle); return false; }
    PaxoFFIModule *m = modules(r);
    m[r->module_len].handle = handle;
    m[r->module_len].path = strdup(path);
    if (!m[r->module_len].path) { PAXO_DSO_CLOSE(handle); return false; }
    r->module_len++;
    return true;
}
