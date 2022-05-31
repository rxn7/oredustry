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

static const std::string TEXTURES_TO_LOAD[] = {
	"res/player.png",
	"res/logo.png",
	"res/title.png",
};

Oredustry::Oredustry() : 
m_Cursor(std::make_unique<Cursor>(30)),
od::Game(WINDOW_PARAMS) {
	for(const std::string &texture : TEXTURES_TO_LOAD)
		od::Asset::Load<od::Texture>(texture);

	od::Asset::Load<od::Font>("res/font.ttf", 16);

	glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Oredustry::OnShutdown() {
}

void Oredustry::DrawDebug() {
	if(!m_DebugText->m_Visible) return;

	if(m_DebugTextUpdateCounter < 2000000) return;
	m_DebugTextUpdateCounter = 0;

	float deltaFloat = static_cast<std::chrono::duration<float, std::milli>>(m_FrameStartTimePoint - m_FrameEndTimePoint).count() / 1000.0f;
	int32_t fps = static_cast<int32_t>(1.f / deltaFloat);

	std::stringstream ss;
	ss << "==FRAME DEBUG INGO==\n" << "time: " << m_DeltaTime << "μs\n" << "fps: " << fps << "\n";

	// OD_LOG_INFO(ss.str());

	m_DebugText->m_Text = ss.str();
	m_DebugText->Render();
}

void Oredustry::Awake() {
	m_DebugText = std::make_unique<od::UI::Text>(*od::Asset::GetAsset<od::Font>("res/font.ttf"), glm::f32vec2{0,0}, "Debug", 1, od::Colors::BLACK);

	SetScene(std::make_unique<MainMenuScene>());
}

void Oredustry::Update(uint32_t deltaTime) {
	od::Game::Update(deltaTime);

	if(od::Input::IsKeyJustPressed(GLFW_KEY_GRAVE_ACCENT))
		m_DebugText->m_Visible ^= 1;

	m_DebugTextUpdateCounter += deltaTime;
}

void Oredustry::DrawUI() {
	DrawDebug();
	m_Cursor->Render();
}
