#pragma once

#include "core/Libs.h"
#include "core/GLTexture.h"
#include "core/Font.h"
#include "core/Color.h"
#include "core/TextAlign.h"
#include "core/assets/TextureAtlas.h"
#include "core/rendering/Shader.h"

namespace od::Renderer {
	extern std::shared_ptr<od::Shader> ColorShader;
	extern std::shared_ptr<od::Shader> TextureShader;
	extern std::shared_ptr<od::Shader> TextureAtlasShader;
	extern std::shared_ptr<od::Shader> ColorSwapShader;
	extern std::shared_ptr<od::Shader> GlyphShader;

	void Init();

	void Begin2D();
	void End2D();
	void BeginUI();
	void EndUI();

	void RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color);
	void RenderTexture(const glm::f32vec2 &position, const glm::f32vec2 &size, od::GLTexture *texture, const od::Color &color);
	void RenderTexture(const glm::f32vec2 &position, const glm::f32vec2 &size, od::GLTexture *texture, const od::Color &color, Shader *shader);
	void RenderTextureAtlas(const glm::f32vec2 &position, const glm::f32vec2 &size, uint16_t frame, od::TextureAtlas *textureAtlas, const od::Color &color);
	void RenderText(const std::string &text, od::Font *font, const glm::f32vec2 &position, const od::Color &color, float scale=1, od::TextAlignHorizontal alignH=od::TextAlignHorizontal::Center, od::TextAlignVertical alignV=od::TextAlignVertical::Middle);

	extern uint32_t drawCalls;
}
