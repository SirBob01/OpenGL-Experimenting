#include "renderer.h"

Renderer::Renderer() {
    glGenVertexArrays(1, &vao_handle_);
    glBindVertexArray(vao_handle_);

    // Set default state
    glEnable(GL_DEPTH_TEST);
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
    // Bind the mesh before enabling vertex attribute array
    mesh.bind();
    bind();

    // Bind the material
    material.set_matrix4("transform", transform);
    material.bind();

    // Set states based on material flags
    if (material.get_backface_cull()) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }
    glDepthMask(material.get_depth_write());

    // Draw call
    glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0);
}