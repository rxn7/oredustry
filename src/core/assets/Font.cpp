#include "Font.h"
#include "core/Game.h"
#include "stb_image_write.h"

// TODO(optimization): Pack all glyph into a single texture
od::Font::Font(const std::string &path, int32_t size, int32_t filter) : od::Asset(path) {
	if(FT_New_Face(od::Game::GetInstance()->GetFT(), path.c_str(), 0, &m_Face) != 0) {
		OD_LOG_ERROR("Failed to load font '" << path << "'!");
		return;
	}

	FT_Set_Pixel_Sizes(m_Face, 0, size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   
	for(unsigned char c = 0; c < 128; ++c) {
		if(FT_Load_Char(m_Face, c, FT_LOAD_RENDER) != 0) {
			OD_LOG_ERROR("Failed to load character '" << toascii(c) << "' from font '" << path << "'");
			continue;
		}

		m_Characters.insert({c, od::Character {
			glm::i32vec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
			glm::i32vec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
			m_Face->glyph->advance.x,
			std::make_unique<od::GLTexture>(m_Face->glyph->bitmap.buffer, m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows, GL_RED, GL_RED, filter)
		}});
	}

	FT_Done_Face(m_Face);
}

od::Font::~Font() {
}
