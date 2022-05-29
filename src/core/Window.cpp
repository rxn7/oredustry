#include "Window.h"
#include "Log.h"

od::Window::Window(const od::WindowParameters &params) : 
m_Width(params.width), m_Height(params.height) {
	m_SDLWindow = SDL_CreateWindow(params.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, params.width, params.height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if(!m_SDLWindow) {
		OD_LOG_ERROR("Failed to create the SDL window");
		return;
	}

	if(params.iconPath != "") {
		// TODO: Load icon without SDL_IMG
		/*
		SDL_Surface *iconSurface = ;
		if(!iconSurface) {
			OD_LOG_ERROR("Failed to load icon '" << params.iconPath << "', reason: " << IMG_GetError());
			return;
		}

		SDL_SetWindowIcon(m_SDLWindow, iconSurface);
		SDL_FreeSurface(iconSurface);
		*/
	}
}

od::Window::~Window() {
	SDL_DestroyWindow(m_SDLWindow);
}

void od::Window::ProcessWindowEvent(const SDL_WindowEvent &event) {
	SDL_GetWindowSize(m_SDLWindow, &m_Width, &m_Height);
}
