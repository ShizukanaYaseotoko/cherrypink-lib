#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <unordered_map>

#include "rendering/mesh.hpp"
#include "rendering/texture.hpp"

namespace cherrypink {

    class ResourceManager {
        public:
            ResourceManager(
                    std::filesystem::path resourceDirectory) // We're copying the path to
                                                             // avoid changing the resource
                                                             // directory during runtime
                : m_resourceDirectory(resourceDirectory) {}

            std::optional<Mesh *> LoadMesh(const std::filesystem::path &path);
            std::optional<Texture *> LoadTexture(const std::filesystem::path &path);
            std::filesystem::path GetAssetPath(const std::filesystem::path &path);
            void Shutdown();

        private:
            const std::filesystem::path m_resourceDirectory;
            std::unordered_map<std::filesystem::path, Mesh> m_meshCache;
            std::unordered_map<std::filesystem::path, uint32_t> m_textureIndices;
            std::unordered_map<uint32_t, Texture *> m_textures;
    };

} // namespace cherrypink
