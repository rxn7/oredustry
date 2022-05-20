#include "Input.h"

#define KEY_COUNT 322
static constexpr size_t STATE_SIZE = sizeof(uint8_t) * KEY_COUNT;

static uint8_t *state;
static uint8_t *oldState;

void od::Input::Init() {
	state = static_cast<uint8_t*>(malloc(STATE_SIZE));
	oldState = static_cast<uint8_t*>(malloc(STATE_SIZE));
}

void od::Input::Update() {
	std::copy(state, state + STATE_SIZE, oldState);
	state = const_cast<uint8_t*>(SDL_GetKeyboardState(0));
}

bool od::Input::IsKeyPressed(SDL_KeyCode key) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return state[scancode];
}

bool od::Input::IsKeyJustPressed(SDL_KeyCode key) {
	SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return state[scancode] && !oldState[scancode];
}
