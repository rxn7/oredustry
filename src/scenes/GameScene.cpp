#include "GameScene.h"
#include "core/Asset.h"
#include "core/Input.h"
#include "core/TextAlign.h"
#include "core/assets/Texture.h"
#include "core/ui/Anchor.h"
#include "core/ui/Button.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"
#include "MainMenuScene.h"
#include "core/ui/Text.h"

GameScene::GameScene() :
m_Player(new Player()),
m_PauseRect(new od::UI::ColorRect({200, 200, 200, 128}, {0,0}, {500,700}, ANCHORS_CENTER)),
m_ScoreText(new od::UI::Text(od::Game::GetInstance()->GetFont(), {0,0}, "Score: 0", 1.0f, od::Colors::BLACK, od::TextAlignHorizontal::Center, od::TextAlignVertical::Top, {od::UI::Anchor::Center, od::UI::Anchor::Start})),
od::Scene({255,255,255,255}) {
	m_PauseRect->m_Visible = false;

	od::Font *font = od::Game::GetInstance()->GetFont();

	m_PauseRect->AddChildElement(std::shared_ptr<od::UI::Button>(new od::UI::Button(font, "Exit to menu", std::bind(&GameScene::ExitToMenu, this), {0, 100}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::End})));
	m_PauseRect->AddChildElement(std::shared_ptr<od::UI::Button>(new od::UI::Button(font, "Exit to desktop", std::bind(&od::Game::ShutdownWithoutReason, od::Game::GetInstance()), {0, 20}, {150, 60}, {od::UI::Anchor::Center, od::UI::Anchor::End})));
	AddUiElement(m_PauseRect);

	AddUiElement(m_ScoreText);

	for(uint8_t i=0; i<10; ++i)
		SpawnRandomOre();
}

void GameScene::Update(uint32_t deltaTime) {
	od::Scene::Update(deltaTime);

	if(od::Input::IsKeyJustPressed(GLFW_KEY_ESCAPE))
		m_PauseRect->m_Visible ^= 1;

	if(m_PauseRect->m_Visible)
		return;

	if(od::Input::IsButtonJustPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		glm::f32vec2 cursorPos = od::Game::GetInstance()->GetWorldCursorPosition();
		for(std::vector<Ore>::reverse_iterator it = m_Ores.rbegin(); it != m_Ores.rend(); ++it) {
			Ore &ore = *it;
			glm::f32vec2 orePos = ore.GetPosition();
			if(cursorPos.x > orePos.x - 25
			&& cursorPos.x < orePos.x + 25
			&& cursorPos.y > orePos.y - 26
			&& cursorPos.y < orePos.y + 25) {
				ore.Hit(20);
				if(ore.IsQueuedForDestruction())
					m_ScoreText->m_Text = "Score: " + std::to_string(++m_Score);

				break;
			}
		}
	}

	od::Entity::DeleteDestroyedEntities<Ore>(m_Ores);

	if(m_Ores.size() == 0)
		for(uint8_t i=0; i<20; ++i)
			SpawnRandomOre();

	m_Player->Update(deltaTime);
}

void GameScene::Tick() {
}

void GameScene::Render2D() {
	for(Ore &ore : m_Ores)
		ore.Render();

	m_Player->Render();
}

void GameScene::ExitToMenu() {
	od::Game::GetInstance()->SetScene(std::make_unique<MainMenuScene>());
}

void GameScene::SpawnRandomOre() {
	m_Ores.emplace_back(100, glm::f32vec2(Ore::SIZE.x * (rand() % 10 - 5), Ore::SIZE.y * (rand() % 10 - 5)));
}