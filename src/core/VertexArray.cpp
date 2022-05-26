#include "VertexArray.h"

od::VertexArray::VertexArray() {
}

void od::VertexArray::Bind() {
	glBindVertexArray(m_ID);
}

void od::VertexArray::Unbind() {
	glBindVertexArray(0);
}
