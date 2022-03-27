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

#include "resource.h"
#include "shader.h"
#include "texture.h"

/**
 * Graphics configuration for setting the visual properties of a mesh
 *
 * Attach a vertex shader and fragment shader
 */
class Material : public Resource {
    std::unordered_map<std::string, uint32_t> location_cache_;

    // Value maps
    std::unordered_map<uint32_t, int> integer_values_;
    std::unordered_map<uint32_t, float> float_values_;
    std::unordered_map<uint32_t, glm::mat4> mat4_values_;
    std::unordered_map<uint32_t, uint32_t> texture_values_;

    /**
     * Get the location of a uniform, accessing cached results if necessary
     */
    uint32_t get_uniform_location(std::string identifier);

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
};

#endif