#pragma once

#include "Oredustry.h"
#include "core/ui/Image.h"
#include "core/ui/Button.h"

class MainMenuScene : public od::Scene {
public:
	MainMenuScene();

private:
	void StartGame();
	void ExitGame();
};
