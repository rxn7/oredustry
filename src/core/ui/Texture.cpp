#include "Texture.h"
#include "Oredustry.h"

od::UI::Texture::Texture(SDL_Texture *texture, const Vector2 &position, const Vector2 &size, bool centered) :
m_IsTextureOwner(false),
m_Texture(texture),
m_Centered(centered),
m_Size(size) {
	m_Position = position;
}

od::UI::Texture::Texture(std::string_view path, const Vector2 &position, const Vector2 &size, bool centered) : 
m_IsTextureOwner(true),
m_Centered(centered),
m_Size(size) {
	m_Position = position;
	m_Texture = IMG_LoadTexture(od::renderer, path.data());
}

od::UI::Texture::~Texture() {
	if(m_IsTextureOwner)
		SDL_DestroyTexture(m_Texture);
}

void od::UI::Texture::Render() {
	SDL_Rect dest = {.w = static_cast<int32_t>(m_Size.x), .h = static_cast<int32_t>(m_Size.y) };

	if(m_Centered) {
		dest.x = m_Position.x - dest.w * 0.5f;
		dest.y = m_Position.y - dest.h * 0.5f;
	} else {
		dest.x = m_Position.x;
		dest.y = m_Position.y;
	}

	SDL_RenderCopyEx(od::renderer, m_Texture, 0, &dest, m_Rotation, 0, SDL_FLIP_NONE);
}
