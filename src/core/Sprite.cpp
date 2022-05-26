#include "Sprite.h"

od::Sprite::Sprite(std::shared_ptr<od::Texture> texture, const glm::f32vec2 &size, const glm::f32vec2 &position) :
m_Size(size),
m_Texture(texture),
od::Entity(position) {
	if(m_Size.x < 0 || m_Size.y < 0) {
		m_Size.x = texture->GetWidth();
		m_Size.y = texture->GetHeight();
	}
}

void od::Sprite::Render() {
}
