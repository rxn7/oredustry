#pragma once
#include <iostream>
#include <memory>
#include <string_view>
#include "core/Core.h"
#include "core/Scene.h"
#include "core/Vector2.h"
#define FONT_SIZE 16

namespace od {
	extern SDL_Renderer *renderer;
	extern SDL_Window *window;
	extern FC_Font *font;

	void Init();
	void Start();
	void Shutdown(int code = EXIT_SUCCESS, std::string_view reason = "");
	void SetScene(std::unique_ptr<Scene> scene);

	int32_t GetWindowWidth();
	int32_t GetWindowHeight();
	uint32_t GetTimeSinceStart();

	od::Vector2i GetPointerPosition();

	inline float ScreenCenterX() {
		return od::GetWindowWidth() * 0.5f;
	}

	inline float ScreenCenterY() {
		return od::GetWindowHeight() * 0.5f;
	}

	inline static od::Vector2i ScreenCenter() {
		return od::Vector2i(od::ScreenCenterX(), od::ScreenCenterY());
	}
}
