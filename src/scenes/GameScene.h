#pragma once

#include "Player.h"
#include "core/Scene.h"
#include "core/ui/ColorRect.h"
#include "Ore.h"

class GameScene : public od::Scene {
public:
	GameScene();
	void Update(uint32_t deltaTime) override;
	void Render2D() override;

private:
	void ExitToMenu();
	void ExitGame();
	void SpawnRandomOre();

private:
	std::unique_ptr<Player> m_Player;
	std::shared_ptr<od::UI::ColorRect> m_PauseRect;
	std::vector<Ore> m_Ores;
	bool m_Paused;
};
