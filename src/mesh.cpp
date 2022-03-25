#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices) {
    generate_buffers(vertices, indices);
}

Mesh::Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
           std::vector<uint32_t> &indices) {
    std::vector<Vertex> vertices;
    for (int i = 0; i < positions.size(); i++) {
        vertices.push_back({positions[i], normals[i], glm::vec2(0, 0)});
    }
    indices = indices;
    generate_buffers(vertices, indices);
}

Mesh::Mesh(std::vector<glm::vec3> &positions,
           std::vector<glm::vec2> &texture_coordinates,
           std::vector<uint32_t> &indices) {
    std::vector<Vertex> vertices;
    for (int i = 0; i < positions.size(); i++) {
        vertices.push_back(
            {positions[i], glm::vec3(0, 0, 0), texture_coordinates[i]});
    }
    indices = indices;
    generate_buffers(vertices, indices);
}

void Mesh::generate_buffers(std::vector<Vertex> &vertices,
                            std::vector<uint32_t> &indices) {
    vertex_buffer_ = std::make_unique<VertexBuffer>(vertices);
    index_buffer_ = std::make_unique<IndexBuffer>(indices);
}

void Mesh::bind() {
    vertex_buffer_->bind();
    index_buffer_->bind();
}

size_t Mesh::get_index_count() { return index_buffer_->get_index_count(); }
