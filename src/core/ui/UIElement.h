#pragma once

#include <vector>
#include <array>
#include "../Libs.h"
#include "Anchor.h"

#define ENSURE_VISIBLE if(!m_Visible) return;

namespace od::UI {
	class UIElement {
	public:
		UIElement(const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors);
		void UpdateAnchoredPosition();
		void AddChildElement(const std::shared_ptr<od::UI::UIElement> &element);
		virtual void Awake() {}
		virtual void Render() {}
		virtual void Update(uint32_t deltaTime) {}
		virtual void ProcessEvent(const SDL_Event &event) {}
		void ProcessEventChildren(const SDL_Event &event);
		void UpdateChildren(uint32_t deltaTime);
		void RenderChildren();

	public:
		std::vector<std::shared_ptr<od::UI::UIElement>> m_Children;
		bool m_Visible = true;
		Anchors m_Anchors;
		glm::i32vec2 m_Position;
		glm::i32vec2 m_AnchoredPosition;
		glm::i32vec2 m_Size;
	};
}
