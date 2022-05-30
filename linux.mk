OUT := bin/linux/oredustry
CC := clang++
INC := -I/usr/include/freetype2
CFLAGS := -std=c++20
OBJ_DIR := obj/linux
LIBS := -lglfw -lGL -lGLEW -lfreetype

include common.mk
