#pragma once

#include "core/Libs.h"

namespace od {
	class GLTexture {
	public:
		GLTexture(int32_t filter = GL_NEAREST);
		GLTexture(uint8_t *pixels, uint32_t width, uint32_t height, int32_t internalFormat, int32_t format, int32_t filter);
		virtual ~GLTexture();

		void SetData(uint8_t *pixels, uint32_t width, uint32_t height, int32_t internalFormat, int32_t format);
		void Bind() const;

	private:
		void Init(int32_t filter);

	protected:
		uint32_t m_ID;
	};
}
