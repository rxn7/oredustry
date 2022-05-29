#pragma once

#include "core/Libs.h"
#include "core/assets/Texture.h"
#include "core/Color.h"

namespace od::Renderer {
	enum class TextureShaderType {
		Normal,
		ColorSwap,
	};

	void Init();

	void Begin2D();
	void End2D();
	void BeginUI();
	void EndUI();

	void RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color);
	void RenderQuadTextured(const glm::f32vec2 &position, const glm::f32vec2 &size, const std::shared_ptr<od::Texture> &texture, const od::Color &color, TextureShaderType shaderType = TextureShaderType::Normal);
}
