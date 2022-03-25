#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>

#include <array>
#include <vector>

#include "pipeline.h"

/**
 * Enumerates the different types of texture mappings
 */
const std::array<std::string, 3> texture_mapping_identifiers = {
    "specular", "diffuse", "normal"};
enum TextureMapping { Specular = 0, Diffuse = 1, Normal = 2 };

/**
 * Describes a unique texture
 */
struct TextureDescriptor {
    std::string image_filename;
    TextureMapping mapping;
};

/**
 * Material object to describe the visual look of a model
 */
struct Material {
    std::vector<TextureDescriptor> textures;
    std::string vertex_shader_filename;
    std::string fragment_shader_filename;

    /**
     * Set material-specific uniform values to a shader pipeline
     *
     * Does nothing by default
     */
    virtual void set_uniforms(Pipeline &pipeline){};
};

#endif