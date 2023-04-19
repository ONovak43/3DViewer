#include "pch.hpp"
#include "Model.hpp"


namespace VL
{

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        : m_vertices(vertices), m_indices(indices)
    {
    }

    Model::Model()
        : m_meshes()
    {
    }

    void Model::addMesh(const Mesh& mesh)
    {
        m_meshes.push_back(mesh);
    }

    std::vector<Mesh> Model::getMeshes()
    {
		return m_meshes;
	}
}
