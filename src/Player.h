#pragma once

#include "core/Core.h"

namespace od {
	class Player {
	public:
		Player();
		void Update(uint32_t deltaTime);
		void Render();

	private:
		SDL_Texture *m_Texture; // TODO: Sprite class
	};
}
