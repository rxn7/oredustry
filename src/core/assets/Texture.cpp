#include "Texture.h"
#include "core/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

od::Texture::Texture(const std::string &path, uint32_t filter) : od::Asset(path) {
	int32_t channels = 0;

	uint8_t *img = stbi_load(m_Path.data(), &m_Width, &m_Height, &channels, 0);
	if(!img) {
		OD_LOG_ERROR("Failed to load texture '" << path << "'!");
		return;
	}

	int32_t internalFormat = channels == 4 ? GL_RGBA : GL_RGB;
	m_GLTexture = std::make_unique<od::GLTexture>(img, m_Width, m_Height, internalFormat, internalFormat, filter);
	stbi_image_free(img);
}
