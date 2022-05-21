#include "UIElement.h"
#include "Oredustry.h"

void od::UI::UIElement::Update(uint32_t deltaTime) {
	switch(m_Anchors[0]) {
		case Anchor::Center:
			m_AnchoredPosition.x = od::ScreenCenterX() + m_Position.x;
			break;

		case Anchor::Start:
			m_AnchoredPosition.x = m_Position.x;
			break;

		case Anchor::End:
			m_AnchoredPosition.x = od::GetWindowWidth() - m_Position.x;
			break;
	}

	switch(m_Anchors[1]) {
		case Anchor::Center:
			m_AnchoredPosition.y = od::ScreenCenterY() + m_Position.y;
			break;

		case Anchor::Start:
			m_AnchoredPosition.y = m_Position.y;
			break;

		case Anchor::End:
			m_AnchoredPosition.y = od::GetWindowHeight() - m_Position.y;
			break;
	}
}
