#pragma once

#include "Libs.h"
#include "Asset.h"

namespace od {
	enum class TextureFilter {
		Nearest,
		Linear,
	};

	class Texture : public od::Asset {
	public:
		Texture(TextureFilter filter = TextureFilter::Nearest);

		bool OnLoad() override;
		void Bind();

		inline std::string GetPath() const { return m_Path; }
		inline int32_t GetWidth() const { return m_Width; }
		inline int32_t GetHeight() const { return m_Height; }

	private:
		TextureFilter m_Filter;
		uint32_t m_Width, m_Height;
		uint32_t m_GLTexture;
	};
}
