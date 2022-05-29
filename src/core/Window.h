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

		inline void SetSize(int32_t width, int32_t height) { m_Width = width; m_Height = height; }
		inline int32_t GetStartWidth() const { return m_StartWidth; }
		inline int32_t GetStartHeight() const { return m_StartHeight; }
		inline int32_t GetHalfWidth() const { return m_Width * 0.5f; }
		inline int32_t GetHalfHeight() const { return m_Height * 0.5f; }
		inline int32_t GetWidth() const { return m_Width; } 
		inline int32_t GetHeight() const { return m_Height; } 
		inline glm::i32vec2 GetSize() const { return {m_Width, m_Height}; }
		inline glm::i32vec2 GetCenter() const { return {GetHalfWidth(), GetHalfHeight()}; }
		inline GLFWwindow *GetGLFWWindow() const { return m_GLFWWindow; };

	private:
		int32_t m_Width, m_Height;
		int32_t m_StartWidth,  m_StartHeight;
		GLFWwindow *m_GLFWWindow;
	};
}
