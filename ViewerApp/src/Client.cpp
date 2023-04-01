#include "Client.hpp"

#include <filesystem>


void Viewer::start()
{
    using VL::AssetManager;
    using namespace std::filesystem;
    auto path = current_path();
    auto assets = path / "assets/Shader/main";
    std::string s{ assets.generic_string()};

    auto _program = AssetManager::getInstance().getShaderProgram(s);
    m_program = std::move(_program);

    std::vector<float> vertices = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    std::vector <uint32_t> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    std::vector<VL::VertexAttribute> vertexAttributes = {
        VL::VertexAttribute(3, VL::VertexAttribute::Type::FLOAT, 0),
	};


    m_vertexArray = std::make_unique<VL::OpenGL::OpenGLVertexArray>();
    m_vertexBuffer = std::make_shared<VL::OpenGL::OpenGLVertexBuffer>(vertices);
    m_indexBuffer = std::make_shared <VL::OpenGL::OpenGLIndexBuffer>(indices);
    auto attributes = VL::VertexAttribute(3, VL::VertexAttribute::Type::FLOAT, 0);

    m_vertexArray->setVertexBuffer(m_vertexBuffer);
    m_vertexArray->setIndexBuffer(m_indexBuffer);
    m_vertexArray->addVertexAtributes(vertexAttributes);    
}

void Viewer::update(VL::StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime)
{
    m_program->use();
    m_vertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Viewer::stop()
{
}

void Viewer::onKeyEvent(std::shared_ptr<VL::KeyPressEvent>& e)
{
}
