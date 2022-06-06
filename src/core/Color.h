#pragma once

#include "core/Libs.h"

namespace od {
	typedef glm::u8vec4 Color;

	namespace Colors {
		constexpr od::Color WHITE = {255, 255, 255, 255};
		constexpr od::Color BLACK = {0, 0, 0, 255};
		constexpr od::Color RED = {255, 0, 0, 255};
		constexpr od::Color GREEN = {0, 255, 0, 255};
		constexpr od::Color BLUE = {0, 0, 255, 255};
	}
}
