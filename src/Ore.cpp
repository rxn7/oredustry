#include "Ore.h"
#include "core/Game.h"
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
	m_Color.g = static_cast<float>(m_Health) / static_cast<float>(m_MaxHealth) * 255;
	m_Color.r = 255 - m_Color.g;
	m_Color.b = 0;
	m_Color.a = 255;
}

void Ore::Render() {
	od::Renderer::RenderQuad(m_Position, {50,50}, m_Color);
	od::Renderer::RenderText(std::to_string(m_Health), od::Game::GetInstance()->GetFont(), m_Position, od::Colors::BLACK);
}
