#pragma once

#include "Libs.h"
#include "Vector2.h"
#include "Scene.h"

#define FONT_SIZE 16

namespace od::Core {
	extern SDL_Renderer *renderer;
	extern SDL_Window *window;
	extern TTF_Font *font;

	SDL_Texture *LoadTexture(std::string_view path);
	TTF_Font *LoadFont(std::string_view path, int32_t size);

	void Init();
	void Shutdown(int code=EXIT_SUCCESS, std::string_view reason="Unknown");
	void Start();
	void SetScene(std::unique_ptr<od::Scene>);

	float CalculateFrameDeltaTimeMilliFloat();
	uint32_t GetFrameDeltaTime();
	uint32_t GetTimeSinceStart();
	int32_t GetScreenWidth();
	int32_t GetScreenHeight();
	od::Vector2i GetPointerPosition();
	inline float GetScreenCenterX() { return od::Core::GetScreenWidth() * 0.5f; }
	inline float GetScreenCenterY() { return od::Core::GetScreenHeight() * 0.5f; }
	inline static od::Vector2i ScreenCenter() { return od::Vector2i(od::Core::GetScreenCenterX(), od::Core::GetScreenCenterY()); }
}
