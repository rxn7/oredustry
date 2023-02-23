#include "TextureAtlas.h"

od::TextureAtlas::TextureAtlas(const std::string &path, uint16_t frameCount, uint32_t filter) : m_FrameCount(frameCount), od::Texture(path, filter) {
    m_FrameSize = static_cast<float>(GetWidth()) / static_cast<float>(frameCount);
}