#include "Client.hpp"
#include "imgui.h"

#include <filesystem>


void Viewer::start()
{
    using VL::AssetManager;
    using namespace std::filesystem;
    auto path = current_path();
    auto assets = path / "assets/Shader/main";
    std::string s{ assets.generic_string() };

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
    m_program->bind();
    m_vertexArray->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_program->unbind();
}

void Viewer::renderGUI()
{
    bool my_tool_active = false;
    float my_color[4] = { 1.0f, 1.0f, 0.4f, 1.0f };
    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Edit a color stored as 4 floats
    ImGui::ColorEdit4("Color", my_color);

    // Generate samples and plot them
    float samples[100];
    for (int n = 0; n < 100; n++)
        samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    ImGui::PlotLines("Samples", samples, 100);

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();
}

void Viewer::stop()
{
}

void Viewer::onKeyEvent(std::shared_ptr<VL::KeyPressEvent>& e)
{
}
