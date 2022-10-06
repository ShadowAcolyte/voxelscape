#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera {
public:
    float m_fov;
    float m_pitch;
    float m_yaw;
    float m_camspeed;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    static const glm::vec3 up; // World's "up" direction

    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::mat4 m_projView;

    Camera() = default;
    Camera(float m_fov, float aspect_ratio, float znear, float zfar);

    // Update view matrix
    void Update();
    // Update projection matrix
    void Update(float m_fov, float aspect_ratio, float znear, float zfar);
};
