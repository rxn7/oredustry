#include "GameScene.h"
#include "core/Input.h"
#include "core/ui/Button.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"

GameScene::GameScene() :
m_Player(new Player()),
m_PauseRect(new od::UI::ColorRect({0.5f, 0.5f, 0.5f, 0.6f}, {0,0}, {500,800}, ANCHORS_CENTER)),
od::Scene({255,255,255,255}) {
	m_PauseRect->m_Visible = false;
	m_PauseRect->AddChildElement(std::shared_ptr<od::UI::Button>(new od::UI::Button("Exit", std::bind(&od::Game::ShutdownWithoutReason, od::Game::GetInstance()), {0, 20}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::End})));
	AddUiElement(m_PauseRect);
}

void GameScene::Update(uint32_t deltaTime) {
	od::Scene::Update(deltaTime);

	if(od::Input::IsKeyJustPressed(GLFW_KEY_ESCAPE))
		m_PauseRect->m_Visible ^= 1;

	if(m_PauseRect->m_Visible) return;

	m_Player->Update(deltaTime);
}

void GameScene::Draw() {
	// Reference object
	od::Renderer::RenderQuad({0,0}, {50,50}, {0.5f, 0.2f, 0.9f, 1.0f});

	m_Player->Render();
}
