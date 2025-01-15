#!/usr/bin/bash
clang -c src/main.c src/field.c
clang main.o field.o -o minesweep
rm main.o field.o
