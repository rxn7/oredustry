#include "Oredustry.h"
#include "core/Input.h"
#include "scenes/MainMenuScene.h"
#include "core/assets/Font.h"

static const od::WindowParameters WINDOW_PARAMS = {
	.title = "Oredustry",
	.width = 1680,
	.height = 960,
	.iconPath = "res/logo.png"
};

Oredustry::Oredustry() : od::Game(WINDOW_PARAMS) {
	m_Font = od::Asset::Load<od::Font>("res/font.ttf", 16);
	// TODO: Load all textures in a loading screen
	od::Asset::Load<od::Texture>("res/player.png");
}

void Oredustry::OnShutdown() {
}

void Oredustry::DrawDebug() {
	if(!m_DebugText->m_Visible) return;

	int32_t fps = static_cast<int32_t>(10000.f / static_cast<std::chrono::duration<float, std::micro>>(m_FrameEndTimePoint - m_FrameStartTimePoint).count());

	std::stringstream ss;
	ss << "frame: " << m_DeltaTime << "μs\n" << "fps: " << fps << "\nPress ~ to toggle debug";

	m_DebugText->SetText(ss.str());
	m_DebugText->Render();
}

void Oredustry::Awake() {
	m_DebugText = std::unique_ptr<od::UI::Text>(new od::UI::Text(m_Font->GetTTFFont(), {}, {0, 0, 0, 255}, "Debug", od::UI::TextAlign::Left, ANCHORS_START));
	SetScene(std::make_unique<MainMenuScene>());
}

void Oredustry::Update(uint32_t deltaTime) {
	if(od::Input::IsKeyJustPressed(SDLK_BACKQUOTE))
		m_DebugText->m_Visible ^= 1;
}

void Oredustry::DrawUI() {
	DrawDebug();
}
