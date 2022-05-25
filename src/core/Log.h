#pragma once

#include <iostream>
#include <sstream>

namespace od::Log {
#define OD_LOG_INFO(text) (std::cout << "[Info] " << text << "\n")
#define OD_LOG_ERROR(text) (std::cout << "[Error] " << text << "\n")
}
