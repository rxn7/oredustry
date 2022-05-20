#pragma once
#include <iostream>
#include <memory>
#include "core/Core.h"
#define FONT_SIZE 16

namespace od {
	void Init();
	void Shutdown(int code = EXIT_SUCCESS, std::string_view reason = "");
	void Start();
	void LoadScene(std::unique_ptr<Scene> scene);
}
