#include "Ore.h"
#include "AssetUIDs.h"
#include "core/Asset.h"
#include "core/Color.h"
#include "core/GLTexture.h"
#include "core/Game.h"
#include "core/assets/Texture.h"
#include "core/assets/TextureAtlas.h"
#include "core/rendering/QuadRenderBatch.h"
#include "core/rendering/RenderBatch.h"
#include "core/rendering/Renderer.h"
#include <glm/fwd.hpp>
#include <math.h>
#include <memory>

static std::unique_ptr<od::QuadRenderBatch> s_DestroyTextureRenderBatch = nullptr, s_OreTextureRenderBatch = nullptr;
static od::GLTexture *s_Texture = nullptr;
static od::TextureAtlas *s_DestroyTextureAtlas = nullptr;

Ore::Ore(uint16_t maxHealth, glm::f32vec2 position) : m_MaxHealth(maxHealth), m_Health(maxHealth), od::Entity(position) {
	m_DestroyStageFrame = rand() % 6 + 1;
}

void Ore::Init() {
	if(!s_Texture)
		s_Texture = od::Asset::Get<od::Texture>(ORE_TEXTURE_UID)->GetGLTexture(); 

	if(!s_DestroyTextureAtlas)
		s_DestroyTextureAtlas = od::Asset::Get<od::TextureAtlas>(DESTROY_TEXTURE_ATLAS_UID);

	if(!s_OreTextureRenderBatch) {
		s_OreTextureRenderBatch = std::make_unique<od::QuadRenderBatch>(0, 50, od::Renderer::TextureShader.get(), s_Texture);
		od::Renderer::AddBatch(s_OreTextureRenderBatch.get());
	}

	if(!s_DestroyTextureRenderBatch) {
		s_DestroyTextureRenderBatch = std::make_unique<od::QuadRenderBatch>(0, 50, od::Renderer::TextureShader.get(), s_DestroyTextureAtlas->GetGLTexture());
		od::Renderer::AddBatch(s_DestroyTextureRenderBatch.get());
	}
}

void Ore::Hit(uint16_t damage) {
	m_Health -= damage;
	m_DestroyStageFrame = (1.0f - (static_cast<float>(m_Health) / static_cast<float>(m_MaxHealth))) * s_DestroyTextureAtlas->GetFrameCount();

	if(m_Health <= 0) {
		m_Health = 0;
		Destroy();
	}
}

void Ore::Render() {
	s_OreTextureRenderBatch->AddQuad(m_Position, Ore::SIZE, od::Colors::WHITE);
	
	if(m_Health != m_MaxHealth) {
		const float normalizedFrameSize = s_DestroyTextureAtlas->GetNormalizedFrameSize();

		std::array<glm::f32vec2, 4> uvs = {
			glm::f32vec2(normalizedFrameSize * m_DestroyStageFrame, 0),
			glm::f32vec2(normalizedFrameSize * m_DestroyStageFrame, 1),
			glm::f32vec2(normalizedFrameSize * (m_DestroyStageFrame+1), 1),
			glm::f32vec2(normalizedFrameSize * (m_DestroyStageFrame+1), 0),
		};

		s_DestroyTextureRenderBatch->AddQuad(m_Position, Ore::SIZE, od::Colors::WHITE, uvs);
	}
}