#include "Image.h"
#include "core/rendering/Renderer.h"

od::UI::Image::Image(std::shared_ptr<od::GLTexture> texture, const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors) :
m_Rotation(0),
m_Texture(texture),
od::UI::UIElement(position, size, anchors) {
}

void od::UI::Image::Render() {
	ENSURE_VISIBLE;
	od::Renderer::RenderTexture(m_AnchoredPosition, m_Size, m_Texture.get(), od::Colors::WHITE);
	od::UI::UIElement::Render();
}
