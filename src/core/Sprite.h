#pragma once

#include "core/Entity.h"
#include "core/assets/Texture.h"

namespace od {
	class Sprite : public od::Entity {
	public:
		Sprite(std::shared_ptr<od::GLTexture> texture, const glm::f32vec2 &size = {100,100}, const glm::f32vec2 &position = {0,0});
		void Render() override;
	
	public:
		std::shared_ptr<od::GLTexture> m_Texture;
		glm::f32vec2 m_Size;
	};
}
