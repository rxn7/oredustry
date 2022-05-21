#include "Player.h"
#include "core/Core.h"

od::Player::Player() {
	m_Texture = IMG_LoadTexture(od::Core::renderer, "res/player.png");
}

void od::Player::Update(uint32_t deltaTime) {
}

void od::Player::Render() {
	SDL_RenderCopy(od::Core::renderer, m_Texture, 0, 0);
}
