#pragma once

#include <string_view>
#include "../Core.h"

namespace od::UI {
	enum class TextAlign {
		Left = FC_ALIGN_LEFT,
		Center = FC_ALIGN_CENTER,
		Righ = FC_ALIGN_RIGHT
	};

	class Text {
	public:
		Text(FC_Font *font, float x, float y, const SDL_Color &color, std::string_view text, TextAlign align = TextAlign::Left);
		virtual ~Text();
		void Render();
		void SetText(std::string_view text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color &color);
		inline std::string_view GetText() const { return m_Text; }

	private:
		TextAlign m_Align;
		std::string m_Text = "";
		float m_X, m_Y;
		SDL_Color m_Color;
		SDL_Texture *m_Texture = nullptr;
		FC_Font *m_Font = nullptr;
	};
}
