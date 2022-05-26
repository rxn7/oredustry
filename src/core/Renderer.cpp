#include "Renderer.h"
#include "Log.h"

void od::Renderer::Init() {
	OD_LOG_INFO("Renderer info:" 
		<< "\nOpenGL Vendor: "		<< glGetString(GL_VENDOR)
		<< "\nOpenGL Renderer: "	<< glGetString(GL_RENDERER)
		<< "\nOpenGL Version: "		<< glGetString(GL_VERSION)
	);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void od::Renderer::RenderQuad(const glm::vec2 &position, const glm::vec2 &size, const SDL_Color &color) {
	const float halfWidth = size.x * 0.5f;
	const float halfHeight = size.y * 0.5f;
}
