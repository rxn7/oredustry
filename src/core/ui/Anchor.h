#pragma once

#include <array>

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
}
