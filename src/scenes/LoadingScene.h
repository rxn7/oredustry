#pragma once

#include <memory>
#include "Oredustry.h"
#include "core/ui/Texture.h"
#include "core/ui/Text.h"

namespace od {
	class LoadingScene : public Scene {
	public:
		LoadingScene();
		void Update(uint32_t deltaTime) override;

	private:
		od::UI::Texture *m_SpinnerTexture;
		od::UI::Text *m_LoadingText;
		std::string m_LoadingTextDots;
		uint32_t m_LoadingTextDotTimer;
		uint32_t m_FakeLoadingTimer;
	};
}
