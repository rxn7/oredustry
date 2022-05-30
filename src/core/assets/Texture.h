#pragma once

#include "core/Libs.h"
#include "core/Asset.h"
#include "core/GLTexture.h"

namespace od {
	class Texture : public od::Asset {
	public:
		Texture(const std::string &path, uint32_t filter = GL_NEAREST);

		inline int32_t GetWidth() const { return m_Width; }
		inline int32_t GetHeight() const { return m_Height; }
		inline std::shared_ptr<GLTexture> GetGLTexture() const { return m_GLTexture; }

	private:
		int32_t m_Width, m_Height;
		std::shared_ptr<GLTexture> m_GLTexture;
	};
}
