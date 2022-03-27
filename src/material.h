#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <string>
#include <unordered_map>

#include "cubemap.h"
#include "resource.h"
#include "shader.h"
#include "texture.h"

/**
 * Graphics configuration for setting the visual properties of a mesh
 *
 * Attach a vertex shader and fragment shader
 */
class Material : public Resource {
    std::unordered_map<std::string, int> location_cache_;

    // Value maps
    std::unordered_map<int, int> integer_values_;
    std::unordered_map<int, float> float_values_;
    std::unordered_map<int, glm::mat4> mat4_values_;
    std::unordered_map<int, uint32_t> texture_values_;
    std::unordered_map<int, uint32_t> cubemap_values_;

    /**
     * Get the location of a uniform, accessing cached results if necessary
     */
    int get_uniform_location(std::string identifier);

  public:
    Material(Shader &vertex_shader, Shader &fragment_shader);
    ~Material();

    /**
     * Use the material
     */
    void bind();

    /**
     * Set an integer uniform
     */
    void set_integer(std::string identifier, int value);

    /**
     * Set a float uniform
     */
    void set_float(std::string identifier, float value);

    /**
     * Set a 4x4 matrix uniform
     */
    void set_matrix4(std::string identifier, glm::mat4 &value);

    /**
     * Set a texture
     */
    void set_texture(Texture &texture, TextureMapping mapping);

    /**
     * Set a cubemap
     */
    void set_cubemap(std::string identifier, Cubemap &cubemap);
};

#endif