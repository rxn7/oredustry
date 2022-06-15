#include "core/Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "core/assets/Texture.h"
#include "core/Log.h"
#include <glm/gtc/matrix_transform.hpp>
#include "core/shaders/ColorShader.h"
#include "core/shaders/ColorSwapShader.h"
#include "core/shaders/GlyphShader.h"
#include "core/shaders/TextureShader.h"

static od::Shader *s_ColorShader;
static od::Shader *s_TextureShader;
static od::Shader *s_ColorSwapShader;
static od::Shader *s_GlyphShader;

static std::vector<std::unique_ptr<od::Shader>> m_Shaders;

static std::unique_ptr<od::VertexArray> s_TexturedQuadVa;

static std::unique_ptr<od::VertexArray> s_Va;
static std::vector<od::Vertex> s_GlyphVertices;
static std::vector<od::Vertex> s_QuadVertices;

uint32_t od::Renderer::drawCalls = 0;
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

	s_GlyphShader = new od::Shader(od::Shaders::GlyphShader::VertexSrc, od::Shaders::GlyphShader::FragmentSrc);
	m_Shaders.push_back(std::unique_ptr<od::Shader>(s_GlyphShader));

	{	
		// TODO: Batching
		std::vector<od::Vertex> verts = {
			{ {-0.5f, -0.5f}, {0.0f, 0.0f}, od::Colors::WHITE},
			{ { 0.5f, -0.5f}, {1.0f, 0.0f}, od::Colors::WHITE},
			{ { 0.5f,  0.5f}, {1.0f, 1.0f}, od::Colors::WHITE},
			{ { 0.5f,  0.5f}, {1.0f, 1.0f}, od::Colors::WHITE},
			{ {-0.5f,  0.5f}, {0.0f, 1.0f}, od::Colors::WHITE},
			{ {-0.5f, -0.5f}, {0.0f, 0.0f}, od::Colors::WHITE}
		};

		s_TexturedQuadVa = std::make_unique<od::VertexArray>(verts, GL_STATIC_DRAW);
	}

	s_Va = std::make_unique<od::VertexArray>(10000, GL_DYNAMIC_DRAW);
}

static void CreateModelMatrix(glm::f32mat4 &model, const glm::f32vec2 &position, const glm::f32vec2 &scale) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::f32vec3(position, 0.0f));
	model = glm::scale(model, glm::f32vec3(scale, 1.0f));
}

static void s_RenderGlyphs() {
	od::Game::GetInstance()->GetFont()->GetTexture().GetGLTexture()->Bind();
	s_GlyphShader->Bind();
	s_Va->Bind();
	s_Va->SetData(s_GlyphVertices, GL_DYNAMIC_DRAW);
	s_Va->Render();

	s_GlyphVertices.clear();
}

static void s_RenderQuads() {
	s_ColorShader->Bind();
	s_Va->Bind();
	s_Va->SetData(s_QuadVertices, GL_DYNAMIC_DRAW);
	s_Va->Render();

	s_QuadVertices.clear();
}


void od::Renderer::Begin2D() {
	od::Renderer::drawCalls = 0;

	for(const std::unique_ptr<od::Shader> &shader : m_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());
	}
}

void od::Renderer::End2D() {
	s_RenderQuads();
	s_RenderGlyphs();
}

void od::Renderer::BeginUI() {
	for(const std::unique_ptr<od::Shader> &shader : m_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());
	}
}

void od::Renderer::EndUI() {
	s_RenderQuads();
	s_RenderGlyphs();
}

// TODO: Batched rendering!
// TODO: This doesn't work for some reason
void od::Renderer::RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color) {
	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	s_QuadVertices.emplace_back(glm::f32vec2{position.x - halfWidth, position.y - halfHeight}, glm::f32vec2{0.0f, 0.0f}, color);
	s_QuadVertices.emplace_back(glm::f32vec2{position.x + halfWidth, position.y - halfHeight}, glm::f32vec2{1.0f, 0.0f}, color);
	s_QuadVertices.emplace_back(glm::f32vec2{position.x + halfWidth, position.y + halfHeight}, glm::f32vec2{1.0f, 1.0f}, color);

	s_QuadVertices.emplace_back(glm::f32vec2{position.x + halfWidth, position.y + halfHeight}, glm::f32vec2{1.0f, 1.0f}, color);
	s_QuadVertices.emplace_back(glm::f32vec2{position.x - halfWidth, position.y + halfHeight}, glm::f32vec2{0.0f, 1.0f}, color);
	s_QuadVertices.emplace_back(glm::f32vec2{position.x - halfWidth, position.y - halfHeight}, glm::f32vec2{0.0f, 0.0f}, color);
}

// TODO: Batched rendering!
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

	s_TexturedQuadVa->Bind();
	s_TexturedQuadVa->Render();
}

// TODO: Center align each line individually
void od::Renderer::RenderText(const std::string &text, od::Font *font, const glm::f32vec2 &position, const od::Color &color, float scale, od::TextAlignHorizontal alignH, od::TextAlignVertical alignV) {
	if(text.size() < 1 || scale == 0 || !font || color.a == 0) return;

	float textWidth = font->GetTextWidth(text.size(), scale);

	scale *= font->GetSize();

	float charWidth = font->GetCharWidth() * scale;
	float charHeight = font->GetCharHeight() * scale;
	float x = position.x;
	float y = position.y;

	switch(alignH) {
		case od::TextAlignHorizontal::Left:
			break;

		case od::TextAlignHorizontal::Center:
			x -= textWidth * 0.5f;
			break;

		case od::TextAlignHorizontal::Right:
			x -= textWidth;
			break;
	}

	switch(alignV) {
		case od::TextAlignVertical::Bottom:
			break;

		case od::TextAlignVertical::Middle:
			y += charHeight * 0.5f;
			break;

		case od::TextAlignVertical::Top:
			y += charHeight;
			break;
	}

	for(std::string::const_iterator it = text.begin(); it != text.end(); ++it) {
		if(*it == '\n') {
			x = position.x;
			y += font->GetCharHeight() * 2.f;
			continue;
		}

		if(*it < 32 || *it > 126)
			continue;

		glm::f32vec2 uvStart, uvEnd;
		font->GetCharUV(*it, uvStart, uvEnd);

		s_GlyphVertices.emplace_back(glm::f32vec2{x, y-charHeight},			uvStart, color);
		s_GlyphVertices.emplace_back(glm::f32vec2{x, y},		 		glm::f32vec2{uvStart.x, uvEnd.y}, color);
		s_GlyphVertices.emplace_back(glm::f32vec2{x+charWidth, y},			uvEnd, color);
		s_GlyphVertices.emplace_back(glm::f32vec2{x, y-charHeight},			uvStart, color);
		s_GlyphVertices.emplace_back(glm::f32vec2{x+charWidth, y},			uvEnd, color);
		s_GlyphVertices.emplace_back(glm::f32vec2{x+charWidth, y-charHeight},		glm::f32vec2{uvEnd.x, uvStart.y}, color);

		x += charWidth;
	}
}
