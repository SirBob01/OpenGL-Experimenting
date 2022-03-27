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
#include "pipeline.h"
#include "texture.h"

/**
 * Defines the core renderer API
 */
class Renderer {
    uint32_t vao_handle_;
    std::unordered_map<std::string, std::unique_ptr<Pipeline>> pipelines_;
    std::unordered_map<std::string, std::unique_ptr<Texture>> textures_;
    std::unordered_map<std::string, std::unique_ptr<Cubemap>> cubemaps_;

    bool buffer_bound_;

    /**
     * Get a cached pipeline
     */
    Pipeline &get_pipeline(std::string vertex_shader_filename,
                           std::string fragment_shader_filename);

    /**
     * Get a cached texture
     */
    Texture &get_texture(std::string image_filename);

    /**
     * Get a cached cubemap
     */
    Cubemap &get_cubemap(std::vector<std::string> &cubemap_image_filenames);

    /**
     * Bind the context
     */
    void bind();

    /**
     * Use a provided material
     */
    void use_material(Material &material, glm::mat4 &transform);

  public:
    Renderer();
    ~Renderer();

    /**
     * Draw a mesh with a material and a transform
     */
    void draw(Mesh &mesh, Material &material, glm::mat4 &transform);
};

#endif