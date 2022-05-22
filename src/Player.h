#pragma once

#include "core/Core.h"
#include "core/Sprite.h"

namespace od {
	class Player : public od::Sprite {
	public:
		Player();
		void Update(uint32_t deltaTime);
	};
}
