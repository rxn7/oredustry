#pragma once

#include "Color.h"
#include <glm/fwd.hpp>

namespace od {
	struct Quad {
		glm::f32vec2 position;
		glm::f32vec2 size;
		Color color;	
	};
}