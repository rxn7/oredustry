#include "Player.h"
#include "core/Input.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"
#include "Oredustry.h"

#define MOVE_SPEED 0.0002f

Player::Player() : od::Sprite(od::Asset::GetAsset<od::Texture>("res/player.png")->GetGLTexture()) {
	od::Texture *texture = od::Asset::GetAsset<od::Texture>("res/player.png"); m_Size = { texture->GetWidth(), texture->GetHeight() };
}

void Player::Update(uint32_t deltaTime) {
	glm::f32vec2 moveDir{0,0};
	if(od::Input::IsKeyPressed(GLFW_KEY_W)) moveDir.y--;
	if(od::Input::IsKeyPressed(GLFW_KEY_S)) moveDir.y++;
	if(od::Input::IsKeyPressed(GLFW_KEY_D)) moveDir.x++;
	if(od::Input::IsKeyPressed(GLFW_KEY_A)) moveDir.x--;

	// TODO: What the hell? Checking if moveDir.length() != 0 doesn't work, glm::normalize still returns nan 
	moveDir = glm::normalize(moveDir);
	// TODO: Hacky fix for the problem above
	if(isnanf(moveDir.x) || isnanf(moveDir.y))
		moveDir = {0,0};

	moveDir *= deltaTime * MOVE_SPEED;

	m_Position += moveDir;

	od::Game::GetInstance()->SetCameraPosition(m_Position);
}

void Player::Render() {
	od::Sprite::Render();
	od::Renderer::RenderText("Player", Oredustry::GetInstance()->GetFont(), m_Position - glm::f32vec2{0, m_Size.y * 0.65f}, od::Colors::BLACK, 0.7f, od::TextAlignHorizontal::Center, od::TextAlignVertical::Middle);
}
