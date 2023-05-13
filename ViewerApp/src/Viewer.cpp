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
    : m_renderer(nullptr), m_program(nullptr), m_rotation(0.f), m_deltaTime(0.f)
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
    
    m_rotation += 10.f * deltaTime;

    // Model
    auto model{ VL::mat4(1.0f) };
    model = VL::translate(model, VL::vec3(std::array{ 0.0f, -1.f, 0.0f }));
    model = VL::scale(model, VL::vec3(1.f));

    // Camera
    auto position{ m_camera.getPosition() };
    auto direction{ m_camera.getMoveDirection() };
    auto finalCameraPos = position + direction * m_deltaTime * 2.f ;
    m_camera.setPosition(finalCameraPos);

    // Projection
    auto projectionMatrix{ VL::perspective(VL::radians(90.f), 800.f / 600.f, 0.1f, 100.0f) }; // EDIT

    m_program->bind();
    {
        m_program->setMat4("projection", projectionMatrix);
        m_program->setMat4("view", m_camera.getViewMatrix());
        m_program->setMat4("model", model);
        m_modelRenderer->draw(m_program);
    }
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

void Viewer::onMouseMovedEvent(const std::shared_ptr<VL::MouseMoveEvent>& e)
{
    if (m_enableCameraRotation == false)
    {
		return;
	}

    auto x = e->getX();
    auto y = e->getY();
    static float lastX = x;
    static float lastY = y;

    if (m_resetMousePosition)
    {
        m_resetMousePosition = false;
        lastX = x;
        lastY = y;
    }

    auto yaw = m_camera.getYaw() + ((x - lastX) * 0.5f);
    auto pitch = m_camera.getPitch() + ((lastY - y) * 0.5f);

    pitch = std::clamp(pitch, -89.f, 89.f);
    yaw = std::clamp(yaw, -360.f, 360.f);

    m_camera.setOrientation(yaw, pitch);

    lastX = x;
    lastY = y;
}

void Viewer::onMouseButtonPressedEvent(const std::shared_ptr<VL::MouseButtonPressEvent>& e)
{
    if (e->getButton() == VL::MouseButtonPressEvent::MOUSE_CODES::ButtonMiddle)
    {
        m_enableCameraRotation = true;
        VL::Application::getInstance().setCursorVisible(false);
    }
}

void Viewer::onMouseButtonReleasedEvent(const std::shared_ptr<VL::MouseButtonReleaseEvent>& e)
{
    if (e->getButton() == VL::MouseButtonPressEvent::MOUSE_CODES::ButtonMiddle)
    {
        m_enableCameraRotation = false;
        VL::Application::getInstance().setCursorVisible(true);
        m_resetMousePosition = true;
    }
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
        break;
    case codes::Q:
        m_camera.move(Camera::DIRECTION::UP, type == KEY_EVENT_TYPE::PRESSED);
        break;
    case codes::E:
        m_camera.move(Camera::DIRECTION::DOWN, type == KEY_EVENT_TYPE::PRESSED);
        break;
    case codes::R:
        m_camera.setPosition(VL::vec3(std::array{ -1.f, 0.f, 0.f }));
        m_camera.setOrientation(0.5f, 0.f);
        m_resetMousePosition = true;
        break;
    }
}
