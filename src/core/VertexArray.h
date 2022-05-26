#pragma once

#include "Libs.h"

namespace od {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();
		void Bind();
		void Unbind();

	private:
		uint32_t m_ID;
		uint32_t m_VertexBuffer;
		uint32_t m_IndexBuffer;
	};
}
