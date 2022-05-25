#include "GameScene.h"
#include "core/Input.h"

od::GameScene::GameScene() :
m_Player(new Player()),
m_PauseRect(new od::UI::ColorRect({200, 30, 50, 100}, {0,0}, {500,800}, ANCHORS_CENTER)){
	m_PauseRect->m_Visible = false;
	AddUiElement(m_PauseRect);
}

void od::GameScene::Update(uint32_t deltaTime) {
	od::Scene::Update(deltaTime);

	if(od::Input::IsKeyJustPressed(SDLK_ESCAPE))
		m_PauseRect->m_Visible ^= 1;

	if(!m_PauseRect->m_Visible) {
		m_Player->Update(deltaTime);
	}
}

void od::GameScene::Draw() {
	m_Player->Render();
}
