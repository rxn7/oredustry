#pragma once

#include <array>
#include "../Core.h"
#include "../Vector2.h"

#define ANCHORS_CENTER {od::UI::Anchor::Center, od::UI::Anchor::Center}
#define ANCHORS_START {od::UI::Anchor::Start, od::UI::Anchor::Start}
#define ANCHORS_END {od::UI::Anchor::End, od::UI::Anchor::End}

namespace od::UI {
	enum class Anchor {
		Center,
		Start,
		End,
	};

	typedef std::array<Anchor, 2> Anchors;

	class UIElement {
	public:
		virtual void Update(uint32_t deltaTime);
		virtual void Render() {}
		virtual void ProcessEvent(const SDL_Event &event) {}

	public:
		Anchors m_Anchors;
		od::Vector2i m_Position;
		od::Vector2i m_AnchoredPosition;
	};
}
