#include "SplashScreenScene.h"
#include "MainMenuScene.h"
#include "Oredustry.h"
#include <cmath>
#include <sstream>

#define NEW_DOT_INTERVAL 500
#define FAKE_LOADING_TIME 1500

od::SplashScreenScene::SplashScreenScene() :
m_LoadingText(new od::UI::Text(od::font, od::Vector2(od::ScreenCenterX(), od::GetWindowHeight() - FONT_SIZE*2.5f), SDL_Color{0,0,0,255}, "Loading", od::UI::TextAlign::Center)),
m_SpinnerTexture(new od::UI::Texture("res/logo.png", Vector2::ScreenCenter(), {128,128}, true)),
m_FakeLoadingTimer(0),
m_LoadingTextDotTimer(0) {
}

od::SplashScreenScene::~SplashScreenScene() {
}

void od::SplashScreenScene::Awake() {
}

void od::SplashScreenScene::Update(uint32_t deltaTime, uint32_t timeSinceStart) {
	m_LoadingTextDotTimer += deltaTime;
	if(m_LoadingTextDotTimer >= NEW_DOT_INTERVAL) {
		m_LoadingTextDotTimer = 0;

		if(m_LoadingTextDots.size() >= 3)	m_LoadingTextDots.clear();
		else					m_LoadingTextDots.push_back('.');
	}

	m_FakeLoadingTimer += deltaTime;
	if(m_FakeLoadingTimer >= FAKE_LOADING_TIME)
		od::SetScene(std::unique_ptr<MainMenuScene>(new MainMenuScene()));

	m_SpinnerTexture->m_Rotation  = timeSinceStart * 0.08f;
}

void od::SplashScreenScene::ProcessEvent(const SDL_Event &event) {
	if(event.type == SDL_WINDOWEVENT) {
		m_SpinnerTexture->m_Position = od::Vector2::ScreenCenter();

		m_LoadingText->m_Position.x = od::ScreenCenterX();
		m_LoadingText->m_Position.y = od::GetWindowHeight() - FONT_SIZE*2.5f;
	}
}

void od::SplashScreenScene::Draw() {
	m_SpinnerTexture->Render();
}

void od::SplashScreenScene::DrawUI() {
	std::stringstream ss;
	ss << std::round(static_cast<float>(m_FakeLoadingTimer) / FAKE_LOADING_TIME * 100.f) << "%\nLoading" << m_LoadingTextDots;
	m_LoadingText->SetText(ss.str());

	m_LoadingText->Render();
}
