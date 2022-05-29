#include "core/Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "core/assets/Texture.h"
#include "core/Log.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/shaders/ColorShader.h"
#include "core/shaders/TextureShader.h"

static std::unique_ptr<od::VertexArray> s_QuadVa;
static std::unique_ptr<od::Shader> s_ColorShader, s_TextureShader;
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
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	s_ColorShader = std::make_unique<od::Shader>(od::Shaders::ColorShader::VertexSrc, od::Shaders::ColorShader::FragmentSrc);
	s_TextureShader = std::make_unique<od::Shader>(od::Shaders::TextureShader::VertexSrc, od::Shaders::TextureShader::FragmentSrc);

	s_QuadVa = std::make_unique<od::VertexArray>(s_QuadVertices);
}

void od::Renderer::Begin2D() {
	s_ColorShader->Bind();
	s_ColorShader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());

	s_TextureShader->Bind();
	s_ColorShader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());
}

void od::Renderer::End2D() {
}

void od::Renderer::BeginUI() {
	s_ColorShader->Bind();
	s_ColorShader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());

	s_TextureShader->Bind();
	s_ColorShader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());
}

void od::Renderer::EndUI() {
}

void od::Renderer::RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color) {
	glm::f32mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::f32vec3(position, 0.0f));
	model = glm::scale(model, glm::f32vec3(size, 1.0f));

	s_ColorShader->Bind();
	s_ColorShader->SetUniformMat4("u_Model", model);
	s_ColorShader->SetUniformColor("u_Color", color);

	s_QuadVa->Bind();
	s_QuadVa->Render();
}

void od::Renderer::RenderQuadTextured(const glm::f32vec2 &position, const glm::f32vec2 &size, const std::shared_ptr<od::Texture> &texture, const od::Color &color) {
	glm::f32mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::f32vec3(position, 0.0f));
	model = glm::scale(model, glm::f32vec3(size, 1.0f));

	texture->Bind();

	s_TextureShader->Bind();
	s_TextureShader->SetUniformMat4("u_Model", model);
	s_TextureShader->SetUniformColor("u_Color", color);

	s_QuadVa->Bind();
	s_QuadVa->Render();
}
