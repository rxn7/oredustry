OUT := bin/linux/oredustry
CC := clang++
CFLAGS := -std=c++20
OBJ_DIR := obj/linux
LIBS := -lglfw -lGL -lGLEW

include common.mk
