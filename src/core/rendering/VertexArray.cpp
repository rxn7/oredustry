#include "VertexArray.h"
#include "core/Log.h"

od::VertexArray::VertexArray(const std::vector<od::Vertex> &vertices) :
m_VertexCount(vertices.size()) {
	Init();
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(od::Vertex), vertices.data(), GL_STATIC_DRAW);
}

od::VertexArray::VertexArray() {
	Init();
}

void od::VertexArray::Init() {
	glCreateVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);

	glCreateBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(od::Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(od::Vertex), (void*)sizeof(glm::f32vec2));
}

void od::VertexArray::SetVertices(const std::vector<od::Vertex> &vertices) {
	Bind(); m_VertexCount = vertices.size();
	glBufferData(GL_ARRAY_BUFFER, m_VertexCount * sizeof(od::Vertex), vertices.data(), GL_STATIC_DRAW);
}

od::VertexArray::~VertexArray() {
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteProgram(m_ID);
}

void od::VertexArray::Bind() {
	glBindVertexArray(m_ID);
}

void od::VertexArray::Unbind() {
	glBindVertexArray(0);
}

void od::VertexArray::Render() {
	Bind();
	glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
}