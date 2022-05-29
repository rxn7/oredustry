#pragma once

#include "core/Entity.h"
#include "core/assets/Texture.h"

namespace od {
	class Sprite : public od::Entity {
	public:
		Sprite(std::shared_ptr<od::Texture> texture, const glm::f32vec2 &size = {-1,-1}, const glm::f32vec2 &position = {200,200});
		void Render() override;
	
	public:
		std::shared_ptr<od::Texture> m_Texture;
		glm::f32vec2 m_Size;
	};
}
