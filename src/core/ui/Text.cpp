#include "Text.h"
#include "../../Oredustry.h"

od::UI::Text::~Text() {
	if(m_Texture)
		SDL_DestroyTexture(m_Texture);
}

od::UI::Text::Text(FC_Font *font, float x, float y, const SDL_Color &color, std::string_view text, od::UI::TextAlign align) : m_Font(font), m_Align(align)  {
	SetColor(color);
	SetPosition(x, y);
	SetText(text);
}

void od::UI::Text::SetPosition(float x, float y) {
	m_X = x;
	m_Y = y;
}

void od::UI::Text::SetText(std::string_view text) {
	m_Text = text;
}

void od::UI::Text::SetColor(const SDL_Color &color) {
	m_Color = color;
}

void od::UI::Text::Render() {
	FC_DrawAlign(m_Font, od::renderer, m_X, m_Y, (FC_AlignEnum)m_Align, m_Text.c_str());
}
