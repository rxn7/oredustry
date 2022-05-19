#pragma once

#include "Core.h"

namespace od::Input {
	void Update();
	bool IsKeyPressed(uint8_t key);
	bool IsKeyJustPressed(uint8_t key);
}
