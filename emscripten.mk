OUT := bin/emscripten/oredustry.html
CC := em++
CFLAGS := -std=c++17 -O2 -sALLOW_MEMORY_GROWTH=1 -sUSE_WEBGL2=1 -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS="['png']" -sUSE_SDL_TTF=2 --embed-file res
OBJ_DIR := obj/emscripten

include common.mk
