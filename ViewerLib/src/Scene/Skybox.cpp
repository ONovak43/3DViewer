#include "pch.hpp"
#include "Skybox.hpp"
#include "Assets/AssetManager.hpp"

VL::Skybox::Skybox(const std::string& shaderPath, const std::string& texturesPath, Renderer* renderer, const std::string& uniformName)
    : m_program(nullptr), m_vertexArray(m_renderer->createVertexArray()), m_renderer(renderer), m_uniformName(uniformName)
{
    using Vertex = VL::Vertex1P;

    std::vector<VL::VertexAttribute> vertexAttributes = {
        VL::VertexAttribute(3, VL::VertexAttribute::Type::FLOAT, 0, sizeof(Vertex)),
    };

    auto VBO{ m_renderer->createVertexBuffer() };
    VBO->setStaticData(m_skyboxVertices.data(), m_skyboxVertices.size() * sizeof(Vertex));
    auto EBO{ m_renderer->createIndexBuffer(m_skyboxIndices) };

    m_vertexArray->setVertexBuffer(VBO);
    m_vertexArray->setIndexBuffer(EBO);
    m_vertexArray->addVertexAtributes(vertexAttributes, 0);

    m_texture = m_renderer->loadTexture(texturesPath, TEXTURE_TYPE::TEXTURE_CUBE_MAP);
    auto _program{ AssetManager::getInstance().getShaderProgram(shaderPath) };
    m_program = std::move(_program);
}

void VL::Skybox::render()
{
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);

    m_program->bind();
    m_program->setInt(m_uniformName, 1);
    m_texture->bind(1);
    m_renderer->renderTriangles(m_vertexArray, m_skyboxIndices.size());
    m_program->unbind();

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
}
