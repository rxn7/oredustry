#include "Window.h"
#include "Log.h"
#include "Game.h"

#include "stb_image.h"

static void s_WindowSizeCallback(GLFWwindow *win, int32_t width, int32_t height);

od::Window::Window(const od::WindowParameters &params) : 
m_Width(params.width), m_Height(params.height), m_StartWidth(m_Width), m_StartHeight(m_Height) {
	m_GLFWWindow = glfwCreateWindow(params.width, params.height, params.title.c_str(), 0, 0);

	if(!m_GLFWWindow) {
		OD_LOG_ERROR("Failed to create the GLFW window");
		return;
	}

	glfwMakeContextCurrent(m_GLFWWindow);
	glfwSetWindowSizeCallback(m_GLFWWindow, s_WindowSizeCallback);
	glfwSetWindowUserPointer(m_GLFWWindow, (void*)this);

	// Set icon
	if(params.iconPath != "") {
		GLFWimage img;
		img.pixels = stbi_load(params.iconPath.c_str(), &img.width, &img.height, 0, STBI_rgb_alpha);

		glfwSetWindowIcon(m_GLFWWindow, 1, &img);

		OD_LOG_INFO("Icon '" << params.iconPath << "' has been set");

		stbi_image_free(img.pixels);
	}
}

od::Window::~Window() {
	glfwDestroyWindow(m_GLFWWindow);
}

static void s_WindowSizeCallback(GLFWwindow *win, int32_t width, int32_t height) {
	od::Window *window = static_cast<od::Window*>(glfwGetWindowUserPointer(win));

	window->SetSize(width, height);
	od::Game::GetInstance()->HandleWindowResize(width, height);
}
