#pragma once

#include "core/Entity.h"
#include "core/Renderable.h"
#include "core/assets/Texture.h"
#include "core/Color.h"

namespace od {
	class Sprite : public od::Entity, public od::Renderable {
	public:
		Sprite(od::GLTexture *texture, const glm::f32vec2 &size = {100,100}, const glm::f32vec2 &position = {0,0}, const Color &color = Colors::WHITE);
		void Render() override;
	
	protected:
		od::GLTexture *m_Texture;
		glm::f32vec2 m_Size;
		Color m_Color;
	};
}