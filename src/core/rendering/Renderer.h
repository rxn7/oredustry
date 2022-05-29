#pragma once

#include "core/Libs.h"
#include "core/assets/Texture.h"

namespace od::Renderer {
	void Init();
	void RenderQuad(const glm::i32vec2 &position, const glm::i32vec2 &size, const SDL_Color &color);
	void RenderQuadTextured(const glm::i32vec2 &position, const glm::i32vec2 &size, const std::shared_ptr<od::Texture> &texture, const SDL_Color &color);
	void Begin2D();
	void End2D();
	void BeginUI();
	void EndUI();
}
