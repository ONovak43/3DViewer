#pragma once

struct CameraProps
{
    VL::vec3 m_position;
    VL::vec3 m_camUp;
    VL::vec3 m_front;
    VL::vec3 m_right;
    VL::vec3 m_up;
    
    float m_yaw;
    float m_pitch;

    CameraProps(
        const VL::vec3& position = VL::vec3(std::array{ 0.0f, 0.0f, 0.0f }),
        const VL::vec3& camUp = VL::vec3(std::array{ 0.0f, 1.0f, 0.0f }),
        const VL::vec3& front = VL::vec3(std::array{ 1.0f, 0.0f, 0.0f }),
        const VL::vec3& right = VL::vec3(std::array{ 0.0f, 1.0f, 0.0f }),
        const VL::vec3& up = VL::vec3(std::array{ 0.0f, 0.0f, 1.0f }),
        float yaw = 0.0f,
        float pitch = 0.5f
        )
        : m_position(position), m_camUp(camUp), m_front(front),
        m_right(right), m_up(up), m_yaw(yaw), m_pitch(pitch)
    {

    };
};

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

    Camera(const CameraProps& properties);

    void move(DIRECTION direction, bool isMoving);

    const VL::mat4& setPosition(const VL::vec3& position);
    const VL::mat4& setFront(const VL::vec3& front);
    const VL::mat4& setUp(const VL::vec3& up);
    const VL::mat4& setOrientation(float pitch, float yaw);

    [[nodiscard]] const VL::vec3& getPosition() const { return m_position; }
    [[nodiscard]] const VL::vec3& getFront() const { return m_front; }
    [[nodiscard]] const VL::vec3& getUp() const { return m_up; }
    [[nodiscard]] const VL::vec3& getRight() const { return m_right; }
	[[nodiscard]] float getYaw() const { return m_yaw; }
	[[nodiscard]] float getPitch() const { return m_pitch; }
    [[nodiscard]] std::vector<VL::vec3> getMoveDirections() const;

    [[nodiscard]] const VL::mat4& getViewMatrix() const;

private:        
    const VL::mat4& updateViewMatrix();

private:
    VL::mat4 m_viewMatrix;
    VL::vec3 m_position;
    VL::vec3 m_camUp;
    VL::vec3 m_front;
    VL::vec3 m_up;
    VL::vec3 m_right;

    float m_yaw;
    float m_pitch;

    std::vector<DIRECTION> m_movingDirections;
};
