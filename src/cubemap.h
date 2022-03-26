#ifndef CUBEMAP_H_
#define CUBEMAP_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <array>
#include <stdexcept>
#include <string>

#include "vendor/stb_image.h"

/**
 * Cubemap object
 */
class CubeMap {
    uint32_t handle_;

  public:
    CubeMap(std::array<std::string, 6> face_image_filenames);
    ~CubeMap();

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