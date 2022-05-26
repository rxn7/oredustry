#pragma once

#include "UIElement.h"

namespace od::UI {
	enum class TextAlign {
		Left,
		Center,
		Right
	};

	class Text : public UIElement {
	public:
		Text(TTF_Font *font, const glm::i32vec2 &position, const SDL_Color &color, std::string_view text, TextAlign align = TextAlign::Left, const Anchors &anchors = ANCHORS_CENTER);
		virtual ~Text();
		void Render() override;
		void SetText(std::string_view text);
		void SetColor(const SDL_Color &color);
		void SetPosition(const glm::i32vec2 &position);
		void RenderTexture();

		inline glm::i32vec2 GetSize() const { return m_Size; }
		inline std::string_view GetText() const { return m_Text; }

	private:
		TextAlign m_Align;
		std::string m_Text = "";
		TTF_Font *m_Font = nullptr;
		SDL_Color m_Color;
	};
}
