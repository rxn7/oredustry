#pragma once

#include <string_view>
#include "../Core.h"

namespace od::UI {
	class Text {
	public:
		Text() {}
		Text(TTF_Font *font, float x, float y, const SDL_Color &color, std::string_view text);
		virtual ~Text();
		void Render();
		void SetText(std::string_view text, bool renderTexture=true);
		void SetPosition(float x, float y, bool renderTexture=true);
		void SetColor(const SDL_Color &color, bool renderTexture=true);
		inline std::string_view GetText() const { return m_Text; }
	
	private:
		void RenderTexture();

	private:
		std::string m_Text = "";
		SDL_Rect m_Rect = {0};
		SDL_Color m_Color;
		SDL_Texture *m_Texture = nullptr;
		TTF_Font *m_Font = nullptr;
	};
}
