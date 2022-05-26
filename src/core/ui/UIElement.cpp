#include "UIElement.h"
#include "core/Game.h"

od::UI::UIElement::UIElement(const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors) : 
m_Position(position), m_Size(size), m_Anchors(anchors) {
}

void od::UI::UIElement::UpdateAnchoredPosition() {
	switch(m_Anchors[0]) {
		case Anchor::Center:
			m_AnchoredPosition.x = od::Game::GetInstance()->GetWindow().GetHalfWidth() + m_Position.x;
			break;

		case Anchor::Start:
			m_AnchoredPosition.x = m_Position.x;
			break;

		case Anchor::End:
			m_AnchoredPosition.x = od::Game::GetInstance()->GetWindow().GetWidth() - m_Position.x;
			break;
	}

	switch(m_Anchors[1]) {
		case Anchor::Center:
			m_AnchoredPosition.y = od::Game::GetInstance()->GetWindow().GetHalfHeight() + m_Position.y;
			break;

		case Anchor::Start:
			m_AnchoredPosition.y = m_Position.y;
			break;

		case Anchor::End:
			m_AnchoredPosition.y = od::Game::GetInstance()->GetWindow().GetHeight() - m_Position.y;
			break;
	}

	for(std::shared_ptr<od::UI::UIElement> element : m_Children) {
		switch(element->m_Anchors[0]) {
			case Anchor::Center:
				element->m_AnchoredPosition.x = m_AnchoredPosition.x - m_Size.x * 0.5f + m_Position.x;
				break;

			case Anchor::Start:
				element->m_AnchoredPosition.x = m_AnchoredPosition.x + element->m_Position.x;
				break;

			case Anchor::End:
				element->m_AnchoredPosition.x = m_AnchoredPosition.x + m_Size.x - element->m_Position.x;
				break;
		}

		switch(element->m_Anchors[1]) {
			case Anchor::Center:
				element->m_AnchoredPosition.y = m_AnchoredPosition.y - m_Size.y * 0.5f + m_Position.y;
				break;

			case Anchor::Start:
				element->m_AnchoredPosition.y = m_AnchoredPosition.y + element->m_Position.y;
				break;

			case Anchor::End:
				element->m_AnchoredPosition.y = m_AnchoredPosition.y + m_Size.y - element->m_Position.y;
				break;
		}
	}
}

void od::UI::UIElement::AddChildElement(std::shared_ptr<od::UI::UIElement> element) {
	m_Children.push_back(element);
}

void od::UI::UIElement::UpdateChildren(uint32_t deltaTime) {
	for(std::shared_ptr<UIElement> element : m_Children)
		element->Update(deltaTime);
}

void od::UI::UIElement::RenderChildren() {
	for(std::shared_ptr<UIElement> element : m_Children)
		element->Render();
}

void od::UI::UIElement::ProcessEventChildren(const SDL_Event &event) {
	for(std::shared_ptr<UIElement> element : m_Children)
		element->ProcessEvent(event);
}
