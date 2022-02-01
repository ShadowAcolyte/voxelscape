#ifndef VOX_MESH_H
#define VOX_MESH_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texcoord;
    glm::vec3 m_color;

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoord, glm::vec3 color)
        : m_position(position), m_normal(normal), m_texcoord(texcoord), m_color(color) {}
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty, float cx, float cy, float cz)
        : m_position(px, py, pz), m_normal(nx, ny, nz), m_texcoord(tx, ty), m_color(cx, cy, cz) {}
};

struct Mesh
{
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};

#endif // !VOX_MESH_H
