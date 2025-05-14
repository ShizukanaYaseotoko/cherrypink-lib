#include "glad/glad.h"

#include "rendering/mesh.hpp"
#include "rendering/opengl/opengl.hpp"
#include "spdlog/spdlog.h"

#include "GLFW/glfw3.h"
#include <algorithm>
#include <vector>

namespace cherrypink {

    bool OpenGLContext::Init() {
        glfwMakeContextCurrent(m_window->Handle());
        if (!gladLoadGL()) {
            spdlog::critical("Failed to initialize OpenGL");
            return false;
        }
        return true;
    }

    void OpenGLContext::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_window->Handle()); }

    Mesh OpenGLContext::CreateMesh(const std::vector<float> &vertices,
            const std::vector<unsigned int> &indices) {
        unsigned int vao = 0, vbo = 0, ebo = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        float *vertexArray = new float[vertices.size()];
        std::copy(vertices.begin(), vertices.end(), vertexArray);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertexArray,
                GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        unsigned int *indexArray = new unsigned int[indices.size()];
        std::copy(indices.begin(), indices.end(), indexArray);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                indexArray, GL_STATIC_DRAW);

        return Mesh(vao, vbo, vertices, indices);
    }

    OpenGLTexture *OpenGLContext::CreateTexture(TextureParameters parameters,
            unsigned char *data) {
        return new OpenGLTexture(parameters, data);
    }

    void OpenGLContext::DrawMesh(const Mesh &mesh) {
        glDrawElements(GL_TRIANGLES, mesh.Indices(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLContext::SetViewport(unsigned int x, unsigned int y,
            unsigned int width, unsigned int height) {
        glViewport(x, y, width, height);
    }

} // namespace cherrypink
