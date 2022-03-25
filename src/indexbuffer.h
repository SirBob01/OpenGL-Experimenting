#ifndef INDEXBUFFER_H_
#define INDEXBUFFER_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <vector>

/**
 * Stores vertex data into a memory buffer for GPU access
 */
class IndexBuffer {
    uint32_t handle_;
    size_t count_;

  public:
    IndexBuffer(std::vector<uint32_t> &indices);
    ~IndexBuffer();

    /**
     * Bind the index buffer to be used by the current context
     */
    void bind();

    /**
     * Unbind the index buffer from the current context
     */
    void unbind();

    /**
     * Get the number of indices in the buffer
     */
    size_t get_index_count();
};

#endif
