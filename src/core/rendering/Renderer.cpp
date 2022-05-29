#include "core/Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "core/assets/Texture.h"
#include "core/Log.h"
#include <glm/gtc/matrix_transform.hpp>

// TODO: Separate header files for each shaders

static const std::string s_VertexShaderSrc = R"(
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main() {
	gl_Position = u_Projection * u_Model * vec4(a_Position, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
}
)";

static const std::string s_FragmentShaderSrc = R"(
#version 330 core

in vec2 v_TexCoord;
out vec4 f_Color;

uniform vec4 u_Color;

void main() {
	f_Color = u_Color;
}
)";

static std::unique_ptr<od::VertexArray> s_QuadVa;
static std::unique_ptr<od::Shader> s_Shader;
static std::vector<od::Vertex> s_QuadVertices = {
	{ {-0.5f, -0.5f}, {0.0f, 0.0f} },
	{ { 0.5f, -0.5f}, {1.0f, 0.0f} },
	{ { 0.5f,  0.5f}, {1.0f, 1.0f} },

	{ { 0.5f,  0.5f}, {1.0f, 1.0f} },
	{ {-0.5f,  0.5f}, {0.0f, 1.0f} },
	{ {-0.5f, -0.5f}, {0.0f, 0.0f} }
};

void od::Renderer::Init() {
	OD_LOG_INFO("Renderer info:" 
		<< "\nOpenGL Vendor: "		<< glGetString(GL_VENDOR)
		<< "\nOpenGL Renderer: "	<< glGetString(GL_RENDERER)
		<< "\nOpenGL Version: "		<< glGetString(GL_VERSION)
	);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	s_Shader = std::make_unique<od::Shader>(s_VertexShaderSrc, s_FragmentShaderSrc);
	s_QuadVa = std::make_unique<od::VertexArray>(s_QuadVertices);
}

void od::Renderer::Begin2D() {
	s_Shader->Bind();
	s_Shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());
}

void od::Renderer::End2D() {
}

void od::Renderer::BeginUI() {
	s_Shader->Bind();
	s_Shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());
}

void od::Renderer::EndUI() {
}

void od::Renderer::RenderQuad(const glm::i32vec2 &position, const glm::i32vec2 &size, const od::Color &color) {
	s_Shader->Bind();
	s_QuadVa->Bind();

	glm::f32mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

	s_Shader->SetUniformMat4("u_Model", model);
	s_Shader->SetUniformColor("u_Color", color);

	s_QuadVa->Render();
}

void RenderQuadTextured(const glm::i32vec2 &position, const glm::i32vec2 &size, const std::shared_ptr<od::Texture> &texture, const od::Color &color) {
	s_Shader->Bind();
	s_QuadVa->Bind();

	glm::f32mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

	s_Shader->SetUniformMat4("u_Model", model);
	s_Shader->SetUniformColor("u_Color", color);

	s_QuadVa->Render();
}
