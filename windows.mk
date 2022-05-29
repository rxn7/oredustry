OUT := bin/windows/oredustry.exe
CC := x86_64-w64-mingw32-g++
CFLAGS := -std=c++20
OBJ_DIR := obj/windows
LIBS := -lSDL2 -lopengl32 -lglu32 -lglew32 -opengl

include common.mk
