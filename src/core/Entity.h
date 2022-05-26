#pragma once

#include "Libs.h"

namespace od {
	class Entity {
	public:
		Entity(const glm::f32vec2 &position = {0,0});
		virtual void Awake() {}
		virtual void Update(uint32_t deltaTime) {}
		virtual void Render() {}

	protected:
		glm::f32vec2 m_Position;
	};
}
