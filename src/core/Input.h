#pragma once

#include "Libs.h"

namespace od::Input {
	void Init();
	void EndFrame();
	bool IsKeyPressed(int key);
	bool IsKeyJustPressed(int key);
	bool IsButtonPressed(int btn);
	bool IsButtonJustPressed(int btn);
}
