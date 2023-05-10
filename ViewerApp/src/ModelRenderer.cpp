#include "ModelRenderer.hpp"
#include "ObjectLoader.hpp"
#include <string>

ModelRenderer::ModelRenderer(const std::string& modelPath, VL::Renderer* renderer)
    : m_renderer(renderer), m_vertexArray()
{
    ObjectLoader loader(m_renderer);
    m_model = loader.loadModel(modelPath);

	auto meshes = m_model->getMeshes();

    for (auto& mesh : meshes)
    {
		prepareMesh(mesh);
	}
}

void ModelRenderer::draw(std::shared_ptr<VL::IShaderProgram>& program)
{
    auto meshes = m_model->getMeshes();
	for (auto i = 0; i < meshes.size(); i++)
	{
		prepareTextures(meshes, i, program);
        m_renderer->renderTriangles(m_vertexArray[i]);
	}
}

void ModelRenderer::prepareMesh(const VL::Mesh& mesh)
{
    using Vertex = VL::Vertex1P1N1UV;

    std::vector<VL::VertexAttribute> vertexAttributes = {
        VL::VertexAttribute(3, VL::VertexAttribute::Type::FLOAT, 0, sizeof(Vertex)),
        VL::VertexAttribute(3, VL::VertexAttribute::Type::FLOAT, offsetof(Vertex, m_normal), sizeof(Vertex)),
        VL::VertexAttribute(2, VL::VertexAttribute::Type::FLOAT, offsetof(Vertex, m_uv), sizeof(Vertex)),
    };

    auto VAO = m_renderer->createVertexArray();
    auto VBO = m_renderer->createVertexBuffer();
    VBO->setStaticData(mesh.m_vertices.data(), mesh.m_vertices.size() * sizeof(Vertex));
    auto EBO = m_renderer->createIndexBuffer(mesh.m_indices);

    VAO->setVertexBuffer(VBO);
    VAO->setIndexBuffer(EBO);
    VAO->addVertexAtributes(vertexAttributes, 0);
    m_vertexArray.emplace_back(VAO);
}

void ModelRenderer::prepareTextures(std::vector<VL::Mesh>& meshes, uint32_t meshId, std::shared_ptr<VL::IShaderProgram>& program)
{
    auto textureSlot = 0;
    auto& mesh = meshes[meshId];

    for (auto j = 0; j < mesh.m_texturesDiffuse.size(); j++)
    {
        program->setInt("texture_diffuse" + std::to_string(j + 1), j);
        mesh.m_texturesDiffuse[j]->bind(textureSlot++);
    }

    for (auto j = 0; j < mesh.m_texturesSpecular.size(); j++)
    {
        program->setInt("texture_specular" + std::to_string(j + 1), j);
        mesh.m_texturesSpecular[j]->bind(textureSlot++);
    }

    for (auto j = 0; j < mesh.m_texturesNormal.size(); j++)
    {
        program->setInt("texture_normal" + std::to_string(j + 1), j);
        mesh.m_texturesNormal[j]->bind(textureSlot++);
    }

    for (auto j = 0; j < mesh.m_texturesHeight.size(); j++)
    {
        program->setInt("texture_height" + std::to_string(j + 1), j);
        mesh.m_texturesHeight[j]->bind(textureSlot++);
    }
}
