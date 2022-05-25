OUT := bin/linux/oredustry
CC := clang++
CFLAGS := -std=c++17 -O2
LIBS := -lSDL2 -lSDL2_ttf -lSDL2_image
OBJ_DIR := obj/linux

include common.mk
