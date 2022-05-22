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

		inline bool operator==(Vector2 &other) const {
			return x == other.x && y == other.y;
		}

		inline bool operator!=(Vector2 &other) const {
			return x != other.x || y != other.y;
		}

		inline void operator*=(Vector2 &other) {
			x *= other.x;
			y *= other.y;
		}

		inline void operator*=(float value) {
			x *= value;
			y *= value;
		}

		inline Vector2 operator*(Vector2 &other) const {
			return Vector2(x*other.x, y*other.y);
		}

		inline Vector2 operator*(float value) const {
			return Vector2(x*value, y*value);
		}

		inline Vector2 operator+(Vector2 &other) const {
			return Vector2(x+other.x, y+other.y);
		}

		inline void operator+=(Vector2 &other) {
			x += other.x;
			y += other.y;
		}

		inline Vector2 operator-(Vector2 &other) const {
			return Vector2(x-other.x, y-other.y);
		}

		inline void operator-=(Vector2 &other) {
			x -= other.x;
			y -= other.y;
		}

		inline Vector2 operator/(Vector2 &other) const {
			return Vector2(x/other.x, y/other.y);
		}

		inline Vector2 operator/(float value) const {
			return Vector2(x/value, y/value);
		}

		inline void operator/=(Vector2 &other) {
			x /= other.x;
			y /= other.y;
		}

		inline void operator/=(float value) {
			x /= value;
			y /= value;
		}

		inline float Length() const {
			return sqrtf(x*x + y*y);
		}

		inline void Normalize() {
			float len = Length();
			if(len != 0) {
				x /= len;
				y /= len;
			} else {
				x = 0;
				y = 0;
			}
		}
	};

	typedef Vector2<double> Vector2d;
	typedef Vector2<float> Vector2f;
	typedef Vector2<int32_t> Vector2i;
	typedef Vector2<uint32_t> Vector2u;
}
