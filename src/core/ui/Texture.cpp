#include "Texture.h"

od::UI::Texture::Texture(SDL_Texture *texture, const Vector2i &position, const Vector2i &size, const Anchors &anchors) :
m_IsTextureOwner(false),
m_Rotation(0),
m_Texture(texture),
od::UI::UIElement(position, size, anchors) {
}

od::UI::Texture::Texture(std::string_view path, const Vector2i &position, const Vector2i &size, const Anchors &anchors) : 
m_Rotation(0),
m_IsTextureOwner(true),
od::UI::UIElement(position, size, anchors) {
	m_Texture = od::Core::LoadTexture(path);
}

od::UI::Texture::~Texture() {
	if(m_IsTextureOwner)
		SDL_DestroyTexture(m_Texture);
}

void od::UI::Texture::Render() {
	ENSURE_VISIBLE

	SDL_Rect dest = {.w = static_cast<int32_t>(m_Size.x), .h = static_cast<int32_t>(m_Size.y) };
	dest.x = m_AnchoredPosition.x - dest.w * 0.5f;
	dest.y = m_AnchoredPosition.y - dest.h * 0.5f;
	
	SDL_RenderCopyEx(od::Core::renderer, m_Texture, 0, &dest, m_Rotation, 0, SDL_FLIP_NONE);

	od::UI::UIElement::Render();
}
