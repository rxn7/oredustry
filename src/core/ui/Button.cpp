#include "Button.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"
#include "core/Color.h"
#include "core/Input.h"

od::UI::Button::Button(od::Font *font, std::string_view text, ButtonClickCallback clickCallback, const glm::i32vec2 &position, const glm::i32vec2 &size, Anchors anchors) :
m_Font(font),
m_ClickCallback(clickCallback),
od::UI::UIElement(position, size, anchors) {
	SetText(text);
}

void od::UI::Button::Update(uint32_t deltaTime) {
	const float halfWidth = m_Size.x * 0.5f;
	const float halfHeight = m_Size.y * 0.5f;

	glm::i32vec2 cursorPosition = od::Game::GetInstance()->GetCursorPosition();
	m_Hovered = cursorPosition.x >= m_AnchoredPosition.x - halfWidth && cursorPosition.x <= m_AnchoredPosition.x + halfWidth && cursorPosition.y >= m_AnchoredPosition.y - halfHeight && cursorPosition.y <= m_AnchoredPosition.y + halfHeight;

	if(m_Hovered && od::Input::IsButtonJustPressed(GLFW_MOUSE_BUTTON_LEFT))
		m_ClickCallback();
}

void od::UI::Button::SetText(const std::string_view &text) {
	m_Text = text;
	float textWidth = m_Font->GetTextWidth(m_Text.size());

	if(m_Size.x < textWidth)
		m_Size.x = textWidth;
}

void od::UI::Button::Render() {
	ENSURE_VISIBLE;

	od::Color color;
	if(IsHovered())
		color = {0.6f, 0.6f, 0.6f, 1.0f};
	else
		color = {0.8f, 0.8f, 0.8f, 1.0f};

	od::Renderer::RenderQuad(m_AnchoredPosition, m_Size, color);
	od::Renderer::RenderText(m_Text, m_Font, m_AnchoredPosition, od::Colors::BLACK, 1, od::TextAlignHorizontal::Center, od::TextAlignVertical::Middle);
}
