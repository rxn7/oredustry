#pragma once

#include "RenderBatch.h"
#include "core/GLTexture.h"
#include <glm/fwd.hpp>

const std::array<glm::f32vec2, 4> DEFAULT_QUAD_UVS = {
	glm::f32vec2(0,0),
	glm::f32vec2(0,1),
	glm::f32vec2(1,1),
	glm::f32vec2(1,0),
};

namespace od {
	class QuadRenderBatch : public RenderBatch {
		public:
			QuadRenderBatch(uint8_t zIndex, uint32_t maxQuads, Shader *shader, GLTexture *texture = nullptr);
			void AddQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const Color &color, const std::array<glm::f32vec2, 4> &uvs = DEFAULT_QUAD_UVS);
			bool IsFull() const;
	};
}