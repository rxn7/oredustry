#pragma once

#include "UIElement.h"
#include "core/Color.h"
#include "core/TextAlign.h"
#include "core/assets/Font.h"

namespace od::UI {
	class Text : public UIElement {
	public:
		Text(od::Font *font, const glm::i32vec2 &position, const std::string_view &text, float scale, const od::Color &color = od::Colors::WHITE, TextAlignHorizontal alignH = TextAlignHorizontal::Left, TextAlignVertical alignV = TextAlignVertical::Top, const Anchors &anchors = ANCHORS_CENTER);
		~Text();

		void Render() override;

	public:
		TextAlignHorizontal m_AlignHorizontal;
		TextAlignVertical m_AlignVertical;
		std::string m_Text;
		od::Color m_Color;

	private:
		float m_Scale;
		od::Font *m_Font;
	};
}
