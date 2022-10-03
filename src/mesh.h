#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
    glm::vec3 color;

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoord, glm::vec3 color)
        : position(position), normal(normal), texcoord(texcoord), color(color) {}
    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty, float cx, float cy, float cz)
        : position(px, py, pz), normal(nx, ny, nz), texcoord(tx, ty), color(cx, cy, cz) {}
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};
