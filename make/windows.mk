.PHONY: copy_dlls all

CC := x86_64-w64-mingw32-gcc
PLATFORM := windows

include make/shared.mk

all: setup compile