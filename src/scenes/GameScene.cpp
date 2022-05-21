#include "GameScene.h"

od::GameScene::GameScene() :
m_Player(new Player()) {
}

void od::GameScene::Update(uint32_t deltaTime) {
	m_Player->Update(deltaTime);
}

void od::GameScene::Draw() {
	m_Player->Render();
}
