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
#include "core/shaders/TextShader.h"

static std::vector<od::Vertex> s_QuadVertices = {
	{ {-0.5f, -0.5f}, {0.0f, 0.0f} },
	{ { 0.5f, -0.5f}, {1.0f, 0.0f} },
	{ { 0.5f,  0.5f}, {1.0f, 1.0f} },
	{ { 0.5f,  0.5f}, {1.0f, 1.0f} },
	{ {-0.5f,  0.5f}, {0.0f, 1.0f} },
	{ {-0.5f, -0.5f}, {0.0f, 0.0f} }
};

static std::unique_ptr<od::VertexArray> s_QuadVa;
static std::unique_ptr<od::VertexArray> s_GlyphVa;

static od::Shader *s_ColorShader;
static od::Shader *s_TextureShader;
static od::Shader *s_ColorSwapShader;
static od::Shader *s_TextShader;

static std::vector<std::unique_ptr<od::Shader>> m_Shaders;

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

	m_Shaders.clear();

	s_ColorShader = new od::Shader(od::Shaders::ColorShader::VertexSrc, od::Shaders::ColorShader::FragmentSrc);
	m_Shaders.push_back(std::unique_ptr<od::Shader>(s_ColorShader));

	s_TextureShader = new od::Shader(od::Shaders::TextureShader::VertexSrc, od::Shaders::TextureShader::FragmentSrc);
	m_Shaders.push_back(std::unique_ptr<od::Shader>(s_TextureShader));

	s_ColorSwapShader = new od::Shader(od::Shaders::ColorSwapShader::VertexSrc, od::Shaders::ColorSwapShader::FragmentSrc);
	m_Shaders.push_back(std::unique_ptr<od::Shader>(s_ColorSwapShader));

	s_TextShader = new od::Shader(od::Shaders::TextShader::VertexSrc, od::Shaders::TextShader::FragmentSrc);
	m_Shaders.push_back(std::unique_ptr<od::Shader>(s_TextShader));

	s_QuadVa = std::make_unique<od::VertexArray>(s_QuadVertices, GL_STATIC_DRAW);
	s_GlyphVa = std::make_unique<od::VertexArray>(6, GL_DYNAMIC_DRAW);
}

void od::Renderer::Begin2D() {
	for(const std::unique_ptr<od::Shader> &shader : m_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());
	}
}

void od::Renderer::End2D() {
}

void od::Renderer::BeginUI() {
	for(const std::unique_ptr<od::Shader> &shader : m_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());
	}
}

void od::Renderer::EndUI() {
}

// TODO: Instance rendering?
void od::Renderer::RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color) {
	glm::f32mat4 model = glm::mat4(1);
	CreateModelMatrix(model, position, size);

	s_ColorShader->Bind();
	s_ColorShader->SetUniformMat4("u_Model", model);
	s_ColorShader->SetUniformColor("u_Color", color);

	s_QuadVa->Bind();
	s_QuadVa->Render();
}

void od::Renderer::RenderQuadTextured(const glm::f32vec2 &position, const glm::f32vec2 &size, od::GLTexture *texture, const od::Color &color, TextureShaderType shaderType) {
	glm::f32mat4 model = glm::mat4(1);
	CreateModelMatrix(model, position, size);

	od::Shader *shader;
	switch(shaderType) {
		case TextureShaderType::Normal:		shader = s_TextureShader;	break;
		case TextureShaderType::ColorSwap:	shader = s_ColorSwapShader;	break;

		default:
			OD_LOG_ERROR("od::Renderer::RenderQuadTextured: Invalid TextureShaderType!");
			return;
	}

	texture->Bind();

	shader->Bind();
	shader->SetUniformMat4("u_Model", model);
	shader->SetUniformColor("u_Color", color);

	s_QuadVa->Bind();
	s_QuadVa->Render();
}

// TODO: Horizontal centering isn't correct
void od::Renderer::RenderText(const std::string &text, od::Font *font, const glm::f32vec2 &position, const od::Color &color, float scale, od::TextAlignHorizontal alignH, od::TextAlignVertical alignV) {
	if(text.size() < 1) return;

	s_GlyphVa->Bind();
	s_TextShader->Bind();
	s_TextShader->SetUniformColor("u_Color", color);

	float textWidth = font->GetTextWidth(text, scale);
	float x = position.x;
	float y = position.y;

	for(std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
		if(*it == '\n') {
			x = position.x;
			y += font->GetHeight() * 1.5f;
			continue;
		}

		const od::Character &c = font->GetCharacter(*it);
		float xpos = (x + c.bearing.x) * scale;
		float ypos = y - (c.bearing.y - c.size.y) * scale;

		switch(alignH) {
			case TextAlignHorizontal::Left:
				break;

			case TextAlignHorizontal::Right: 
				xpos -= textWidth;
				break;

			case TextAlignHorizontal::Center:
				xpos -= textWidth * 0.5f;
				break;
		}

		switch(alignV) {
			case TextAlignVertical::Bottom:
				break;

			case TextAlignVertical::Top:
				ypos += font->GetHeight();
				break;

			case TextAlignVertical::Middle:
				ypos += font->GetHeight() * 0.5f;
				break;
		}

		float w = c.size.x * scale;
		float h = c.size.y * scale;
		std::vector<od::Vertex> vertices = {
			{ { xpos, ypos-h, },   { 0.0f, 0.0f } },            
			{ { xpos, ypos,   },   { 0.0f, 1.0f } },
			{ { xpos+w, ypos,   },   { 1.0f, 1.0f } },
                                                 
			{ { xpos, ypos-h, },   { 0.0f, 0.0f } },
			{ { xpos+w, ypos,   },   { 1.0f, 1.0f } },
			{ { xpos+w, ypos-h, },   { 1.0f, 0.0f } }  
		};

		c.texture->Bind();
		s_GlyphVa->SubData(vertices);
		s_GlyphVa->Render();

		x += (c.advance >> 6) * scale;
	}
}
