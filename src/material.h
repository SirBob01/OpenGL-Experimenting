#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <glm/glm.hpp>

#include <array>
#include <vector>

#include "pipeline.h"

/**
 * Enumerates the different types of texture mappings
 */
enum TextureMapping {
    Diffuse = 0,  // Colors each point on the mesh (standard texture)
    Specular = 1, // Defines how shiny each point on the mesh is
    Normal = 2    // Defines physical texture (e.g., bumpiness or smoothness)
};

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
    std::vector<std::string> cubemap_image_filenames = {};

    /**
     * Set material-specific uniform values to a shader pipeline
     *
     * Does nothing by default
     */
    virtual void set_uniforms(Pipeline &pipeline){};
};

#endif