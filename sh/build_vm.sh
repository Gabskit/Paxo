#!/usr/bin/env bash
set -e

echo "Compilando Lepvm (C23)..."

mkdir -p Build

clang -std=c23 -O3 -Wall -Wextra -ffixed-point \
  -D_POSIX_C_SOURCE=200809L \
  -I./Src/Vm \
  -I./Src/Vm/third_party/chipmunk \
  -I./Src/Vm/third_party/chipmunk/chipmunk \
  Src/Vm/Main.c \
  Src/Vm/third_party/chipmunk/src/*.c \
  -o Build/lep \
  -lm -ldl -rdynamic

echo "¡Compilación exitosa! Binario en: Build/lep"
