#ifndef RENDERSTATE_H_
#define RENDERSTATE_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

/**
 * Defines the current render context, holding information like
 * the vertex attribute layout
 */
class RenderState {
    uint32_t handle_;

  public:
    RenderState();
    ~RenderState();

    /**
     * Bind the context
     */
    void bind();

    /**
     * Unbind the context
     */
    void unbind();
};

#endif