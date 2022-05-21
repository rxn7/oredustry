#include "Text.h"
#include "../../Oredustry.h"

od::UI::Text::Text(TTF_Font *font, const od::Vector2i &position, const SDL_Color &color, std::string_view text, od::UI::TextAlign align, Anchors anchors) : 
m_Font(font),
m_Texture(nullptr),
m_Align(align)  {
	m_Anchors = anchors;
	m_Position = position;
	SetColor(color);
	SetText(text);
}

od::UI::Text::~Text() {
	if(m_Texture)
		SDL_DestroyTexture(m_Texture);
}


void od::UI::Text::SetText(std::string_view text) {
	m_Text = text;
	RenderTexture();
}

void od::UI::Text::SetColor(const SDL_Color &color) {
	m_Color = color;
}

void od::UI::Text::RenderTexture() {
	if(m_Texture)
		SDL_DestroyTexture(m_Texture);

	SDL_Surface *surface = TTF_RenderUTF8_Solid_Wrapped(m_Font, m_Text.c_str(), m_Color, 0);
	m_Texture = SDL_CreateTextureFromSurface(od::renderer, surface);

	m_Size.x = surface->w;
	m_Size.y = surface->h;

	SDL_FreeSurface(surface);
	CalculateRect();
}

void od::UI::Text::CalculateRect() {
	m_Rect = {.y = m_AnchoredPosition.y, .w = m_Size.x, .h = m_Size.y};
	switch(m_Align) {
		case od::UI::TextAlign::Left:
			m_Rect.x = m_AnchoredPosition.x;
			break;

		case od::UI::TextAlign::Center:
			m_Rect.x = m_AnchoredPosition.x - m_Size.x * 0.5f;
			break;

		case od::UI::TextAlign::Right:
			m_Rect.x = m_AnchoredPosition.x - m_Size.x;
			break;
	}
}

void od::UI::Text::Render() {
	if(m_Texture)
		SDL_RenderCopy(od::renderer, m_Texture, 0, &m_Rect);
}
