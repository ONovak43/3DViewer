#pragma once
#include "Entity.hpp"
#include "Vertex.hpp"
#include "Renderer/Texture.hpp"

#include <vector>

namespace VL
{
    using Vertex = Vertex1P1N1UV;
    struct Mesh
    {
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        std::vector<std::shared_ptr<ITexture>> m_texturesDiffuse;
        std::vector<std::shared_ptr<ITexture>> m_texturesSpecular;
        std::vector<std::shared_ptr<ITexture>> m_texturesNormal;
        std::vector<std::shared_ptr<ITexture>> m_texturesHeight;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    };

    class Model
    {
    public:
        Model();
        void addMesh(const Mesh& mesh);
        std::vector<Mesh> getMeshes();

    private:
        std::vector<Mesh> m_meshes;
    };
}

