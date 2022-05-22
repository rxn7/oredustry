#include "Core.h"
#include "Log.h"
#include "Input.h"
#include "Scene.h"
#include "Oredustry.h"

SDL_Window *od::Core::window = nullptr;
SDL_Renderer *od::Core::renderer = nullptr;
TTF_Font *od::Core::font = nullptr;

static std::unique_ptr<od::Scene> nextScene, currentScene;
static std::chrono::high_resolution_clock::time_point clockStart, clockFrameStart, clockFrameEnd;
static od::Vector2i pointerPosition;
static uint32_t timeSinceStart = 0, deltaTime = 0;
static od::Vector2i screenSize;

static void CalculateFrameDelta();
static void ProcessEvents();

void od::Core::Init() {
	clockStart = std::chrono::high_resolution_clock::now();

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		od::Core::Shutdown(EXIT_FAILURE, "Failed to initialize SDL");

	if(TTF_Init() != 0)
		od::Core::Shutdown(EXIT_FAILURE, "Failed to initialize SDL_ttf");

	if(!IMG_Init(IMG_INIT_PNG))
		od::Core::Shutdown(EXIT_FAILURE, "Failed to initialize SDL_image: " + std::string(IMG_GetError()));

	if(!(od::Core::window = SDL_CreateWindow("Oredustry", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)))
		od::Core::Shutdown(EXIT_FAILURE, "Failed to create the window: " + std::string(SDL_GetError()));

	if(!(od::Core::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
		od::Core::Shutdown(EXIT_FAILURE, "Failed to create the renderer: " + std::string(SDL_GetError()));

	SDL_SetWindowIcon(window, IMG_Load("res/logo.png"));

	od::Input::Init();
	od::Core::font = od::Core::LoadFont("res/font.ttf", FONT_SIZE);
}

void od::Core::Shutdown(int code, std::string_view reason) {
	std::stringstream ss;
	ss << "Quitting, reason: " << reason;

	if(code)	od::Log::Error(ss.str());
	else		od::Log::Info(ss.str());

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();

	exit(code);
}

void od::Core::Start() {
	od::Oredustry::Start();

	while(true) {
		CalculateFrameDelta();
		timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(clockFrameStart - clockStart).count();

		// If next scene is queued, change the currentScene to the nextScene
		if(nextScene) {
			currentScene = std::move(nextScene);
			currentScene->Awake();
		}

		od::Input::Update();
		ProcessEvents();

		SDL_GetWindowSize(od::Core::window, &screenSize.x, &screenSize.y);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		od::Oredustry::Update(deltaTime);	

		if(currentScene != nullptr) {
			currentScene->Update(deltaTime);
			currentScene->Draw();
			currentScene->DrawUI();
		}

		od::Oredustry::Draw();
		od::Oredustry::DrawUI();

		SDL_RenderPresent(renderer);
	}
}

SDL_Texture *od::Core::LoadTexture(std::string_view path) {
	SDL_Texture *texture = IMG_LoadTexture(od::Core::renderer, path.data());
	if(!texture) {
		std::stringstream ss;
		ss << "Failed to load texture: '" << path << "': " << IMG_GetError();
		od::Log::Error(ss.str());
		return nullptr;
	}

	return texture;
}

TTF_Font *od::Core::LoadFont(std::string_view path, int32_t size) {
	TTF_Font *font = TTF_OpenFont(path.data(), size);
	if(!font) {
		std::stringstream ss;
		ss << "Failed to load font: '" << path << "': " << TTF_GetError();
		od::Log::Error(ss.str());
		return nullptr;
	}

	return font;
}

static void CalculateFrameDelta() {
	if(timeSinceStart != 0)
		clockFrameEnd = clockFrameStart;
	else
		clockFrameEnd = std::chrono::high_resolution_clock::now();

	clockFrameStart = std::chrono::high_resolution_clock::now();

	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(clockFrameStart - clockFrameEnd).count();
	if(deltaTime < 0) deltaTime = 0; 
}

static void ProcessEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) { 
			case SDL_QUIT:
				od::Core::Shutdown(0, "Window has been closed");
				break;
				
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&pointerPosition.x, &pointerPosition.y);
				break;
		}

		if(currentScene)
			currentScene->ProcessEvent(event);
	}
}

void od::Core::SetScene(std::unique_ptr<Scene> scene) {
	nextScene = std::move(scene);
}

od::Vector2i od::Core::GetPointerPosition() {
	return pointerPosition;
}

int32_t od::Core::GetScreenWidth() {
	return screenSize.x;
}

int32_t od::Core::GetScreenHeight() {
	return screenSize.y;
}

uint32_t od::Core::GetTimeSinceStart() {
	return timeSinceStart;
}

float od::Core::CalculateFrameDeltaTimeMilliFloat() {
	return static_cast<std::chrono::duration<float, std::milli>>(clockFrameStart - clockFrameEnd).count();
}

uint32_t od::Core::GetFrameDeltaTime() {
	return deltaTime;
}
