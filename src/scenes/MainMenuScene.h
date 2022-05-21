#pragma once

#include "Oredustry.h"
#include "core/ui/Texture.h"
#include "core/ui/Button.h"

namespace od {
	class MainMenuScene : public Scene {
	public:
		MainMenuScene();

	private:
		void StartGame();
		void ExitGame();
	};
}
