OUT := bin/linux/oredustry
CC := clang++
CFLAGS := -std=c++20 -O2
LIBS := -lSDL2 -lSDL2_ttf -lSDL2_image -lGL
OBJ_DIR := obj/linux

include common.mk
