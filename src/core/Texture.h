#pragma once

#include "Libs.h"

namespace od {
	enum class TextureFilter {
		Nearest,
		Linear,
	};

	class Texture {
	public:
		Texture(std::string_view path, TextureFilter filter = TextureFilter::Nearest);

		void Bind();

		inline std::string GetPath() const { return m_Path; }
		inline int32_t GetWidth() const { return m_Width; }
		inline int32_t GetHeight() const { return m_Height; }

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_GLTexture;
	};
}
