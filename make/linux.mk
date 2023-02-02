CC := clang++
PLATFORM := linux
LDFLAGS += $(shell pkg-config --libs glfw3 glew) -lm

include make/shared.mk

all: setup compile