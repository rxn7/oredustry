#include "Text.h"
#include "../../Oredustry.h"

od::UI::Text::~Text() {
	if(m_Texture)
		SDL_DestroyTexture(m_Texture);
}

od::UI::Text::Text(TTF_Font *font, float x, float y, const SDL_Color &color, std::string_view text) : m_Font(font)  {
	SetColor(color, false);
	SetPosition(x, y, false);
	SetText(text);
}

void od::UI::Text::SetPosition(float x, float y, bool renderTexture) {
	m_Rect.x = x;
	m_Rect.y = y;
	if(renderTexture)
		RenderTexture();
}

void od::UI::Text::SetText(std::string_view text, bool renderTexture) {
	m_Text = text;
	if(renderTexture)
		RenderTexture();
}

void od::UI::Text::SetColor(const SDL_Color &color, bool renderTexture) {
	m_Color = color;
	if(renderTexture)
		RenderTexture();
}

void od::UI::Text::Render() {
	SDL_RenderCopy(od::renderer, m_Texture, nullptr, &m_Rect);
}

void od::UI::Text::RenderTexture() {
	SDL_Surface *surface = TTF_RenderText_Solid_Wrapped(font, m_Text.c_str(), m_Color, 0); 
	if(!surface) {
		od::LogError("Failed to create text surface");
		return;
	}

	m_Texture = SDL_CreateTextureFromSurface(od::renderer, surface);
	if(!m_Texture) {
		od::LogError("Failed to create text texture");
		return;
	}

	SDL_FreeSurface(surface);
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Rect.w, &m_Rect.h);
}
