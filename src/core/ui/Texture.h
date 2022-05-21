#pragma once

#include <string_view>
#include "UIElement.h"
#include "../Core.h"
#include "../Vector2.h"
#include "UIElement.h"

namespace od::UI {
	class Texture : public UIElement {
	public:
		Texture(SDL_Texture *texture, const od::Vector2 &position, const od::Vector2 &size = Vector2(), bool centered=true);
		Texture(std::string_view path, const od::Vector2 &position, const od::Vector2 &size, bool centered=true);
		virtual ~Texture();
		void Render() override;

	public:
		float m_Rotation;
		bool m_Centered;

	protected:
		bool m_IsTextureOwner;
		od::Vector2 m_Size;
		SDL_Texture *m_Texture;
	};
}
