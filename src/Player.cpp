#include "Player.h"
#include "core/Core.h"
#include "core/Input.h"

#define MOVE_SPEED 0.0002f

od::Player::Player() : od::Sprite("res/player.png") {
}

void od::Player::Update(uint32_t deltaTime) {
	od::Vector2f moveDir = {0,0};
	if(od::Input::IsKeyPressed(SDLK_s)) moveDir.y++;
	if(od::Input::IsKeyPressed(SDLK_w)) moveDir.y--;
	if(od::Input::IsKeyPressed(SDLK_d)) moveDir.x++;
	if(od::Input::IsKeyPressed(SDLK_a)) moveDir.x--;
	moveDir.Normalize();

	moveDir *= deltaTime * MOVE_SPEED;

	m_Position += moveDir;
}
