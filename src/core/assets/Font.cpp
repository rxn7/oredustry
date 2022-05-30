#include "Font.h"
#include "core/Game.h"

od::Font::Font(const std::string &path, int32_t size) : od::Asset(path) {
	if(FT_New_Face(od::Game::GetInstance()->GetFT(), path.c_str(), 0, &m_Face) != 0) {
		OD_LOG_ERROR("Failed to load font '" << path << "'!");
		return;
	}

	FT_Set_Pixel_Sizes(m_Face, 0, size);

	// TODO: Create texture with all glyphs
	m_Texture = std::make_unique<od::GLTexture>();
}

od::Font::~Font() {
	FT_Done_Face(m_Face);
}
