#ifndef RENDER_MESH_H_
#define RENDER_MESH_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>

#include <fstream>
#include <memory>
#include <vector>

#include "indexbuffer.h"
#include "vertex.h"
#include "vertexbuffer.h"

/**
 * Mesh object
 */
class Mesh {
    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;

    std::unique_ptr<VertexBuffer> vertex_buffer_;
    std::unique_ptr<IndexBuffer> index_buffer_;

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