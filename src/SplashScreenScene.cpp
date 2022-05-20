#include "SplashScreenScene.h"
#include "Oredustry.h"
#include <cmath>

#define NEW_DOT_INTERVAL 500

static SDL_Texture *image = nullptr;
static SDL_Rect imageRect = {0};
static float angle = 0;
static std::string dots="";
static int32_t newDotTimer = 0;

od::SplashScreenScene::~SplashScreenScene() {
	if(image)
		SDL_DestroyTexture(image);
}

void od::SplashScreenScene::Awake() {
	if(!(image = IMG_LoadTexture(od::renderer, "res/splashscreen.png"))) {
		od::LogError("Failed to load res/splashscreen.png: " + std::string(IMG_GetError()));
		return;
	}

	SDL_QueryTexture(image, nullptr, nullptr, &imageRect.w, &imageRect.h);
}

void od::SplashScreenScene::Update(uint32_t deltaTime, uint32_t timeSinceStart) {
	newDotTimer += deltaTime;
	if(newDotTimer >= NEW_DOT_INTERVAL) {
		if(dots.size() >= 3)	dots.clear();
		else			dots.push_back('.');
		newDotTimer = 0;
	}

	angle = cosf(timeSinceStart / 1000.f) * 30;
}

void od::SplashScreenScene::Draw() {
	imageRect.x = od::GetWindowWidth() * 0.5f - imageRect.w * 0.5f;
	imageRect.y = od::GetWindowHeight() * 0.5f - imageRect.h * 0.5f;
	SDL_RenderCopyEx(od::renderer, image, 0, &imageRect, angle, 0, SDL_FLIP_NONE);
}

void od::SplashScreenScene::DrawUI() {
	float x = od::GetWindowWidth() * 0.5f;
	float y = od::GetWindowHeight() - FONT_SIZE*1.5f;
	std::string loadingText = "Loading" + dots;
	// al_draw_text(font, al_map_rgb(0,0,0), x, y, ALLEGRO_ALIGN_CENTER, loadingText.c_str());
}
