#pragma once

#include "core/Libs.h"

namespace od {
	typedef glm::f32vec4 Color;

	namespace Colors {
		constexpr Color WHITE = {1.0f, 1.0f, 1.0f, 1.0f};
		constexpr Color BLACK = {0.0f, 0.0f, 0.0f, 1.0f};
		constexpr Color RED = {1.0f, 0.0f, 0.0f, 1.0f};
		constexpr Color GREEN = {0.0f, 1.0f, 0.0f, 1.0f};
		constexpr Color BLUE = {0.0f, 0.0f, 1.0f, 1.0f};
	}
}
