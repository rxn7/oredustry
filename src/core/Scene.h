#pragma once

#include <memory>
#include <vector>
#include "core/Renderable.h"
#include "ui/UIElement.h"
#include "Entity.h"
#include "core/Color.h"

namespace od {
	class Scene {
	public:
		virtual ~Scene() {}
		virtual void Awake();
		virtual void Update(uint32_t frameDelta);
		virtual void Tick() {}
		virtual void Render2D();
		virtual void RenderUI();
		void AddUiElement(std::shared_ptr<od::UI::UIElement> uiElement);
		void AddEntity(std::shared_ptr<od::Entity> ent);

	protected:
		Scene(const od::Color &clearColor);

	public:
		od::Color m_ClearColor;
		std::vector<std::shared_ptr<od::UI::UIElement>> m_UiElements;
		std::vector<std::shared_ptr<od::Entity>> m_Entities;
	};
}