#pragma once

#include "mesh.hpp"
#include "rendering/texture.hpp"
#include "rendering/window.hpp"
#include <vector>

namespace cherrypink {

    class RenderingContext {
        public:
            RenderingContext(Window *window) : m_window(window) {}
            virtual ~RenderingContext() {};
            virtual bool Init() = 0;
            virtual void Clear() = 0;
            virtual void SwapBuffers() = 0;
            virtual Mesh CreateMesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices) = 0;
            virtual Texture *CreateTexture(TextureParameters parameters, unsigned char * data) = 0;
            virtual void DrawMesh(const Mesh &mesh) = 0;
            virtual void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
            Window *GetWindow() { return m_window; }

        protected:
            Window *m_window;
    };

} // namespace cherrypink
