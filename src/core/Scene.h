#pragma once

#include "Core.h"

namespace od {
	class Scene {
	public:
		virtual void Awake() {}
		virtual void Update(uint32_t frameDelta, uint32_t timeSinceEpoch) {}
		virtual void Draw(ALLEGRO_DISPLAY *dislay) {}
		virtual void DrawUI(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {}
	};
}
