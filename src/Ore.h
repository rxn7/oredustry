#pragma once

#include "core/Entity.h"
#include "core/Color.h"
#include "core/GLTexture.h"
#include "core/Renderable.h"
#include <glm/fwd.hpp>

class Ore : public od::Entity, public od::Renderable {
public:
	Ore(uint16_t maxHealth, glm::f32vec2 position);
	void Hit(uint16_t damage);
	void Render() override;
	static void Init();
	static void RenderBatches();

public:
	bool m_IsHovered = false;
	static constexpr glm::f32vec2 SIZE = {50, 50};

private:
	uint16_t m_MaxHealth;
	uint16_t m_Health = 100;
	uint8_t m_DestroyStageFrame = 0;
};