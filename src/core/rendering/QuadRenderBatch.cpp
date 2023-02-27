#include "QuadRenderBatch.h"
#include "core/GLTexture.h"
#include "core/Log.h"

od::QuadRenderBatch::QuadRenderBatch(uint8_t zIndex, uint32_t maxQuads, Shader *shader, GLTexture *texture) :
od::RenderBatch(zIndex, shader, texture, maxQuads*4, maxQuads*6) {
}

void od::QuadRenderBatch::AddQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const Color &color, const std::array<glm::f32vec2, 4> &uvs) {
	const float halfWidth = size.x * 0.5f;
	const float halfHeight = size.y * 0.5f;
	
	const uint32_t vertCount = m_Vertices.size();

	AddVertex({glm::f32vec2{position.x-halfWidth, position.y-halfHeight}, uvs[0], color});
	AddVertex({glm::f32vec2{position.x-halfWidth, position.y+halfHeight}, uvs[1], color});
	AddVertex({glm::f32vec2{position.x+halfWidth, position.y+halfHeight}, uvs[2], color});
	AddVertex({glm::f32vec2{position.x+halfWidth, position.y-halfHeight}, uvs[3], color});
	
	AddElement(vertCount);
	AddElement(vertCount+1);
	AddElement(vertCount+2);
	AddElement(vertCount+2);
	AddElement(vertCount+3);
	AddElement(vertCount);
}

bool od::QuadRenderBatch::IsFull() const {
	return !CanFit(4, 6);
}