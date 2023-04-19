#include "Client.hpp"
#include "imgui.h"
#include "ObjectLoader.hpp"
#include "Scene/Vertex.hpp"
#include "Math/MatrixTransform.hpp"

#include <filesystem>

void Viewer::start()
{
    using VL::AssetManager;
    auto path = std::filesystem::current_path();
    auto shaderPath = path / "assets/Shader/main";
    auto objPath = path / "assets/Objects/test.obj";

    std::string shaderAsset{ shaderPath.generic_string() };
    std::string objAsset{ objPath.generic_string() };

    auto _program = AssetManager::getInstance().getShaderProgram(shaderAsset);
    m_program = std::move(_program);
    m_modelRenderer = std::make_unique<ModelRenderer>(objAsset, m_renderer);
}

void Viewer::update(VL::StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime)
{
    m_program->bind();
    auto camPosition = VL::vec3(std::array{ 0.0f, 0.0f, 1.0f });
    auto camFront = VL::vec3(std::array{ 0.0f, 0.0f, -1.0f });
    auto worldUp = VL::vec3(std::array{ 0.0f, 1.0f, 0.0f });

    auto projectionMatrix = VL::perspective(1.57079633f, 800.f/600.f, 0.1f, 1000.0f); // EDIT
    auto viewMatrix = VL::lookAt(camPosition, camFront, worldUp);
    auto model = VL::mat4(1.0f);

    model = VL::translate(model, VL::vec3(std::array{ 0.0f, 0.0f, -30.0f }));
    model = VL::scale(model, VL::vec3(std::array{ 1.f, 1.f, 1.f }));
    
    m_program->setMat4("projection", projectionMatrix);
    m_program->setMat4("view", viewMatrix);
    m_program->setMat4("model", model);

    m_modelRenderer->draw(m_program);

    m_program->unbind();
}

void Viewer::renderGUI()
{
    bool my_tool_active = false;
    float my_color[4] = { 1.0f, 1.0f, 0.4f, 1.0f };

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Load", "CTRL+L")) {}
            if (ImGui::MenuItem("Export", "CTRL+S")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "CTRL+X")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void Viewer::stop()
{
}

void Viewer::onKeyEvent(std::shared_ptr<VL::KeyPressEvent>& e)
{
}

void Viewer::setRenderer(VL::Renderer* renderer)
{
    m_renderer = renderer;
}