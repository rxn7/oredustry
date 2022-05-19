#include "Oredustry.h"
#include <sstream>
#include <chrono>

#define FONT_SIZE 16

static ALLEGRO_DISPLAY *display = nullptr;
static ALLEGRO_FONT *font = nullptr;
static ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
static std::chrono::high_resolution_clock frameClock;
static std::chrono::high_resolution_clock::time_point clockStart, clockEnd;
static std::uint32_t deltaFrame;
static bool isRunning = true;

static void UnregisterEvents();
static void RegisterEvents();
static void ProcessEvents();
static void DrawDebugText();

static void DrawDebugText() {
	std::stringstream ss;
	ss << "fps: " << (int)(1.f / (static_cast<float>(deltaFrame) / 1000.0f));
	al_draw_text(font, al_map_rgb(0, 0, 0), 0, 0, 0, ss.str().c_str());

	ss.str(std::string());
	ss << "frame: " << deltaFrame << "ms";
	al_draw_text(font, al_map_rgb(0, 0, 0), 0, FONT_SIZE, 0, ss.str().c_str());
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


void od::Start() {
	while(isRunning) {
		ProcessEvents();

		clockEnd = clockStart;
		clockStart = frameClock.now();

		deltaFrame = std::chrono::duration_cast<std::chrono::milliseconds>(clockStart - clockEnd).count();

		al_clear_to_color(al_map_rgb(255, 255, 255));
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
		Shutdown(EXIT_FAILURE, "Failed to initialize allegro\n");

	if(!al_init_font_addon())
		Shutdown(EXIT_FAILURE, "Failed to initialize allegro_font\n");

	if(!al_init_ttf_addon())
		Shutdown(EXIT_FAILURE, "Failed to initialize allegro_ttf");

	if(!(display = al_create_display(640, 480)))
		Shutdown(EXIT_FAILURE, "Failed to create display");

	if(!(font = al_load_ttf_font("font.ttf", FONT_SIZE, 0)))
		Shutdown(EXIT_FAILURE, "Failed to load font, you are probably missing the font.ttf file");

	if(!(event_queue = al_create_event_queue()))
		Shutdown(EXIT_FAILURE, "Failed to create event queue");

	al_set_window_title(display, "Oredustry");
	RegisterEvents();
}

void od::Log(std::string_view text) {
	std::cout << "[Info] " << text << "\n";
}

void od::LogError(std::string_view text) {
	std::cout << "[Error] " << text << "\n";
}
