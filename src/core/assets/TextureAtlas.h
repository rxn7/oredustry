#pragma once

#include "core/assets/Texture.h"
#include <glm/fwd.hpp>

namespace od {
    class TextureAtlas : public od::Texture {
    public:
        TextureAtlas(const std::string &path, uint16_t frameCount, uint32_t filter = GL_NEAREST);
        inline float GetFrameSize() const { return m_FrameSize; }
        inline float GetNormalizedFrameSize() const { return m_FrameSize / static_cast<float>(GetWidth()); }
        inline uint16_t GetFrameCount() const { return m_FrameCount; }

    private:
        float m_FrameSize;
        uint16_t m_FrameCount;
    };
}