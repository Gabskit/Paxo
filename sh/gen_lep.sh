#!/usr/bin/env bash
# gen_lep.sh - Genera lep.h (single-header) a partir de los fuentes de la VM
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VM_SRC="$ROOT_DIR/Src/Vm/Src"
OUT="$ROOT_DIR/Build/lep.h" #se guarda en /Build junto con los binarios de vm y compilador

# Archivos en orden de dependencia (sin Main.c ni Jit.c)
FILES=(
  "$VM_SRC/Calc.c"
  "$VM_SRC/Deque.c"
  "$VM_SRC/termcolor-c.h"
  "$VM_SRC/Typecast_and_read.c"
  "$VM_SRC/Functions.c"
  "$VM_SRC/Vm.c"
)

# Verificar que existen
for f in "${FILES[@]}"; do
  if [[ ! -f "$f" ]]; then
    echo "Error: no se encontro $f" >&2
    exit 1
  fi
done

# Extraer includes externos únicos
declare -A seen_includes
unique_includes=()
for f in "${FILES[@]}"; do
  while IFS= read -r line; do
    if [[ "$line" =~ ^[[:space:]]*#include[[:space:]]+\<(.+)\> ]]; then
      inc="${BASH_REMATCH[1]}"
      if [[ -z "${seen_includes[$inc]+_}" ]]; then
        seen_includes[$inc]=1
        unique_includes+=("$line")
      fi
    fi
  done < "$f"
done

# Generar lep.h
{
  echo "/* lep.h - Light Environment Processing VM (single-header library)"
  echo " * Auto-generado por sh/gen_lep.sh"
  echo " * No editar manualmente."
  echo " */"
  echo "#ifndef LEP_H"
  echo "#define LEP_H"
  echo ""

  # Includes externos
  for inc in "${unique_includes[@]}"; do
    echo "$inc"
  done
  echo ""

  # Types y declaraciones siempre visibles
  for f in "${FILES[@]}"; do
    echo "/* --- $(basename "$f") --- */"
    sed -E '/^#pragma once$/d; /^[[:space:]]*#include[[:space:]]+"[^"]+"$/d; s/inline /static inline /g; s/static static inline/static inline/g' "$f"
    echo ""
  done

  echo "#endif /* LEP_H */"
} > "$OUT"

echo "lep.h generado en $OUT ($(wc -l < "$OUT") lineas)"
