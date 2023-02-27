#include "Sprite.h"
#include "core/rendering/Renderer.h"

od::Sprite::Sprite(od::GLTexture *texture, const glm::f32vec2 &size, const glm::f32vec2 &position, const Color &color) :
m_Size(size),
m_Texture(texture),
m_Color(color),
od::Entity(position) {

}

void od::Sprite::Render() {
	od::Renderer::RenderTexture(m_Position, m_Size, m_Texture, m_Color);
}