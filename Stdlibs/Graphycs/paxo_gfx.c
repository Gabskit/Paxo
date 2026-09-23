// modules/paxo_gfx.c
#include "../lep_ffi.h"
#include "sokol_app.h"
#include "nanovg.h"

static const LEPFFIAPI *api = NULL;

static LEPVar gfx_draw_rect(LEPEnv *env, const LEPVar *args, uint8_t argc) {
    float x = (float)api->to_float(args[0]);
    float y = (float)api->to_float(args[1]);
    float w = (float)api->to_float(args[2]);
    float h = (float)api->to_float(args[3]);

    // Llamadas directas a NanoVG
    // nvgBeginPath(vg); nvgRect(vg, x, y, w, h); ...

    return api->make_null();
}

// Exportación del módulo
bool LEP_module_init(LEPNativeRegistry *reg, const LEPFFIAPI *paxo_api) {
    api = paxo_api;

    api->register_fn(reg, "gfx.drawRect", gfx_draw_rect, 4, 4);
    // Registrar más funciones de Sokol / NanoVG aquí...

    return true;
}
