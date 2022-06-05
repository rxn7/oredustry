#pragma once

#include <memory>
#include <functional>
#include "UIElement.h"
#include "Text.h"

namespace od::UI {
	typedef std::function<void()> ButtonClickCallback;

	class Button : public UIElement {
	public:
		Button(od::Font *font, std::string_view text, ButtonClickCallback clickCallback, const glm::i32vec2 &position, const glm::i32vec2 &size, Anchors anchor = ANCHORS_CENTER);
		void Render() override;
		void Update(uint32_t deltaTime) override;
		inline bool IsHovered() const { return m_Hovered; }
		void SetText(const std::string_view &text);

	private:
		std::string m_Text;
		od::Font *m_Font;
		ButtonClickCallback m_ClickCallback;
		bool m_Hovered;
	};
}
