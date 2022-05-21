#pragma once

#include <memory>
#include <vector>
#include "ui/UIElement.h"

namespace od {
	class Scene {
	public:
		virtual ~Scene() {}
		virtual void Awake() {}
		virtual void Update(uint32_t frameDelta);
		virtual void Draw() {}
		virtual void DrawUI();
		virtual void ProcessEvent(const SDL_Event &event);
		void AddUiElement(std::unique_ptr<od::UI::UIElement> uiElement);

	protected:
		std::vector<std::unique_ptr<od::UI::UIElement>> m_UiElements;
	};
}
