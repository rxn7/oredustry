#pragma once

#include "../Vector2.h"

namespace od::UI {
	class UIElement {
	public:
		virtual void Render() {}

	public:
		Vector2 m_Position;
	};
}
