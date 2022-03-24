#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <vector>

#include "vertex.h"

/**
 * Stores raw vertex data into a memory buffer for
 * GPU access
 */
class VertexBuffer {
    uint32_t handle_;

  public:
    VertexBuffer(std::vector<Vertex> &vertices);
    ~VertexBuffer();

    /**
     * Bind the vertex buffer to be used by the current context
     */
    void bind();

    /**
     * Unbind the vertex buffer from the current context
     */
    void unbind();
};

#endif
