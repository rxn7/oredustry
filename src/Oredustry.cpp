#include "Oredustry.h"
#include "core/Input.h"
#include "SplashScreen.h"
#include <sstream>
#include <chrono>

static ALLEGRO_DISPLAY *display = nullptr;
static ALLEGRO_FONT *font = nullptr;
static ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
static std::chrono::high_resolution_clock frameClock;
static std::chrono::high_resolution_clock::time_point clockStart, clockEnd;
static std::unique_ptr<od::Scene> currentScene;
static uint32_t frameDelta;
static bool isRunning = true;
static bool showDebug = true;

static void CalculateFrameDelta();
static void UnregisterEvents();
static void RegisterEvents();
static void ProcessEvents();
static void DrawDebugText();

static void DrawDebugText() {
	if(!showDebug) return;

	float frameDeltaSeconds = static_cast<float>(frameDelta) / 1000.f;

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
	clockEnd = clockStart;
	clockStart = frameClock.now();
	frameDelta = std::chrono::duration_cast<std::chrono::milliseconds>(clockStart - clockEnd).count();
}

void od::Start() {
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
			currentScene->Update(frameDelta);
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

	if(!(display = al_create_display(640, 480)))
		od::Shutdown(EXIT_FAILURE, "Failed to create display");

	if(!(font = al_load_ttf_font("font.ttf", FONT_SIZE, 0)))
		od::Shutdown(EXIT_FAILURE, "Failed to load font, you are probably missing the font.ttf file");

	if(!(event_queue = al_create_event_queue()))
		od::Shutdown(EXIT_FAILURE, "Failed to create event queue");

	al_set_window_title(display, "Oredustry");
	RegisterEvents();
}

void od::Log(std::string_view text) {
	std::cout << "[Info] " << text << "\n";
}

void od::LogError(std::string_view text) {
	std::cout << "[Error] " << text << "\n";
}

void od::LoadScene(std::unique_ptr<Scene> scene) {
	currentScene = std::move(scene);
	currentScene->Awake();
}
