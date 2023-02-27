#include "core/Font.h"
#include "core/Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "core/Renderable.h"
#include "core/assets/Texture.h"
#include "core/Log.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <set>
#include <memory>
#include "core/rendering/QuadRenderBatch.h"
#include "core/rendering/RenderBatch.h"
#include "core/shaders/ColorShader.h"
#include "core/shaders/ColorSwapShader.h"
#include "core/shaders/GlyphShader.h"
#include "core/shaders/TextureAtlasShader.h"
#include "core/shaders/TextureShader.h"

static std::vector<od::Shader*> s_Shaders;

std::shared_ptr<od::Shader> od::Renderer::ColorShader;
std::shared_ptr<od::Shader> od::Renderer::TextureShader;
std::shared_ptr<od::Shader> od::Renderer::TextureAtlasShader;
std::shared_ptr<od::Shader> od::Renderer::ColorSwapShader;
std::shared_ptr<od::Shader> od::Renderer::GlyphShader;

static std::vector<od::RenderBatch*> s_Batches;
static std::unique_ptr<od::QuadRenderBatch> s_QuadRenderBatch;
static std::unique_ptr<od::QuadRenderBatch> s_GlyphRenderBatch;

static std::unique_ptr<od::VertexArray> s_TexturedQuadVa;

uint32_t od::Renderer::drawCalls = 0;
void od::Renderer::Init(od::Font *font) {
	OD_LOG_INFO("Renderer info:" 
		<< "\nOpenGL Vendor: "		<< glGetString(GL_VENDOR)
		<< "\nOpenGL Renderer: "	<< glGetString(GL_RENDERER)
		<< "\nOpenGL Version: "		<< glGetString(GL_VERSION)
	);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	s_Shaders.clear();

	ColorShader = std::make_shared<od::Shader>(od::Shaders::ColorShader::VertexSrc, od::Shaders::ColorShader::FragmentSrc);
	s_Shaders.push_back(ColorShader.get());

	TextureShader = std::make_shared<od::Shader>(od::Shaders::TextureShader::VertexSrc, od::Shaders::TextureShader::FragmentSrc);
	s_Shaders.push_back(TextureShader.get());

	ColorSwapShader = std::make_shared<od::Shader>(od::Shaders::ColorSwapShader::VertexSrc, od::Shaders::ColorSwapShader::FragmentSrc);
	s_Shaders.push_back(ColorSwapShader.get());

	GlyphShader = std::make_shared<od::Shader>(od::Shaders::GlyphShader::VertexSrc, od::Shaders::GlyphShader::FragmentSrc);
	s_Shaders.push_back(GlyphShader.get());

	TextureAtlasShader = std::make_shared<od::Shader>(od::Shaders::TextureAtlasShader::VertexSrc, od::Shaders::TextureAtlasShader::FragmentSrc);
	s_Shaders.push_back(TextureAtlasShader.get());

	{	
		// TODO: Batching
		std::vector<od::Vertex> verts = {
			{ {-0.5f, -0.5f}, {0.0f, 0.0f}, od::Colors::WHITE},
			{ {-0.5f,  0.5f}, {0.0f, 1.0f}, od::Colors::WHITE},
			{ { 0.5f,  0.5f}, {1.0f, 1.0f}, od::Colors::WHITE},
			{ { 0.5f, -0.5f}, {1.0f, 0.0f}, od::Colors::WHITE},
		};

		std::vector<uint16_t> elements = { 0, 3, 2, 2, 1, 0};

		s_TexturedQuadVa = std::make_unique<od::VertexArray>(verts, elements, GL_STATIC_DRAW);
	}

	s_QuadRenderBatch = std::make_unique<od::QuadRenderBatch>(0, 500, ColorShader.get());
	AddBatch(s_QuadRenderBatch.get());

	s_GlyphRenderBatch = std::make_unique<od::QuadRenderBatch>(0, 10000, GlyphShader.get(), font->GetTexture().GetGLTexture());
	AddBatch(s_GlyphRenderBatch.get());
}

static void CreateModelMatrix(glm::f32mat4 &model, const glm::f32vec2 &position, const glm::f32vec2 &scale) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::f32vec3(position, 0.0f));
	model = glm::scale(model, glm::f32vec3(scale, 1.0f));
}

void od::Renderer::Begin2D() {
	od::Renderer::drawCalls = 0;

	for(od::Shader *shader : s_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetProjection());
	}
}

void od::Renderer::End2D() {
	for(od::RenderBatch *batch : s_Batches)
		batch->Render();
}

void od::Renderer::BeginUI() {
	for(od::Shader *shader : s_Shaders) {
		shader->Bind();
		shader->SetUniformMat4("u_Projection", od::Game::GetInstance()->GetUIProjection());
	}
}

void od::Renderer::EndUI() {
	for(od::RenderBatch *batch : s_Batches)
		batch->Render();
}

void od::Renderer::AddBatch(od::RenderBatch *batch) {
	s_Batches.push_back(batch);
}

// TODO: Create batch for each requested z-index
void od::Renderer::RenderQuad(const glm::f32vec2 &position, const glm::f32vec2 &size, const od::Color &color) {
	if(s_QuadRenderBatch->IsFull()) {
		// TODO: Create new batch
		return;
	}

	s_QuadRenderBatch->AddQuad(position, size, color);
}

void od::Renderer::RenderTexture(const glm::f32vec2 &position, const glm::f32vec2 &size, od::GLTexture *texture, const od::Color &color) {
	RenderTexture(position, size, texture, color, TextureShader.get());
}

void od::Renderer::RenderTexture(const glm::f32vec2 &position, const glm::f32vec2 &size, od::GLTexture *texture, const od::Color &color, Shader *shader) {
	glm::f32mat4 model = glm::mat4(1);
	CreateModelMatrix(model, position, size);

	texture->Bind();

	shader->Bind();
	shader->SetUniformMat4("u_Model", model);
	shader->SetUniformColor("u_Color", color);

	s_TexturedQuadVa->Bind();
	s_TexturedQuadVa->Render();
}

void od::Renderer::RenderTextureAtlas(const glm::f32vec2 &position, const glm::f32vec2 &size, uint16_t frame, od::TextureAtlas *textureAtlas, const od::Color &color) {
	glm::f32mat4 model = glm::mat4(1);
	CreateModelMatrix(model, position, size);

	textureAtlas->GetGLTexture()->Bind();

	TextureAtlasShader->Bind();
	TextureAtlasShader->SetUniformMat4("u_Model", model);
	TextureAtlasShader->SetUniformColor("u_Color", color);
	TextureAtlasShader->SetUniformFloat("u_FrameSize", textureAtlas->GetNormalizedFrameSize());
	TextureAtlasShader->SetUniformInt("u_Frame", frame);

	s_TexturedQuadVa->Bind();
	s_TexturedQuadVa->Render();
}

// TODO: Center align each line individually
void od::Renderer::RenderText(const std::string &text, od::Font *font, const glm::f32vec2 &position, const od::Color &color, float scale, od::TextAlignHorizontal alignH, od::TextAlignVertical alignV) {
	if(text.size() < 1 || scale == 0 || !font || color.a == 0) return;

	const float textWidth = font->GetTextWidth(text.size(), scale);

	scale *= font->GetSize();

	const float charWidth = font->GetCharWidth() * scale;
	const float charHeight = font->GetCharHeight() * scale;
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
		if(s_GlyphRenderBatch->IsFull())
			return;

		if(*it == '\n') {
			x = position.x;
			y += font->GetCharHeight() * 2.f;
			continue;
		}

		if(*it < 32 || *it > 126)
			continue;

		glm::f32vec2 uvStart, uvEnd;
		font->GetCharUV(*it, uvStart, uvEnd);

		const uint32_t vertCount = s_GlyphRenderBatch->GetVertexCount();
		
		s_GlyphRenderBatch->AddVertex({glm::f32vec2{x, y-charHeight},			uvStart, color});
		s_GlyphRenderBatch->AddVertex({glm::f32vec2{x, y},		 		glm::f32vec2{uvStart.x, uvEnd.y}, color});
		s_GlyphRenderBatch->AddVertex({glm::f32vec2{x+charWidth, y},			uvEnd, color});
		s_GlyphRenderBatch->AddVertex({glm::f32vec2{x+charWidth, y-charHeight},		glm::f32vec2{uvEnd.x, uvStart.y}, color});

		s_GlyphRenderBatch->AddElement(vertCount);
		s_GlyphRenderBatch->AddElement(vertCount+1);
		s_GlyphRenderBatch->AddElement(vertCount+2);
		s_GlyphRenderBatch->AddElement(vertCount+2);
		s_GlyphRenderBatch->AddElement(vertCount+3);
		s_GlyphRenderBatch->AddElement(vertCount);

		x += charWidth;
	}
}