#include "Oredustry.h"
#include "core/Input.h"
#include "scenes/MainMenuScene.h"
#include "scenes/LoadingScene.h"

static std::unique_ptr<od::UI::Text> debugText;
static bool showDebug = true;

static void DrawDebugText() {
	if(!showDebug) return;

	float timeDeltaFloat = od::Core::CalculateFrameDeltaTimeMilliFloat();
	int32_t fps = static_cast<int32_t>(1000.f / timeDeltaFloat);

	std::stringstream ss;
	ss << "frame: " << od::Core::GetFrameDeltaTime() << "μs\n" << "fps: " << fps << "\nPress ~ to toggle debug";

	debugText->SetText(ss.str());
	debugText->Render();
}

void od::Oredustry::Start() {
	debugText = std::unique_ptr<od::UI::Text>(new od::UI::Text(od::Core::font, od::Vector2i(), SDL_Color{0, 0, 0, 255}, "Debug", od::UI::TextAlign::Left, ANCHORS_START));
	od::Core::SetScene(std::unique_ptr<od::Scene>(new MainMenuScene()));
}

void od::Oredustry::Update(uint32_t deltaTime) {
	if(od::Input::IsKeyJustPressed(SDLK_BACKQUOTE))
		showDebug ^= 1;
}

void od::Oredustry::Draw() {
}

void od::Oredustry::DrawUI() {
	if(showDebug)
		DrawDebugText();
}
