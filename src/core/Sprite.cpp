#include "Sprite.h"
#include "core/rendering/Renderer.h"

od::Sprite::Sprite(std::shared_ptr<od::GLTexture> texture, const glm::f32vec2 &size, const glm::f32vec2 &position) :
m_Size(size),
m_Texture(texture),
od::Entity(position) {
}

void od::Sprite::Render() {
	od::Renderer::RenderQuadTextured(m_Position, m_Size, m_Texture, {1.0f,1.0f,1.0f,1.0f});
}
