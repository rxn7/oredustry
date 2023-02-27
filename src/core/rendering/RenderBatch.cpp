#include "RenderBatch.h"
#include "core/GLTexture.h"
#include "core/Log.h"
#include <glm/fwd.hpp>

od::RenderBatch::RenderBatch(uint8_t zIndex, Shader *shader, GLTexture *texture, uint32_t maxVertices, uint32_t maxElements)
: m_Zindex(zIndex),
m_MaxVertices(maxVertices),
m_MaxElements(maxElements),
m_Shader(shader),
m_Texture(texture),
m_Va(maxVertices, maxElements, GL_DYNAMIC_DRAW) {
	m_Vertices.reserve(maxVertices);
	m_Elements.reserve(maxElements);
}

bool od::RenderBatch::CanFit(uint32_t vertexCount, uint32_t elementCount) const {
	return m_Vertices.size() + vertexCount <= m_MaxVertices && m_Elements.size() + elementCount <= m_MaxElements;
}

void od::RenderBatch::Render() {
	while(m_Vertices.size() > m_MaxVertices)
		m_Vertices.pop_back();

	while(m_Elements.size() > m_MaxElements)
		m_Elements.pop_back();
	
	if(m_Texture != nullptr)
		m_Texture->Bind();

	m_Shader->Bind();
	m_Shader->SetUniformMat4("u_Model", glm::f32mat4(1.0f));
	m_Va.Bind();
	m_Va.SubData(m_Vertices, m_Elements);
	m_Va.Render();

	m_Elements.clear();
	m_Vertices.clear();
}