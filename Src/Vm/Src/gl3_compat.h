#pragma once
// gl3_compat.h - incluye los headers de OpenGL si están disponibles.
// Header separado para que gen_lep.sh no ize <GL/gl.h> sin protección
// al generar lep.h (mantiene el single-header portable).
#if __has_include(<GL/gl.h>)
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#endif
