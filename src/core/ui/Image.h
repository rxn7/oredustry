#pragma once

#include <string_view>
#include "UIElement.h"
#include "core/assets/Texture.h"

namespace od::UI {
	class Image : public UIElement {
	public:
		Image(std::shared_ptr<od::GLTexture> texture, const glm::i32vec2 &position, const glm::i32vec2 &size = {0,0}, const Anchors &anchors = ANCHORS_CENTER);
		void Render() override;

	public:
		float m_Rotation = 0;

	protected:
		std::shared_ptr<od::GLTexture> m_Texture;
	};
}
