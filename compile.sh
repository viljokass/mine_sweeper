#!/usr/bin/bash
clang -c src/main.c src/field.c src/veil.c src/render.c
clang main.o field.o veil.o render.o -o minesweep
rm main.o field.o veil.o render.o
