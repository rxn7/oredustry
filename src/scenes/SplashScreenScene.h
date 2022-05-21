#pragma once

#include <memory>
#include "Oredustry.h"
#include "core/ui/Texture.h"
#include "core/ui/Text.h"

namespace od {
	class SplashScreenScene : public Scene {
	public:
		SplashScreenScene();
		~SplashScreenScene();
		void Awake() override;
		void Update(uint32_t deltaTime, uint32_t timeSinceStart) override;
		void ProcessEvent(const SDL_Event &event) override;
		void Draw() override;
		void DrawUI() override;

	private:
		std::unique_ptr<od::UI::Texture> m_SpinnerTexture;
		std::unique_ptr<od::UI::Text> m_LoadingText;
		std::string m_LoadingTextDots;
		uint32_t m_LoadingTextDotTimer;
		uint32_t m_FakeLoadingTimer;
	};
}
