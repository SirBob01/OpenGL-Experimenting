#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <stdexcept>
#include <string>

#include "resource.h"

/**
 * Enumerates the different types of texture mappings
 */
enum class TextureMapping {
    Diffuse = 0,  // Colors each point on the mesh (standard texture)
    Specular = 1, // Defines how shiny each point on the mesh is
    Normal = 2    // Defines physical texture (e.g., bumpiness or smoothness)
};

/**
 * Texture object
 */
class Texture : public Resource {
  public:
    Texture(std::string filename);
    ~Texture();
};

#endif