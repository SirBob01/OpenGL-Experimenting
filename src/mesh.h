#ifndef RENDER_MESH_H_
#define RENDER_MESH_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>

#include <fstream>
#include <vector>

/**
 * A vertex stores its model space coodinates and
 * texture coordinates
 *
 * Data layout is essentially how it's read by the GPU in the shader
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coordinates;
};

/**
 * Mesh object
 */
class Mesh {
    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;

    uint32_t vertex_buffer_;
    uint32_t index_buffer_;

    /**
     * Generate the vertex and index buffers
     */
    void generate_buffers();

  public:
    Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);
    Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
         std::vector<uint32_t> &indices);
    Mesh(std::vector<glm::vec3> &positions,
         std::vector<glm::vec2> &texture_coordinates,
         std::vector<uint32_t> &indices);
    ~Mesh();

    /**
     * Bind the vertex and index buffers to the current context
     */
    void use();

    /**
     * Draw this mesh and add it to the currently active pipeline
     */
    void draw();
};

#endif