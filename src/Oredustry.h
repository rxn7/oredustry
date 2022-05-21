#pragma once
#include <iostream>
#include <memory>
#include <string_view>
#include "core/Core.h"
#include "core/Scene.h"
#define FONT_SIZE 16

namespace od {
	extern SDL_Renderer *renderer;
	extern SDL_Window *window;
	extern FC_Font *font;
	void Init();
	void Shutdown(int code = EXIT_SUCCESS, std::string_view reason = "");
	void Start();
	void SetScene(std::unique_ptr<Scene> scene);

	int32_t GetWindowWidth();
	int32_t GetWindowHeight();

	inline static float ScreenCenterX() {
		return od::GetWindowWidth() * 0.5f;
	}

	inline static float ScreenCenterY() {
		return od::GetWindowHeight() * 0.5f;
	}
}
