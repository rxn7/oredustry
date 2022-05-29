#include "Image.h"
#include "core/rendering/Renderer.h"

od::UI::Image::Image(std::shared_ptr<od::Texture> texture, const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors) :
m_Rotation(0),
m_Texture(texture),
od::UI::UIElement(position, size, anchors) {
}

void od::UI::Image::Render() {
	ENSURE_VISIBLE

	// TODO: Use custom renderer
	// SDL_RenderCopyEx(od::Core::renderer, m_Texture, 0, &dest, m_Rotation, 0, SDL_FLIP_NONE);

	od::UI::UIElement::Render();
}
