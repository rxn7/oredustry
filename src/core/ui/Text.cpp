#include "Text.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"

od::UI::Text::Text(od::Font *font, const glm::i32vec2 &position, const std::string_view &text, float scale, const od::Color &color, TextAlignHorizontal alignH, TextAlignVertical alignV, const Anchors &anchors) :
m_Font(font),
m_AlignHorizontal(alignH),
m_AlignVertical(alignV),
m_Scale(scale),
m_Text(text),
od::UI::UIElement(position, {0,0}, anchors) {
	m_Color = color;
}

od::UI::Text::~Text() {
}

void od::UI::Text::Render() {
	ENSURE_VISIBLE
	od::Renderer::RenderText(m_Text, m_Font, m_AnchoredPosition, m_Color, m_Scale, m_AlignHorizontal, m_AlignVertical);
	od::UI::UIElement::Render();
}
