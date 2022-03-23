#ifndef RENDER_MESH_H_
#define RENDER_MESH_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>

#include <vector>
#include <fstream>


/**
 * A vertex stores its model space coodinates and 
 * texture coordinates
 */
struct Vertex {
    glm::vec3 position;
    glm::vec2 texture_coordinates;
};

/**
 * Mesh object
 */
class Mesh {
    uint32_t vertex_buffer_;
    uint32_t index_buffer_;

    uint32_t num_indices_;

public:
    Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);
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