#pragma once

#include "Libs.h"

namespace od::Renderer {
	void Init();
	void RenderQuad(const glm::vec2 &position, const glm::vec2 &size, const SDL_Color &color);
}
