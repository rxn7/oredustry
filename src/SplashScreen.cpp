#include "SplashScreen.h"
#include "Oredustry.h"
#include <spng.h>
#include <cmath>

#define NEW_DOT_INTERVAL 500

static ALLEGRO_BITMAP *image = nullptr;
static int32_t imageWidth = 0;
static int32_t imageHeight = 0;
static float angle = 0;
static std::string dots="";
static int32_t newDotTimer = 0;

od::SplashScreenScene::~SplashScreenScene() {
	if(image)
		al_destroy_bitmap(image);
}

void od::SplashScreenScene::Awake() {
	od::Log("SplashScreenScene is awake");

	if(!(image = al_load_bitmap("res/splashscreen.png"))) {
		std::stringstream ss;
		ss << "Failed to load res/splashscreen.png: " << al_get_errno();
		od::LogError(ss.str());

		delete this;
	}

	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);
}

void od::SplashScreenScene::Update(uint32_t deltaTime, uint32_t timeSinceStart) {
	newDotTimer += deltaTime;
	if(newDotTimer >= NEW_DOT_INTERVAL) {
		if(dots.size() >= 3)
			dots.clear();

		else 
			dots.push_back('.');

		newDotTimer = 0;
	}

	angle = cosf(timeSinceStart / 1000.f) * od::Math::Deg2Rad(30);
}

void od::SplashScreenScene::Draw(ALLEGRO_DISPLAY *display) {
	float x = al_get_display_width(display) / 2;
	float y = al_get_display_height(display) / 2;
	al_draw_rotated_bitmap(image, imageWidth / 2, imageHeight / 2, x, y, angle, 0);
}

void od::SplashScreenScene::DrawUI(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {
	float x = al_get_display_width(display) / 2;
	float y = al_get_display_height(display) - FONT_SIZE*1.5f;
	std::string loadingText = "Loading" + dots;
	al_draw_text(font, al_map_rgb(0,0,0), x, y, ALLEGRO_ALIGN_CENTER, loadingText.c_str());
}
