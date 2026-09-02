#!/usr/bin/env bash
# build_vm.sh - Compila la VM (Lepvm)
#
# - Detecta compilador y estándar soportado vía sh/pick_cc.sh
#   (gcc, clang o cc; funciona en Linux, macOS y MinGW/Windows).
# - Incluye las fuentes de Chipmunk2D, pdfio, zlib, Sokol y NanoVG
#   (Src/Vm/Src/third_party).
# - Gráficos vía Sokol + NanoVG habilitados por defecto.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
VM_SRC="$ROOT_DIR/Src/Vm/Src"
TP="$VM_SRC/third_party"
# Compilador, estándar y libs de enlace según plataforma.
eval "$(bash "$SCRIPT_DIR/pick_cc.sh")"

mkdir -p "$ROOT_DIR/Build"

OUT="Lepvm"
case "$(uname -s)" in
  MINGW* | MSYS* | CYGWIN*) OUT="Lepvm.exe" ;;
esac

NVG_CFLAGS=""
NVG_LIBS=""
NVG_SRCS=""
if [[ "${LEP_ENABLE_NVG:-1}" == "1" ]]; then
  NVG_CFLAGS="-DLEP_ENABLE_NVG"
  # NVG_NO_STB evita que nanovg.c vuelva a definir los símbolos stbi_*:
  # Functions.c ya los implementa (STB_IMAGE_IMPLEMENTATION). Sin esta
  # bandera el enlazado falla con "multiple definition" para stbi_*.
  NVG_CFLAGS="$NVG_CFLAGS -DNVG_NO_STB"
  # FONS_NO_STB_TT_IMPL: nanovg.c declara stb_truetype pero no lo implementa
  # (evita stbtt_* duplicados con Functions.c); las funciones se resuelven
  # contra el impl de la TU principal (LEP_HAS_FONT).
  NVG_CFLAGS="$NVG_CFLAGS -DFONS_NO_STB_TT_IMPL"
  # Núcleo de NanoVG compilado como una TU separada (nanovg.c).
  NVG_SRCS="$VM_SRC/nanovg.c"
  case "$(uname -s)" in
    MINGW* | MSYS* | CYGWIN*) 
        NVG_LIBS="-lopengl32 -lgdi32" 
        ;;
    Darwin*) 
        NVG_LIBS="-framework OpenGL -framework Cocoa -framework QuartzCore -framework AudioToolbox" 
        ;;
    *) 
        NVG_LIBS="-lGL -lX11 -lXi -lXcursor -ldl -lm -lpthread" 
        ;;
  esac
  echo "[build_vm] Gráficos sokol+NanoVG habilitados (-DLEP_ENABLE_NVG)"
else
  echo "[build_vm] Gráficos sokol+NanoVG deshabilitados (LEP_ENABLE_NVG=1 para activar)"
fi

# shellcheck disable=SC2086
"$CC" ${STD:+-std=$STD} -Wall -Wextra -O3 -DNDEBUG \
  -I"$VM_SRC" -I"$TP/chipmunk" -I"$TP/zlib" -I"$TP/pdfio" \
  $NVG_CFLAGS \
  "$VM_SRC/Main.c" \
  $NVG_SRCS \
  "$TP"/chipmunk/src/*.c \
  "$TP"/pdfio/*.c \
  "$TP"/zlib/*.c \
  -o "$ROOT_DIR/Build/$OUT" \
  $NVG_LIBS $LIBS

echo "[build_vm] Build/$OUT generado"
