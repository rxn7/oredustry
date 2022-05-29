#include "Input.h"
#include "core/Game.h"

static std::array<bool, GLFW_KEY_LAST> s_Keyboard;
static std::array<bool, GLFW_KEY_LAST> s_OldKeyboard;
static std::array<bool, GLFW_MOUSE_BUTTON_LAST> s_Mouse;
static std::array<bool, GLFW_MOUSE_BUTTON_LAST> s_OldMouse;

static void s_KeyCallback(GLFWwindow *window, int32_t key, int32_t scancode, int32_t action, int32_t mods) {
	if(action == GLFW_PRESS)
		s_Keyboard[key] = true;
	else if(action == GLFW_RELEASE)
		s_Keyboard[key] = false;
}

static void s_MouseCallback(GLFWwindow *window, int32_t button, int32_t action, int32_t mods) {
	if(action == GLFW_PRESS)
		s_Mouse[button] = true;
	else if(action == GLFW_RELEASE)
		s_Mouse[button] = false;
}

void od::Input::Init() {
	glfwSetKeyCallback(od::Game::GetInstance()->GetWindow().GetGLFWWindow(), s_KeyCallback);
	glfwSetMouseButtonCallback(od::Game::GetInstance()->GetWindow().GetGLFWWindow(), s_MouseCallback);
}

void od::Input::EndFrame() {
	s_OldKeyboard = s_Keyboard;
	s_OldMouse = s_Mouse;
}

bool od::Input::IsKeyPressed(int32_t key) {
	return s_Keyboard[key];
}

bool od::Input::IsKeyJustPressed(int32_t key) {
	return s_Keyboard[key] && !s_OldKeyboard[key];
}

bool od::Input::IsButtonPressed(int32_t btn) {
	return s_Mouse[btn];
}

bool od::Input::IsButtonJustPressed(int32_t btn) {
	return s_Mouse[btn] && !s_OldMouse[btn];
}
