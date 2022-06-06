#include "GameScene.h"
#include "core/Input.h"
#include "core/ui/Button.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"
#include "MainMenuScene.h"

GameScene::GameScene() :
m_Player(new Player()),
m_PauseRect(new od::UI::ColorRect({200, 200, 200, 128}, {0,0}, {500,700}, ANCHORS_CENTER)),
od::Scene({255,255,255,255}) {
	m_PauseRect->m_Visible = false;
	od::Font *font = od::Game::GetInstance()->GetFont();
	m_PauseRect->AddChildElement(std::shared_ptr<od::UI::Button>(new od::UI::Button(font, "Exit to menu", std::bind(&GameScene::ExitToMenu, this), {0, 100}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::End})));
	m_PauseRect->AddChildElement(std::shared_ptr<od::UI::Button>(new od::UI::Button(font, "Exit to desktop", std::bind(&od::Game::ShutdownWithoutReason, od::Game::GetInstance()), {0, 20}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::End})));
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
	od::Renderer::RenderQuad({0,0}, {50,50}, {255, 0, 255, 255});
	od::Renderer::RenderText("Reference Object", Oredustry::GetInstance()->GetFont(), {0,0}, {50, 200, 164, 255}, 1.0f);

	m_Player->Render();
}

void GameScene::ExitToMenu() {
	od::Game::GetInstance()->SetScene(std::make_unique<MainMenuScene>());
}
