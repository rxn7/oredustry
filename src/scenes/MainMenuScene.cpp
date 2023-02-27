#include "MainMenuScene.h"
#include "GameScene.h"
#include "core/Game.h"
#include "core/Asset.h"
#include "core/rendering/Renderer.h"

MainMenuScene::MainMenuScene() : od::Scene({255,255,255,255}) {
	od::Font *font = od::Game::GetInstance()->GetFont();
	AddUiElement(std::shared_ptr<od::UI::Image>(new od::UI::Image(od::Asset::Get<od::Texture>("title")->GetGLTexture(), {0, 64}, {512, 128}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
	AddUiElement(std::shared_ptr<od::UI::Button>(new od::UI::Button(font, "Start Game", std::bind(&MainMenuScene::StartGame, this), {0, 200}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
	AddUiElement(std::shared_ptr<od::UI::Button>(new od::UI::Button(font, "Exit", std::bind(&od::Game::ShutdownWithoutReason, od::Game::GetInstance()), {0, 300}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
}

void MainMenuScene::StartGame() {
	od::Game::GetInstance()->SetScene(std::make_unique<GameScene>());
}
