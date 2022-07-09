#pragma once

#include "Shader.h"
#include "VertexArray.h"


namespace od {
	class RenderBatch {
		public:
			RenderBatch(uint8_t zIndex, Shader *shader, uint32_t maxVertices = 1000, uint32_t maxElements = 2000);
			void Render();
			bool CanFit(uint32_t vertexCount, uint32_t elementCount) const;

			inline void Bind() const { m_Va.Bind(); }
			inline void AddVertex(const od::Vertex& vert) { m_Vertices.push_back(vert); }
			inline void AddElement(uint16_t element) { m_Elements.push_back(element); }
			inline uint32_t GetVertexCount() const { return m_Vertices.size(); }
			inline uint32_t GetElementCount() const { return m_Elements.size(); }
			inline uint8_t GetZIndex() const { return m_Zindex; }

		protected:
			uint32_t m_MaxVertices;
			uint32_t m_MaxElements;
			uint8_t m_Zindex;
			VertexArray m_Va;
			std::vector<od::Vertex> m_Vertices;	
			std::vector<uint16_t> m_Elements;
			Shader *m_Shader;
	};
}