#include "MainMenuScene.h"
#include "GameScene.h"
#include "core/Game.h"

MainMenuScene::MainMenuScene() : od::Scene({255,255,255,255}) {
	AddUiElement(std::shared_ptr<od::UI::Image>(new od::UI::Image(std::make_unique<od::Texture>("res/title.png"), {0, 64}, {512, 128}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
	AddUiElement(std::shared_ptr<od::UI::Button>(new od::UI::Button("Start Game", od::Game::GetInstance()->GetFont(), std::bind(&MainMenuScene::StartGame, this), {0, 200}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
	AddUiElement(std::shared_ptr<od::UI::Button>(new od::UI::Button("Exit", od::Game::GetInstance()->GetFont(), std::bind(&MainMenuScene::ExitGame, this), {0, 300}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
}

void MainMenuScene::StartGame() {
	od::Game::GetInstance()->SetScene(std::make_unique<GameScene>());
}

void MainMenuScene::ExitGame() {
	od::Game::GetInstance()->Shutdown(false, "You pressed the Exit Game button");
}
