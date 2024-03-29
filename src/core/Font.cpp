#include "Font.h"
#include "core/Game.h"

// TODO: More modular font system
#define COLS 18
#define ROWS 7

od::Font::Font(od::Texture *texture, int32_t filter, float size) : m_Size(size), m_Texture(texture) {
	m_CharSize = { (m_Texture->GetWidth()-1) / COLS, (m_Texture->GetHeight()-1) / ROWS };
	m_CharSizeNorm = glm::f32vec2(m_CharSize.x, m_CharSize.y) / glm::f32vec2(m_Texture->GetWidth(), m_Texture->GetHeight());
}

od::Font::~Font() {
}

void od::Font::GetCharUV(char c, glm::f32vec2 &start, glm::f32vec2 &end) {
	if(c < 32 || c > 126) {
		start = end = {};
		return;
	}

	const int32_t index = c - 32;
	const glm::i32vec2 charCell = {index % COLS, index / COLS};
	const glm::i32vec2 charPosPix = charCell * m_CharSize;

	start = glm::f32vec2(charPosPix.x, charPosPix.y) / glm::f32vec2(m_Texture->GetWidth(), m_Texture->GetHeight());
	end = start + m_CharSizeNorm;
}

// TODO: What about new lines? And non-renderable characters?
float od::Font::GetTextWidth(uint32_t length, float scale) const {
	return m_CharSize.x * length * scale * m_Size;
}