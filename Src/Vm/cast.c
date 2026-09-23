#pragma once
#include "vars.c"

// Convierte una variable existente a un nuevo tipo y la empuja a la Arena
uint32_t lep_cast_var(LEPEnv* env, uint32_t src_id, LEPType target_type) {
    LEPVartag src_tag = env->tags[src_id];
    void* src_data = lep_get_var_data(env, src_id);
    
    // Si ya es del tipo deseado, podemos simplemente devolver el mismo ID
    // o crear una copia exacta (aquí devolvemos una copia para evitar mutaciones indeseadas)
    if (src_tag.type == target_type) {
        return lep_push_var(env, src_tag.type, src_tag.bytesize, src_data, src_tag.bytesize);
    }

    // Lógica de conversión (Ejemplo: Cualquier cosa a DOUBLE)
    if (target_type == FP) {
        double result = 0.0;
        
        switch (src_tag.type) {
            case INT:  result = (double)(*(int64_t*)src_data); break;
            case UINT: result = (double)(*(uint64_t*)src_data); break;
            case BOOL: result = (*(bool*)src_data) ? 1.0 : 0.0; break;
            // Aquí agregarías parseo de STRING a número, etc.
            default: break; 
        }
        return LEP_PUSH(env, result);
    }
    
    // Lógica de conversión (Ejemplo: Cualquier cosa a ENTERO)
    if (target_type == INT) {
        int64_t result = 0;
        switch (src_tag.type) {
            case FP:   result = (int64_t)(*(double*)src_data); break;
            case BOOL: result = (*(bool*)src_data) ? 1 : 0; break;
            default: break;
        }
        return LEP_PUSH(env, result);
    }
    // Convertir a FRAC (_Fract)
if (target_type == FRAC) {
    _Fract result = 0.0r;
    switch (src_tag.type) {
        case FP:    result = (_Fract)LEP_AS(env, src_id, double); break;
        case INT:   result = (_Fract)LEP_AS(env, src_id, int64_t); break;
        case ACCUM: result = (_Fract)LEP_AS(env, src_id, _Accum); break;
        default: break;
    }
    return LEP_PUSH(env, result);
}

// Convertir a ACCUM (_Accum)
if (target_type == ACCUM) {
    _Accum result = 0.0k;
    switch (src_tag.type) {
        case FP:   result = (_Accum)LEP_AS(env, src_id, double); break;
        case INT:  result = (_Accum)LEP_AS(env, src_id, int64_t); break;
        case FRAC: result = (_Accum)LEP_AS(env, src_id, _Fract); break;
        default: break;
    }
    return LEP_PUSH(env, result);
}


    // Por defecto, si no sabe cómo convertir, devuelve 0 entero o dispara un error
    return LEP_PUSH(env, (int64_t)0);
}
