#pragma once
#include <iostream>
#include <memory>
#include <string_view>
#include "core/Core.h"
#define FONT_SIZE 16

namespace od {
	extern SDL_Renderer *renderer;
	extern SDL_Window *window;
	extern TTF_Font *font;
	void Init();
	void Shutdown(int code = EXIT_SUCCESS, std::string_view reason = "");
	void Start();
	void LoadScene(std::unique_ptr<Scene> scene);
	int32_t GetWindowWidth();
	int32_t GetWindowHeight();
}
