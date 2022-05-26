#pragma once

#include <memory>
#include <functional>
#include "UIElement.h"
#include "Text.h"

namespace od::UI {
	typedef std::function<void()> ButtonClickCallback;

	class Button : public UIElement {
	public:
		Button(std::string_view text, TTF_Font *font, ButtonClickCallback clickCallback, const glm::i32vec2 &position, const glm::i32vec2 &size, Anchors anchor = ANCHORS_CENTER);
		void ProcessEvent(const SDL_Event &event) override;
		void Render() override;
		void Update(uint32_t deltaTime) override;
		void SetText(std::string_view text);
		inline bool IsHovered() const { return m_Hovered; }
	private:
		ButtonClickCallback m_ClickCallback;
		bool m_Hovered;
		std::unique_ptr<od::UI::Text> m_Text;
	};
}
