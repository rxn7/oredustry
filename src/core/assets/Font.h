#pragma once

#include "core/Asset.h"
#include "core/GLTexture.h"
#include "core/Libs.h"
#include <map>

namespace od {
	struct Character {
		glm::i32vec2 size;
		glm::i32vec2 bearing;
		FT_Pos advance;
		std::unique_ptr<od::GLTexture> texture;
	};

	class Font : public od::Asset {
	public:
		Font(const std::string &path, int32_t size, int32_t filter = GL_LINEAR);
		virtual ~Font();

		inline FT_Face &GetFace() const { return m_Face; }
		inline float GetHeight() const { return m_Height; }
		float GetTextWidth(const std::string &text, float scale) const;
		const Character &GetCharacter(unsigned char c) const;
	
	private:
		mutable FT_Face m_Face;
		std::map<unsigned char, Character> m_Characters;
		float m_Height;
	};
}
