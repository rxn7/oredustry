#include "SplashScreenScene.h"
#include "Oredustry.h"
#include <cmath>

#define NEW_DOT_INTERVAL 500

od::SplashScreenScene::SplashScreenScene() : m_LoadingText(new od::UI::Text(od::font, 0, 0, SDL_Color{0,0,0,255}, "Loading", od::UI::TextAlign::Center)) {
	if(!(m_Texture = IMG_LoadTexture(od::renderer, "res/splashscreen.png"))) {
		od::LogError("Failed to load res/splashscreen.png: " + std::string(IMG_GetError()));
		return;
	}

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TextureRect.w, &m_TextureRect.h);
}

od::SplashScreenScene::~SplashScreenScene() {
	if(m_Texture)
		SDL_DestroyTexture(m_Texture);
}

void od::SplashScreenScene::Awake() {
}

void od::SplashScreenScene::Update(uint32_t deltaTime, uint32_t timeSinceStart) {
	m_LoadingTextDotTimer += deltaTime;
	if(m_LoadingTextDotTimer >= NEW_DOT_INTERVAL) {
		m_LoadingTextDotTimer = 0;

		if(m_LoadingTextDots.size() >= 3)	m_LoadingTextDots.clear();
		else					m_LoadingTextDots.push_back('.');

		m_LoadingText->SetText("Loading" + m_LoadingTextDots);
	}

	m_TextureAngle = cosf(timeSinceStart * 0.001f) * 30;
}

void od::SplashScreenScene::Draw() {
	// Center the texture
	m_TextureRect.x = od::GetWindowWidth() * 0.5f - m_TextureRect.w * 0.5f;
	m_TextureRect.y = od::GetWindowHeight() * 0.5f - m_TextureRect.h * 0.5f;

	SDL_RenderCopyEx(od::renderer, m_Texture, 0, &m_TextureRect, m_TextureAngle, 0, SDL_FLIP_NONE);
}

void od::SplashScreenScene::DrawUI() {
	float x = od::GetWindowWidth() * 0.5f;
	float y = od::GetWindowHeight() - FONT_SIZE*1.5f;
	m_LoadingText->SetPosition(x, y);
	m_LoadingText->Render();
}
