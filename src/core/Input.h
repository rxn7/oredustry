#pragma once

#include "Core.h"

namespace od::Input {
	void Init();
	void Update();
	bool IsKeyPressed(SDL_KeyCode key);
	bool IsKeyJustPressed(SDL_KeyCode key);
}
