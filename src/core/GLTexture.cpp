#include "GLTexture.h"

od::GLTexture::GLTexture(int32_t filter) {
	Init(filter);
}

od::GLTexture::GLTexture(uint8_t *pixels, uint32_t width, uint32_t height, int32_t internalFormat, int32_t format, int32_t filter) {
	Init(filter);
	SetData(pixels, width, height, internalFormat, format);
}

od::GLTexture::~GLTexture() {
	glDeleteTextures(1, &m_ID);
}

void od::GLTexture::Init(int32_t filter) {
	glGenTextures(1, &m_ID);
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void od::GLTexture::SetData(uint8_t *pixels, uint32_t width, uint32_t height, int32_t internalFormat, int32_t format) {
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
}

void od::GLTexture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void od::GLTexture::Unbind() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}