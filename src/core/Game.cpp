#include "Game.h"
#include "Input.h"
#include "rendering/Renderer.h"
#include "Log.h"
#include <glm/gtc/matrix_transform.hpp>

static od::Game *s_Instance;

od::Game::Game(const od::WindowParameters &params) {
	s_Instance = this;

	m_StartTimePoint = std::chrono::high_resolution_clock::now();

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		Shutdown(true, "Failed to initialize SDL");

	m_Window = std::make_unique<Window>(params);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_GLCtx = SDL_GL_CreateContext(m_Window->GetSDLWindow());
	if(!m_GLCtx)
		Shutdown(true, "Failed to create OpenGL context");

	glewExperimental = true;
	if(glewInit() != GLEW_OK)
		Shutdown(true, "Failed to initialize GLEW");

	SDL_GL_SetSwapInterval(0);

	glClearColor(0, 0, 0, 255);

	od::Input::Init();
	od::Renderer::Init();
}

od::Game *od::Game::GetInstance() {
	return s_Instance;
}

void od::Game::Shutdown(bool error, std::string_view reason) {
	if(error)	OD_LOG_ERROR("Quitting, error: " << reason);
	else		OD_LOG_INFO("Quitting, reason: " << reason);

	m_IsRunning = false;

	OnShutdown();

	m_Window.reset();
	m_Scene.reset();

	SDL_GL_DeleteContext(m_GLCtx);
	SDL_Quit();

	exit(error);
}

void od::Game::SetScene(std::unique_ptr<od::Scene> scene) {
	m_NextScene = std::move(scene);
}

void od::Game::Start() {
	Awake();

	while(m_IsRunning) {
		UpdateViewport();
		CalculateDeltaTime();
		m_TimeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(m_FrameStartTimePoint - m_StartTimePoint).count();
		SwapScenes();

		if(m_LastWindowSize != m_Window->GetSize() && m_Scene)
			for(auto element : m_Scene->m_UiElements)
				element->UpdateAnchoredPosition();
		m_LastWindowSize = m_Window->GetSize();

		od::Input::Update();
		PollEvents();

		m_Projection = glm::ortho(m_CameraPosition.x, m_CameraPosition.x + static_cast<float>(od::Game::GetInstance()->GetWindow().GetWidth()), m_CameraPosition.y + static_cast<float>(od::Game::GetInstance()->GetWindow().GetHeight()), m_CameraPosition.y, 0.0f, 1.0f);
		m_UIProjection = glm::ortho(0.0f, static_cast<float>(od::Game::GetInstance()->GetWindow().GetWidth()), static_cast<float>(od::Game::GetInstance()->GetWindow().GetHeight()), 0.0f, 0.0f, 1.0f);

		// Update
		Update(m_DeltaTime);	
		if(m_Scene)
			m_Scene->Update(m_DeltaTime);

		glClear(GL_COLOR_BUFFER_BIT);

		// 2D Rendering
		od::Renderer::Begin2D();
		if(m_Scene)
			m_Scene->Draw();
		Draw();
		od::Renderer::End2D();

		// UI Renderign
		od::Renderer::BeginUI();
		if(m_Scene)
			m_Scene->DrawUI();
		DrawUI();
		od::Renderer::EndUI();

		SDL_GL_SwapWindow(m_Window->GetSDLWindow());
	}
}

void od::Game::PollEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) { 
			case SDL_QUIT:
				Shutdown(false, "Window has been closed");
				break;
				
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&m_CursorPosition.x, &m_CursorPosition.y);
				break;

			case SDL_WINDOWEVENT:
				m_Window->ProcessWindowEvent(event.window);
				UpdateViewport();
				break;
		}

		if(m_Scene)
			m_Scene->ProcessEvent(event);
	}
}

void od::Game::UpdateViewport() {
	glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
}

void od::Game::SwapScenes() {
	if(m_NextScene.get() == nullptr) return;

	m_Scene = std::move(m_NextScene);
	m_Scene->Awake();

	glClearColor(m_Scene->m_ClearColor.r / 255.0f, m_Scene->m_ClearColor.g / 255.0f, m_Scene->m_ClearColor.b / 255.0f, 255);
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
