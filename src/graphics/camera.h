#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
    float fov;
    float pitch;
    float yaw;
    float camspeed;

    glm::vec3 position;
    glm::vec3 direction;
    static const glm::vec3 up; // World's "up" direction

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 projView;

    Camera() = default;
    Camera(float fov, float aspect_ratio, float znear, float zfar);

    // Update view matrix
    void Update();
    // Update projection matrix
    void Update(float fov, float aspect_ratio, float znear, float zfar);
};
