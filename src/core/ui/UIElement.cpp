#include "UIElement.h"
#include "core/Game.h"
#include "core/Log.h"

od::UI::UIElement::UIElement(const glm::i32vec2 &position, const glm::i32vec2 &size, const Anchors &anchors) : 
m_Position(position), m_Size(size), m_Anchors(anchors) {
}
void od::UI::UIElement::UpdateAnchoredPosition() {
	float width = od::Game::GetInstance()->GetWindow().GetStartWidth();
	float height = od::Game::GetInstance()->GetWindow().GetStartHeight();

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

	for(std::shared_ptr<od::UI::UIElement> child : m_Children) {
		switch(child->m_Anchors[0]) {
			case Anchor::Center:
				child->m_AnchoredPosition.x = m_AnchoredPosition.x + child->m_Position.x;
				break;

			case Anchor::Start:
				child->m_AnchoredPosition.x = m_AnchoredPosition.x - m_Size.x * 0.5f + child->m_Position.x + child->m_Size.x * 0.5f;
				break;

			case Anchor::End:
				child->m_AnchoredPosition.x = m_AnchoredPosition.x + m_Size.x * 0.5f - child->m_Position.x - child->m_Size.x * 0.5f;
				break;
		}

		switch(child->m_Anchors[1]) {
			case Anchor::Center:
				child->m_AnchoredPosition.y = m_AnchoredPosition.y + child->m_Position.y;
				break;

			case Anchor::Start:
				child->m_AnchoredPosition.y = m_AnchoredPosition.y - m_Size.y * 0.5f + child->m_Position.y + child->m_Size.y * 0.5f;
				break;

			case Anchor::End:
				child->m_AnchoredPosition.y = m_AnchoredPosition.y + m_Size.y * 0.5f - child->m_Position.y - child->m_Size.y * 0.5f;
				break;
		}
	}
}

void od::UI::UIElement::AddChildElement(const std::shared_ptr<od::UI::UIElement> &element) {
	m_Children.push_back(element);
}

void od::UI::UIElement::UpdateChildren(uint32_t deltaTime) {
	ENSURE_VISIBLE;
	for(std::shared_ptr<UIElement> element : m_Children)
		element->Update(deltaTime);
}

void od::UI::UIElement::RenderChildren() {
	ENSURE_VISIBLE;
	for(std::shared_ptr<UIElement> element : m_Children)
		element->Render();
}
