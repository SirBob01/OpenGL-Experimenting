#ifndef RENDER_PIPELINE_H_
#define RENDER_PIPELINE_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * Graphics pipeline configuration
 *
 * Attach a vertex shader and fragment shader
 */
class Pipeline {
    uint32_t program_;
    std::unordered_map<std::string, uint32_t> cache_;
    std::pair<std::string, std::string> key_;

    /**
     * Read shader source code from a file
     */
    const std::vector<char> read_from_disk(std::string filename);

    /**
     * Bind a shader program to the pipeline program
     */
    uint32_t bind_shader(std::string filename, GLenum type);

    /**
     * Get the location of a uniform, accessing cached results if necessary
     */
    uint32_t get_uniform_location(std::string identifier);

  public:
    Pipeline(std::string vertex_shader_filename,
             std::string fragment_shader_filename);

    /**
     * Use the pipeline
     */
    void use();

    /**
     * Get a unique key for this pipeline to efficiently draw objects
     * per pipeline, minimizing switching between shader programs
     */
    const std::pair<std::string, std::string> &get_key();

    /**
     * Set a uniform 4x4 matrix
     */
    void set_uniform_matrix4(std::string identifier, float matrix[]);

    /**
     * Set a uniform integer value
     */
    void set_uniform_int(std::string identifier, uint32_t number);

    /**
     * Set a uniform float value
     */
    void set_uniform_float(std::string identifier, float number);
};

#endif