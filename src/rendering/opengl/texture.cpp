#include "rendering/opengl/opengl.hpp"
#include "spdlog/spdlog.h"
#include <cstdint>
#include <glad/glad.h>
#include <rendering/texture.hpp>

namespace cherrypink {

    OpenGLTexture::OpenGLTexture(TextureParameters parameters, unsigned char *data)
        : Texture(parameters, data) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            uint32_t textureId;
            glGenTextures(1, &textureId);

            glBindTexture(GL_TEXTURE_2D, textureId);

            GLint format = GL_RGB;

            switch (parameters.channels) {
                case 1:
                    format = GL_RED;
                    break;
                case 2:
                    format = GL_RG;
                    break;
                case 3:
                    format = GL_RGB;
                    break;
                case 4:
                    format = GL_RGBA;
                    break;
                default:
                    spdlog::warn("Unknown image format with {channels} number of channels, "
                            "falling back to RGB!");
            }

            glTexImage2D(GL_TEXTURE_2D, 0, format, parameters.width, parameters.height, 0,
                    format, GL_UNSIGNED_BYTE, data);
        }

    OpenGLTexture::~OpenGLTexture() { glDeleteTextures(1, Address()); }

    void OpenGLTexture::Bind() { glBindTexture(GL_TEXTURE_2D, Id()); }

    void OpenGLTexture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

} // namespace cherrypink
