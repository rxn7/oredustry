#pragma once
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

namespace od {
	void Init();
	void Shutdown(int code = EXIT_SUCCESS, std::string_view reason = "");
	void Start();
	void Log(std::string_view text);
	void LogError(std::string_view text);
}
