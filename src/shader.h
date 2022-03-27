#ifndef SHADER_H_
#define SHADER_H_

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "resource.h"

/**
 * Enumerates the programmable stages of the rendering pipeline
 */
enum class ShaderStage {
    Vertex,
    Fragment,
};

/**
 * Shader object
 */
class Shader : public Resource {
    ShaderStage stage_;

    /**
     * Read a shader file from disk
     */
    const std::vector<char> read_from_disk(std::string filename);

  public:
    Shader(std::string filename, ShaderStage stage);
    ~Shader();

    /**
     * Bind the shader to a program
     */
    void bind(uint32_t program_handle_) const;

    /**
     * Get the shader's stage in the pipeline
     */
    const ShaderStage &get_stage() const;
};

#endif
