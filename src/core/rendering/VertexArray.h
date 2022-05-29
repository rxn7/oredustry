#pragma once

#include "../Libs.h"
#include "Vertex.h"
#include <vector>

namespace od {
	class VertexArray {
	public:
		VertexArray(const std::vector<od::Vertex> &vertices);
		VertexArray();
		~VertexArray();
		void Bind();
		void Unbind();
		void Render();
		void SetVertices(const std::vector<od::Vertex> &vertices);

	private:
		void Init();

	private:
		uint32_t m_ID;
		uint32_t m_VertexCount;
		uint32_t m_VertexBuffer;
	};
}
