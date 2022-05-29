#include "Window.h"
#include "Log.h"

#include "stb_image.h"

od::Window::Window(const od::WindowParameters &params) : 
m_Width(params.width), m_Height(params.height), m_StartWidth(m_Width), m_StartHeight(m_Height) {
	m_SDLWindow = SDL_CreateWindow(params.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, params.width, params.height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if(!m_SDLWindow) {
		OD_LOG_ERROR("Failed to create the SDL window");
		return;
	}

	if(params.iconPath != "") {
		int32_t width, height, channels;
		uint8_t *icon = stbi_load(params.iconPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
		SDL_Surface *iconSurface = SDL_CreateRGBSurfaceWithFormatFrom(icon, width, height, 32, 4*width, SDL_PIXELFORMAT_RGBA32);
		stbi_image_free(icon);

		if(!iconSurface) {
			OD_LOG_ERROR("Failed to load icon '" << params.iconPath << "'");
			return;
		}

		SDL_SetWindowIcon(m_SDLWindow, iconSurface);
		SDL_FreeSurface(iconSurface);

		OD_LOG_INFO("Icon '" << params.iconPath << "' has been set");
	}
}

od::Window::~Window() {
	SDL_DestroyWindow(m_SDLWindow);
}

void od::Window::ProcessWindowEvent(const SDL_WindowEvent &event) {
	SDL_GetWindowSize(m_SDLWindow, &m_Width, &m_Height);
}
