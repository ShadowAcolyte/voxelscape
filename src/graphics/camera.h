#ifndef VOX_CAMERA_H
#define VOX_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
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
    Camera(float fov, float aspectRatio, float znear, float zfar);

    // Update view matrix
    void Update();
    // Update projection matrix
    void Update(float fov, float aspectRatio, float znear, float zfar);
};

#endif // !VOX_CAMERA_H
