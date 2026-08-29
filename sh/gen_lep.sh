#!/usr/bin/env bash
# gen_lep.sh - Genera lep.h y lep_paxo.h (single-headers) a partir de los fuentes de la VM
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VM_SRC="$ROOT_DIR/Src/Vm/Src"

BUILD_DIR="$ROOT_DIR/Build"

# Archivos paxo (nucleo de la VM, sin dependencias externas)
PAXO_FILES=(
  "$VM_SRC/Calc.c"
  "$VM_SRC/Deque.c"
  "$VM_SRC/Typecast_and_read.c"
  "$VM_SRC/Functions.c"
  "$VM_SRC/Vm.c"
)

# Librerias de terceros (incluidas en la version completa)
THIRD_PARTY_FILES=(
  "$VM_SRC/gl3_compat.h"
  "$VM_SRC/termcolor-c.h"
  "$VM_SRC/miniaudio.h"
  "$VM_SRC/nanovg.h"
  "$VM_SRC/nanovg_gl3.h"
  "$VM_SRC/simple2d.h"
	"$VM_SRC/stb_image.h"
	"$VM_SRC/stb_image_resize2.h"
	"$VM_SRC/stb_image_write.h"
	"$VM_SRC/stb_truetype.h"
	"$VM_SRC/SDL3"/*
)

ALL_FILES=("${PAXO_FILES[@]}" "${THIRD_PARTY_FILES[@]}")

# Verificar que existen
for f in "${ALL_FILES[@]}"; do
  if [[ ! -f "$f" ]]; then
    echo "Error: no se encontro $f" >&2
    exit 1
  fi
done

# Funcion para extraer includes externos unicos de una lista de archivos
extract_includes() {
  local files=("$@")
  declare -A seen_inc
  local incs=()
  for f in "${files[@]}"; do
    while IFS= read -r line; do
      if [[ "$line" =~ ^[[:space:]]*#include[[:space:]]+\<(.+)\> ]]; then
        local inc="${BASH_REMATCH[1]}"
        if [[ -z "${seen_inc[$inc]+_}" ]]; then
          seen_inc[$inc]=1
          incs+=("$line")
        fi
      fi
    done < "$f"
  done
  printf '%s\n' "${incs[@]}"
}

# Funcion para generar un single-header
generate_header() {
  local guard="$1"
  local title="$2"
  shift 2
  local files=("$@")

  local -a includes
  mapfile -t includes < <(extract_includes "${files[@]}")

  {
    echo "/* $title - Auto-generado por sh/gen_lep.sh"
    echo " * No editar manualmente."
    echo " */"
    echo "#ifndef $guard"
    echo "#define $guard"
    echo ""

    for inc in "${includes[@]}"; do
      echo "$inc"
    done
    echo ""

    for f in "${files[@]}"; do
      echo "/* --- $(basename "$f") --- */"
      sed -E '/^#pragma once$/d; /^[[:space:]]*#[[:space:]]*include[[:space:]]+"[^"]+".*$/d; s/inline /static inline /g; s/static static inline/static inline/g' "$f"
      echo ""
    done

    echo "#endif /* $guard */"
  }
}

# --- Generar lep_paxo.h (solo fuentes paxo, sin librerias de terceros) ---
generate_header "LEP_PAXO_H" "lep_paxo.h - Light Environment Processing VM (paxo-only)" "${PAXO_FILES[@]}" > "$BUILD_DIR/lep_paxo.h"
echo "lep_paxo.h generado en $BUILD_DIR/lep_paxo.h ($(wc -l < "$BUILD_DIR/lep_paxo.h") lineas)"

# --- Generar lep.h (version completa con librerias de terceros) ---
generate_header "LEP_H" "lep.h - Light Environment Processing VM (single-header library)" "${ALL_FILES[@]}" > "$BUILD_DIR/lep.h"
echo "lep.h generado en $BUILD_DIR/lep.h ($(wc -l < "$BUILD_DIR/lep.h") lineas)"
