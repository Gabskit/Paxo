#!/usr/bin/env bash
# gen_lep.sh - Genera lep.h (single-header con TODAS las librerías embebidas)
# y lep_paxo.h (solo núcleo paxo). A partir de los fuentes de la VM.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VM_SRC="$ROOT_DIR/Src/Vm/Src"
TP="$VM_SRC/third_party"
BUILD_DIR="$ROOT_DIR/Build"
CC="${CC:-gcc}"

# Archivos paxo (núcleo de la VM, sin dependencias externas). Se ordenan
# igual que la TU completa: Functions.c define los nativos y Vm.c el bucle.
PRE_FILES=(
  "$VM_SRC/termcolor-c.h"
)

PAXO_FILES=(
  "$VM_SRC/Calc.c"
  "$VM_SRC/Deque.c"
  "$VM_SRC/Typecast_and_read.c"
  "$VM_SRC/Functions.c"
  "$VM_SRC/Vm.c"
)

# ====================================================================
# Librerías de terceros que se EMBEBEN en lep.h (implementaciones reales).
# Header-only (stb/miniaudio) o multi-TU (chipmunk/zlib/pdfio/sokol+nanovg),
# inlinadas en orden declaración->implementación dentro del mismo header.
# ====================================================================

# stb_*: los cuerpos llevan su propia implementación gated por
# STB_*_IMPLEMENTATION (se define justo antes de cada uno).
STB_FILES=(
  stb_image.h
  stb_image_write.h
  stb_truetype.h
  stb_easy_font.h
  stb_ds.h
)

# miniaudio: MA_IMPLEMENTATION activa su cuerpo.
MA_FILES=(
  miniaudio.h
)

# zlib (base para pdfio). zlib.h incluye a zconf.h; internos tras zutil.h.
ZLIB_H_FILES=(
  zconf.h
  zlib.h
  zutil.h
  crc32.h
  inftrees.h
  inflate.h
  inffast.h
  deflate.h
  inffixed.h
)
# Orden de amalgamacion clasico (infback.c no se usa: pdfio solo necesita
# crc/inflate/deflate, y ademas infback.c duplicaria statics de inflate.c).
ZLIB_C_FILES=(
  "$TP/zlib/adler32.c"
  "$TP/zlib/zutil.c"
  "$TP/zlib/crc32.c"
  "$TP/zlib/trees.c"
  "$TP/zlib/deflate.c"
  "$TP/zlib/inftrees.c"
  "$TP/zlib/inflate.c"
  "$TP/zlib/inffast.c"
)

# chipmunk 2D: primero el paraguas chipmunk.h (define CP_EXPORT y la version),
# luego los headers publicos en el orden de sus includes, luego privados,
# luego fuentes.
CHIP_H_FILES=(
  chipmunk.h
  chipmunk_types.h
  cpVect.h
  cpBB.h
  cpTransform.h
  cpRobust.h
  cpSpatialIndex.h
  cpArbiter.h
  cpShape.h
  cpPolyShape.h
  cpBody.h
  cpPinJoint.h
  cpSlideJoint.h
  cpPivotJoint.h
  cpGrooveJoint.h
  cpDampedSpring.h
  cpDampedRotarySpring.h
  cpRotaryLimitJoint.h
  cpRatchetJoint.h
  cpGearJoint.h
  cpSimpleMotor.h
  cpConstraint.h
  cpSpace.h
  cpHastySpace.h
  cpMarch.h
  cpPolyline.h
  chipmunk_structs.h
  chipmunk_private.h
)
CHIP_C_FILES=( "$TP"/chipmunk/src/*.c )

# pdfio: headers (privado requiere zlib) luego fuentes.
PDFIO_H_FILES=(
  pdfio.h
  pdfio-content.h
  pdfio-private.h
  ttf.h
  pdfio-base-font-widths.h
  pdfio-cgats001-compat.h
)
PDFIO_C_FILES=( "$TP"/pdfio/*.c )

# sokol + nanovg + fontstash: opcional (LEP_ENABLE_NVG). gl3_compat.h va
# primero (provee <GL/gl.h> si existe). fontstash usa las declaraciones de
# stb_truetype ya embebidas arriba (FONS_NO_STB_TT_IMPL evita duplicados).
NVG_FILES=(
  gl3_compat.h
  sokol_app.h
  sokol_gfx.h
  sokol_time.h
  nanovg.h
  fontstash.h
  nanovg.c
  nanovg_gl.h
)

ALL_EMBED=()
for f in "${STB_FILES[@]}" "${MA_FILES[@]}"; do ALL_EMBED+=("$VM_SRC/$f"); done
for f in "${ZLIB_H_FILES[@]}"; do ALL_EMBED+=("$TP/zlib/$f"); done
for f in "${ZLIB_C_FILES[@]}"; do ALL_EMBED+=("$f"); done
for f in "${CHIP_H_FILES[@]}"; do ALL_EMBED+=("$TP/chipmunk/chipmunk/$f"); done
for f in "${CHIP_C_FILES[@]}"; do ALL_EMBED+=("$f"); done
for f in "${PDFIO_H_FILES[@]}"; do ALL_EMBED+=("$TP/pdfio/$f"); done
for f in "${PDFIO_C_FILES[@]}"; do ALL_EMBED+=("$f"); done
for f in "${NVG_FILES[@]}"; do ALL_EMBED+=("$VM_SRC/$f"); done

# Verificar que existen
for f in "${PRE_FILES[@]}" "${PAXO_FILES[@]}" "${ALL_EMBED[@]}"; do
  if [[ ! -f "$f" ]]; then
    echo "Error: no se encontro $f" >&2
    exit 1
  fi
done

# Includes con <> que pertenecen a librerías embebidas (se eliminan del
# cuerpo Y de la lista de includes externos): su falta se satisface con el
# texto inlinado. El resto de includes <> del sistema se protegen con
# __has_include para mantener lep.h portable.
STRIP_ANGLE='(chipmunk\/[^>]+|zlib\.h|zconf\.h|ft2build\.h|memory\.h|ApplicationServices\/[^>]+|TargetConditionals\.h|OpenGL\/gl[^>]*\.h)'

# Extraer includes externos únicos (<> ) de una lista de archivos, filtrando
# los que corresponden a librerías embebidas.
extract_includes() {
  local files=("$@")
  grep -hE '^[[:space:]]*#[[:space:]]*include[[:space:]]+<[^>]+>' "${files[@]}" 2>/dev/null \
    | grep -vE "$STRIP_ANGLE" \
    | awk '!seen[$0]++'
}

# Emitir el contenido saneado de un archivo (sin #pragma once, sin includes
# locales "", sin includes <> embebidos/inexistentes).
# $2 = 1 -> fuerza "static inline" (solo nucleo paxo; en librerias de
# terceros rompe macros como stbi_inline/ma_inl y no hace falta, ya que
# dentro de una sola TU no hay riesgo de multiplo definicion).
emit_snip() {
  local file="$1"
  local want_static_inline="${2:-0}"
  echo "/* --- $(basename "$file") --- */"
  if [[ "$want_static_inline" == 1 ]]; then
    sed -E '
      /^#pragma once$/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+"[^"]+".*$/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+<'"$STRIP_ANGLE"'>/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+(FT_FREETYPE_H|FT_ADVANCES_H)/d;
      s/inline /static inline /g;
      s/static static inline/static inline/g
    ' "$file"
  else
    sed -E '
      /^#pragma once$/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+"[^"]+".*$/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+<'"$STRIP_ANGLE"'>/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+(FT_FREETYPE_H|FT_ADVANCES_H)/d
    ' "$file"
  fi
  echo ""
}

# stb_image_resize2.h usa auto-inclusion multi-pase (#include ''STBIR__HEADER_FILENAME'').
# Impresible de embeber textualmente, asi que se cuece con el preprocesador
# del sistema en gen-time: se conservan SOLO las secciones marcadas con la
# ruta de stb_image_resize2.h (los cuerpos de headers de sistema se desechan;
# lep.h provee sus declaraciones en el prologo). El resultado no tiene
# ninguna auto-inclusion y es independiente del compilador consumidor.
bake_resize2() {
  local unit="$BUILD_DIR/.gen_resize2.c"
  {
    echo "// bootstrap bake"
    echo "#undef STBIR_ONLY_HEADERS"
    echo "#define STB_IMAGE_RESIZE_IMPLEMENTATION"
    echo "#include \"stb_image_resize2.h\""
  } > "$unit"
  echo "/* --- stb_image_resize2.h (cocido: multi-pase resuelto) --- */"
  "$CC" -E "$unit" -I"$VM_SRC" | awk '
    /^# [0-9]+ "/ { f = ($0 ~ /stb_image_resize2\.h/) ? 1 : 0; next }
    f { print }
  '
  rm -f "$unit"
  echo ""
}

# Generar el single-header completo de la VM (con terceros embebidos)
generate_lep_full() {
  local guard="$1"
  local title="$2"
  shift 2
  local files=("$@")

  local -a includes
  mapfile -t includes < <(extract_includes "${PRE_FILES[@]}" "${PAXO_FILES[@]}" "${ALL_EMBED[@]}")

  {
    echo "/* $title - Auto-generado por sh/gen_lep.sh"
    echo " * No editar manualmente." 
    echo " *"
    echo " * EmbeNe el nucleo de la VM (Calc, Deque, Typecast, Functions, Vm)"
    echo " * junto con las librerias de terceros reales:"
    echo " *   - stb_image/write/resize2/truetype/easy_font/ds (imagenes/fuentes)"
    echo " *   - miniaudio (audio)"
    echo " *   - chipmunk 2D (fisica)"
    echo " *   - zlib + pdfio (PDF)"
    echo " *   - sokol + nanovg (graficos, opcional: -DLEP_ENABLE_NVG)"
    echo " * Asi, los nativos img_* font_* audio_* phys_* pdf_* sokol_* nvg_*"
    echo " * son implementaciones reales, sin stubs ni dependencias externas."
    echo " */"
    echo "#ifndef $guard"
    echo "#define $guard"
    echo ""

    for inc in "${includes[@]}"; do
      local inc_hdr
      inc_hdr="$(printf '%s\n' "$inc" | sed -E 's/^[[:space:]]*#[[:space:]]*include[[:space:]]+<([^>]+)>.*/\1/')"
      if [[ "$inc_hdr" =~ $STRIP_ANGLE ]]; then
        continue
      fi
      echo "#if __has_include(<$inc_hdr>)"
      echo "$inc"
      echo "#endif"
    done
    echo ""

    # --- Marcadores de terceros embebidos ---
    echo "/* ===== Terceros embebidos reales ===== */"
    echo ""
    echo "#ifndef LEP_EMBEDDED_LIBS"
    echo "#define LEP_EMBEDDED_LIBS 1"
    echo "#endif"
    echo "#ifndef CP_SPACE_DISABLE_DEBUG_API"
    echo "#define CP_SPACE_DISABLE_DEBUG_API 1"
    echo "#endif"
    echo ""
    echo "#if !defined(LEP_NO_STB)"
    echo "#define LEP_HAS_IMG 1"
    echo "#define LEP_HAS_FONT 1"
    echo "#endif"
    echo "#if !defined(LEP_NO_MINIAUDIO)"
    echo "#define LEP_HAS_AUDIO 1"
    echo "#endif"
    echo "#define LEP_HAS_PHYS 1"
    echo "#define LEP_HAS_PDF 1"
    echo ""

    # --- stb (imagenes/fuentes/ds) ---
    echo "/* ===== stb_image ===== */"
    echo "#ifndef STB_IMAGE_IMPLEMENTATION"
    echo "#define STB_IMAGE_IMPLEMENTATION"
    echo "#endif"
    emit_snip "$VM_SRC/stb_image.h"
    echo "/* ===== stb_image_write ===== */"
    echo "#ifndef STB_IMAGE_WRITE_IMPLEMENTATION"
    echo "#define STB_IMAGE_WRITE_IMPLEMENTATION"
    echo "#endif"
    emit_snip "$VM_SRC/stb_image_write.h"
echo "/* ===== stb_image_resize2 (cocido) ===== */"
    bake_resize2
    echo "/* ===== stb_truetype ===== */"
    echo "#ifndef STB_TRUETYPE_IMPLEMENTATION"
    echo "#define STB_TRUETYPE_IMPLEMENTATION"
    echo "#endif"
    emit_snip "$VM_SRC/stb_truetype.h"
    echo "/* ===== stb_easy_font ===== */"
    emit_snip "$VM_SRC/stb_easy_font.h"
    echo "/* ===== stb_ds ===== */"
    emit_snip "$VM_SRC/stb_ds.h"

    # --- miniaudio ---
    echo "/* ===== miniaudio ===== */"
    echo "#ifndef MA_IMPLEMENTATION"
    echo "#define MA_IMPLEMENTATION"
    echo "#endif"
    emit_snip "$VM_SRC/miniaudio.h"

    # --- zlib ---
    echo "/* ===== zlib ===== */"
    for f in "${ZLIB_H_FILES[@]}"; do
      emit_snip "$TP/zlib/$f"
    done
    # trees.h usa DIST_CODE_LEN, que en la compilacion separada define trees.c.
    echo "#ifndef DIST_CODE_LEN"
    echo "#define DIST_CODE_LEN 512"
    echo "#endif"
    emit_snip "$TP/zlib/trees.h"
    for f in "${ZLIB_C_FILES[@]}"; do
      emit_snip "$f"
    done

    # --- chipmunk ---
    echo "/* ===== chipmunk 2D ===== */"
    for f in "${CHIP_H_FILES[@]}"; do
      emit_snip "$TP/chipmunk/chipmunk/$f"
    done
    emit_snip "$TP/chipmunk/src/prime.h"
    for f in "${CHIP_C_FILES[@]}"; do
      emit_snip "$f"
    done

    # --- pdfio ---
    echo "/* ===== pdfio ===== */"
    for f in "${PDFIO_H_FILES[@]}"; do
      emit_snip "$TP/pdfio/$f"
    done
    for f in "${PDFIO_C_FILES[@]}"; do
      emit_snip "$f"
    done

    # --- sokol + nanovg (opcional) ---
    echo "/* ===== sokol + nanovg (LEP_ENABLE_NVG) ===== */"
    echo "#if defined(LEP_ENABLE_NVG)"
    echo "#ifndef SOKOL_GLCORE"
    echo "#define SOKOL_GLCORE"
    echo "#endif"
    echo "#ifndef SOKOL_NO_ENTRY"
    echo "#define SOKOL_NO_ENTRY"
    echo "#endif"
    echo "#ifndef SOKOL_APP_IMPL"
    echo "#define SOKOL_APP_IMPL"
    echo "#endif"
    echo "#ifndef SOKOL_GFX_IMPL"
    echo "#define SOKOL_GFX_IMPL"
    echo "#endif"
    echo "#ifndef SOKOL_TIME_IMPL"
    echo "#define SOKOL_TIME_IMPL"
    echo "#endif"
    echo "#ifndef NANOVG_GL3_IMPLEMENTATION"
    echo "#define NANOVG_GL3_IMPLEMENTATION"
    echo "#endif"
    echo "#ifndef FONTSTASH_IMPLEMENTATION"
    echo "#define FONTSTASH_IMPLEMENTATION"
    echo "#endif"
    echo "#ifndef NVG_NO_STB"
    echo "#define NVG_NO_STB"
    echo "#endif"
    echo "#ifndef FONS_NO_STB_TT_IMPL"
    echo "#define FONS_NO_STB_TT_IMPL"
    echo "#endif"
    echo "#ifndef LEP_HAS_NVG"
    echo "#define LEP_HAS_NVG 1"
    echo "#endif"
    for f in "${NVG_FILES[@]}"; do
      emit_snip "$VM_SRC/$f"
    done
    echo "#endif /* LEP_ENABLE_NVG */"
    echo ""

    # --- Núcleo paxo ---
    echo "/* ===== Nucleo paxo ===== */"
    for f in "${files[@]}"; do
      emit_snip "$f" 1
    done

    echo "#endif /* $guard */"
  }
}

# --- Generar lep.h (núcleo + terceros) ---
generate_lep_full "LEP_H" "lep.h - Light Environment Processing VM (single-header, con terceros embebidos)" "${PRE_FILES[@]}" "${PAXO_FILES[@]}" > "$BUILD_DIR/lep.h"
echo "lep.h generado en $BUILD_DIR/lep.h ($(wc -l < "$BUILD_DIR/lep.h") lineas)"

# --- Generar lep_paxo.h (solo fuentes paxo) ---
{
  echo "/* lep_paxo.h - Auto-generado por sh/gen_lep.sh"
  echo " * No editar manualmente."
  echo " * Solo el nucleo de la VM (Calc, Deque, Typecast, Functions, Vm)"
  echo " * y termcolor-c.h. Los nativos de terceros degradan a fallback."
  echo " * Usa Build/lep.h si necesitas las librerias reales."
  echo " */"
  echo "#ifndef LEP_PAXO_H"
  echo "#define LEP_PAXO_H"
  echo ""
  includes_paxo=()
  mapfile -t includes_paxo < <(extract_includes "${PRE_FILES[@]}" "${PAXO_FILES[@]}")
  for inc in "${includes_paxo[@]}"; do
    inc_hdr="$(printf '%s\n' "$inc" | sed -E 's/^[[:space:]]*#[[:space:]]*include[[:space:]]+<([^>]+)>.*/\1/')"
    echo "#if __has_include(<$inc_hdr>)"
    echo "$inc"
    echo "#endif"
  done
  echo ""
  for f in "${PRE_FILES[@]}" "${PAXO_FILES[@]}"; do
    emit_snip "$f" 1
  done
  echo "#endif /* LEP_PAXO_H */"
} > "$BUILD_DIR/lep_paxo.h"
echo "lep_paxo.h generado en $BUILD_DIR/lep_paxo.h ($(wc -l < "$BUILD_DIR/lep_paxo.h") lineas)"