#include "pch.hpp"
#include "Camera.hpp"
#include "../../glm/glm.hpp"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

namespace
{
    VL::vec3 getBackwardVector(const VL::vec3& frontVec)
    {
        auto output = frontVec;
        output[0] *= -1;
        return output;
    }

    VL::vec3 getLeftVector(const VL::vec3& rightVec)
    {
        auto output = rightVec;
        output[1] *= -1;
        return output;
    }
}

Camera::Camera(const CameraProps& properties)
    : m_position(properties.m_position), m_camUp(properties.m_camUp),
    m_front(properties.m_front), m_up(properties.m_up),
    m_right(properties.m_right), m_yaw(properties.m_yaw), 
    m_pitch(properties.m_pitch)
{
    updateViewMatrix();
    //setOrientation(m_pitch, m_yaw);
}

void Camera::move(Camera::DIRECTION direction, bool isMoving)
{
    if (isMoving == true) {
        m_movingDirections.emplace_back(direction);
    }
    else
    {
        m_movingDirections.erase(std::find(m_movingDirections.begin(), m_movingDirections.end(), direction));
    }
}

const VL::mat4& Camera::setPosition(const VL::vec3& position)
{
    auto t = m_viewMatrix;
    m_position = position;
    return updateViewMatrix();
}

const VL::mat4& Camera::setFront(const VL::vec3& front)
{
    m_front = VL::normalize(front);
    return updateViewMatrix();
}

const VL::mat4& Camera::setUp(const VL::vec3& up) {
    m_up = up;
    return updateViewMatrix();
}

const VL::mat4& Camera::setOrientation(float pitch, float yaw)
{
    //m_pitch = pitch;
    //m_yaw = yaw;

    //setFront(VL::vec3(std::array{
    //    cos(VL::radians(m_yaw)) * cos(VL::radians(m_pitch)),
    //    sin(VL::radians(m_pitch)),
    //    sin(VL::radians(m_yaw)) * cos(VL::radians(m_pitch)) }
    //));

    //m_right = VL::normalize(VL::cross(m_front, m_up));
    //m_up = VL::normalize(VL::cross(m_right, m_front));

    return updateViewMatrix();
}


std::vector<VL::vec3> Camera::getMoveDirections() const
{
    std::vector<VL::vec3> output;
    for (auto& dir : m_movingDirections)
    {
        switch (dir)
        {
        case DIRECTION::FORWARD:
            output.emplace_back(m_front);
            break;
        case DIRECTION::BACKWARD:
            output.emplace_back(getBackwardVector(m_front));
            break;
        case DIRECTION::LEFT:
            output.emplace_back(getLeftVector(m_right));
            break;
        case DIRECTION::RIGHT:
            output.emplace_back(m_right);
            break;
        }
    }

    return output;
}

const VL::mat4& Camera::getViewMatrix() const
{
    return m_viewMatrix;
}

const VL::mat4& Camera::updateViewMatrix()
{
    m_viewMatrix = VL::lookAt(m_position, m_position + m_front, m_camUp);
    return m_viewMatrix;
}

