#!/usr/bin/env bash
# gen_lep.sh - Amalgama total: lep.h (C + Zig a C) y lep.zig (Zig Monolítico)
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VM_SRC="$ROOT_DIR/Src/Vm/Src"
TP="$VM_SRC/third_party"
BUILD_DIR="$ROOT_DIR/Build"
CC="${CC:-gcc}"

mkdir -p "$BUILD_DIR"

# ====================================================================
# Escaneo dinámico de fuentes y subdirectorios (C y Zig, ordenados)
# ====================================================================
PRE_FILES=("$VM_SRC/termcolor-c.h")

PAXO_C_FILES=()
while IFS= read -r -d '' f; do
  if [[ "$(basename "$f")" != "nanovg.c" ]]; then
    PAXO_C_FILES+=("$f")
  fi
done < <(find "$VM_SRC" -maxdepth 3 -type f -name "*.c" -print0 | sort -z)

PAXO_ZIG_FILES=()
while IFS= read -r -d '' f; do
  PAXO_ZIG_FILES+=("$f")
done < <(find "$VM_SRC" -maxdepth 3 -type f -name "*.zig" -print0 | sort -z)

# ====================================================================
# Terceros para la amalgama C
# ====================================================================
STB_FILES=(stb_image.h stb_image_write.h stb_truetype.h stb_easy_font.h stb_ds.h)
MA_FILES=(miniaudio.h)
ZLIB_H_FILES=(zconf.h zlib.h zutil.h inftrees.h inflate.h inffast.h deflate.h inffixed.h)
ZLIB_C_FILES=(
  "$TP/zlib/adler32.c" "$TP/zlib/zutil.c" "$TP/zlib/crc32.c"
  "$TP/zlib/trees.c" "$TP/zlib/deflate.c" "$TP/zlib/inftrees.c"
  "$TP/zlib/inflate.c" "$TP/zlib/inffast.c"
)
CHIP_H_FILES=(
  chipmunk_types.h cpVect.h cpBB.h cpTransform.h cpRobust.h cpSpatialIndex.h
  cpArbiter.h cpShape.h cpPolyShape.h cpBody.h cpPinJoint.h cpSlideJoint.h
  cpPivotJoint.h cpGrooveJoint.h cpDampedSpring.h cpDampedRotarySpring.h
  cpRotaryLimitJoint.h cpRatchetJoint.h cpGearJoint.h cpSimpleMotor.h
  cpConstraint.h cpSpace.h cpHastySpace.h cpMarch.h cpPolyline.h
  chipmunk_structs.h chipmunk_private.h chipmunk.h
)
CHIP_C_FILES=()
while IFS= read -r -d '' f; do
  CHIP_C_FILES+=("$f")
done < <(find "$TP/chipmunk/src" -type f -name "*.c" -print0 | sort -z)

NVG_FILES=(gl3_compat.h sokol_app.h sokol_gfx.h sokol_time.h nanovg.h fontstash.h nanovg.c nanovg_gl.h)

ALL_EMBED=()
for f in "${STB_FILES[@]}" "${MA_FILES[@]}"; do ALL_EMBED+=("$VM_SRC/$f"); done
for f in "${ZLIB_H_FILES[@]}"; do ALL_EMBED+=("$TP/zlib/$f"); done
for f in "${ZLIB_C_FILES[@]}"; do ALL_EMBED+=("$f"); done
for f in "${CHIP_H_FILES[@]}"; do ALL_EMBED+=("$TP/chipmunk/chipmunk/$f"); done
for f in "${CHIP_C_FILES[@]}"; do ALL_EMBED+=("$f"); done
for f in "${NVG_FILES[@]}"; do ALL_EMBED+=("$VM_SRC/$f"); done

STRIP_ANGLE='(chipmunk\/[^>]+|zlib\.h|zconf\.h|ft2build\.h|memory\.h|ApplicationServices\/[^>]+|TargetConditionals\.h|OpenGL\/gl[^>]*\.h)'

extract_includes() {
  grep -hE '^[[:space:]]*#[[:space:]]*include[[:space:]]+<[^>]+>' "$@" 2>/dev/null \
    | grep -vE "$STRIP_ANGLE" \
    | awk '!seen[$0]++'
}

emit_snip() {
  local file="$1"
  local want_static_inline="${2:-0}"
  if [[ ! -f "$file" ]]; then return 0; fi
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

bake_resize2() {
  if [[ ! -f "$VM_SRC/stb_image_resize2.h" ]]; then return 0; fi
  local unit="$BUILD_DIR/.gen_resize2.c"
  {
    echo "// bootstrap bake"
    echo "#undef STBIR_ONLY_HEADERS"
    echo "#define STB_IMAGE_RESIZE_IMPLEMENTATION"
    echo "#include \"stb_image_resize2.h\""
  } > "$unit"
  echo "/* --- stb_image_resize2.h (cocido) --- */"
  "$CC" -E "$unit" -I"$VM_SRC" | awk '
    /^# [0-9]+ "/ { f = ($0 ~ /stb_image_resize2\.h/) ? 1 : 0; next }
    f { print }
  '
  rm -f "$unit"
  echo ""
}

emit_zlib_crc32() {
  echo "/* --- crc32.c --- */"
  sed -E '/^[[:space:]]*#[[:space:]]*include[[:space:]]+"crc32.h".*$/{
    r '"$TP"'/zlib/crc32.h
    d
  }' "$TP/zlib/crc32.c" | sed -E '
      /^#pragma once$/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+"[^"]+".*$/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+<'"$STRIP_ANGLE"'>/d;
      /^[[:space:]]*#[[:space:]]*include[[:space:]]+(FT_FREETYPE_H|FT_ADVANCES_H)/d
    '
  echo ""
}

transpiler_zig_to_c() {
  local zfile="$1"
  local tmp_c="$BUILD_DIR/.tmp_$(basename "$zfile" .zig).c"
  if command -v zig >/dev/null 2>&1; then
    echo "/* --- Transpilado desde $(basename "$zfile") --- */"
    if zig build-obj "$zfile" -femit-c="$tmp_c" -I"$VM_SRC" -I"$BUILD_DIR" 2>/dev/null; then
      if [ -f "$tmp_c" ]; then
        sed -E '
          /^[[:space:]]*#[[:space:]]*include[[:space:]]+<'"$STRIP_ANGLE"'>/d
        ' "$tmp_c"
        rm -f "$tmp_c"
      fi
    fi
    echo ""
  fi
}

# ====================================================================
# 1. AMALGAMA C (lep.h)
# ====================================================================
{
  echo "/* lep.h - Single Header Amalgam para Paxo VM (C + Zig transpilado a C) */"
  echo "#ifndef LEP_H"
  echo "#define LEP_H"
  echo ""

  mapfile -t includes < <(extract_includes "${PRE_FILES[@]}" "${PAXO_C_FILES[@]}" "${ALL_EMBED[@]}")
  for inc in "${includes[@]}"; do
    inc_hdr="$(printf '%s\n' "$inc" | sed -E 's/^[[:space:]]*#[[:space:]]*include[[:space:]]+<([^>]+)>.*/\1/')"
    if [[ "$inc_hdr" =~ $STRIP_ANGLE ]]; then continue; fi
    echo "#if __has_include(<$inc_hdr>)"
    echo "$inc"
    echo "#endif"
  done
  echo ""

  echo "#ifndef LEP_EMBEDDED_LIBS"
  echo "#define LEP_EMBEDDED_LIBS 1"
  echo "#endif"
  echo "#ifndef CP_SPACE_DISABLE_DEBUG_API"
  echo "#define CP_SPACE_DISABLE_DEBUG_API 1"
  echo "#endif"
  echo "#ifndef CP_EXPORT"
  echo "#define CP_EXPORT"
  echo "#endif"

  for t in cpArray cpHashSet cpBody cpShape cpCircleShape cpSegmentShape cpPolyShape \
           cpConstraint cpPinJoint cpSlideJoint cpPivotJoint cpGrooveJoint \
           cpDampedSpring cpDampedRotarySpring cpRotaryLimitJoint cpRatchetJoint \
           cpGearJoint cpSimpleMotorJoint cpCollisionHandler cpContactPointSet \
           cpArbiter cpSpace; do
    echo "typedef struct $t $t;"
  done
  echo ""

  echo "#define STB_IMAGE_IMPLEMENTATION"
  emit_snip "$VM_SRC/stb_image.h"
  echo "#define STB_IMAGE_WRITE_IMPLEMENTATION"
  emit_snip "$VM_SRC/stb_image_write.h"
  bake_resize2
  echo "#define STB_TRUETYPE_IMPLEMENTATION"
  emit_snip "$VM_SRC/stb_truetype.h"
  emit_snip "$VM_SRC/stb_easy_font.h"
  emit_snip "$VM_SRC/stb_ds.h"

  echo "#define MA_IMPLEMENTATION"
  emit_snip "$VM_SRC/miniaudio.h"

  for f in "${ZLIB_H_FILES[@]}"; do emit_snip "$TP/zlib/$f"; done
  echo "#ifndef DIST_CODE_LEN"
  echo "#define DIST_CODE_LEN 512"
  echo "#endif"
  emit_snip "$TP/zlib/trees.h"
  for f in "${ZLIB_C_FILES[@]}"; do
    if [[ "$(basename "$f")" == "crc32.c" ]]; then emit_zlib_crc32; else emit_snip "$f"; fi
  done
  echo "#undef N"
  echo "#undef W"

  for f in "${CHIP_H_FILES[@]}"; do emit_snip "$TP/chipmunk/chipmunk/$f"; done
  emit_snip "$TP/chipmunk/src/prime.h"
  for f in "${CHIP_C_FILES[@]}"; do emit_snip "$f"; done
  echo "#undef A"
  echo "#undef B"
  echo "#undef STAMP"
  echo "#undef PAIRS"

  echo "#if defined(LEP_ENABLE_NVG)"
  echo "#define SOKOL_GLCORE"
  echo "#define SOKOL_NO_ENTRY"
  echo "#define SOKOL_APP_IMPL"
  echo "#define SOKOL_GFX_IMPL"
  echo "#define SOKOL_TIME_IMPL"
  echo "#define NANOVG_GL3_IMPLEMENTATION"
  echo "#define FONTSTASH_IMPLEMENTATION"
  echo "#define NVG_NO_STB"
  echo "#define FONS_NO_STB_TT_IMPL"
  for f in "${NVG_FILES[@]}"; do emit_snip "$VM_SRC/$f"; done
  echo "#endif"
  echo ""

  for f in "${PRE_FILES[@]}" "${PAXO_C_FILES[@]}"; do
    emit_snip "$f" 
  done

  for zf in "${PAXO_ZIG_FILES[@]}"; do
    transpiler_zig_to_c "$zf"
  done

  echo "#endif /* LEP_H */"
} > "$BUILD_DIR/lep.h"

echo "[gen_lep] Build/lep.h generado correctamente."
