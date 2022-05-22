#include "Sprite.h"

od::Sprite::Sprite(std::string_view texturePath, od::Vector2f size, od::Vector2f position) :
m_Size(size),
m_IsTextureOwner(true) {
	m_Texture = od::Core::LoadTexture(texturePath);
	if(m_Size.x < 0 || m_Size.y < 0) {
		int w, h;
		SDL_QueryTexture(m_Texture, 0, 0, &w, &h);
		m_Size.x = w;
		m_Size.y = h;
	}
}

od::Sprite::Sprite(SDL_Texture *texture, od::Vector2f size, od::Vector2f position) :
m_Texture(texture),
m_IsTextureOwner(false) {
	if(m_Size.x < 0 || m_Size.y < 0)
		SDL_QueryTexture(m_Texture, 0, 0, reinterpret_cast<int32_t*>(&m_Size.x), reinterpret_cast<int32_t*>(&m_Size.y));
}

od::Sprite::~Sprite() {
	if(m_IsTextureOwner)
		SDL_DestroyTexture(m_Texture);
}

void od::Sprite::Render() {
	SDL_FRect rect = {.x = m_Position.x - m_Size.x * 0.5f, .y = m_Position.y - m_Size.y * 0.5f, .w = m_Size.x, .h = m_Size.y };
	SDL_RenderCopyF(od::Core::renderer, m_Texture, 0, &rect);
}
