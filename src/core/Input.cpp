#include "Input.h"

uint8_t *state;
uint8_t *oldState;

void od::Input::Init() {
	state = static_cast<uint8_t*>(malloc(sizeof(uint8_t) * 2048));
	oldState = static_cast<uint8_t*>(malloc(sizeof(uint8_t) * 2048));
}

void od::Input::Update() {
	memcpy(oldState, state, sizeof(uint8_t) * sizeof(SDL_KeyCode));
	state = const_cast<uint8_t*>(SDL_GetKeyboardState(0));
}

bool od::Input::IsKeyPressed(uint8_t key) {
	return state[key];
}

bool od::Input::IsKeyJustPressed(uint8_t key) {
	return state[key] && !oldState[key];
}
