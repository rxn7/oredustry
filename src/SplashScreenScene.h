#pragma once

#include <memory>
#include "Oredustry.h"

namespace od {
	class SplashScreenScene : public Scene {
	public:
		SplashScreenScene();
		~SplashScreenScene();
		void Awake() override;
		void Update(uint32_t deltaTime, uint32_t timeSinceEpoch) override;
		void Draw() override;
		void DrawUI() override;

	private:
		SDL_Texture *m_Texture;
		SDL_Rect m_TextureRect;
		float m_TextureAngle;
		std::string m_LoadingTextDots;
		uint32_t m_LoadingTextDotTimer;
		std::unique_ptr<od::UI::Text> m_LoadingText;
	};
}
