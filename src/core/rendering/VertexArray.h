#pragma once

#include "../Libs.h"
#include "Vertex.h"
#include <vector>

namespace od {
	class VertexArray {
	public:
		VertexArray(const std::vector<od::Vertex> &vertices, int32_t target);
		VertexArray(int32_t vertexCount, int32_t target);
		~VertexArray();
		void Bind();
		void Unbind();
		void Render();
		void SetData(const std::vector<od::Vertex> &vertices, int32_t target);
		void SubData(const std::vector<od::Vertex> &vertices);

	private:
		void Init();

	private:
		uint32_t m_ID;
		uint32_t m_VertexCount;
		uint32_t m_VertexBuffer;
	};
}
