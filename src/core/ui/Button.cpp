#include "Button.h"
#include "core/Game.h"
#include "core/rendering/Renderer.h"
#include "core/Color.h"
#include "core/Input.h"

od::UI::Button::Button(std::string_view text, ButtonClickCallback clickCallback, const glm::i32vec2 &position, const glm::i32vec2 &size, Anchors anchors) :
m_ClickCallback(clickCallback),
m_Text(new od::UI::Text({}, text, 16, od::Colors::BLACK, od::UI::TextAlign::Center)),
od::UI::UIElement(position, size, anchors) {
}

void od::UI::Button::Update(uint32_t deltaTime) {
	m_Text->m_AnchoredPosition = glm::i32vec2(m_AnchoredPosition.x, m_AnchoredPosition.y - m_Text->GetSize().y * 0.5f);

	const float halfWidth = m_Size.x * 0.5f;
	const float halfHeight = m_Size.y * 0.5f;

	glm::i32vec2 cursorPosition = od::Game::GetInstance()->GetCursorPosition();
	m_Hovered = cursorPosition.x >= m_AnchoredPosition.x - halfWidth && cursorPosition.x <= m_AnchoredPosition.x + halfWidth && cursorPosition.y >= m_AnchoredPosition.y - halfHeight && cursorPosition.y <= m_AnchoredPosition.y + halfHeight;

	if(m_Hovered && od::Input::IsButtonJustPressed(GLFW_MOUSE_BUTTON_LEFT))
		m_ClickCallback();
}

void od::UI::Button::Render() {
	ENSURE_VISIBLE;

	od::Color color;
	if(IsHovered())
		color = {0.6f, 0.6f, 0.6f, 1.0f};
	else
		color = {0.8f, 0.8f, 0.8f, 1.0f};

	od::Renderer::RenderQuad(m_AnchoredPosition, m_Size, color);
	m_Text->Render();
}

void od::UI::Button::SetText(std::string_view text) {
	m_Text->SetText(text);
}
