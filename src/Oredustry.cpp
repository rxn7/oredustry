#include "Oredustry.h"
#include "core/Input.h"
#include "core/rendering/Renderer.h"
#include "scenes/MainMenuScene.h"

static const od::WindowParameters WINDOW_PARAMS = {
	.title = "Oredustry",
	.width = 1680,
	.height = 960,
	.iconPath = "res/logo.png"
};

Oredustry::Oredustry() : od::Game(WINDOW_PARAMS) {
	// TODO: Load all assets during loading screen
	od::Asset::Load<od::Texture>("res/player.png");

	SDL_ShowCursor(false);
}

void Oredustry::OnShutdown() {
}

void Oredustry::DrawCursor() {
	float r = static_cast<float>(m_CursorPosition.x) / static_cast<float>(m_Window->GetWidth());
	float g = static_cast<float>(m_CursorPosition.y) / static_cast<float>(m_Window->GetHeight());
	float b = 1.f - g;
	od::Renderer::RenderQuad(m_CursorPosition, {20,20}, {r,g,b,1.0f});
}

void Oredustry::DrawDebug() {
	if(!m_DebugText->m_Visible) return;

	if(m_DebugTextUpdateCounter < 5000) return;
	m_DebugTextUpdateCounter = 0;

	float deltaFloat = static_cast<std::chrono::duration<float, std::milli>>(m_FrameStartTimePoint - m_FrameEndTimePoint).count() / 1000.0f;
	int32_t fps = static_cast<int32_t>(1.f / deltaFloat);

	std::stringstream ss;
	ss << "frame: " << m_DeltaTime << "μs\n" << "fps: " << fps << "\n\n";

	m_DebugText->SetText(ss.str());
	m_DebugText->Render();
}

void Oredustry::Awake() {
	m_DebugText = std::unique_ptr<od::UI::Text>(new od::UI::Text({}, "Debug", 16, {0, 0, 0, 255}, od::UI::TextAlign::Left, ANCHORS_START));
	SetScene(std::make_unique<MainMenuScene>());
}

void Oredustry::Update(uint32_t deltaTime) {
	if(od::Input::IsKeyJustPressed(SDLK_BACKQUOTE))
		m_DebugText->m_Visible ^= 1;

	m_DebugTextUpdateCounter += deltaTime;
}

void Oredustry::DrawUI() {
	DrawDebug();
	DrawCursor();
}
