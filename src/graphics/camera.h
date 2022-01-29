#ifndef VOX_CAMERA_H
#define VOX_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace camera
{
    extern const glm::vec3 up; // World's "up" direction

    struct Camera
    {
        float fov;
        float pitch;
        float yaw;
        float camspeed;

        glm::vec3 position;
        glm::vec3 direction;

        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 proj_view;

        Camera() = default;
        Camera(float fov, float aspectRatio, float znear, float zfar);
    };

    // Update view matrix
    void update(Camera& cam);
    // Update projection matrix
    void update(Camera& cam, float fov, float aspect_ratio, float znear, float zfar);
}

#endif // !VOX_CAMERA_H
