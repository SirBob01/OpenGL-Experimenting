#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <stdexcept>

#include "util/stb_image.h"

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
     */
    void use();
};

#endif