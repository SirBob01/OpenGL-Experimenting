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

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &index_buffer_);
}

void Mesh::generate_buffers() {
    // Bind the vertex array
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(),
                 vertices_.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind the index array
    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices_.size(),
                 indices_.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::use() {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);

    // Map the data partitions of each vertex to attribute pointers
    // Model space coodinates (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // Normal vector (x, y, z)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coordinates (u, v)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Mesh::draw() {
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}
