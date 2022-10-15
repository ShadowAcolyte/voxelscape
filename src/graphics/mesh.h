#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texcoord;
    glm::vec3 m_color;

    Vertex(glm::vec3 m_position, glm::vec3 m_normal, glm::vec2 m_texcoord, glm::vec3 m_color)
        : m_position(m_position), m_normal(m_normal), m_texcoord(m_texcoord), m_color(m_color) {}
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty, float cx, float cy, float cz)
        : m_position(px, py, pz), m_normal(nx, ny, nz), m_texcoord(tx, ty), m_color(cx, cy, cz) {}
};

struct Mesh {
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};
