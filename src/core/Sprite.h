#pragma once

#include "core/Core.h"

namespace od {
	class Sprite {
	public:
		Sprite(std::string_view texturePath, od::Vector2f size = {-1,-1}, od::Vector2f position = {0,0});
		Sprite(SDL_Texture *texture, od::Vector2f size = {-1,-1}, od::Vector2f position = {0,0});
		void Render();
		virtual ~Sprite();
	
	public:
		od::Vector2f m_Size;
		od::Vector2f m_Position;
		SDL_Texture *m_Texture;
		bool m_IsTextureOwner;
	};
}
