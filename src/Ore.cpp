#include "Ore.h"
#include "core/Color.h"
#include "core/Game.h"
#include "core/assets/Texture.h"
#include "core/rendering/Renderer.h"

Ore::Ore(uint16_t maxHealth, glm::f32vec2 position) : m_MaxHealth(maxHealth), m_Health(maxHealth), od::Entity(position) {
	UpdateColor();
}

void Ore::Hit(uint16_t damage) {
	m_Health -= damage;

	if(m_Health <= 0) {
		m_Health = 0;
		Destroy();
	}

	UpdateColor();
}

void Ore::UpdateColor() {
	m_Color.a = static_cast<float>(m_Health) / static_cast<float>(m_MaxHealth) * 255;
}

void Ore::Render() {
	od::Texture *texture = od::Asset::GetAsset<od::Texture>("res/ore.png"); 
	od::Renderer::RenderQuadTextured(m_Position, {50,50}, texture->GetGLTexture().get(), m_Color);
	od::Renderer::RenderText(std::to_string(m_Health), od::Game::GetInstance()->GetFont(), m_Position, od::Colors::BLACK);
}
