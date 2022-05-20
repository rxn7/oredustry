#pragma once

#include <iostream>
#include <sstream>

namespace od {
	inline void Log(std::string_view text) {
		std::cout << "[Info] " << text << "\n";
	}

	inline void LogError(std::string_view text) {
		std::cout << "[Error] " << text << "\n";
	}
}
