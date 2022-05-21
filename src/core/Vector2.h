#pragma once

#include <cstdint>
#include <cmath>

namespace od {
	template<typename T>
	struct Vector2 {
		T x, y;

		Vector2(T x, T y) {
			this->x = x;
			this->y = y;
		}

		Vector2() {
			this->x = 0;
			this->y = 0;
		}

		inline float Length() const {
			return sqrtf(x*x + y*y);
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int32_t> Vector2i;
	typedef Vector2<uint32_t> Vector2u;
}
