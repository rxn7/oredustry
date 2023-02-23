#pragma once

#include "Player.h"
#include "core/Scene.h"
#include "core/ui/ColorRect.h"
#include "Ore.h"
#include "core/ui/Text.h"
#include <cstdint>

class GameScene : public od::Scene {
public:
	GameScene();
	void Update(uint32_t deltaTime) override;
	void Tick() override;
	void Render2D() override;

private:
	void ExitToMenu();
	void ExitGame();
	void SpawnOres();

private:
	std::unique_ptr<Player> m_Player;
	std::shared_ptr<od::UI::ColorRect> m_PauseRect;
	std::shared_ptr<od::UI::Text> m_ScoreText;
	std::vector<Ore> m_Ores;
	uint32_t m_Score = 0;
	bool m_Paused;
};
