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
	};

	class Font : public od::Asset {
	public:
		Font(const std::string &path, int32_t size);
		virtual ~Font();

		inline FT_Face &GetFace() const { return m_Face; }

		inline const Character &GetCharacter(unsigned char c) const {
			std::map<unsigned char, Character>::const_iterator it = m_Characters.find(c);
			if(it != m_Characters.end())
				return m_Characters.at(c); 

			return m_Characters.at(0);
		}

		inline const od::GLTexture &GetTexture() const { return *m_Texture; }
	
	private:
		mutable FT_Face m_Face;
		std::unique_ptr<od::GLTexture> m_Texture;
		std::map<unsigned char, Character> m_Characters;
	};
}