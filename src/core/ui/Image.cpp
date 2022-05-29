#include "Image.h"
#include "core/rendering/Renderer.h"

od::UI::Image::Image(std::shared_ptr<od::Texture> texture, const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors) :
m_Rotation(0),
m_Texture(texture),
od::UI::UIElement(position, size, anchors) {
}

void od::UI::Image::Render() {
	ENSURE_VISIBLE

	od::Renderer::RenderQuadTextured(m_AnchoredPosition, m_Size, m_Texture, {1.0f, 1.0f, 1.0f, 1.0f});

	od::UI::UIElement::Render();
}
