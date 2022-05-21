#include "Texture.h"
#include "Oredustry.h"

od::UI::Texture::Texture(SDL_Texture *texture, const Vector2i &position, const Vector2i &size, std::array<Anchor, 2> axisPositions) :
m_IsTextureOwner(false),
m_Texture(texture),
m_Rotation(0),
m_Size(size) {
	m_Anchors = axisPositions;
	m_Position = position;
}

od::UI::Texture::Texture(std::string_view path, const Vector2i &position, const Vector2i &size, std::array<Anchor, 2> axisPositions) : 
m_IsTextureOwner(true),
m_Rotation(0),
m_Size(size) {
	m_Anchors = axisPositions;
	m_Position = position;
	m_Texture = IMG_LoadTexture(od::renderer, path.data());
}

od::UI::Texture::~Texture() {
	if(m_IsTextureOwner)
		SDL_DestroyTexture(m_Texture);
}

void od::UI::Texture::Render() {
	SDL_Rect dest = {.w = static_cast<int32_t>(m_Size.x), .h = static_cast<int32_t>(m_Size.y) };
	dest.x = m_AnchoredPosition.x - dest.w * 0.5f;
	dest.y = m_AnchoredPosition.y - dest.h * 0.5f;
	
	SDL_RenderCopyEx(od::renderer, m_Texture, 0, &dest, m_Rotation, 0, SDL_FLIP_NONE);
}
