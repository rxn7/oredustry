#include "Oredustry.h"
#include "SplashScreenScene.h"
#include <sstream>
#include <chrono>

SDL_Window *od::window = nullptr;
SDL_Renderer *od::renderer = nullptr;
TTF_Font *od::font = nullptr;

static od::UI::Text debugText;
static std::chrono::high_resolution_clock hrClock;
static std::chrono::high_resolution_clock::time_point clockStart, clockFrameStart, clockFrameEnd;
static std::unique_ptr<od::Scene> currentScene;
static uint32_t deltaTime = 0;
static uint32_t timeSinceStart = 0;
static bool isRunning = true;
static bool showDebug = true;
static int32_t windowWidth = 0, windowHeight = 0;

static void CalculateFrameDelta();
static void ProcessEvents();
static void DrawDebugText();

static void DrawDebugText() {
	if(!showDebug) return;

	std::chrono::duration<float, std::milli> timeDeltaFloat = clockFrameStart - clockFrameEnd;
	int32_t fps = static_cast<int32_t>(1000.f / timeDeltaFloat.count());

	std::stringstream ss;
	ss << "frame: " << deltaTime << "ms\n" << "fps: " << fps << "\nPress ~ to toggle debug";

	debugText.SetText(ss.str());
	debugText.Render();
}

static void ProcessEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) { 
			case SDL_QUIT:
				od::Shutdown(0, "Window has been closed");
				break;
				
			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(od::window, &windowWidth, &windowHeight);
				break;
		}
	}
}

static void CalculateFrameDelta() {
	if(timeSinceStart != 0)
		clockFrameEnd = clockFrameStart;
	else
		clockFrameEnd = hrClock.now();

	clockFrameStart = hrClock.now();
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(clockFrameStart - clockFrameEnd).count();
	if(deltaTime < 0) deltaTime = 0; 
	timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(clockFrameStart - clockStart).count();
}

void od::Start() {
	clockStart = hrClock.now();
	od::LoadScene(std::unique_ptr<SplashScreenScene>(new SplashScreenScene));

	while(isRunning) {
		CalculateFrameDelta();
		ProcessEvents();
		od::Input::Update();

		// Toggle showDebug on tilde press
		if(od::Input::IsKeyJustPressed(SDLK_BACKQUOTE))
			showDebug = !showDebug;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		if(currentScene != nullptr) {
			currentScene->Update(deltaTime, timeSinceStart);
			currentScene->Draw();
			currentScene->DrawUI();
		}

		DrawDebugText();

		SDL_RenderPresent(renderer);
	}
}

void od::Shutdown(int code, std::string_view reason) {
	std::stringstream ss;
	ss << "Quitting, reason: " << reason;

	if(code)	od::LogError(ss.str());
	else		od::Log(ss.str());

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	TTF_Quit();

	exit(code);
}

void od::Init() {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		od::Shutdown(EXIT_FAILURE, "Failed to initialize SDL");

	if(TTF_Init() != 0)
		od::Shutdown(EXIT_FAILURE, "Failed to initialize SDL_ttf");

	if(!IMG_Init(IMG_INIT_PNG))
		od::Shutdown(EXIT_FAILURE, "Failed to initialize SDL_image: " + std::string(IMG_GetError()));

	if(!(od::window = SDL_CreateWindow("Oredustry", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)))
		od::Shutdown(EXIT_FAILURE, "Failed to create the window: " + std::string(SDL_GetError()));

	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	if(!(od::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)))
		od::Shutdown(EXIT_FAILURE, "Failed to create the renderer: " + std::string(SDL_GetError()));

	od::Input::Init();
	od::font = TTF_OpenFont("res/font.ttf", FONT_SIZE);
	debugText = od::UI::Text(od::font, 0, 0, SDL_Color{0, 0, 0, 255}, "Debug");
}

void od::LoadScene(std::unique_ptr<Scene> scene) {
	currentScene = std::move(scene);
	currentScene->Awake();
}

int32_t od::GetWindowWidth() {
	return windowWidth;
}

int32_t od::GetWindowHeight() {
	return windowHeight;
}