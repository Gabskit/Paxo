// Ffi.c
#include <dlfcn.h>
#include <stdio.h>
#include "Ffi.h"

// Instancia global o asignada al runtime de las funciones API
static const LEPFFIAPI g_paxo_ffi_api = {
    .register_fn = paxo_register_native_dynamic,
    .to_int      = lep_var_to_int,
    .to_float    = lep_var_to_float,
    .to_string   = lep_var_to_string,
    .to_pointer  = lep_var_to_pointer,
    .make_int    = lep_make_int,
    .make_float  = lep_make_float,
    .make_string = lep_make_string,
    .make_pointer= lep_make_pointer,
    .make_null   = lep_make_null
};

bool paxo_load_module(LEPNativeRegistry *reg, const char *path) {
    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "[FFI Error] No se pudo cargar %s: %s\n", path, dlerror());
        return false;
    }

    LEPModuleInitFn init_fn = (LEPModuleInitFn)dlsym(handle, "LEP_module_init");
    if (!init_fn) {
        fprintf(stderr, "[FFI Error] Símbolo 'LEP_module_init' no encontrado en %s\n", path);
        dlclose(handle);
        return false;
    }

    // Inicializar el módulo pasándole el registro dinámico y la tabla de API
    return init_fn(reg, &g_paxo_ffi_api);
}
