#include "Texture.h"
#include "core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

od::Texture::Texture(uint32_t filter) : m_Filter(filter) {
}

bool od::Texture::OnLoad() {
	int32_t channels = 0;

	uint8_t *img = stbi_load(m_Path.data(), &m_Width, &m_Height, &channels, 0);
	if(!img)
		return false;

	glGenTextures(1, &m_GLTexture);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Filter);

	int32_t internalFormat = channels == 4 ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	stbi_image_free(img);

	Unbind();

	return true;
}

void od::Texture::Bind() const {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_GLTexture);
}

void od::Texture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}
