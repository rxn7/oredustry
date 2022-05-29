#pragma once

#include "core/Libs.h"
#include "core/Asset.h"

namespace od {
	enum class TextureFilter {
		Nearest,
		Linear,
	};

	class Texture : public od::Asset {
	public:
		Texture(TextureFilter filter = TextureFilter::Nearest);

		bool OnLoad() override;
		void Bind() const;
		void Unbind() const;

		inline std::string GetPath() const { return m_Path; }
		inline int32_t GetWidth() const { return m_Width; }
		inline int32_t GetHeight() const { return m_Height; }

	private:
		TextureFilter m_Filter;
		uint32_t m_Width, m_Height;
		uint32_t m_GLTexture;
	};
}
