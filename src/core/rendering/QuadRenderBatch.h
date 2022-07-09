#pragma once

#include "RenderBatch.h"

namespace od {
	class QuadRenderBatch : public RenderBatch {
		public:
			QuadRenderBatch(uint8_t zIndex, uint32_t maxQuads, Shader *shader);
			void AddQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const Color &color);
			bool IsFull() const;
	};
}