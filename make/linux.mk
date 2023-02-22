.PHONY: ALL

CC := clang++
PLATFORM := linux
LDFLAGS += $(shell pkg-config --libs glfw3 glew openal)

include make/shared.mk

all: setup compile
