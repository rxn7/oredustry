#include "Renderer.h"

void od::Renderer::Init() {
}

void od::Renderer::RenderQuad(const glm::vec2 &position, const glm::vec2 &size, const SDL_Color &color) {
	const float halfWidth = size.x * 0.5f;
	const float halfHeight = size.y * 0.5f;

	glBegin(GL_QUADS);
		glColor4ub(color.r, color.g, color.b, color.a);
		glVertex2f(position.x - halfWidth, position.y - halfHeight);
		glVertex2f(position.x - halfWidth, position.y + halfHeight);
		glVertex2f(position.x + halfWidth, position.y + halfHeight);
		glVertex2f(position.x + halfWidth, position.y - halfHeight);
	glEnd();
}
