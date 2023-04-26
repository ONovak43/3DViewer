#include "Viewer.hpp"
#include "imgui.h"
#include "ObjectLoader.hpp"
#include "Scene/Vertex.hpp"
#include "Math/Math.hpp"
#include "Assets/AssetManager.hpp"
#include "Core/Application.hpp"

#include <filesystem>

void Viewer::start()
{
    using VL::AssetManager;
    auto path = std::filesystem::current_path();
    auto shaderPath = path / "assets/Shader/main";
    auto objPath = path / "assets/Objects/quirky/scene.gltf";

    std::string shaderAsset{ shaderPath.generic_string() };
    std::string objAsset{ objPath.generic_string() };

    auto _program = AssetManager::getInstance().getShaderProgram(shaderAsset);
    m_program = std::move(_program);
    m_modelRenderer = std::make_unique<ModelRenderer>(objAsset, m_renderer);
}

void Viewer::update(VL::StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime)
{
    m_program->bind();
    m_rotation += 10.f * deltaTime;
    auto camPosition = VL::vec3(std::array{ 0.0f, 0.0f, 1.f });
    auto camFront = VL::vec3(std::array{ 0.0f, 0.0f, -1.0f });
    auto worldUp = VL::vec3(std::array{ 0.0f, 1.0f, 0.0f });

    auto projectionMatrix = VL::perspective(1.57079633f, 800.f/600.f, 0.1f, 100.0f); // EDIT
    auto viewMatrix = VL::lookAt(camPosition, camPosition + camFront, worldUp);
    auto model = VL::mat4(1.0f);

    model = VL::translate(model, VL::vec3(std::array{ 0.0f, -0.2f, 0.0f }));
    model = VL::scale(model, VL::vec3(std::array{ .3f, .3f, .3f }));
    model = VL::rotate(model, VL::radians(m_rotation), VL::vec3(std::array{ 1.f, 1.f, 0.f }));

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

void Viewer::setRenderer(VL::Renderer* renderer)
{
    m_renderer = renderer;
}

void Viewer::onKeyPressedEvent(std::shared_ptr<VL::KeyPressEvent>& e)
{
    auto key = e->getKeyCode();

    if (key == VL::KeyboardEvent::KEY_CODES::ESCAPE) {
        VL::Application::getInstance().stop();
    }
}

void Viewer::onMouseMovedEvent(std::shared_ptr<VL::MouseMovedEvent>& e)
{
}