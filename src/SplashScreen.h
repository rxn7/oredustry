#pragma once

#include <memory>
#include "core/Scene.h"

namespace od {
	class SplashScreenScene : public Scene {
	public:
		~SplashScreenScene();
		void Awake() override;
		void Update(uint32_t deltaTime, uint32_t timeSinceEpoch) override;
		void Draw(ALLEGRO_DISPLAY *display) override;
		void DrawUI(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) override;
	};
}
