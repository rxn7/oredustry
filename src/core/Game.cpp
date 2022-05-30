#include "Game.h"
#include "Input.h"
#include "rendering/Renderer.h"
#include "Log.h"
#include <glm/gtc/matrix_transform.hpp>

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

	if(FT_Init_FreeType(&m_Ft) != 0)
		Shutdown(true, "Failed to initialize FreeType");

	glClearColor(0, 0, 0, 255);

	od::Input::Init();
	od::Renderer::Init();
}

od::Game *od::Game::GetInstance() {
	return s_Instance;
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
	FT_Done_FreeType(m_Ft);

	exit(error);
}

void od::Game::ShutdownWithoutReason() {
	Shutdown(false);
}

void od::Game::SetScene(std::unique_ptr<od::Scene> scene) {
	m_NextScene = std::move(scene);
}

void od::Game::HandleWindowResize(int32_t width, int32_t height) {
	UpdateViewport();
	for(auto element : m_Scene->m_UiElements)
		element->UpdateAnchoredPosition();
}

void od::Game::Start() {
	Awake();

	while(!glfwWindowShouldClose(m_Window->GetGLFWWindow())) {
		CalculateDeltaTime();
		m_TimeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(m_FrameStartTimePoint - m_StartTimePoint).count();
		SwapScenes();

		glfwPollEvents();

		// Update
		Update(m_DeltaTime);	
		if(m_Scene)
			m_Scene->Update(m_DeltaTime);

		UpdateProjections();
		glClear(GL_COLOR_BUFFER_BIT);

		// 2D Rendering
		od::Renderer::Begin2D();
		if(m_Scene)
			m_Scene->Draw();
		Draw();
		od::Renderer::End2D();

		// UI Rendering
		od::Renderer::BeginUI();
		if(m_Scene)
			m_Scene->DrawUI();
		DrawUI();
		od::Renderer::EndUI();

		od::Input::EndFrame();
		glfwSwapBuffers(m_Window->GetGLFWWindow());
	}
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

	glClearColor(m_Scene->m_ClearColor.r, m_Scene->m_ClearColor.g, m_Scene->m_ClearColor.b, 1.0f);
}

void od::Game::CalculateDeltaTime() {
	if(m_TimeSinceStart != 0)
		m_FrameEndTimePoint = m_FrameStartTimePoint;
	else
		m_FrameEndTimePoint = std::chrono::high_resolution_clock::now();

	m_FrameStartTimePoint = std::chrono::high_resolution_clock::now();

	m_DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(m_FrameStartTimePoint - m_FrameEndTimePoint).count();
	if(m_DeltaTime < 0) m_DeltaTime = 0; 
}

static void s_CursorPosCallback(GLFWwindow *win, double x, double y) {
	od::Game::GetInstance()->SetCursorPosition({x, y});
}
