#pragma once

#include "core/Asset.h"
#include "core/assets/Texture.h"
#include "core/Libs.h"
#include <map>

namespace od {
	class Font {
	public:
		Font(od::Texture *texture, int32_t filter = GL_LINEAR, float size=2);
		virtual ~Font();
		void GetCharUV(char c, glm::f32vec2 &start, glm::f32vec2 &end);
		inline const od::Texture &GetTexture() const { return *m_Texture; }
		inline float GetSize() const { return m_Size; }
		inline float GetCharWidth() const { return m_CharSize.x; }
		inline float GetCharHeight() const { return m_CharSize.y; }
		float GetTextWidth(uint32_t length, float scale=1) const;

	private:
		od::Texture *m_Texture;
		glm::i32vec2 m_CharSize;
		glm::f32vec2 m_CharSizeNorm;
		float m_Size;
	};
}
