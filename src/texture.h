#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <string>

#include "vendor/stb_image.h"

/**
 * Texture object
 */
class Texture {
    uint32_t handle_;

  public:
    Texture(std::string filename);
    ~Texture();

    /**
     * Use this texture for the current draw
     *
     * Activate a texture unit at an index and bind to it
     */
    void bind(uint32_t index);

    /**
     * Stop using this texture
     */
    void unbind();
};

#endif