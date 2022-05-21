#pragma once

#include <string_view>
#include "UIElement.h"
#include "../Vector2.h"
#include "../Core.h"

namespace od::UI {
	enum class TextAlign {
		Left = FC_ALIGN_LEFT,
		Center = FC_ALIGN_CENTER,
		Righ = FC_ALIGN_RIGHT
	};

	class Text : public UIElement {
	public:
		Text(FC_Font *font, const Vector2 &position, const SDL_Color &color, std::string_view text, TextAlign align = TextAlign::Left);
		virtual ~Text();
		void Render() override;
		void SetText(std::string_view text);
		void SetColor(const SDL_Color &color);
		inline std::string_view GetText() const { return m_Text; }

	private:
		TextAlign m_Align;
		std::string m_Text = "";
		SDL_Color m_Color;
		FC_Font *m_Font = nullptr;
	};
}
