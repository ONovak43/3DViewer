#include "Viewer.hpp"
#include "imgui.h"
#include "ObjectLoader.hpp"
#include "Scene/Vertex.hpp"
#include "Math/Math.hpp"
#include "Assets/AssetManager.hpp"
#include "Core/Application.hpp"

#include <filesystem>
#include <utility>

Viewer::Viewer()
    : m_camera(CameraProps()), m_renderer(nullptr), m_program(nullptr), m_rotation(0.f), m_deltaTime(0.f)
{
}

void Viewer::start()
{
    using VL::AssetManager;
    auto path{ std::filesystem::current_path() };
    auto shaderPath{ path / "assets/Shader/main" };
    auto objPath{ path / "assets/Objects/quirky_bird/scene.gltf" };

    std::string shaderAsset{ shaderPath.generic_string() };
    std::string objAsset{ objPath.generic_string() };

    auto _program = AssetManager::getInstance().getShaderProgram(shaderAsset);
    m_program = std::move(_program);
    m_modelRenderer = std::make_unique<ModelRenderer>(objAsset, m_renderer);
    m_camera.setPosition(VL::vec3(std::array{ -1.f, 0.f, 0.f }));
}

void Viewer::update(VL::StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime)
{
    m_deltaTime = deltaTime;
    m_program->bind();
    m_rotation += 10.f * deltaTime;

    auto projectionMatrix{ VL::perspective(VL::radians(90.f), 800.f / 600.f, 0.1f, 100.0f) }; // EDIT
    auto model{ VL::mat4(1.0f) };

    model = VL::translate(model, VL::vec3(std::array{ 0.0f, -1.f, 0.0f }));
    model = VL::scale(model, VL::vec3(std::array{ 1.f, 1.f, 1.f }));
    //model = VL::rotate(model, VL::radians(m_rotation), VL::vec3(std::array{ 1.f, 1.f, 0.f }));

    auto moveDirections = m_camera.getMoveDirections();
   
    for(auto& dir : moveDirections) {
        auto finalCameraPos = m_camera.getPosition() + dir * m_deltaTime * 1.f;
        m_camera.setPosition(finalCameraPos);
    }

    m_program->setMat4("projection", projectionMatrix);
    m_program->setMat4("view", m_camera.getViewMatrix());
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

void Viewer::onKeyPressedEvent(const std::shared_ptr<VL::KeyPressEvent>& e)
{
    auto key = e->getKeyCode();

    switch (key)
    {
    case VL::KeyboardEvent::KEY_CODES::ESCAPE:
        VL::Application::getInstance().stop();
        break;
    default:
        onKeyEvent(key, KEY_EVENT_TYPE::PRESSED);
    }
}

void Viewer::onKeyReleasedEvent(const std::shared_ptr<VL::KeyReleaseEvent>& e)
{
    auto key = e->getKeyCode();

    switch (key)
    {
    default:
        onKeyEvent(key, KEY_EVENT_TYPE::RELEASED);
    }
}

void Viewer::onMouseMovedEvent(const std::shared_ptr<VL::MouseMovedEvent>& e)
{
    auto yaw = m_camera.getYaw() +  (e->getX() * 0.1);
    auto pitch = m_camera.getPitch() + (e->getY() * 0.1);

    if (pitch >= 89.f) 
    {
		pitch = 89.f;
	}
    else if (pitch < -89.f)
    {
        pitch = -89.f;
    }

    if (yaw > 360 || yaw < -360) 
    {
        yaw = 0.f;
    }

    m_camera.setOrientation(yaw, pitch);
}

void Viewer::onKeyEvent(VL::KeyboardEvent::KEY_CODES key, KEY_EVENT_TYPE type)
{
    using codes = VL::KeyboardEvent::KEY_CODES;

    switch (key)
    {
    case codes::W:
        m_camera.move(Camera::DIRECTION::FORWARD, type == KEY_EVENT_TYPE::PRESSED);
        break;
    case codes::S:
        m_camera.move(Camera::DIRECTION::BACKWARD, type == KEY_EVENT_TYPE::PRESSED);
        break;
    case codes::A:
        m_camera.move(Camera::DIRECTION::LEFT, type == KEY_EVENT_TYPE::PRESSED);
        break;
    case codes::D:
        m_camera.move(Camera::DIRECTION::RIGHT, type == KEY_EVENT_TYPE::PRESSED);
    }
}
