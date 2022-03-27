#ifndef CUBEMAP_H_
#define CUBEMAP_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "vendor/stb_image.h"

/**
 * Cubemap object
 */
class Cubemap {
    uint32_t handle_;

  public:
    Cubemap(std::vector<std::string> &face_image_filenames);
    ~Cubemap();

    /**
     * Use this cubemap for the current draw
     */
    void bind(uint32_t index);

    /**
     * Unbind this cubemap
     */
    void unbind();
};

#endif