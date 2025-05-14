#pragma once

#include <cstdint>
#include <glad/glad.h>

namespace cherrypink {

    struct TextureParameters {
        uint32_t width;
        uint32_t height;
        uint8_t channels;
    };

    class Texture {
        public:
            Texture(TextureParameters parameters, unsigned char *data)
                : m_width(parameters.width), m_height(parameters.height),
                m_channels(parameters.channels) {}
            uint32_t Width() const { return m_width; }
            uint32_t Height() const { return m_height; };
            uint32_t Channels() const { return m_channels; };
            uint32_t Id() const { return m_channels; };
            const GLuint *Address() const { return &m_id; }
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

        private:
            uint32_t m_width;
            uint32_t m_height;
            uint32_t m_channels;
            uint32_t m_id;
    };

} // namespace cherrypink
