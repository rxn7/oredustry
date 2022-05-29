OUT := bin/windows/oredustry.exe
CC := x86_64-w64-mingw32-g++
CFLAGS := -std=c++17 -O2
LIBS := -lSDL2 -lSDL2_ttf -lSDL2_image -lGL -lGLEW
OBJ_DIR := obj/windows

include common.mk
