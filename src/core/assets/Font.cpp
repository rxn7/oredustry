#include "Font.h"
#include "core/Game.h"

od::Font::Font(const std::string &path, int32_t size) : od::Asset(path) {
	if(FT_New_Face(od::Game::GetInstance()->GetFT(), path.c_str(), 0, &m_Face) != 0) {
		OD_LOG_ERROR("Failed to load font '" << path << "'!");
		return;
	}

	FT_Set_Pixel_Sizes(m_Face, 0, size);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for(uint8_t c=0; c<128; ++c) {
		if(FT_Load_Char(m_Face, c, FT_LOAD_RENDER) != 0) {
			OD_LOG_ERROR("Failed to load character '" << c << "' for font '" << m_Path << "'");
			continue;
		}

		std::shared_ptr<od::GLTexture> texture = std::make_shared<od::GLTexture>(m_Face->glyph->bitmap.buffer, m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows, GL_RED, GL_RED, GL_LINEAR);

		Character character = {
			texture,
			glm::i32vec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
			glm::i32vec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
			m_Face->glyph->advance.x
		};

		m_Characters.insert({c, character});
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

od::Font::~Font() {
	FT_Done_Face(m_Face);
}
