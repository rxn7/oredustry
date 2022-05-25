#pragma once

#include <vector>
#include <array>
#include "../Libs.h"
#include "../Vector2.h"
#include "Anchor.h"

#define ENSURE_VISIBLE if(!m_Visible) return;

namespace od::UI {
	class UIElement {
	public:
		UIElement(const od::Vector2i &position, const od::Vector2i &size, const Anchors &anchors);
		void UpdateAnchoredPosition();
		void AddChildElement(std::shared_ptr<od::UI::UIElement> element);
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
		od::Vector2i m_Position;
		od::Vector2i m_AnchoredPosition;
		od::Vector2i m_Size;
	};
}
