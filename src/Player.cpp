#include "Player.h"
#include "core/Input.h"

#define MOVE_SPEED 0.0002f

Player::Player() : od::Sprite(std::make_shared<od::Texture>("res/player.png")) {
}

void Player::Update(uint32_t deltaTime) {
	glm::f32vec2 moveDir = {0,0};
	if(od::Input::IsKeyPressed(SDLK_s)) moveDir.y++;
	if(od::Input::IsKeyPressed(SDLK_w)) moveDir.y--;
	if(od::Input::IsKeyPressed(SDLK_d)) moveDir.x++;
	if(od::Input::IsKeyPressed(SDLK_a)) moveDir.x--;
	moveDir = glm::normalize(moveDir);

	moveDir *= deltaTime * MOVE_SPEED;
	m_Position += moveDir;
}
