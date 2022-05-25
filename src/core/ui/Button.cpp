#include "Button.h"

od::UI::Button::Button(std::string_view text, ButtonClickCallback clickCallback, const od::Vector2i &position, const od::Vector2i &size, Anchors anchors) :
m_ClickCallback(clickCallback),
m_Text(new od::UI::Text(od::Core::font, od::Vector2i(), SDL_Color{0,0,0,255}, text, od::UI::TextAlign::Center)),
m_Rect{static_cast<int32_t>(position.x - size.x * 0.5f), static_cast<int32_t>(position.y - size.x * 0.5f + FONT_SIZE * 0.5f), size.x, size.y},
od::UI::UIElement(position, size, anchors) {
}

void od::UI::Button::ProcessEvent(const SDL_Event &event) {
	od::UI::UIElement::ProcessEvent(event);

	if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && m_ClickCallback && IsHovered())
		m_ClickCallback();
}

void od::UI::Button::Update(uint32_t deltaTime) {
	m_Rect.x = m_AnchoredPosition.x - m_Rect.w * 0.5f;
	m_Rect.y = m_AnchoredPosition.y - m_Rect.h * 0.5f;

	m_Text->m_AnchoredPosition = od::Vector2i(m_AnchoredPosition.x, m_AnchoredPosition.y - m_Text->GetSize().y * 0.5f);
	m_Text->CalculateRect();

	od::Vector2i pointer = od::Core::GetPointerPosition();
	m_Hovered = pointer.x >= m_Rect.x && pointer.x <= m_Rect.x + m_Rect.w && pointer.y >= m_Rect.y && pointer.y <= m_Rect.y + m_Rect.h;
}

void od::UI::Button::Render() {
	if(IsHovered())
		SDL_SetRenderDrawColor(od::Core::renderer, 200, 200, 200, 255);
	else
		SDL_SetRenderDrawColor(od::Core::renderer, 220, 220, 220, 255);

	SDL_RenderFillRect(od::Core::renderer, &m_Rect);

	SDL_SetRenderDrawColor(od::Core::renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(od::Core::renderer, &m_Rect);

	m_Text->Render();
}

void od::UI::Button::SetText(std::string_view text) {
	m_Text->SetText(text);
}
