#!/usr/bin/env bash
# pick_cc.sh - Detecta compilador C, estándar soportado y libs de enlace.
# Emite asignaciones listas para `eval`:
#   CC=gcc|clang|cc
#   STD=gnu23|gnu2x|gnu17|gnu11   (vacío si ninguna aplica)
#   LIBS="..."                    (flags de enlace según plataforma)
# Uso: eval "$(bash sh/pick_cc.sh)"
set -euo pipefail

pick_compiler() {
  if [ -n "${CC:-}" ] && command -v "$CC" >/dev/null 2>&1; then
    echo "$CC"
    return
  fi
  local c
  for c in gcc clang cc; do
    if command -v "$c" >/dev/null 2>&1; then
      echo "$c"
      return
    fi
  done
  echo "" # nada disponible
}

probe_std() {
  # Compilador y estándar dados; retorna 0 si acepta un main vacío por stdin.
  printf 'int main(void){return 0;}\n' | "$1" -x c -std="$2" - -o /dev/null >/dev/null 2>&1
}

CC_FOUND="$(pick_compiler)"
if [ -z "$CC_FOUND" ]; then
  echo "pick_cc: no se encontro compilador C (gcc/clang/cc)" >&2
  exit 1
fi

STD=""
for s in gnu23 gnu2x gnu17 gnu11; do
  if probe_std "$CC_FOUND" "$s"; then
    STD="$s"
    break
  fi
done
# STD vacío = usar el estándar por defecto del compilador.

case "$(uname -s)" in
  MINGW* | MSYS* | CYGWIN*)
    LIBS="-lm"
    ;;
  *)
    LIBS="-lm -lpthread -ldl"
    ;;
esac

echo "CC=$CC_FOUND"
echo "STD=$STD"
echo "LIBS=\"$LIBS\""
