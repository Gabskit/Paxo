#include "../../Src/Vm/Ffi.h"

/* Demonstrates that DEC crosses the extensible FFI unchanged. */
static uint32_t native_decimal_identity(LEPEnv *env, const uint32_t *args, uint8_t argc) {
    if (argc != 1 || args[0] >= env->var_count || env->tags[args[0]].type != DEC) return 0;
    return lep_push_var(env, DEC, env->tags[args[0]].bytesize,
                        lep_get_var_data(env, args[0]), env->tags[args[0]].bytesize == M ? sizeof(decimal64) : sizeof(decimal64));
}

bool paxo_module_init(PaxoNativeRegistry *registry, const PaxoFFIAPI *api) {
    (void)api;
    return paxo_ffi_register(registry, "decimal_identity", native_decimal_identity, 1, 1);
}
