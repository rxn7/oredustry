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
	"res/ore.png",
};

Oredustry *Oredustry::s_Instance;

Oredustry::Oredustry() : 
m_Cursor(std::make_unique<Cursor>(30)),
od::Game(WINDOW_PARAMS) {
	s_Instance = this;

	for(const std::string &texture : TEXTURES_TO_LOAD)
		od::Asset::Load<od::Texture>(texture);

	glfwSetInputMode(m_Window->GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Oredustry::Ready() {
	SetScene(std::make_unique<MainMenuScene>());
}

void Oredustry::HandleRenderUI() {
	od::Game::HandleRenderUI();
	m_Cursor->Render();
}