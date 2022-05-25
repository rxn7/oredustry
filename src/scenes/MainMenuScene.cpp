#include "MainMenuScene.h"
#include "GameScene.h"

od::MainMenuScene::MainMenuScene() {
	AddUiElement(std::shared_ptr<od::UI::Texture>(new od::UI::Texture("res/title.png", od::Vector2i(0, 64), {512, 128}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
	AddUiElement(std::shared_ptr<od::UI::Button>(new od::UI::Button("Start Game", std::bind(&MainMenuScene::StartGame, this), od::Vector2i(0, 200), {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
	AddUiElement(std::shared_ptr<od::UI::Button>(new od::UI::Button("Exit", std::bind(&MainMenuScene::ExitGame, this), od::Vector2i(0, 300), {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::Start})));
}

void od::MainMenuScene::StartGame() {
	od::Core::SetScene(std::unique_ptr<od::Scene>(new GameScene()));

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
}

void od::MainMenuScene::ExitGame() {
	od::Core::Shutdown(0, "You pressed the Exit Game button");
}
