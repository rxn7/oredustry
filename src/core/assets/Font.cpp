#include "Font.h"

od::Font::Font(uint32_t size) : m_Size(size) {
}

od::Font::~Font() {
	TTF_CloseFont(m_TTFFont);
}

bool od::Font::OnLoad() {
	m_TTFFont = TTF_OpenFont(m_Path.data(), m_Size);
	if(!m_TTFFont) {
		OD_LOG_ERROR("Failed to load font '" << m_Path << "', reason: " << TTF_GetError());
		return false;
	}

	return true;
}
