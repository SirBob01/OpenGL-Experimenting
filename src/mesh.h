#ifndef RENDER_MESH_H_
#define RENDER_MESH_H_

#include <SDL2/SDL.h>

#include <vector>
#include <fstream>

#include "loader/glad.h"
#include <SDL2/SDL_opengl.h>

/**
 * A vertex stores its model space coodinates and 
 * texture coordinates
 */
struct Vertex {
    // Model space coordinates
    float x, y, z;

    // Texture coordinates
    float u, v;
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