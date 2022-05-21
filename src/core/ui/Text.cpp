#include "Text.h"
#include "../../Oredustry.h"

od::UI::Text::~Text() {
}

od::UI::Text::Text(FC_Font *font, const od::Vector2 &position, const SDL_Color &color, std::string_view text, od::UI::TextAlign align) : 
m_Font(font),
m_Align(align)  {
	m_Position = position;
	SetColor(color);
	SetText(text);
}

void od::UI::Text::SetText(std::string_view text) {
	m_Text = text;
}

void od::UI::Text::SetColor(const SDL_Color &color) {
	m_Color = color;
}

void od::UI::Text::Render() {
	FC_DrawAlign(m_Font, od::renderer, m_Position.x, m_Position.y, (FC_AlignEnum)m_Align, m_Text.c_str());
}
