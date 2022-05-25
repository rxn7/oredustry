#pragma once

#include "core/Core.h"
#include "core/Entity.h"

namespace od {
	class Sprite : public od::Entity {
	public:
		Sprite(std::string_view texturePath, const od::Vector2f &size = {-1,-1}, const od::Vector2f &position = {0,0});
		Sprite(SDL_Texture *texture, const od::Vector2f &size = {-1,-1}, const od::Vector2f &position = {0,0});
		void Render() override;
		virtual ~Sprite();
	
	public:
		od::Vector2f m_Size;
		SDL_Texture *m_Texture;
		bool m_IsTextureOwner;
	};
}
