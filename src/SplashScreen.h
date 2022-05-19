#pragma once

#include <memory>
#include "core/Scene.h"

namespace od {
	class SplashScreenScene : public Scene {
	public:
		void Awake() override;
		void Update(uint32_t frameDelta) override;
		void Draw(ALLEGRO_DISPLAY *display) override;
		void DrawUI(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) override;
	};
}
