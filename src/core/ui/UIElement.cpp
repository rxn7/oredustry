#include "UIElement.h"
#include "core/Core.h"

void od::UI::UIElement::Update(uint32_t deltaTime) {
	switch(m_Anchors[0]) {
		case Anchor::Center:
			m_AnchoredPosition.x = od::Core::ScreenCenterX() + m_Position.x;
			break;

		case Anchor::Start:
			m_AnchoredPosition.x = m_Position.x;
			break;

		case Anchor::End:
			m_AnchoredPosition.x = od::Core::GetScreenWidth() - m_Position.x;
			break;
	}

	switch(m_Anchors[1]) {
		case Anchor::Center:
			m_AnchoredPosition.y = od::Core::ScreenCenterY() + m_Position.y;
			break;

		case Anchor::Start:
			m_AnchoredPosition.y = m_Position.y;
			break;

		case Anchor::End:
			m_AnchoredPosition.y = od::Core::GetScreenHeight() - m_Position.y;
			break;
	}
}
