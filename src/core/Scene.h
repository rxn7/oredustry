#pragma once

#include <memory>
#include <vector>
#include "ui/UIElement.h"
#include "Entity.h"

namespace od {
	class Scene {
	public:
		virtual ~Scene() {}
		virtual void Awake();
		virtual void Update(uint32_t frameDelta);
		virtual void Draw();
		virtual void DrawUI();
		virtual void ProcessEvent(const SDL_Event &event);
		void AddUiElement(std::shared_ptr<od::UI::UIElement> uiElement);
		void AddEntity(std::shared_ptr<od::Entity> ent);

	public:
		std::vector<std::shared_ptr<od::UI::UIElement>> m_UiElements;
		std::vector<std::shared_ptr<od::Entity>> m_Entities;
	};
}
