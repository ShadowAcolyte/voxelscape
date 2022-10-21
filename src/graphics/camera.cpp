#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "camera.h"
#include <iostream>

const glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera(float fov, float aspect_ratio, float znear, float zfar)
{
    this->yaw = 0;
    this->pitch = 0;
    this->fov = fov;
    this->camspeed = 0.01f;

    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->direction = glm::vec3(0.0f, 0.0f, 1.0f);

    this->projection = glm::perspective(fov, aspect_ratio, znear, zfar);
    this->view = glm::lookAt(this->position, this->position + this->direction, Camera::up);
    this->projView = this->projection * this->view;
}

void Camera::Update(float fov, float aspect_ratio, float znear, float zfar)
{
    this->projection = glm::perspective(fov, aspect_ratio, znear, zfar);
    this->projView = this->projection * this->view;
}

void Camera::Update()
{
    this->direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->direction.y = sin(glm::radians(this->pitch));
    this->direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->direction = glm::normalize(this->direction);

    this->view = glm::lookAt(this->position, this->position + this->direction, Camera::up);
    this->projView = this->projection * this->view;
}
