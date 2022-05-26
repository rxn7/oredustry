#pragma once

#include "core/Asset.h"

namespace od {
	class Font : public od::Asset {
	public:
		Font(uint32_t size);
		virtual ~Font();
		bool OnLoad() override;

		inline TTF_Font *GetTTFFont() const { return m_TTFFont; }
		inline uint32_t GetSize() const { return m_Size; }

	private:
		TTF_Font *m_TTFFont;
		uint32_t m_Size;
	};
}
