#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 color;

    Vertex() = default;
    Vertex(glm::vec3 m_position, glm::vec3 m_normal, glm::vec2 m_texcoord, glm::vec3 m_color)
        : position(m_position), normal(m_normal), texcoord(m_texcoord), color(m_color)
    {
    }
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty, float cx, float cy, float cz)
        : position(px, py, pz), normal(nx, ny, nz), texcoord(tx, ty), color(cx, cy, cz)
    {
    }
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
