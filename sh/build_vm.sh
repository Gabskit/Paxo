#!/usr/bin/env bash
# build_vm.sh - Compila la VM (Lepvm)
#
# - Detecta compilador y estándar soportado vía sh/pick_cc.sh
#   (gcc, clang o cc; funciona en Linux, macOS y MinGW/Windows).
# - Incluye las fuentes vendidas de Chipmunk2D, pdfio y zlib
#   (Src/Vm/Src/third_party), por lo que no requieren instalación.
# - stb_image / stb_truetype / miniaudio son header-only: se compilan solos.
# - Si detecta SDL3 en el sistema (pkg-config), habilita las funciones de
#   ventana/gráficos con -DPAXO_ENABLE_SDL3.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VM_SRC="$ROOT_DIR/Src/Vm/Src"
TP="$VM_SRC/third_party"
SDL="$VM_SRC/SDL3"

# Compilador, estándar y libs de enlace según plataforma.
eval "$(bash "$SCRIPT_DIR/pick_cc.sh")"

mkdir -p "$ROOT_DIR/Build"

# Sufijo ejecutable de la plataforma (.exe bajo MinGW/MSYS).
OUT="Lepvm"
case "$(uname -s)" in
  MINGW* | MSYS* | CYGWIN*) OUT="Lepvm.exe" ;;
esac

# Detección opcional de SDL3 para ventana/gráficos.
# Los cflags van antes de los objetos y las libs después del main.
SDL_CFLAGS=""
SDL_LIBS=""
if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists sdl3 2>/dev/null; then
  SDL_CFLAGS="-DPAXO_ENABLE_SDL3 $(pkg-config --cflags sdl3)"
  SDL_LIBS="$(pkg-config --libs sdl3)"
  echo "[build_vm] SDL3 detectada: ventanas/gráficos habilitados"
else
  echo "[build_vm] SDL3 no encontrada: win_* quedará deshabilitado"
fi

# shellcheck disable=SC2086
"$CC" ${STD:+-std=$STD} -Wall -Wextra -O3 -DNDEBUG \
  -I"$VM_SRC" -I"$TP/chipmunk" -I"$TP/zlib" -I"$TP/pdfio" \
  $SDL_CFLAGS \
  "$VM_SRC/Main.c" \
  "$TP"/chipmunk/src/*.c \
  "$TP"/chipmunk/src/*.h \
  "$TP"/pdfio/*.c \
  "$TP"/pdfio/*.h \
  "$TP"/zlib/*.c \
  "$TP"/zlib/*.h \
	"$SDL"/* .h \
  -o "$ROOT_DIR/Build/$OUT" \
  $SDL_LIBS $LIBS

echo "[build_vm] Build/$OUT generado"
