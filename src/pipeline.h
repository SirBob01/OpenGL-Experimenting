#ifndef RENDER_PIPELINE_H_
#define RENDER_PIPELINE_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
#include <vector>
#include <fstream>

/**
 * Graphics pipeline configuration
 */
class Pipeline {
    uint32_t program_;
    
    /**
     * Read shader source code from a file
     */
    const std::vector<char> read_from_disk(std::string filename);

    /**
     * Bind a shader program to the pipeline program
     */
    uint32_t bind_shader(std::string filename, GLenum type);

public:
    Pipeline(std::string vertex_shader_filename, 
             std::string fragment_shader_filename);

    /**
     * Use the pipeline
     */
    void use();

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