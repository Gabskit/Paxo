#!/usr/bin/env bash
set -e

echo "Compilando Lepvm (C23)..."

mkdir -p Build

clang -std=c23 -O3 \
  -I./Src/Vm \
  -I./Src/Vm/third_party/chipmunk \
  -I./Src/Vm/third_party/chipmunk/chipmunk \
  Src/Vm/Main.c \
  Src/Vm/third_party/chipmunk/src/*.c \
  -o Build/lep \
  -lm -ldl

echo "¡Compilación exitosa! Binario en: Build/lep"
