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

	od::Color color = {
		static_cast<float>(cursorPosition.x) / static_cast<float>(window.GetWidth()),
		static_cast<float>(cursorPosition.y) / static_cast<float>(window.GetHeight()),
		1.f - static_cast<float>(cursorPosition.y) / static_cast<float>(window.GetHeight()),
		1.0f
	};

	float halfSize = m_Size.x * 0.5f;
	m_Position = {cursorPosition.x + halfSize, cursorPosition.y + halfSize};

	od::Renderer::RenderQuadTextured(m_Position, m_Size, m_Texture.get(), color, od::Renderer::TextureShaderType::ColorSwap);

	if(Oredustry::GetInstance()->IsDebugOn()) {
		std::stringstream cursorPositionSs;
		cursorPositionSs << cursorPosition.x << ", " << cursorPosition.y;
		od::Renderer::RenderText(cursorPositionSs.str(), od::Game::GetInstance()->GetFont(), m_Position + halfSize, od::Colors::BLACK, 1.f, od::TextAlignHorizontal::Left, od::TextAlignVertical::Top);
	}
}
