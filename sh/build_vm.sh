#!/usr/bin/env bash
set -e

echo "Compilando Lepvm (C23)..."

mkdir -p Build

gcc-15 -std=gnu23 -O3 \
  -I./Src/Vm/Src \
  -I./Src/Vm/Src/third_party/chipmunk \
  -I./Src/Vm/Src/third_party/chipmunk/chipmunk \
  Src/Vm/Src/Main.c \
  Src/Vm/Src/third_party/chipmunk/src/*.c \
  -o Build/lep \
  -lm -ldl

echo "¡Compilación exitosa! Binario en: Build/lep"
