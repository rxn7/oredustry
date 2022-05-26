#include "Texture.h"
#include "Log.h"

od::Texture::Texture(TextureFilter filter) : m_Filter(filter) {
}

bool od::Texture::OnLoad() {
	SDL_Surface *surface = IMG_Load(m_Path.c_str());
	if(!surface) {
		OD_LOG_ERROR("Failed to load texture '" << m_Path << "', reason: " << IMG_GetError());
		return false;
	}

	m_Width = surface->w;
	m_Height = surface->h;

	glGenTextures(1, &m_GLTexture);
	glBindTexture(GL_TEXTURE_2D, m_GLTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int32_t>(m_Filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int32_t>(m_Filter));

	SDL_LockSurface(surface);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);

	return true;
}

void od::Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_GLTexture);
}
