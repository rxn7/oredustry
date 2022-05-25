#pragma once

#include "Vector2.h"

namespace od {
	class Entity {
	public:
		Entity(const Vector2f &position = {0,0});
		virtual void Awake() {}
		virtual void Update(uint32_t deltaTime) {}
		virtual void Render() {}

	protected:
		Vector2f m_Position;
	};
}
