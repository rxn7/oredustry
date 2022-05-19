#include "Input.h"

static ALLEGRO_KEYBOARD_STATE state;
static ALLEGRO_KEYBOARD_STATE oldState;

void od::Input::Update() {
	oldState = state;
	al_get_keyboard_state(&state);
}

bool od::Input::IsKeyPressed(uint8_t key) {
	return al_key_down(&state, key);
}

bool od::Input::IsKeyJustPressed(uint8_t key) {
	return al_key_down(&state, key) && !al_key_down(&oldState, key);
}
