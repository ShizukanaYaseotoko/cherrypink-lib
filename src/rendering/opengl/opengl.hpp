#pragma once

#include "rendering/context.hpp"
#include "rendering/material.hpp"
#include "rendering/shader.hpp"
#include "rendering/texture.hpp"

namespace cherrypink {

    class OpenGLTexture : public Texture {
        public:
            OpenGLTexture(TextureParameters parameters, unsigned char *data);
            ~OpenGLTexture();
            void Bind() override;
            void Unbind() override;
    };

    class OpenGLContext : public RenderingContext {
        public:
            OpenGLContext(Window *window) : RenderingContext(window) {}
            ~OpenGLContext() override {}

            bool Init() override;
            void Clear() override;
            void SwapBuffers() override;
            Mesh CreateMesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices) override;
            OpenGLTexture *CreateTexture(TextureParameters parameters, unsigned char *data) override;
            void DrawMesh(const Mesh &mesh) override;
            void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
    };

    class OpenGLShader : public Shader {
        public:
            OpenGLShader(unsigned int type, const char *code);
            ~OpenGLShader() {}
    };

    class OpenGLShaderProgram : public ShaderProgram {
        public:
            OpenGLShaderProgram(OpenGLShader *vertexShader, OpenGLShader *fragmentShader);
            void Enable() override;
            void Disable() override;
            void SetUniform1f(const char *uniformName, float value) override;
            void SetUniform2f(const char *uniformName, glm::vec2 &&value) override;
            void SetUniform3f(const char *uniformName, glm::vec3 &&value) override;
            void SetUniform4f(const char *uniformName, glm::vec4 &&value) override;
            void SetUniform2x2f(const char *uniformName, glm::mat2x2 &&value) override;
            void SetUniform3x3f(const char *uniformName, glm::mat3x3 &&value) override;
            void SetUniform4x4f(const char *uniformName, glm::mat4x4 &&value) override;
            void SetUniformMaterial(const char *uniformName,
                    const ShaderMaterial &material) override;
    };

} // namespace cherrypink
