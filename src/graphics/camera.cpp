#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "camera.h"
#include <iostream>

const glm::vec3 Camera::up = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera(float m_fov, float aspect_ratio, float znear, float zfar) {
    this->m_yaw = 0;
    this->m_pitch = 0;
    this->m_fov = m_fov;
    this->m_camspeed = 0.01f;

    this->m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->m_direction = glm::vec3(0.0f, 0.0f, 1.0f);

    this->m_projection = glm::perspective(m_fov, aspect_ratio, znear, zfar);
    this->m_view = glm::lookAt(this->m_position, this->m_position + this->m_direction, Camera::up);
    this->m_projView =this->m_projection * this->m_view;
}

void Camera::Update(float m_fov, float aspect_ratio, float znear, float zfar) {
    this->m_projection = glm::perspective(m_fov, aspect_ratio, znear, zfar);
    this->m_projView = this->m_projection * this->m_view;
}

void Camera::Update() {
    this->m_direction.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    this->m_direction.y = sin(glm::radians(this->m_pitch));
    this->m_direction.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    this->m_direction = glm::normalize(this->m_direction);

    this->m_view = glm::lookAt(this->m_position, this->m_position + this->m_direction, Camera::up);
    this->m_projView = this->m_projection * this->m_view;
}
