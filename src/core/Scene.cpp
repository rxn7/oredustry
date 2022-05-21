#include "Scene.h"

void od::Scene::ProcessEvent(const SDL_Event &event) {
	for(auto &uiElement : m_UiElements)
		uiElement->ProcessEvent(event);
}

void od::Scene::AddUiElement(std::unique_ptr<od::UI::UIElement> uiElement) {
	m_UiElements.push_back(std::move(uiElement));
}

void od::Scene::Update(uint32_t deltaTime) {
	for(auto &uiElement : m_UiElements)
		uiElement->Update(deltaTime);
}

void od::Scene::DrawUI() {
	for(auto &uiElement : m_UiElements)
		uiElement->Render();
}
