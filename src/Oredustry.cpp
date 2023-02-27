#include "Oredustry.h"
#include "AssetUIDs.h"
#include "core/Asset.h"
#include "core/Input.h"
#include "core/assets/TextureAtlas.h"
#include "core/rendering/Renderer.h"
#include "scenes/MainMenuScene.h"
#include "Ore.h"

static const od::WindowParameters WINDOW_PARAMS = {
	.title = "Oredustry",
	.width = 1680,
	.height = 960,
	.iconPath = "res/logo.png"
};

Oredustry *Oredustry::s_Instance;

Oredustry::Oredustry() : 
od::Game(WINDOW_PARAMS) {
	s_Instance = this;

	od::Asset::Load<od::Texture>(TITLE_TEXTURE_UID, "res/title.png");
	od::Asset::Load<od::Texture>(ORE_TEXTURE_UID, "res/ore.png");
	od::Asset::Load<od::Texture>(LOGO_TEXTURE_UID, "res/logo.png");
	od::Asset::Load<od::Texture>(PLAYER_TEXTURE_UID, "res/player.png");
	od::Asset::Load<od::Texture>(CURSOR_TEXTURE_UID, "res/cursor.png");
	od::Asset::Load<od::TextureAtlas>(DESTROY_TEXTURE_ATLAS_UID, "res/destroy.png", 10);

	od::Texture *fontTexture = od::Asset::Load<od::Texture>("font", "res/font.png");
	m_Font = std::make_unique<od::Font>(fontTexture, GL_NEAREST);

	m_DebugText = std::make_unique<od::UI::Text>(m_Font.get(), glm::f32vec2{0,0}, "Debug", 1, od::Colors::BLACK, od::TextAlignHorizontal::Left, od::TextAlignVertical::Top);
	m_DebugText->m_AnchoredPosition = {0,0};

	m_Cursor = std::make_unique<Cursor>(30);
	glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	od::Renderer::Init(m_Font.get());
}

void Oredustry::Ready() {
	SetScene(std::make_unique<MainMenuScene>());
}

void Oredustry::Update(uint32_t dt) {
	if(od::Input::IsKeyJustPressed(GLFW_KEY_GRAVE_ACCENT))
		m_DebugText->m_Visible ^= 1;
}

void Oredustry::Tick(uint32_t dt) {
	UpdateDebug(dt);
}

void Oredustry::HandleRenderUI() {
	od::Game::HandleRenderUI();
	m_Cursor->Render();
}

void Oredustry::RenderUI() {
	m_DebugText->Render();
}

void Oredustry::UpdateDebug(uint32_t dt) {
	if(!m_DebugText->m_Visible) return;

	float deltaFloat = static_cast<std::chrono::duration<float, std::milli>>(m_FrameStartTimePoint - m_FrameEndTimePoint).count() / 1000.0f;
	int32_t fps = static_cast<int32_t>(1.f / deltaFloat);

	std::stringstream ss;
	ss 	<< "Press ~ to disable debug\n"
		<< "frame time: " << dt << "us\n"
		<< "fps: " << fps << "\n"
		<< "draw calls: " << od::Renderer::drawCalls << "\n"
		<< "time: " << GetTimeSinceStartMs() / 1000.0f << "s\n"
		<< "cur pos: " << m_CursorPosition.x << " " << m_CursorPosition.y;

	m_DebugText->m_Text = ss.str();
}
