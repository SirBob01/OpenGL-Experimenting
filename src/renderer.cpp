#include "renderer.h"

Renderer::Renderer() {
    buffer_bound_ = false;
    glGenVertexArrays(1, &vao_handle_);
    glBindVertexArray(vao_handle_);
}

Renderer::~Renderer() { glDeleteVertexArrays(1, &vao_handle_); }

void Renderer::bind() {
    // Position (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    // Normal vector (x, y, z)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    // Texture coordinates (u, v)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));

    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void Renderer::draw(Mesh &mesh, Material &material, glm::mat4 &transform) {
    mesh.bind();
    if (!buffer_bound_) {
        buffer_bound_ = true;
        bind();
    }
    material.set_matrix4("transform", transform);
    material.bind();
    glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0);
}