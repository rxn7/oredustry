#pragma once

#include "../Libs.h"
#include "Vertex.h"
#include <vector>

namespace od {
	class VertexArray {
	public:
		VertexArray(const std::vector<od::Vertex> &vertices, const std::vector<uint16_t> &elements, int32_t target);
		VertexArray(uint32_t vertexCount, uint32_t elementCount, int32_t target);
		~VertexArray();
		inline void Bind() const { glBindVertexArray(m_ID); }
		inline void Unbind() const { glBindVertexArray(0); }
		void Render() const;
		void SetData(const std::vector<od::Vertex> &vertices, const std::vector<uint16_t> &elements, int32_t target);
		void SubData(const std::vector<od::Vertex> &vertices, const std::vector<uint16_t> &elements);

	private:
		void Init();

	private:
		uint32_t m_ID;
		uint32_t m_ElementCount;
		uint32_t m_VertexCount;
		uint32_t m_VertexBuffer;
		uint32_t m_ElementBuffer;
	};
}
