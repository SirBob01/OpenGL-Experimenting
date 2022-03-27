#ifndef MESH_H_
#define MESH_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>

#include <fstream>
#include <memory>
#include <vector>

#include "buffer.h"
#include "vertex.h"

/**
 * Mesh object
 */
class Mesh {
    std::unique_ptr<Buffer<Vertex>> vertex_buffer_;
    std::unique_ptr<Buffer<uint32_t>> index_buffer_;

    uint32_t index_count_;

    /**
     * Generate the vertex and index buffers
     */
    void generate_buffers(std::vector<Vertex> &vertices,
                          std::vector<uint32_t> &indices);

  public:
    Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices);
    Mesh(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
         std::vector<uint32_t> &indices);
    Mesh(std::vector<glm::vec3> &positions,
         std::vector<glm::vec2> &texture_coordinates,
         std::vector<uint32_t> &indices);

    /**
     * Bind the vertex and index buffers to the current context
     */
    void bind();

    /**
     * Get the number of indices in the buffer
     */
    size_t get_index_count();
};

#endif