#include "core/Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "core/assets/Texture.h"
#include "core/Log.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/shaders/ColorShader.h"
#include "core/shaders/TextureShader.h"
#include "core/shaders/ColorSwapShader.h"

static std::vector<od::Vertex> s_QuadVertices = {
	{ {-0.5f, -0.5f}, {0.0f, 0.0f} },
	{ { 0.5f, -0.5f}, {1.0f, 0.0f} },
	{ { 0.5f,  0.5f}, {1.0f, 1.0f} },
	{ { 0.5f,  0.5f}, {1.0f, 1.0f} },
	{ {-0.5f,  0.5f}, {0.0f, 1.0f} },
	{ {-0.5f, -0.5f}, {0.0f, 0.0f} }
};

static std::unique_ptr<od::VertexArray> s_QuadVa;
static std::shared_ptr<od::Shader> s_ColorShader, s_TextureShader, s_ColorSwapShader;
static std::vector<std::shared_ptr<od::Shader>> m_Shaders;

static void CreateModelMatrix(glm::f32mat4 &model, const glm::f32vec2 &position, const glm::f32vec2 &scale) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::f32vec3(position, 0.0f));
	model = glm::scale(model, glm::f32vec3(scale, 1.0f));
}

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
	m_Shaders.push_back(s_ColorShader);

	s_TextureShader = std::make_unique<od::Shader>(od::Shaders::TextureShader::VertexSrc, od::Shaders::TextureShader::FragmentSrc);
	m_Shaders.push_back(s_TextureShader);

	s_ColorSwapShader = std::make_unique<od::Shader>(od::Shaders::ColorSwapShader::VertexSrc, od::Shaders::ColorSwapShader::FragmentSrc);
	m_Shaders.push_back(s_ColorSwapShader);


	s_QuadVa = std::make_unique<od::VertexArray>(s_QuadVertices);
}

void od::Renderer::Begin2D() {
	for(const std::shared_ptr<od::Shader> &shader : m_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());
	}
}

void od::Renderer::End2D() {
}

void od::Renderer::BeginUI() {
	for(const std::shared_ptr<od::Shader> &shader : m_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());
	}
}

void od::Renderer::EndUI() {
}

void od::Renderer::RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color) {
	glm::f32mat4 model = glm::mat4(1);
	CreateModelMatrix(model, position, size);

	s_ColorShader->Bind();
	s_ColorShader->SetUniformMat4("u_Model", model);
	s_ColorShader->SetUniformColor("u_Color", color);

	s_QuadVa->Bind();
	s_QuadVa->Render();
}

void od::Renderer::RenderQuadTextured(const glm::f32vec2 &position, const glm::f32vec2 &size, const std::shared_ptr<od::Texture> &texture, const od::Color &color, TextureShaderType shaderType) {
	glm::f32mat4 model = glm::mat4(1);
	CreateModelMatrix(model, position, size);

	texture->Bind();

	od::Shader *shader;
	switch(shaderType) {
		case TextureShaderType::Normal:		shader = s_TextureShader.get();		break;
		case TextureShaderType::ColorSwap:	shader = s_ColorSwapShader.get();	break;

		default:
			OD_LOG_ERROR("od::Renderer::RenderQuadTextured: Invalid TextureShaderType!");
			return;
	}

	shader->Bind();
	shader->SetUniformMat4("u_Model", model);
	shader->SetUniformColor("u_Color", color);

	s_QuadVa->Bind();
	s_QuadVa->Render();
}
