#pragma once

#include <string_view>
#include "UIElement.h"
#include "../Core.h"
#include "../Vector2.h"
#include "UIElement.h"

namespace od::UI {
	class Texture : public UIElement {
	public:
		Texture(SDL_Texture *texture, const od::Vector2i &position, const od::Vector2i &size = {0,0}, const Anchors &anchors = ANCHORS_CENTER);
		Texture(std::string_view path, const od::Vector2i &position, const od::Vector2i &size, const Anchors &anchors = ANCHORS_CENTER);
		virtual ~Texture();
		void Render() override;

	public:
		float m_Rotation = 0;

	protected:
		bool m_IsTextureOwner;
		SDL_Texture *m_Texture;
	};
}
