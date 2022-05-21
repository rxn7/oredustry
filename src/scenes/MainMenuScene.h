#pragma once

#include "Oredustry.h"
#include "core/ui/Texture.h"

namespace od {
	class MainMenuScene : public Scene {
	public:
		MainMenuScene();
		~MainMenuScene();
		void Awake() override;
		void Update(uint32_t deltaTime, uint32_t timeSinceStart) override;
		void ProcessEvent(const SDL_Event &event) override;
		void Draw() override;
		void DrawUI() override;

	private:
		std::unique_ptr<od::UI::Texture> m_TitleTexture;
	};
}
