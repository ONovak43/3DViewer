#pragma once

class Camera {
public:
    enum class DIRECTION {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    void move(DIRECTION direction, bool isMoving);

    const VL::mat4& setPosition(const VL::vec3& position);
    const VL::mat4& setFront(const VL::vec3& front);
    const VL::mat4& setCameraUp(const VL::vec3& up);
    const VL::mat4& setOrientation(float pitch, float yaw);

    [[nodiscard]] const VL::vec3& getPosition() const { return m_position; }
    [[nodiscard]] const VL::vec3& getFront() const { return m_front; }
    [[nodiscard]] const VL::vec3& getCameraUp() const { return m_up; }
    [[nodiscard]] const VL::vec3& getRight() const { return m_right; }
    [[nodiscard]] float getYaw() const { return m_yaw; }
    [[nodiscard]] float getPitch() const { return m_pitch; }
    [[nodiscard]] VL::vec3 getMoveDirection() const;

    [[nodiscard]] const VL::mat4& getViewMatrix() const;

private:
    const VL::mat4& updateViewMatrix();

private:
    VL::mat4 m_viewMatrix;
    VL::vec3 m_lookAt = VL::vec3(std::array{ 1.0f, 0.0f, 0.0f });
    VL::vec3 m_position = VL::vec3(0.f);
    VL::vec3 m_camUp = VL::vec3(std::array{ 0.0f, 1.0f, 0.0f });

    VL::vec3 m_front = VL::vec3(std::array{ 1.0f, 0.0f, 0.0f });
    VL::vec3 m_right = VL::vec3(std::array{ 0.0f, 0.0f, 1.0f });
    VL::vec3 m_up = VL::vec3(std::array{ 0.0f, 1.0f, 0.0f });

    float m_yaw = 0.f;
    float m_pitch = 0.5f;

    std::vector<DIRECTION> m_movingDirections;
};