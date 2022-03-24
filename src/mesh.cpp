#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices) {
    vertices_ = vertices;
    indices_ = indices;
    generate_buffers();
}

Mesh::Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
           std::vector<uint32_t> &indices) {
    for (int i = 0; i < positions.size(); i++) {
        vertices_.push_back({positions[i], normals[i], glm::vec2(0, 0)});
    }
    indices_ = indices;
    generate_buffers();
}

Mesh::Mesh(std::vector<glm::vec3> &positions,
           std::vector<glm::vec2> &texture_coordinates,
           std::vector<uint32_t> &indices) {
    for (int i = 0; i < positions.size(); i++) {
        vertices_.push_back(
            {positions[i], glm::vec3(0, 0, 0), texture_coordinates[i]});
    }
    indices_ = indices;
    generate_buffers();
}

void Mesh::generate_buffers() {
    vertex_buffer_ = std::make_unique<VertexBuffer>(vertices_);
    index_buffer_ = std::make_unique<IndexBuffer>(indices_);
}

void Mesh::use() {
    vertex_buffer_->bind();
    index_buffer_->bind();
}

void Mesh::draw() {
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}
