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

	glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	m_Font = std::make_unique<od::Font>("res/font.png", GL_NEAREST);
}

void Oredustry::OnShutdown() {
}

void Oredustry::UpdateDebug(uint32_t deltaTime) {
	if(!m_DebugText->m_Visible) return;

	m_DebugTextUpdateCounter += deltaTime;
	if(m_DebugTextUpdateCounter < 200000) return;
	m_DebugTextUpdateCounter = 0;

	float deltaFloat = static_cast<std::chrono::duration<float, std::milli>>(m_FrameStartTimePoint - m_FrameEndTimePoint).count() / 1000.0f;
	int32_t fps = static_cast<int32_t>(1.f / deltaFloat);

	std::stringstream ss;
	ss << "frame time: " << m_DeltaTime << "us\n" << "fps: " << fps << "\n";

	m_DebugText->m_Text = ss.str();
}

void Oredustry::Awake() {
	m_DebugText = std::make_unique<od::UI::Text>(m_Font.get(), glm::f32vec2{0,0}, "Debug", 1, od::Colors::BLACK, od::TextAlignHorizontal::Left, od::TextAlignVertical::Top);
	m_DebugText->m_AnchoredPosition = {0,0};
	SetScene(std::make_unique<MainMenuScene>());
}

void Oredustry::Update(uint32_t deltaTime) {
	od::Game::Update(deltaTime);

	if(od::Input::IsKeyJustPressed(GLFW_KEY_GRAVE_ACCENT))
		m_DebugText->m_Visible ^= 1;

	UpdateDebug(deltaTime);

}

void Oredustry::DrawUI() {
	m_DebugText->Render();
	m_Cursor->Render();
}
