.PHONY: all

CC := x86_64-w64-mingw32-g++
PLATFORM := windows
INCFLAGS := -I/usr/x86_64-w64-mingw32/include -fstack-protector
CFLAGS := $(shell x86_64-w64-mingw32-pkg-config --static --cflags glfw3) -DGLEW_STATIC -DGLFW_STATIC -DGLEW_NO_GLU
LDFLAGS := -lglew32 -lglfw3 -lopengl32 --static -static-libgcc -static-libstdc++ -mwindows -fstack-protector -lssp

include make/shared.mk

all: setup compile