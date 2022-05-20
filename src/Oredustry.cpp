#include "Oredustry.h"
#include "SplashScreenScene.h"
#include <sstream>
#include <chrono>

static ALLEGRO_DISPLAY *display = nullptr;
static ALLEGRO_FONT *font = nullptr;
static ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
static std::chrono::high_resolution_clock hrClock;
static std::chrono::high_resolution_clock::time_point clockStart, clockFrameStart, clockFrameEnd;
static std::unique_ptr<od::Scene> currentScene;
static uint32_t deltaTime = 0;
static uint32_t timeSinceStart = 0;
static bool isRunning = true;
static bool showDebug = true;

static void CalculateFrameDelta();
static void UnregisterEvents();
static void RegisterEvents();
static void ProcessEvents();
static void DrawDebugText();

static void DrawDebugText() {
	if(!showDebug) return;

	float frameDeltaSeconds = static_cast<float>(deltaTime) / 1000.f;

	al_draw_multiline_textf(font, al_map_rgb(0, 0, 0), 0, 0, al_get_display_width(display), FONT_SIZE, 0, 
		"frame: %fms\n"
		"fps: %i\n"
		"Press ~ to toggle debug", 
		frameDeltaSeconds, static_cast<int>((1.f / frameDeltaSeconds)));
}

static void RegisterEvents() {
	al_register_event_source(event_queue, al_get_display_event_source(display));
}

static void UnregisterEvents() {
	al_unregister_event_source(event_queue, al_get_display_event_source(display));
}

static void ProcessEvents() {
	ALLEGRO_EVENT event;
	while(al_peek_next_event(event_queue, &event)) {
		switch(event.type) { 
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				od::Shutdown(0, "Display has been closed");
				break;
		}

		al_drop_next_event(event_queue);
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
		if(od::Input::IsKeyJustPressed(ALLEGRO_KEY_TILDE))
			showDebug = !showDebug;

		al_clear_to_color(al_map_rgb(255, 255, 255));

		if(currentScene != nullptr) {
			currentScene->Update(deltaTime, timeSinceStart);
			currentScene->Draw(display);
			currentScene->DrawUI(display, font);
		}

		DrawDebugText();

		al_flip_display();
	}
}

void od::Shutdown(int code, std::string_view reason) {
	std::stringstream ss;
	ss << "Quitting, reason: " << reason;

	if(code)	od::LogError(ss.str());
	else		od::Log(ss.str());

	UnregisterEvents();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_destroy_font(font);

	exit(code);
}

void od::Init() {
	if(!al_init())
		od::Shutdown(EXIT_FAILURE, "Failed to initialize allegro\n");

	if(!al_install_keyboard())
		od::Shutdown(EXIT_FAILURE, "Failed to install keyboard\n");

	if(!al_init_font_addon())
		od::Shutdown(EXIT_FAILURE, "Failed to initialize allegro_font\n");

	if(!al_init_ttf_addon())
		od::Shutdown(EXIT_FAILURE, "Failed to initialize allegro_ttf");

	if(!al_init_image_addon())
		od::Shutdown(EXIT_FAILURE, "Failed to initialize allegro_image");

	if(!(display = al_create_display(1280, 720)))
		od::Shutdown(EXIT_FAILURE, "Failed to create display");

	if(!(font = al_load_ttf_font("res/font.ttf", FONT_SIZE, 0)))
		od::Shutdown(EXIT_FAILURE, "Failed to load font, you are probably missing the font.ttf file");

	if(!(event_queue = al_create_event_queue()))
		od::Shutdown(EXIT_FAILURE, "Failed to create event queue");

	al_set_window_title(display, "Oredustry");
	RegisterEvents();
}

void od::LoadScene(std::unique_ptr<Scene> scene) {
	currentScene = std::move(scene);
	currentScene->Awake();
}
