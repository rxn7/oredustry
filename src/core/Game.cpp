#include "Game.h"
#include "Input.h"
#include "Renderer.h"
#include "Log.h"

static od::Game *s_Instance;

od::Game::Game(const od::WindowParameters &params) {
	s_Instance = this;

	m_ClockStart = std::chrono::high_resolution_clock::now();

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		Shutdown(true, "Failed to initialize SDL");

	if(TTF_Init() != 0)
		Shutdown(true, "Failed to initialize SDL_ttf");

	if(!IMG_Init(IMG_INIT_PNG))
		Shutdown(true, "Failed to initialize SDL_image: " + std::string(IMG_GetError()));

	m_Window = std::make_unique<Window>(params);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // TODO: Move to core profile
	m_GLCtx = SDL_GL_CreateContext(m_Window->GetSDLWindow());
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
	TTF_Quit();

	exit(error);
}

void od::Game::SetScene(std::unique_ptr<od::Scene> scene) {
	m_NextScene = std::move(scene);
}

void od::Game::Start() {
	Awake();

	while(m_IsRunning) { UpdateViewport();
		CalculateDeltaTime();
		m_TimeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(m_ClockFrameStart - m_ClockStart).count();
		SwapScenes();

		if(m_LastWindowSize != m_Window->GetSize() && m_Scene)
			for(auto element : m_Scene->m_UiElements)
				element->UpdateAnchoredPosition();
		m_LastWindowSize = m_Window->GetSize();

		od::Input::Update();
		PollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		Update(m_DeltaTime);	

		if(m_Scene.get() != nullptr) {
			m_Scene->Update(m_DeltaTime);
			m_Scene->Draw();
			m_Scene->DrawUI();
		}

		Draw();
		DrawUI();

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
	glOrtho(0.0f, m_Window->GetWidth(), m_Window->GetHeight(), 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

void od::Game::SwapScenes() {
	if(m_NextScene.get() == nullptr) return;

	m_Scene = std::move(m_NextScene);
	m_Scene->Awake();

	glClearColor(m_Scene->m_ClearColor.r / 255.0f, m_Scene->m_ClearColor.g / 255.0f, m_Scene->m_ClearColor.b / 255.0f, 255);
}

void od::Game::CalculateDeltaTime() {
	if(m_TimeSinceStart != 0)
		m_ClockFrameEnd = m_ClockFrameStart;
	else
		m_ClockFrameEnd = std::chrono::high_resolution_clock::now();

	m_ClockFrameStart = std::chrono::high_resolution_clock::now();

	m_DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(m_ClockFrameStart - m_ClockFrameEnd).count();
	if(m_DeltaTime < 0) m_DeltaTime = 0; 
}
