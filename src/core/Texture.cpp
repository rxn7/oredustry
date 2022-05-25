#include "Texture.h"
#include "Log.h"

od::Texture::Texture(std::string_view path, TextureFilter filter) : m_Path(path) {
	SDL_Surface *surface = IMG_Load(path.data());
	if(!surface) {
		OD_LOG_ERROR("Failed to load texture '" << path << "', reason: " << IMG_GetError());
		return;
	}

	m_Width = surface->w;
	m_Height = surface->h;

	glGenTextures(1, &m_GLTexture);
	glBindTexture(GL_TEXTURE_2D, m_GLTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int32_t>(filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int32_t>(filter));

	SDL_LockSurface(surface);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_UnlockSurface(surface);
	SDL_FreeSurface(surface);
}

void od::Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_GLTexture);
}
