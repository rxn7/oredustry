#include "Cursor.h"
#include "core/rendering/Renderer.h"
#include "core/Game.h"
#include <sstream>
#include "Oredustry.h"

Cursor::Cursor(float size) : 
od::Sprite(od::Asset::Load<od::Texture>("res/cursor.png")->GetGLTexture()) {
	m_Size = {size, size};
}

void Cursor::Render() {
	glm::i32vec2 cursorPosition = od::Game::GetInstance()->GetCursorPosition();
	const od::Window &window = od::Game::GetInstance()->GetWindow();

	// Avoid division by 0 errors
	if(cursorPosition.x <= 0 || cursorPosition.y <= 0 || window.GetWidth() <= 0 || window.GetHeight() <= 0)
		return;

	od::Color color = {
		static_cast<float>(cursorPosition.x) / static_cast<float>(window.GetWidth()) * 255,
		static_cast<float>(cursorPosition.y) / static_cast<float>(window.GetHeight()) * 255,
		1.f - static_cast<float>(cursorPosition.y) / static_cast<float>(window.GetHeight()) * 255,
		255
	};

	float halfSize = m_Size.x * 0.5f;
	m_Position = {cursorPosition.x + halfSize, cursorPosition.y + halfSize};

	od::Renderer::RenderTexture(m_Position, m_Size, m_Texture.get(), color, od::Renderer::ColorSwapShader.get());
}
