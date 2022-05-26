#include "GameScene.h"
#include "core/Input.h"

GameScene::GameScene() :
m_Player(new Player()),
m_PauseRect(new od::UI::ColorRect({200, 30, 50, 100}, {0,0}, {500,800}, ANCHORS_CENTER)),
od::Scene({255,255,255,255}) {
	m_PauseRect->m_Visible = false;
	AddUiElement(m_PauseRect);
}

void GameScene::Update(uint32_t deltaTime) {
	od::Scene::Update(deltaTime);

	if(od::Input::IsKeyJustPressed(SDLK_ESCAPE))
		m_PauseRect->m_Visible ^= 1;

	if(m_PauseRect->m_Visible) return;

	m_Player->Update(deltaTime);
}

void GameScene::Draw() {
	m_Player->Render();
}
