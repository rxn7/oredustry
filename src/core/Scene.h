#pragma once

#include "Core.h"

namespace od {
	class Scene {
	public:
		virtual void Awake() {}
		virtual void Update(uint32_t frameDelta, uint32_t timeSinceEpoch) {}
		virtual void Draw() {}
		virtual void DrawUI() {}
	};
}
