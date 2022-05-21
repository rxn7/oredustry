#pragma once

#include "core/Scene.h"
#include "Player.h"

namespace od {
	class GameScene : public Scene {
	public:
		GameScene();
		void Update(uint32_t deltaTime) override;
		void Draw() override;
	
	private:
		std::unique_ptr<Player> m_Player;
	};
}
