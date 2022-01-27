#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "camera.h"

const glm::vec3 camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

camera::Camera::Camera(float fov, float aspect_ratio, float znear, float zfar)
{
    this->yaw = 0;
    this->pitch = 0;
    this->fov = fov;
    this->camspeed = 0.01f;

    this->position = glm::vec3(0.0f, 0.0f, 3.0f);
    this->direction = glm::vec3(0.0f, 0.0f, 1.0f);

    this->projection = glm::perspective(fov, aspect_ratio, znear, zfar);
    this->view = glm::lookAt(position, position + direction, camera::up);
    this->proj_view = projection * view;
}

void camera::update(camera::Camera& cam, float fov, float aspect_ratio, float znear, float zfar)
{
    cam.projection = glm::perspective(fov, aspect_ratio, znear, zfar);
    cam.proj_view = cam.projection * cam.view;
}

void camera::update(camera::Camera& cam)
{
    cam.direction.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    cam.direction.y = sin(glm::radians(cam.pitch));
    cam.direction.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
    cam.direction = glm::normalize(cam.direction);

    cam.view = glm::lookAt(cam.position, cam.position + cam.direction, camera::up);
    cam.proj_view = cam.projection * cam.view;
}
