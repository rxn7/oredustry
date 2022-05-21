#pragma once
#include <iostream>
#include <memory>
#include <string_view>
#include "core/Core.h"
#include "core/Scene.h"
#include "core/Vector2.h"

namespace od::Oredustry {
	extern TTF_Font *font;

	void SetScene(std::unique_ptr<Scene> scene);
	void Start();
	void Update(uint32_t deltaTime);
	void Draw();
	void DrawUI();
}
