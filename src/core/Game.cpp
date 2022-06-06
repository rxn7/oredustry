#include "Game.h"
#include "Input.h"
#include "rendering/Renderer.h"
#include "Log.h"
#include <glm/gtc/matrix_transform.hpp>

static constexpr uint32_t TICK_INTERVAL = 1.0f/30*1000000; // 30 ticks per second
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static od::Game *s_Instance;
static void s_CursorPosCallback(GLFWwindow *win, double x, double y);

od::Game::Game(const od::WindowParameters &params) {
	s_Instance = this;

	m_StartTimePoint = std::chrono::high_resolution_clock::now();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(!glfwInit())
		Shutdown(true, "Failed to initialize GLFW");

	m_Window = std::make_unique<Window>(params);
	glfwSetCursorPosCallback(m_Window->GetGLFWWindow(), s_CursorPosCallback);
	glfwSwapInterval(0);

	glewExperimental = true;
	if(glewInit() != GLEW_OK)
		Shutdown(true, "Failed to initialize GLEW");

	glClearColor(0, 0, 0, 255);

	od::Input::Init();
	od::Renderer::Init();

	// Set initial cursor position
	double mx, my;
	glfwGetCursorPos(m_Window->GetGLFWWindow(), &mx, &my);
	SetCursorPosition({mx, my});

	m_Font = std::make_unique<od::Font>("res/font.png", GL_NEAREST);

	m_DebugText = std::make_unique<od::UI::Text>(m_Font.get(), glm::f32vec2{0,0}, "Debug", 1, od::Colors::BLACK, od::TextAlignHorizontal::Left, od::TextAlignVertical::Top);
	m_DebugText->m_AnchoredPosition = {0,0};
}

od::Game *od::Game::GetInstance() {
	return s_Instance;
}

void od::Game::Start() {
	Ready();

	while(!glfwWindowShouldClose(m_Window->GetGLFWWindow())) {
		uint32_t deltaTime = CalculateDeltaTime();
		m_TimeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(m_FrameStartTimePoint - m_StartTimePoint).count();
		SwapScenes();
		glfwPollEvents();

		HandleUpdate(deltaTime);
		HandleTick(deltaTime);

		UpdateProjections();

		glClear(GL_COLOR_BUFFER_BIT);
		HandleRender2D();
		HandleRenderUI();

		od::Input::EndFrame();
		glfwSwapBuffers(m_Window->GetGLFWWindow());
	}
}

void od::Game::Tick(uint32_t deltaTime) {
	UpdateDebug(deltaTime);
}

void od::Game::Update(uint32_t deltaTime) {
	if(od::Input::IsKeyJustPressed(GLFW_KEY_F12))
		TakeScreenshot();

	if(od::Input::IsKeyJustPressed(GLFW_KEY_GRAVE_ACCENT))
		m_DebugText->m_Visible ^= 1;
}

void od::Game::RenderUI() {
	m_DebugText->Render();
}

void od::Game::HandleTick(uint32_t deltaTime) {
	m_TickTimer += deltaTime;
	if(m_TickTimer >= TICK_INTERVAL) {
		m_TickTimer = 0;

		Tick(deltaTime);
		if(m_Scene)
			m_Scene->Tick();
	}
}

void od::Game::HandleUpdate(uint32_t deltaTime) {
	Update(deltaTime);	
	if(m_Scene)
		m_Scene->Update(deltaTime);
}

void od::Game::HandleRender2D() {
	od::Renderer::Begin2D();

	if(m_Scene)
		m_Scene->Render2D();
	Render2D();

	od::Renderer::End2D();
}

void od::Game::HandleRenderUI() {
	od::Renderer::BeginUI();

	if(m_Scene)
		m_Scene->RenderUI();
	RenderUI();

	od::Renderer::EndUI();
}

void od::Game::Shutdown(bool error, std::string_view reason) {
	if(reason != "") {
		if(error)	OD_LOG_ERROR("Quitting, error: " << reason);
		else		OD_LOG_INFO("Quitting, reason: " << reason);
	}

	glfwSetWindowShouldClose(m_Window->GetGLFWWindow(), true);

	OnShutdown();

	m_Window.reset();
	m_Scene.reset();

	glfwTerminate();

	exit(error);
}

void od::Game::ShutdownWithoutReason() {
	Shutdown(false);
}

void od::Game::UpdateDebug(uint32_t deltaTime) {
	if(!m_DebugText->m_Visible) return;

	float deltaFloat = static_cast<std::chrono::duration<float, std::milli>>(m_FrameStartTimePoint - m_FrameEndTimePoint).count() / 1000.0f;
	int32_t fps = static_cast<int32_t>(1.f / deltaFloat);

	std::stringstream ss;
	ss 	<< "Press ~ to disable debug\n"
		<< "frame time: " << deltaTime << "us\n"
		<< "fps: " << fps << "\n"
		<< "draw calls: " << od::Renderer::drawCalls << "\n"
		<< "time: " << GetTimeSinceStartMs() / 1000.0f << "s";

	m_DebugText->m_Text = ss.str();
}

void od::Game::SetScene(std::unique_ptr<od::Scene> scene) {
	m_NextScene = std::move(scene);
}

void od::Game::HandleWindowResize(int32_t width, int32_t height) {
	UpdateViewport();
	for(auto element : m_Scene->m_UiElements)
		element->UpdateAnchoredPosition();
}

void od::Game::UpdateProjections() {
	float width = static_cast<float>(m_Window->GetWidth());
	float height = static_cast<float>(m_Window->GetHeight());
	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;

	m_Projection = glm::ortho(m_CameraPosition.x - halfWidth, m_CameraPosition.x + halfWidth, m_CameraPosition.y + halfHeight, m_CameraPosition.y - halfHeight, 0.0f, 1.0f);
	m_UIProjection = glm::ortho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
}

void od::Game::UpdateViewport() {
	glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
}

void od::Game::SwapScenes() {
	if(m_NextScene.get() == nullptr) return;

	m_Scene = std::move(m_NextScene);
	m_Scene->Awake();

	glClearColor(m_Scene->m_ClearColor.r / 255.0f, m_Scene->m_ClearColor.g / 255.0f, m_Scene->m_ClearColor.b / 255.0f, 1.0f);
}

uint32_t od::Game::CalculateDeltaTime() {
	if(m_TimeSinceStart != 0)
		m_FrameEndTimePoint = m_FrameStartTimePoint;
	else
		m_FrameEndTimePoint = std::chrono::high_resolution_clock::now();
	m_FrameStartTimePoint = std::chrono::high_resolution_clock::now();

	uint32_t deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(m_FrameStartTimePoint - m_FrameEndTimePoint).count();
	if(deltaTime < 0) deltaTime = 0; 

	return deltaTime;
}

void od::Game::TakeScreenshot(const std::string_view &path) const {
	uint8_t *pixels = new uint8_t[4 * m_Window->GetWidth() * m_Window->GetHeight()];
	glReadPixels(0, 0, m_Window->GetWidth(), m_Window->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	stbi_flip_vertically_on_write(true);
	if(!stbi_write_png(path.data(), m_Window->GetWidth(), m_Window->GetHeight(), 4, pixels, m_Window->GetWidth() * 4))
		OD_LOG_ERROR("Failed to save screenshot to file '" << path << "'");
	else
		OD_LOG_INFO("Screenshot saved to file '" << path << "'");

	delete[] pixels;
}

static void s_CursorPosCallback(GLFWwindow *win, double x, double y) {
	od::Game::GetInstance()->SetCursorPosition({x, y});
}
