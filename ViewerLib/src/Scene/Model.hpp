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

        [[no_discard]] float getWidth() const { return m_width; }
        [[no_discard]] float getHeight() const { return m_height; }
		[[no_discard]] float getDepth() const { return m_depth; }

        void setWidth(float width) { m_width = width; }
        void setHeight(float height) { m_height = height; }
        void setDepth(float depth) { m_depth = depth; }
        

    private:
        std::vector<Mesh> m_meshes;
        float m_width;
        float m_height;
        float m_depth;
    };
}

