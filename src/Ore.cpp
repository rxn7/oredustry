#include "Ore.h"
#include "core/Asset.h"
#include "core/Color.h"
#include "core/GLTexture.h"
#include "core/Game.h"
#include "core/assets/Texture.h"
#include "core/assets/TextureAtlas.h"
#include "core/rendering/Renderer.h"

static std::shared_ptr<od::GLTexture> s_Texture = nullptr;
static od::TextureAtlas *s_DestroyTextureAtlas = nullptr;

Ore::Ore(uint16_t maxHealth, glm::f32vec2 position) : m_MaxHealth(maxHealth), m_Health(maxHealth), od::Entity(position) {
	if(!s_Texture) {
		s_Texture = od::Asset::GetAsset<od::Texture>("res/ore.png")->GetGLTexture(); 
		s_DestroyTextureAtlas = od::Asset::GetAsset<od::TextureAtlas>("res/destroy.png");
	}

	m_DestroyStageFrame = rand() % 6 + 1;
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
	od::Renderer::RenderTexture(m_Position, Ore::SIZE, s_Texture.get(), od::Colors::WHITE);
	
	if(m_Health != m_MaxHealth)
		RenderDestroyTexture();
}

void Ore::RenderDestroyTexture() {
	od::Renderer::RenderTextureAtlas(m_Position, Ore::SIZE, m_DestroyStageFrame, s_DestroyTextureAtlas, od::Colors::WHITE);
}