#ifndef BUFFER_H_
#define BUFFER_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <vector>

#include "resource.h"
#include "vertex.h"

/**
 * Enumerates the different types of buffers
 */
enum class BufferType {
    Vertex,
    Index,
};

/**
 * Enumerates the different usages for a buffer
 */
enum class BufferUsage {
    StaticDraw,
    DynamicDraw,
};

/**
 * Stores raw vertex data into a memory buffer for
 * GPU access
 */
template <typename T> class Buffer : public Resource {
    uint32_t type_;
    uint32_t usage_;

  public:
    Buffer(std::vector<T> &data, BufferType type, BufferUsage usage) {
        // Set OpenGL buffer type constant
        switch (type) {
        case BufferType::Vertex:
            type_ = GL_ARRAY_BUFFER;
            break;
        case BufferType::Index:
            type_ = GL_ELEMENT_ARRAY_BUFFER;
            break;
        default:
            throw std::runtime_error("Invalid buffer type");
            break;
        }

        // Set OpenGL buffer usage constant
        switch (usage) {
        case BufferUsage::StaticDraw:
            usage_ = GL_STATIC_DRAW;
            break;
        case BufferUsage::DynamicDraw:
            usage_ = GL_DYNAMIC_DRAW;
            break;
        default:
            throw std::runtime_error("Invalid buffer usage");
            break;
        }

        glGenBuffers(1, &handle_);
        glBindBuffer(type_, handle_);
        glBufferData(type_, sizeof(T) * data.size(), data.data(), usage_);
        glBindBuffer(type_, 0);
    }
    ~Buffer() { glDeleteBuffers(1, &handle_); }

    /**
     * Bind the buffer to be used by the current context
     */
    void bind() { glBindBuffer(type_, handle_); }

    /**
     * Unbind the buffer from the current context
     */
    void unbind() { glBindBuffer(type_, 0); }
};

#endif
