#include "Player.h"
#include "core/Input.h"
#include "core/Game.h"

#define MOVE_SPEED 0.0002f

Player::Player() : od::Sprite(od::Asset::GetAsset<od::Texture>("res/player.png")) {
}

void Player::Update(uint32_t deltaTime) {
	glm::f32vec2 moveDir{0,0};
	if(od::Input::IsKeyPressed(SDLK_s)) moveDir.y++;
	if(od::Input::IsKeyPressed(SDLK_w)) moveDir.y--;
	if(od::Input::IsKeyPressed(SDLK_d)) moveDir.x++;
	if(od::Input::IsKeyPressed(SDLK_a)) moveDir.x--;

	float moveDirLen = moveDir.length();
	if(moveDirLen != 0) {
		// For some reason using glm::normalize causes the moveDir to be {-nan, -nan}
		// moveDir = glm::normalize(moveDir);
		moveDir.x /= moveDirLen;
		moveDir.y /= moveDirLen;
	}

	moveDir *= deltaTime * MOVE_SPEED;
	m_Position += moveDir;

	od::Game::GetInstance()->SetCameraPosition(m_Position);
}
