#pragma once

#include <memory>
#include "core/Scene.h"

namespace od {
	class SplashScreenScene : public Scene {
	public:
		~SplashScreenScene();
		void Awake() override;
		void Update(uint32_t deltaTime, uint32_t timeSinceEpoch) override;
		void Draw() override;
		void DrawUI() override;
	};
}
