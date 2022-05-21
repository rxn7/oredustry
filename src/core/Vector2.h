#pragma once

#include <cmath>
#include "Oredustry.h"

namespace od {
	struct Vector2 {
		float x, y;

		Vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}

		Vector2() {
			this->x = 0;
			this->y = 0;
		}

		inline static Vector2 ScreenCenter() {
			return Vector2(od::ScreenCenterX(), od::ScreenCenterY());
		}

		inline float Length() const {
			return sqrtf(x*x + y*y);
		}
	};
}
