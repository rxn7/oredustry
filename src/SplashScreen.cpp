#include "SplashScreen.h"
#include "Oredustry.h"

void od::SplashScreenScene::Awake() {
	od::Log("SplashScreenScene is awake");
}

void od::SplashScreenScene::Update(uint32_t frameDelta) {
}

void od::SplashScreenScene::Draw(ALLEGRO_DISPLAY *display) {
}

void od::SplashScreenScene::DrawUI(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {
	al_draw_text(font, al_map_rgb(255, 100, 0), al_get_display_width(display) / 2, al_get_display_height(display) / 2, ALLEGRO_ALIGN_CENTER, "TODO: Actual SplashScreen lol");
}
