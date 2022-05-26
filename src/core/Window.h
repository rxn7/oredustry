#pragma once

#include "Libs.h"

namespace od {
	struct WindowParameters {
		std::string title;
		int32_t width;
		int32_t height;
		std::string iconPath="";
	};

	class Window {
	public:
		Window(const WindowParameters &params);

		~Window();

		void ProcessWindowEvent(const SDL_WindowEvent &event);
		inline int32_t GetHalfWidth() const { return m_Width * 0.5f; }
		inline int32_t GetHalfHeight() const { return m_Height * 0.5f; }
		inline int32_t GetWidth() const { return m_Width; } 
		inline int32_t GetHeight() const { return m_Height; } 
		inline glm::i32vec2 GetSize() const { return {m_Width, m_Height}; }
		inline glm::i32vec2 GetCenter() const { return {GetHalfWidth(), GetHalfHeight()}; }
		inline SDL_Window *GetSDLWindow() const { return m_SDLWindow; };

	private:
		int32_t m_Width, m_Height;
		SDL_Window *m_SDLWindow;
	};
}
