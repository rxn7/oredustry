#pragma once

#include <cstdint>

namespace od {
    class Renderable {
        public:
            virtual void Render() {}

        public:
            uint8_t zIndex;
    };
}