#pragma once

#include "core/Libs.h"
#include "core/Color.h"

namespace od {
	struct Vertex {
		glm::f32vec2 position;
		glm::f32vec2 texCoord;
		od::Color color;

		Vertex(glm::f32vec2 position, glm::f32vec2 texCoord, od::Color color) : position(position), texCoord(texCoord), color(color) { }
	};
}
