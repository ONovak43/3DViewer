#include "pch.hpp"
#include "Camera.hpp"

namespace
{
    VL::vec3 getOppositeVector(const VL::vec3& frontVec)
    {
        auto output = frontVec;
        output *= -1;
        return output;
    }
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
    m_position = position;
    return updateViewMatrix();
}

const VL::mat4& Camera::setFront(const VL::vec3& front)
{
    m_front = VL::normalize(front);
    return updateViewMatrix();
}

const VL::mat4& Camera::setCameraUp(const VL::vec3& up) {
    m_camUp = up;
    return updateViewMatrix();
}

const VL::mat4& Camera::setOrientation(float yaw, float pitch)
{
    m_pitch = pitch;
    m_yaw = yaw;

    auto forward = VL::normalize(VL::vec3(std::array{
        cos(VL::radians(m_yaw)) * cos(VL::radians(m_pitch)),
        sin(VL::radians(m_pitch)),
        sin(VL::radians(m_yaw)) * cos(VL::radians(m_pitch)) }
    ));

    m_lookAt = forward;
    m_front = VL::normalize(m_lookAt);

    m_right = VL::normalize(VL::cross(m_lookAt, m_camUp));
    m_up = VL::normalize(VL::cross(m_right, m_lookAt));

    return updateViewMatrix();
}


VL::vec3 Camera::getMoveDirection() const
{
    auto output = VL::vec3{ 0.f };

    for (auto& dir : m_movingDirections)
    {
        switch (dir)
        {
        case DIRECTION::FORWARD:
            output += m_front;
            break;
        case DIRECTION::BACKWARD:
            output += getOppositeVector(m_front);
            break;
        case DIRECTION::RIGHT:
            output += m_right;
            break;
        case DIRECTION::LEFT:
            output += getOppositeVector(m_right);
            break;
        case DIRECTION::UP:
            output += m_up;
            break;
        case DIRECTION::DOWN:
            output += getOppositeVector(m_up);
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
    m_viewMatrix = VL::lookAt(m_position, m_position + m_lookAt, m_camUp);
    return m_viewMatrix;
}