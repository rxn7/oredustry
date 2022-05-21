#include "LoadingScene.h"
#include "core/Log.h"

#define NEW_DOT_INTERVAL 500000
#define FAKE_LOADING_TIME 2500000

od::SplashScreenScene::SplashScreenScene() :
m_LoadingText(new od::UI::Text(od::Core::font, od::Vector2i(0, FONT_SIZE*2.5f), SDL_Color{0,0,0,255}, "Loading", od::UI::TextAlign::Center, {od::UI::Anchor::Center, od::UI::Anchor::End})),
m_SpinnerTexture(new od::UI::Texture("res/logo.png", od::Vector2i(), {128,128}, ANCHORS_CENTER)),
m_FakeLoadingTimer(0),
m_LoadingTextDotTimer(0) {
	AddUiElement(std::unique_ptr<od::UI::UIElement>(m_LoadingText));
	AddUiElement(std::unique_ptr<od::UI::UIElement>(m_SpinnerTexture));
}

void od::SplashScreenScene::Update(uint32_t deltaTime) {
	od::Scene::Update(deltaTime);

	m_LoadingTextDotTimer += deltaTime;
	if(m_LoadingTextDotTimer >= NEW_DOT_INTERVAL) {
		m_LoadingTextDotTimer = 0;

		if(m_LoadingTextDots.size() >= 3)	m_LoadingTextDots.clear();
		else					m_LoadingTextDots.push_back('.');
	}

	m_FakeLoadingTimer += deltaTime;
	if(m_FakeLoadingTimer >= FAKE_LOADING_TIME)
		// TODO: Load next scene
		// return od::SetScene(std::unique_ptr<od::Scene>(new MainMenuScene()));

	m_SpinnerTexture->m_Rotation = od::Core::GetTimeSinceStart() * 0.08f;

	std::stringstream ss;
	ss << std::round(static_cast<float>(m_FakeLoadingTimer) / FAKE_LOADING_TIME * 100.f) << "% Loading" << m_LoadingTextDots;
	m_LoadingText->SetText(ss.str());
}
