#include "ColorRect.h"
#include "core/rendering/Renderer.h"

od::UI::ColorRect::ColorRect(const SDL_Colour &color, const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors) : 
od::UI::UIElement(position, size, anchors),
m_Color(color) {
}

void od::UI::ColorRect::Render() {
	ENSURE_VISIBLE

	od::Renderer::RenderQuad(m_AnchoredPosition, m_Size, m_Color);

	od::UI::UIElement::Render();
}
