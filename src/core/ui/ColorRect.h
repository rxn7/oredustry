#pragma once

#include "UIElement.h"

namespace od::UI {
	class ColorRect : public UIElement {
	public:
		ColorRect(const SDL_Colour &color, const glm::i32vec2 &position={0,0}, const glm::i32vec2 &size={10,10}, const Anchors &anchors = ANCHORS_CENTER);
		void Render() override;

	private:
		SDL_Color m_Color;
	};
}
