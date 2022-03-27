#ifndef RENDERER_H_
#define RENDERER_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <unordered_map>
#include <vector>

#include "cubemap.h"
#include "material.h"
#include "mesh.h"
#include "resource.h"
#include "texture.h"

/**
 * Defines the core renderer API
 */
class Renderer {
    uint32_t vao_handle_;

    bool buffer_bound_;

    /**
     * Bind the context
     */
    void bind();

  public:
    Renderer();
    ~Renderer();

    /**
     * Draw a mesh with a material and a transform
     */
    void draw(Mesh &mesh, Material &material, glm::mat4 &transform);
};

#endif