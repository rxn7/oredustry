#include "Scene.h"

od::Scene::Scene(const od::Color &clearColor) : m_ClearColor(clearColor) {
}

void od::Scene::Awake() {
	for(auto &uiElement : m_UiElements)
		uiElement->UpdateAnchoredPosition();
}

void od::Scene::AddUiElement(std::shared_ptr<od::UI::UIElement> uiElement) {
	m_UiElements.push_back(uiElement);
	uiElement->Awake();
}

void od::Scene::AddEntity(std::shared_ptr<od::Entity> ent) {
	m_Entities.push_back(ent);
	ent->Awake();
}

void od::Scene::Update(uint32_t deltaTime) {
	for(auto &entity : m_Entities) 
		entity->Update(deltaTime);

	for(auto &uiElement : m_UiElements) {
		uiElement->Update(deltaTime);
		uiElement->UpdateChildren(deltaTime);
	}
}

void od::Scene::RenderUI() {
	for(auto &uiElement : m_UiElements) {
		uiElement->Render();
		uiElement->RenderChildren();
	}
}

void od::Scene::Render2D() {
	for(auto &entity : m_Entities) 
		entity->Render();
}
