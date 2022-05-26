#include "Text.h"

od::UI::Text::Text(TTF_Font *font, const glm::i32vec2 &position, const SDL_Color &color, std::string_view text, od::UI::TextAlign align, const Anchors &anchors) : 
m_Font(font),
m_Align(align),
od::UI::UIElement(position, {0,0}, anchors) {
	m_Color = color;
	SetText(text);
}

od::UI::Text::~Text() {
}


void od::UI::Text::SetText(std::string_view text) {
	m_Text = text;
	RenderTexture();
}

void od::UI::Text::SetColor(const SDL_Color &color) {
	m_Color = color;
	RenderTexture();
}

void od::UI::Text::RenderTexture() {
	SDL_Surface *surface = TTF_RenderUTF8_Solid_Wrapped(m_Font, m_Text.c_str(), m_Color, 0);

	m_Size.x = surface->w;
	m_Size.y = surface->h;

	SDL_FreeSurface(surface);
}

void od::UI::Text::Render() {
	ENSURE_VISIBLE

	od::UI::UIElement::Render();
}
