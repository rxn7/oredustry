#include "VertexArray.h"
#include "core/Log.h"
#include "core/rendering/Renderer.h"

od::VertexArray::VertexArray(const std::vector<od::Vertex> &vertices, const std::vector<uint16_t> &elements, int32_t target) :
m_ElementCount(elements.size()),
m_VertexCount(vertices.size()) {
	Init();
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(od::Vertex), vertices.data(), target);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ElementCount * sizeof(uint16_t), elements.data(), target);
}

od::VertexArray::VertexArray(uint32_t vertexCount, uint32_t elementCount, int32_t target) :
m_ElementCount(elementCount),
m_VertexCount(vertexCount) {
	Init();
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(od::Vertex), NULL, target);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(uint16_t), NULL, target);
}

void od::VertexArray::Init() {
	glCreateVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);

	glCreateBuffers(1, &m_VertexBuffer);
	glCreateBuffers(1, &m_ElementBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(od::Vertex), (void*)offsetof(od::Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(od::Vertex), (void*)offsetof(od::Vertex, texCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, true, sizeof(od::Vertex), (void*)offsetof(od::Vertex, color));
}

void od::VertexArray::SetData(const std::vector<od::Vertex> &vertices, const std::vector<uint16_t> &elements, int32_t target) {
	m_VertexCount = vertices.size();
	m_ElementCount = elements.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(od::Vertex), vertices.data(), target);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_ElementCount * sizeof(uint16_t), elements.data(), target);
}

void od::VertexArray::SubData(const std::vector<od::Vertex> &vertices, const std::vector<uint16_t> &elements) {
	m_VertexCount = vertices.size();
	m_ElementCount = elements.size();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_VertexCount * sizeof(od::Vertex), vertices.data());
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_ElementCount * sizeof(uint16_t), elements.data());
}

od::VertexArray::~VertexArray() {
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_ElementBuffer);
	glDeleteProgram(m_ID);
}

void od::VertexArray::Render() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glDrawElements(GL_TRIANGLES, m_ElementCount, GL_UNSIGNED_SHORT, 0);
	od::Renderer::drawCalls++;
}