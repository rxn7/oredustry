#pragma once

#include "core/Entity.h"
#include "core/Color.h"

class Ore : public od::Entity {
public:
	Ore(uint16_t maxHealth, glm::f32vec2 position);
	void Hit(uint16_t damage);
	void Render() override;

private:
	void UpdateColor();

private:
	uint16_t m_MaxHealth;
	uint16_t m_Health = 100;
	od::Color m_Color;
};
