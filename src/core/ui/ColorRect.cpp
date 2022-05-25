#include "ColorRect.h"
#include "../Core.h"

od::UI::ColorRect::ColorRect(const SDL_Colour &color, const od::Vector2i &position, const od::Vector2i &size, const Anchors &anchors) : 
od::UI::UIElement(position, size, anchors),
m_Color(color) {
}

void od::UI::ColorRect::Render() {
	ENSURE_VISIBLE

	SDL_Rect rect = { 
		.x = static_cast<int32_t>(m_AnchoredPosition.x - m_Size.x * 0.5f),
		.y = static_cast<int32_t>(m_AnchoredPosition.y - m_Size.y * 0.5f),
		.w = m_Size.x,
		.h = m_Size.y,
	};

	SDL_SetRenderDrawColor(od::Core::renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	SDL_RenderFillRect(od::Core::renderer, &rect);

	od::UI::UIElement::Render();
}
