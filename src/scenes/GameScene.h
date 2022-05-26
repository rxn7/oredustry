#pragma once

#include "Player.h"
#include "core/Scene.h"
#include "core/ui/ColorRect.h"

class GameScene : public od::Scene {
public:
	GameScene();
	void Update(uint32_t deltaTime) override;
	void Draw() override;

private:
	std::unique_ptr<Player> m_Player;
	std::shared_ptr<od::UI::ColorRect> m_PauseRect;
	bool m_Paused;
};
