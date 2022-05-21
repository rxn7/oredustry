#pragma once

#include <iostream>
#include <sstream>

namespace od::Log {
	inline void Info(std::string_view text) {
		std::cout << "[Info] " << text << "\n";
	}

	inline void Error(std::string_view text) {
		std::cout << "[Error] " << text << "\n";
	}
}
