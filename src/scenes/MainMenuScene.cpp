#include "MainMenuScene.h"

od::MainMenuScene::MainMenuScene() : 
m_TitleTexture(new od::UI::Texture("res/title.png", od::Vector2(od::ScreenCenterX(), 64), {512, 128}, true)) {
}

od::MainMenuScene::~MainMenuScene() {
}

void od::MainMenuScene::Awake() {
}

void od::MainMenuScene::Update(uint32_t deltaTime, uint32_t timeSinceStart) {
}

void od::MainMenuScene::ProcessEvent(const SDL_Event &event) {
	if(event.type == SDL_WINDOWEVENT) 
			m_TitleTexture->m_Position.x = od::ScreenCenterX();
}

void od::MainMenuScene::Draw() {
}

void od::MainMenuScene::DrawUI() {
	m_TitleTexture->Render();
}
